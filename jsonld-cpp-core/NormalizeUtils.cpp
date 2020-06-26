#include "NormalizeUtils.h"
#include "RDFDatasetUtils.h"
#include "sha1.h"
#include "Permutator.h"
#include <utility>

using nlohmann::json;


NormalizeUtils::NormalizeUtils(
        std::vector<RDF::Quad> iquads,
        std::map<std::string, std::map<std::string, std::vector<RDF::Quad>>> ibnodes,
        UniqueNamer iuniqueNamer,
        JsonLdOptions iopts)
        : quads(std::move(iquads)),
          bnodes(std::move(ibnodes)),
          uniqueNamer(std::move(iuniqueNamer)),
          opts(std::move(iopts))
{}


// for all unnamed blank node ids, generate unique names for them
std::string NormalizeUtils::hashBlankNodes(const std::vector<std::string> & unnamed_) {
    std::vector<std::string> unnamed = unnamed_;
    std::vector<std::string> nextUnnamed;
    std::map<std::string, std::vector<std::string>> duplicates;
    std::map<std::string, std::string> unique;

    // rather than initialize hui to 0, which would make sense, we are going to initialize to 1
    // and refer to hui as (hui-1) in most instances. This allows us to declare hui a size_t rather
    // than an int, which would necessitate a static_cast it every time we need to compare it with
    // something else.
        for (size_t hui = 1;; hui++) {
            if ((hui-1) == unnamed.size()) {
                // we are done iterating over unnamed, now name blank nodes
                bool named = false;
                std::vector<std::string> hashes;
                hashes.reserve(unique.size()); // todo: need to make a keySet() function...
                for(auto const & i : unique) {
                    hashes.push_back(i.first);
                }

                std::sort(hashes.begin(), hashes.end());

                for (const auto & hash : hashes) {
                    std::string bnode = unique.at(hash);
                    uniqueNamer.get(bnode);
                    named = true;
                }

                // continue to hash bnodes if a bnode was assigned a name
                if (named) {
                    // this resets the initial variables, so it seems like it
                    // has to go on the stack
                    // but since this is the end of the function either way, it
                    // might not have to
                    // hashBlankNodes(unnamed);
                    hui = 0;
                    unnamed = nextUnnamed;
                    nextUnnamed.clear();
                    duplicates.clear();
                    unique.clear();
                    continue;
                }
                    // name the duplicate hash bnodes
                else {
                    // names duplicate hash bnodes
                    // enumerate duplicate hash groups in sorted order
                    hashes.clear();
                    hashes.reserve(duplicates.size());
                    for(auto const & i : duplicates) {
                        hashes.push_back(i.first);
                    }

                    std::sort(hashes.begin(), hashes.end());

                    // process each group (iterate over 'hashes', use hash to get group from 'duplicates')
                    for (size_t pgi = 0;; pgi++) {
                        if (pgi == hashes.size()) {
                            // done, create JSON-LD array
                            std::vector<std::string> normalized;

                            // Note: At this point all bnodes in the set of RDF
                            // quads have been
                            // assigned canonical names, which have been stored
                            // in the 'uniqueNamer' object.
                            // Here each quad is updated by assigning each of
                            // its bnodes its new name
                            // via the 'uniqueNamer' object.

                            // update bnode names in each quad and serialize
                            for (const auto& quad : quads) {
                                // todo: replace this with an iteration over function pointers
                                auto n = quad.getSubject();
                                if(n != nullptr) {
                                    if(n->isBlankNode()) {
                                        std::string id = n->getValue();
                                        if(id.find("_:c14n") != 0){
                                            n->setValue(uniqueNamer.get(id));
                                        }
                                    }
                                }
                                n = quad.getObject();
                                if(n != nullptr) {
                                    if(n->isBlankNode()) {
                                        std::string id = n->getValue();
                                        if(id.find("_:c14n") != 0){
                                            n->setValue(uniqueNamer.get(id));
                                        }
                                    }
                                }
                                n = quad.getGraph();
                                if(n != nullptr) {
                                    if(n->isBlankNode()) {
                                        std::string id = n->getValue();
                                        if(id.find("_:c14n") != 0){
                                            n->setValue(uniqueNamer.get(id));
                                        }
                                    }
                                }

                                n = quad.getGraph();
                                if(n != nullptr) {
                                    std::string name;
                                    name = n->getValue();
                                    normalized.push_back(RDFDatasetUtils::toNQuad(quad, &name));
                                }
                                else {
                                    normalized.push_back(RDFDatasetUtils::toNQuad(quad, nullptr));
                                }
                            }

                            // sort normalized output
                            std::sort(normalized.begin(), normalized.end());

                            // handle output format
//                            if (opts.format != null) {
//                                if (JsonLdConsts.APPLICATION_NQUADS.equals(options.format)) {
                                    std::stringstream rval;
                                    for (const auto & n : normalized) {
                                        rval << n;
                                    }
                                    return rval.str();
//                                } else {
//                                    throw new JsonLdError(JsonLdError.Error.UNKNOWN_FORMAT,
//                                                          options.format);
//                                }
//                            }
//                            final StringBuilder rval = new StringBuilder();
//                            for (final String n : normalized) {
//                                rval.append(n);
//                            }
//                            return parseNQuads(rval.toString());
                        }

                        // name each group member
                        std::vector<std::string> group = duplicates.at(hashes.at(pgi));
                        std::vector<HashResult> results;
                        for (size_t n = 0;; n++) {
                            if (n == group.size()) {
                                // name bnodes in hash order

                                std::sort(results.begin(), results.end(),
                                        [](const HashResult & result1, const HashResult & result2) {
                                    return result1.hash < result2.hash;
                                });
                                for (auto r : results) {
                                    // name all bnodes in path namer in key-entry order
                                    for (const auto& key : r.pathNamer.getKeys()) {
                                        auto s = uniqueNamer.get(key);
                                    }
                                }
                                break;
                            } else {
                                // skip already-named bnodes
                                std::string bnode = group.at(n);
                                if (uniqueNamer.exists(bnode)) {
                                    continue;
                                }

                                // hash bnode paths
                                UniqueNamer pathNamer;
                                pathNamer.get(bnode);
                                HashResult result = hashPaths(bnode, pathNamer);
                                results.push_back(result);
                            }
                        }
                    }
                }
            }

            // hash unnamed bnode
            std::string bnode = unnamed.at(hui-1);
            std::string hash = hashQuads(bnode);

            // store hash as unique or a duplicate
            if (duplicates.count(hash)) {
                duplicates.at(hash).push_back(bnode);
                nextUnnamed.push_back(bnode);
            } else if (unique.count(hash)) {
                std::vector<std::string> tmp;
                tmp.push_back(unique.at(hash));
                tmp.push_back(bnode);
                duplicates[hash] = tmp;
                nextUnnamed.push_back(unique.at(hash));
                nextUnnamed.push_back(bnode);
                unique.erase(hash);
            } else {
                unique[hash] = bnode;
            }
        }
}

NormalizeUtils::HashResult NormalizeUtils::hashPaths(const std::string& id, UniqueNamer pathUniqueNamer) {

    std::map<std::string, std::vector<std::string>> groups;
    std::vector<RDF::Quad> bnode_quads = bnodes.at(id).at("quads");
    SHA1 md;

    for (size_t hpi = 0;; hpi++) {
        if (hpi == bnode_quads.size()) {
            // done , hash groups
            std::vector<std::string> groupHashes;
            groupHashes.reserve(groups.size()); // todo: need to make a keySet() function...
            for (auto const &i : groups) {
                groupHashes.push_back(i.first);
            }

            std::sort(groupHashes.begin(), groupHashes.end());

            for (size_t hgi = 0;; hgi++) {
                if (hgi == groupHashes.size()) {
                    HashResult res;
                    res.hash = md.digest();
                    res.pathNamer = pathUniqueNamer;
                    return res;
                }
                // digest group hash
                std::string groupHash = groupHashes.at(hgi);
                md.update(groupHash);

                // choose a path and namer from the permutations
                std::shared_ptr<std::string> chosenPath = nullptr;
                UniqueNamer chosenNamer;
                Permutator permutator(groups.at(groupHash));

                while (true) {
                    bool contPermutation = false;
                    bool breakOut = false;
                    std::vector<std::string> permutation = permutator.next();
                    UniqueNamer pathUniqueNamerCopy = pathUniqueNamer;

                    // build adjacent path
                    std::string path;
                    std::vector<std::string> recurse;
                    for (const auto& bnode : permutation) {
                        // use canonical name if available
                        if (uniqueNamer.exists(bnode)) {
                            path += uniqueNamer.get(bnode);
                        } else {
                            // recurse if bnode isn't named in the path yet
                            if (!pathUniqueNamerCopy.exists(bnode)) {
                                recurse.push_back(bnode);
                            }
                            path += pathUniqueNamerCopy.get(bnode);
                        }

                        // skip permutation if path is already >= chosen path
                        if (chosenPath != nullptr && path.length() >= chosenPath->length() && path > *chosenPath) {
                            if(permutator.hasNext()) {
                                contPermutation = true;
                            } else {
                                // digest chosen path and update namer
                                md.update(*chosenPath);
                                pathUniqueNamer = chosenNamer;
                                // hash the nextGroup
                                breakOut = true;
                            }
                            break;
                        }
                    }

                    // if we should do the next permutation
                    if (contPermutation) {
                        continue;
                    }
                    // if we should stop processing this group
                    if (breakOut) {
                        break;
                    }

                    // does the next recursion
                    for (size_t nrn = 0;; nrn++) {
                        if (nrn == recurse.size()) {
                            if (chosenPath == nullptr || path < *chosenPath) {
                                chosenPath = std::make_shared<std::string>(path);
                                chosenNamer = pathUniqueNamerCopy;
                            }
                            if (!permutator.hasNext()) {
                                // digest chosen path and update namer
                                md.update(*chosenPath);
                                pathUniqueNamer = chosenNamer;
                                // hash the nextGroup
                                breakOut = true;
                            }
                            break;
                        }

                        // do recursion
                        std::string bnode = recurse.at(nrn);
                        HashResult result = hashPaths(bnode, pathUniqueNamerCopy);
                        path += pathUniqueNamerCopy.get(bnode) + "<" + result.hash + ">";
                        pathUniqueNamerCopy = result.pathNamer;

                        // skip permutation if path is already >= chosen path
                        if (chosenPath != nullptr && path.length() >= chosenPath->length() && path > *chosenPath) {
                            if (!permutator.hasNext()) {
                                // digest chosen path and update namer
                                md.update(*chosenPath);
                                pathUniqueNamer = chosenNamer;
                                // hash the nextGroup
                                breakOut = true;
                            }
                            break;
                        }
                        // do next recursion
                    }

                    // if we should stop processing this group
                    if (breakOut) {
                        break;
                    }
                }
            }
        }
        // get adjacent bnode
        RDF::Quad quad = bnode_quads.at(hpi);
        std::shared_ptr<std::string> bnode = getAdjacentBlankNodeName(quad.getSubject(), id);
        std::string direction;
        if (bnode != nullptr) {
            // normal property
            direction = "p";
        } else {
            bnode = getAdjacentBlankNodeName(quad.getObject(), id);
            if (bnode != nullptr) {
                // reverse property
                direction = "r";
            }
        }

        if (bnode != nullptr) {
            // get bnode name (try canonical, path, then hash)
            std::string name;
            if (uniqueNamer.exists(*bnode)) {
                name = uniqueNamer.get(*bnode);
            } else if (pathUniqueNamer.exists(*bnode)) {
                name = pathUniqueNamer.get(*bnode);
            } else {
                name = hashQuads(*bnode);
            }

            // hash direction, property, end bnode name/hash
            SHA1 md1;
            md1.update(direction);
            md1.update(quad.getPredicate()->getValue());
            md1.update(name);
            std::string groupHash = md1.digest();
            if (groups.count(groupHash)) {
                groups[groupHash].push_back(*bnode);
            } else {
                std::vector<std::string> tmp;
                tmp.push_back(*bnode);
                groups[groupHash] = tmp;
            }
        }
    }
}

std::string NormalizeUtils::hashQuads(std::string id) {
    // return cached hash
    if(cachedHashes.count(id))
        return cachedHashes[id];

    // serialize all of bnode's quads
    std::vector<RDF::Quad> bnode_quads = bnodes.at(id).at("quads");
    std::vector<std::string> nquads;
    for (const auto & quad : bnode_quads) {
        std::string graphName;
        auto name = quad.getGraph();
        if(name != nullptr)
            graphName = name->getValue();
        nquads.push_back(
                RDFDatasetUtils::toNQuad(quad,name == nullptr ? nullptr : &graphName, &id));
    }
    // sort serialized quads
    std::sort(nquads.begin(), nquads.end());
    // return hashed quads
    std::string hash = sha1(nquads);
    cachedHashes[id] = hash;
    return hash;
}


/**
 * A helper function that gets the blank node name from an RDF quad node
 * (subject or object). If the node is a blank node and its value does not
 * match the given blank node ID, it will be returned.
 *
 * @param node
 *            the RDF quad node.
 * @param id
 *            the ID of the blank node to look next to.
 *
 * @return the adjacent blank node name or null if none was found.
 */
std::shared_ptr<std::string> NormalizeUtils::getAdjacentBlankNodeName(std::shared_ptr<RDF::Node> node, std::string id) {

    if (node->isBlankNode()) {
        std::string v = node->getValue();
        if (v != id)
            return std::make_shared<std::string>(v);
        else
            return nullptr;
    }
    else
        return nullptr;
}


