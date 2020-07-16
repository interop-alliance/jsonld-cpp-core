#ifndef LIBJSONLD_CPP_NORMALIZEUTILS_H
#define LIBJSONLD_CPP_NORMALIZEUTILS_H

#include "jsoninc.h"
#include "JsonLdOptions.h"
#include "UniqueNamer.h"
#include "RDFDataset.h"

class NormalizeUtils {
private:
    std::vector<RDF::Quad> m_quads;
    std::map<std::string, std::map<std::string, std::vector<RDF::Quad>>> m_bnodes;
    std::map<std::string, std::string> m_cachedHashes;
    UniqueNamer m_uniqueNamer;
    std::shared_ptr<JsonLdOptions> m_options;

    struct HashResult {
        std::string hash;
        UniqueNamer pathNamer;
    };

    HashResult hashPaths(const std::string& id, UniqueNamer pathUniqueNamer);

    std::string hashQuads(std::string id);

public:

    NormalizeUtils(
            std::vector<RDF::Quad> quads,
            std::map<std::string, std::map<std::string, std::vector<RDF::Quad>>> bnodes,
            UniqueNamer  iuniqueNamer,
            const std::shared_ptr<JsonLdOptions>& options);

    std::string hashBlankNodes(const std::vector<std::string> &unnamed_);

    static std::shared_ptr<std::string> getAdjacentBlankNodeName(std::shared_ptr<RDF::Node> node, std::string id);

};

#endif //LIBJSONLD_CPP_NORMALIZEUTILS_H
