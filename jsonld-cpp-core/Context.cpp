#include "Context.h"
#include "JsonLdUrl.h"
#include "ObjUtils.h"
#include <iostream>
#include <utility>

using nlohmann::json;

void Context::checkEmptyKey(const json& map) {
    if(map.count("")) {
        // the term MUST NOT be an empty string ("")
        // https://www.w3.org/TR/json-ld/#h3_terms
        throw JsonLdError(JsonLdError::InvalidTermDefinition, "empty key for value");
    }
}

void Context::checkEmptyKey(const std::map<std::string, std::string>& map) {
    if(map.count("")) {
        // the term MUST NOT be an empty string ("")
        // https://www.w3.org/TR/json-ld/#h3_terms
        throw JsonLdError(JsonLdError::InvalidTermDefinition, "empty key for value");
    }
}

void Context::init() {
    m_contextMap.insert(std::make_pair(JsonLdConsts::BASE, m_options->getBase()));
    m_termDefinitions = ObjUtils::newMap();
}

/**
 * Context Processing Algorithm
 *
 * http://json-ld.org/spec/latest/json-ld-api/#context-processing-algorithms
 *
 * @param localContext
 *            The Local Context object.
 * @return The parsed and merged Context.
 * @throws JsonLdError
 *             If there is an error parsing the contexts.
 */
Context Context::parse(const std::string& baseUrl, const json& localContext)  {
    return applyContextProcessingAlgorithm(baseUrl, localContext);
//    return parseDeprecated(localContext, std::vector<std::string>(), false);
}

/**
 * Context Processing Algorithm
 *
 * http://json-ld.org/spec/latest/json-ld-api/#context-processing-algorithms
 *
 * @param localContext
 *            The Local Context object.
 * @param remoteContexts
 *            The list of Strings denoting the remote Context URLs.
 * @return The parsed and merged Context.
 * @throws JsonLdError
 *             If there is an error parsing the contexts.
 */
Context Context::parse(const std::string& baseUrl, const json& localContext, const std::vector<std::string>& remoteContexts) {
    return applyContextProcessingAlgorithm(baseUrl, localContext, remoteContexts);
//    return parseDeprecated(localContext, remoteContexts, false);
}

/**
 * Helper method used to work around logic errors related to the recursive
 * nature of the JSONLD-API Context Processing Algorithm.
 *
 * @param localContext
 *            The Local Context object.
 * @param remoteContexts
 *            The list of Strings denoting the remote Context URLs.
 * @param parsingARemoteContext
 *            True if localContext represents a remote context that has been
 *            parsed and sent into this method and false otherwise. This
 *            must be set to know whether to propagate the @code{@base} key
 *            from the context to the result.
 * @return The parsed and merged Context.
 * @throws JsonLdError
 *             If there is an error parsing the contexts.
 */
 Context Context::parseDeprecated(const json& localContext, const std::vector<std::string>& remoteContexts, bool parsingARemoteContext) {

//    if (remoteContexts == null) {
//        remoteContexts = new ArrayList<String>();
//    }
    // 1) Initialize result to the result of cloning active context.
    Context result = *this;

    // 2) If local context is not an array, set it to an array containing only local context.
    // set up an array for the loop in 3)
    json myContext = json::array();
    if (!localContext.is_array()) {
        myContext.push_back(localContext);
    }
    else {
        myContext.insert(myContext.end(), localContext.begin(), localContext.end());
    }

    // 3) For each item context in local context:
    for (auto context : myContext) {
        // 3.1) If context is null, set result to a newly-initialized active context and continue with the next context.
        // In JSON-LD 1.0, the base IRI was given a default value here; this is now described conditionally in § 9. The Application Programming Interface.
        if (context.is_null()) {
            Context c(m_options);
            result = c;
            continue;
        }
//        else if (context instanceof Context) { // todo: will this happen in c++ version?
//            result = ((Context) context).clone();
//        }

        // 3.2) If context is a string,
        else if (context.is_string()) {
            // 3.2.1) Set context to the result of resolving value against the base IRI which is established as specified in section 5.1 Establishing a Base URI of [RFC3986].
            // Only the basic algorithm in section 5.2 of [RFC3986] is used; neither Syntax-Based Normalization nor Scheme-Based Normalization are performed.
            // Characters additionally allowed in IRI references are treated in the same way that unreserved characters are treated in URI references, per section 6.5 of [RFC3987].

            throw JsonLdError(JsonLdError::NotImplemented, "context.is_string() not implemented: ");
//            std::string uri = result->get(JsonLdConsts::BASE);
//            uri = JsonLdUrl.resolve(uri, (String) context);

//            // 3.2.2) If context is in the remote contexts array, a recursive context inclusion error has been detected
//            and processing is aborted; otherwise, add context to remote contexts.
//            if (remoteContexts.contains(uri)) {
//                throw new JsonLdError(Error.RECURSIVE_CONTEXT_INCLUSION, uri);
//            }
//            remoteContexts.add(uri);
//
//            // 3.2.3) If context was previously dereferenced, then the processor MUST NOT do a further dereference, and context is set to the previously established internal representation.
//            final RemoteDocument rd = this.options.getDocumentLoader().loadDocument(uri);
//            final Object remoteContext = rd.getDocument();
//            if (!(remoteContext instanceof Map) || !((Map<String, Object>) remoteContext)
//                    .containsKey(JsonLdConsts.CONTEXT)) {
//                // If the dereferenced document has no top-level JSON object
//                // with an @context member
//                throw new JsonLdError(Error.INVALID_REMOTE_CONTEXT, context);
//            }
//            final Object tempContext = ((Map<String, Object>) remoteContext)
//                    .get(JsonLdConsts.CONTEXT);
//
//            // 3.2.4) Otherwise, dereference context, transforming into the internal representation.
//            If context cannot be dereferenced, or cannot be transformed into the internal representation,
//            a loading remote context failed error has been detected and processing is aborted.
//            If the dereferenced document has no top-level dictionary with an @context member, an invalid remote context has been detected and processing is aborted;
//            otherwise, set context to the value of that member.
//            result = result.parse(tempContext, remoteContexts, true);

//            // 3.2.5) Set result to the result of recursively calling this algorithm,
//            passing result for active context, context for local context, and a copy of remote contexts.

            // 3.2.6) Continue with the next context.
//            continue;
        } else if (!(context.is_object())) {
            // 3.3) If context is not a dictionary, an invalid local context error has been detected and processing is aborted.
            throw JsonLdError(JsonLdError::InvalidLocalContext, context);
        }
        checkEmptyKey(context);
        // 3.4) If context has an @base key and remote contexts is empty, i.e., the currently being processed context is not a remote context:
        if (!parsingARemoteContext && context.contains(JsonLdConsts::BASE)) {
            // 3.4.1) Initialize value to the value associated with the @base key.
            auto value = context.at(JsonLdConsts::BASE);

            // 3.4.2) If value is null, remove the base IRI of result.
            if (value.is_null()) {
                result.erase(JsonLdConsts::BASE);
            } else if (value.is_string()) {
                // 3.4.3) Otherwise, if value is an absolute IRI, the base IRI of result is set to value.
                if (JsonLdUtils::isAbsoluteIri(value)) {
                    result.insert(std::make_pair(JsonLdConsts::BASE, value.get<std::string>()));
                } else {
                    // 3.4.4) Otherwise, if value is a relative IRI and the base IRI of result is not null,
                    // set the base IRI of result to the result of resolving value against the current base IRI of result.
                    std::string baseUri = result.at(JsonLdConsts::BASE);
                    if (!JsonLdUtils::isAbsoluteIri(baseUri)) {
                        throw JsonLdError(JsonLdError::InvalidBaseIri, baseUri);
                    }
                    std::string tmpIri = value.get<std::string>();
                    result.insert(std::make_pair(JsonLdConsts::BASE, JsonLdUrl::resolve(&baseUri, &tmpIri)));
                }
            } else {
                // 3.4.5) Otherwise, an invalid base IRI error has been detected and processing is aborted.
                throw JsonLdError(JsonLdError::InvalidBaseIri, "@base must be a string");
            }
        }

        // 3.5) If context has an @version key:
        // 3.5.1) If the associated value is not 1.1, an invalid @version value has been detected, and processing is aborted.
        // 3.5.2) If processing mode is set to json-ld-1.0, a processing mode conflict error has been detected and processing is aborted.
        // 3.5.3) Set processing mode, to json-ld-1.1, if not already set.
        // TODO: 3.5 is completely missed

        // 3.6) If context has an @vocab key:
        // 3.6.1) Initialize value to the value associated with the @vocab key.
        // 3.6.2) If value is null, remove any vocabulary mapping from result.
        // 3.6.3) Otherwise, if value the empty string (""), the effective value is the current base IRI.
        // 3.6.4) Otherwise, if value is an absolute IRI or blank node identifier, the vocabulary mapping of result is set to value.
        // If it is not an absolute IRI, or a blank node identifier, an invalid vocab mapping error has been detected and processing is aborted.
        if (context.contains(JsonLdConsts::VOCAB)) {
            auto value = context.at(JsonLdConsts::VOCAB);
            if (value.is_null()) {
                result.erase(JsonLdConsts::VOCAB);
            } else if (value.is_string()) {
                if (JsonLdUtils::isAbsoluteIri(value)) {
                    result.insert(std::make_pair(JsonLdConsts::VOCAB, value.get<std::string>()));
                } else {
                    throw JsonLdError(JsonLdError::InvalidVocabMapping,
                                      "@value must be an absolute IRI");
                }
            } else {
                throw JsonLdError(JsonLdError::InvalidVocabMapping,
                                  "@vocab must be a string or null");
            }
        }

        // 3.7) If context has an @language key:
        // 3.7.1) Initialize value to the value associated with the @language key.
        // 3.7.2) If value is null, remove any default language from result.
        // 3.7.3) Otherwise, if value is string, the default language of result is set to lowercased value.
        // If it is not a string, an invalid default language error has been detected and processing is aborted.
        if (context.contains(JsonLdConsts::LANGUAGE)) {
            auto value = context.at(JsonLdConsts::LANGUAGE);
            if (value.is_null()) {
                result.erase(JsonLdConsts::LANGUAGE);
            } else if (value.is_string()) {
                result.insert(std::make_pair(JsonLdConsts::LANGUAGE, value.get<std::string>())); // todo: value to lowercase
            } else {
                throw JsonLdError(JsonLdError::InvalidDefaultLanguage, value);
            }
        }

        // 3.8) Create a dictionary defined to use to keep track of whether or not a term has already been defined or currently being defined during recursion.
        std::map<std::string, bool> defined; //todo: thrown out?
        for (const auto& el : context.items()) {
            // 3.9) For each key-value pair in context where key is not @base, @vocab, or @language,
            // invoke the Create Term Definition algorithm, passing result for active context, context for local context, key, and defined.
            const auto& key = el.key();
            if (key == JsonLdConsts::BASE || key == JsonLdConsts::VOCAB || key == JsonLdConsts::LANGUAGE) {
                continue;
            }
            result.createTermDefinition(context, key, defined);
        }
    }

    // 4) Return result.
    return result;
}

Context Context::applyContextProcessingAlgorithm(const std::string& baseUrl, const json& localContext, const std::vector<std::string>& remoteContexts) {
    // 1) Initialize result to the result of cloning active context, with inverse context set to null..
    Context result = *this;
    result.m_inverse = {};

    // 2) If local context is an object containing the member @propagate,
    // its value MUST be boolean true or false, set propagate to that value.

    // 3) If propagate is false, and result does not have a previous context,
    // set previous context in result to active context.

    // 4) If local context is not an array, set local context to an array containing only local context.
    json myContext = json::array();
    if (!localContext.is_array()) {
        myContext.push_back(localContext);
    }
    else {
        myContext.insert(myContext.end(), localContext.begin(), localContext.end());
    }

    // 5) For each item context in local context:
    for (auto context : myContext) {
        // 5.1) If context is null:
        if (context.is_null()) {
            // 5.1.1) If override protected is false and active context contains any protected term definitions,
            // an invalid context nullification has been detected and processing is aborted.

            // 5.1.2) Initialize result as a newly-initialized active context,
            // setting both base IRI and original base URL to the value of original base URL in active context,
            // and, if propagate is false, previous context in result to the previous value of result.
            // TODO:
            Context c(m_options);
            result = c;

            // 5.1.3) Continue with the next context.
            continue;
        }

        // 5.2) If context is a string,
        else if (context.is_string()) {
            throw JsonLdError(JsonLdError::NotImplemented, "context.is_string() not implemented: ");

            // 5.2.1) Initialize context to the result of resolving context against base URL.
            // If base URL is not a valid IRI, then context MUST be a valid IRI,
            // otherwise a loading document failed error has been detected and processing is aborted.

            // 5.2.2) If validate scoped context is false, and remote contexts already includes context
            // do not process context further and continue to any next context in local context.

            // 5.2.3) If the number of entries in the remote contexts array exceeds a processor defined limit,
            // a context overflow error has been detected and processing is aborted; otherwise, add context to remote contexts.

            // 5.2.4) If context was previously dereferenced, then the processor MUST NOT do a further dereference,
            // and context is set to the previously established internal representation: set context document to
            // the previously dereferenced document, and set loaded context to the value of the @context entry
            // from the document in context document.

            // 5.2.5) Otherwise, set context document to the RemoteDocument obtained by dereferencing context
            // using the LoadDocumentCallback, passing context for url, and http://www.w3.org/ns/json-ld#context for profile and for requestProfile.

            // 5.2.5.1) If context cannot be dereferenced, or the document from context document cannot be transformed
            // into the internal representation, a loading remote context failed error has been detected and processing is aborted.

            // 5.2.5.2) If the document has no top-level map with an @context entry,
            // an invalid remote context has been detected and processing is aborted.

            // 5.2.5.3) Set loaded context to the value of that entry.

            // 5.2.6) Set result to the result of recursively calling this algorithm,
            // passing result for active context, loaded context for local context,
            // the documentUrl of context document for base URL, a copy of remote contexts, and validate scoped context.

            // 5.2.7) Continue with the next context.
        }
        // 5.3) If context is not a map, an invalid local context error has been detected and processing is aborted.
        else if (!(context.is_object())) {
            throw JsonLdError(JsonLdError::InvalidLocalContext, context);
        }

        // 5.4) Otherwise, context is a context definition.
        // TODO: do we need this?
        checkEmptyKey(context);

        // 5.5) If context has an @version entry:
        // 5.5.1) If the associated value is not 1.1, an invalid @version value has been detected, and processing is aborted.
        // 5.5.2) If processing mode is set to json-ld-1.0, a processing mode conflict error has been detected and processing is aborted.

        // 5.6) If context has an @import entry:
        // 5.6.1) If processing mode is json-ld-1.0, an invalid context entry error has been detected and processing is aborted.
        // 5.6.2) Otherwise, if the value of @import is not a string, an invalid @import value error has been detected and processing is aborted.
        // 5.6.3) Initialize import to the result of resolving the value of @import against base URL.
        // 5.6.4) Dereference import using the LoadDocumentCallback, passing import for url,
        // and http://www.w3.org/ns/json-ld#context for profile and for requestProfile.
        // 5.6.5) If import cannot be dereferenced, or cannot be transformed into the internal representation,
        // a loading remote context failed error has been detected and processing is aborted.
        // 5.6.6) If the dereferenced document has no top-level map with an @context entry,
        // or if the value of @context is not a context definition (i.e., it is not an map),
        // an invalid remote context has been detected and processing is aborted; otherwise, set import context to the value of that entry.
        // 5.6.7) If import context has a @import entry, an invalid context entry error has been detected and processing is aborted.
        // 5.6.8) Set context to the result of merging context into import context,
        // replacing common entries with those from context.

        // 5.7) If context has an @base entry and remote contexts is empty, i.e.,
        // the currently being processed context is not a remote context:
        if (context.contains(JsonLdConsts::BASE) && remoteContexts.size() == 0) {
            // 5.7.1) Initialize value to the value associated with the @base entry.
            auto value = context.at(JsonLdConsts::BASE);

            if (value.is_null()) {
                // 5.7.2) If value is null, remove the base IRI of result.
                // TODO: Maybe rename BASE to BASE_IRI?
                result.erase(JsonLdConsts::BASE);
            } else if (value.is_string()) {
                // 5.7.3) Otherwise, if value is an IRI, the base IRI of result is set to value.
                if (JsonLdUtils::isAbsoluteIri(value)) {
                    result.insert(std::make_pair(JsonLdConsts::BASE, value.get<std::string>()));
                } else {
                    // 5.7.4) Otherwise, if value is a relative IRI reference and the base IRI of result is not null,
                    // set the base IRI of result to the result of resolving value against the current base IRI of result.
                    // TODO:
                    std::string baseUri = result.at(JsonLdConsts::BASE);
                    if (!JsonLdUtils::isAbsoluteIri(baseUri)) {
                        // 5.7.5) Otherwise, an invalid base IRI error has been detected and processing is aborted.
                        throw JsonLdError(JsonLdError::InvalidBaseIri, baseUri);
                    }
                    std::string tmpIri = value.get<std::string>();
                    result.insert(std::make_pair(JsonLdConsts::BASE, JsonLdUrl::resolve(&baseUri, &tmpIri)));
                }
            } else {
                throw JsonLdError(JsonLdError::InvalidBaseIri, "@base must be a string");
            }
        }

        // 5.8) If context has an @vocab entry:
        if (context.contains(JsonLdConsts::VOCAB)) {
            // 5.8.1) Initialize value to the value associated with the @vocab entry.
            auto value = context.at(JsonLdConsts::VOCAB);

            if (value.is_null()) {
                // 5.8.2) If value is null, remove any vocabulary mapping from result.
                result.erase(JsonLdConsts::VOCAB);
            } else if (value.is_string()) {
                // 5.8.3) Otherwise, if value is an IRI or blank node identifier, the vocabulary mapping of
                // result is set to the result of IRI expanding value using true for document relative.
                // If it is not an IRI, or a blank node identifier, an invalid vocab mapping error has been
                // detected and processing is aborted.

                if (JsonLdUtils::isAbsoluteIri(value)) {
                    result.insert(std::make_pair(JsonLdConsts::VOCAB, value.get<std::string>()));
                } else {
                    throw JsonLdError(JsonLdError::InvalidVocabMapping,
                                      "@value must be an absolute IRI");
                }
            } else {
                throw JsonLdError(JsonLdError::InvalidVocabMapping,
                                  "@vocab must be a string or null");
            }
        }

        // 5.9) If context has an @language entry:
        if (context.contains(JsonLdConsts::LANGUAGE)) {
            // 5.9.1) Initialize value to the value associated with the @language entry.
            auto value = context.at(JsonLdConsts::LANGUAGE);

            if (value.is_null()) {
                // 5.9.2) If value is null, remove any default language from result.
                result.erase(JsonLdConsts::LANGUAGE);
            } else if (value.is_string()) {
                // 5.9.3) Otherwise, if value is a string, the default language of result is set to value.
                result.insert(std::make_pair(JsonLdConsts::LANGUAGE, value.get<std::string>())); // todo: value to lowercase
            } else {
                // If it is not a string, an invalid default language error has been detected and processing is aborted.
                // If value is not well-formed according to section 2.2.9 of [BCP47], processors SHOULD issue a warning.
                // TODO:
                throw JsonLdError(JsonLdError::InvalidDefaultLanguage, value);
            }
        }

        // 5.10) If context has an @direction entry:
        // 5.10.1) If processing mode is json-ld-1.0, an invalid context entry error has been detected and processing is aborted.
        // 5.10.2) Initialize value to the value associated with the @direction entry.
        // 5.10.3) If value is null, remove any base direction from result.
        // 5.10.4) Otherwise, if value is a string, the base direction of result is set to value.
        // If it is not null, "ltr", or "rtl", an invalid base direction error has been detected and processing is aborted.

        // 5.11) If context has an @propagate entry:
        // 5.11.1) If processing mode is json-ld-1.0, an invalid context entry error has
        // been detected and processing is aborted.
        // 5.11.2) Otherwise, if the value of @propagate is not boolean true or false,
        // an invalid @propagate value error has been detected and processing is aborted.

        // 5.12) Create a map defined to keep track of whether or not a term has
        // already been defined or is currently being defined during recursion.
        std::map<std::string, bool> defined; // TODO: thrown out?
        for (const auto& el : context.items()) {
            // 5.13) For each key-value pair in context where key is not @base, @direction, @import, @language, @propagate,
            // @protected, @version, or @vocab, invoke the Create Term Definition algorithm, passing result for active context,
            // context for local context, key, defined, base URL, the value of the @protected entry from context, if any,
            // for protected, override protected, and a copy of remote contexts.
            const auto& key = el.key();
            if (key == JsonLdConsts::BASE ||
                key == JsonLdConsts::VOCAB ||
                key == JsonLdConsts::LANGUAGE ||
                key == JsonLdConsts::DIRECTION ||
                key == JsonLdConsts::IMPORT ||
                key == JsonLdConsts::PROPAGATE ||
                key == JsonLdConsts::PROTECTED ||
                key == JsonLdConsts::VERSION) {
                continue;
            }
            result.createTermDefinition(context, key, defined);
        }
    }

    // 6) Return result.
    return result;
}

std::string Context::getContainer(std::string property) {
//        if (property == null) {
//            return null;
//        }
    if (property == JsonLdConsts::GRAPH) {
        return JsonLdConsts::SET;
    }
    if (property != JsonLdConsts::TYPE && JsonLdUtils::isKeyword(property)) {
        return property;
    }
    if(!m_termDefinitions.contains(property))
        return "";
    auto td = m_termDefinitions[property];
//        if (td == null) {
//            return null;
//        }
    if (td.empty())
        return "";
    auto c = td[JsonLdConsts::CONTAINER];
    if(!c.is_string()) {
        return "";
    }
    else {
        return c.get<std::string>();
    }
}

/**
  * IRI Expansion Algorithm
  *
  * http://json-ld.org/spec/latest/json-ld-api/#iri-expansion
  *
  * Notes:
  * If context is_null(), then we don't bother creating term definitions
  * We don't want to bother with a nullable 'defined' so it can just be empty if context is_null()
  *
  * @param value the Iri to expand
  * @param relative flag
  * @param vocab flag
  * @param context the context map
  * @param defined map of defined values
  * @return the expanded Iri
  * @throws JsonLdError
  */
std::string Context::expandIri(
        std::string value, bool relative, bool vocab,
        const json& context, std::map<std::string, bool> & defined) {
        // 1)
        if (JsonLdUtils::isKeyword(value)) { // todo: also checked for if value was null
            return value;
        }
        // 2)
        if (!context.is_null() && context.contains(value) &&
            defined.find(value) != defined.end() && !defined.at(value) ) {
            createTermDefinition(context, value, defined);
        }
        // 3)
        if (vocab && m_termDefinitions.find(value) != m_termDefinitions.end()) {
            auto td = m_termDefinitions.at(value);
            if (!td.is_null()) {
                if(td.contains(JsonLdConsts::ID))
                    return td.at(JsonLdConsts::ID);
                else
                    return "";
            } else {
                return ""; // todo: was null
            }
        }
        // 4)
        auto colIndex = value.find(':');
        if (colIndex != std::string::npos) {
            // 4.1)
            std::string prefix(value, 0, colIndex);
            std::string suffix(value, colIndex+1);
            // 4.2)
            if (prefix == "_" || suffix.find('/') == 0) {
                return value;
            }
            // 4.3)
            if (!context.is_null() && context.contains(prefix)
                && (defined.find(prefix) == defined.end() || !defined.at(prefix))) {
                createTermDefinition(context, prefix, defined);
            }
            // 4.4)
            if (m_termDefinitions.find(prefix) != m_termDefinitions.end()) {
                auto id = m_termDefinitions.at(prefix).at(JsonLdConsts::ID);
                id = id.get<std::string>() + suffix;
                return id;
            }
            // 4.5)
            return value;
        }
        // 5)
        if (vocab && m_contextMap.find(JsonLdConsts::VOCAB) != m_contextMap.end()) {
            return m_contextMap.at(JsonLdConsts::VOCAB) + value;
        }
        // 6)
        else if (relative) {
            if(this->count(JsonLdConsts::BASE))
                return JsonLdUrl::resolve(&(this->at(JsonLdConsts::BASE)), &value);
            else
                return JsonLdUrl::resolve(nullptr, &value);
        } else if (!context.is_null() && JsonLdUtils::isRelativeIri(value)) {
            throw JsonLdError(JsonLdError::InvalidIriMapping, "not an absolute IRI: " + value);
        }
        // 7)
        return value;
}

std::string Context::expandIri(
        std::string value, bool relative, bool vocab) {
    // dummy objects
    json j;
    std::map<std::string, bool> m;
    return expandIri(std::move(value), relative, vocab, j, m);
}

/**
 * Create Term Definition Algorithm
 *
 * http://json-ld.org/spec/latest/json-ld-api/#create-term-definition
 * https://w3c.github.io/json-ld-api/#create-term-definition
 *
 * @param context the context
 * @param term the term to define
 * @param defined map of defined values
 * @throws JsonLdError
 */
void Context::createTermDefinition(json context, const std::string& term, std::map<std::string, bool> & defined)
{
    // 1) has term been defined already?
    if (defined.find(term) != defined.end()) {
        if (defined.at(term)) {
            return;
        }
        throw JsonLdError(JsonLdError::CyclicIriMapping, term);
    }

    // 2) term is bring created, but not yet complete
    defined[term] = false;

    // 4) + 5) check for keyword redefinition

    // if term is a keyword
    if (JsonLdUtils::isKeyword(term)) {
        // if term is not ('@type' and getAllowContainerSetOnType is true)
        if(!(m_options->getAllowContainerSetOnType() && term == JsonLdConsts::TYPE)) {
            // if context for term contain '@id'
            if( !(context.at(term)).contains(JsonLdConsts::ID)) {
                throw JsonLdError(JsonLdError::KeywordRedefinition, term);
            }
        }
    }

    // 7) remove any previous definition
    if (m_termDefinitions.count(term) ) {
        m_termDefinitions.erase(term);
    }

    // 3) get value associated with term
    auto value = context.at(term);

    // 8) If value is null, create a single member whose key is @id and whose value is null.

    if (value == nullptr ||
        (value.contains(JsonLdConsts::ID) && value.at(JsonLdConsts::ID) == nullptr)) {
        m_termDefinitions[term] = nullptr;
        defined[term] = true;
        return;
    }

    // 9)
    if (value.is_string()) {
        value = ObjUtils::newMap(JsonLdConsts::ID, value);
    }

    // 10)
    if (!(value.is_object())) {
        throw JsonLdError(JsonLdError::InvalidTermDefinition, value);
    }

    // 11) create a new term definition
    auto definition = ObjUtils::newMap();

    // 12) ???

    // 13)
    if (value.contains(JsonLdConsts::TYPE)) {
        auto type = value.at(JsonLdConsts::TYPE);

        // 13.1)
        if (!(type.is_string())) {
            throw JsonLdError(JsonLdError::InvalidTypeMapping, type);
        }
        std::string typeStr = type.get<std::string>();

        // 13.2)
        try {
            typeStr = expandIri(typeStr, false, true, context, defined);
        } catch (JsonLdError &error) {
            std::string msg = error.what();
            if(msg.find(JsonLdError::InvalidIriMapping) != std::string::npos) {
                throw error;
            }
            throw JsonLdError(JsonLdError::InvalidTypeMapping, type);
        }

        // TODO: fix check for absoluteIri (blank nodes shouldn't count, at least not here!)
        // 13.3)
        if (typeStr == JsonLdConsts::ID || typeStr == JsonLdConsts::VOCAB
            || (typeStr.find(JsonLdConsts::BLANK_NODE_PREFIX) != 0
                && JsonLdUtils::isAbsoluteIri(typeStr))) {
            definition[JsonLdConsts::TYPE] = typeStr;
        } else {
            throw JsonLdError(JsonLdError::InvalidTypeMapping, type);
        }
    }

        // 11)
        if (value.contains(JsonLdConsts::REVERSE)) {
            if (value.contains(JsonLdConsts::ID)) {
                throw JsonLdError(JsonLdError::InvalidReverseProperty, value);
            }
            auto reverse = value.at(JsonLdConsts::REVERSE);

            if (!(reverse.is_string())) {
                throw  JsonLdError(JsonLdError::InvalidIriMapping,
                                      "Expected String for @reverse value.");
            }
            std::string reverseStr = reverse.get<std::string>();

            reverseStr = expandIri(reverseStr, false, true, context, defined);
            if (!JsonLdUtils::isAbsoluteIri(reverseStr)) {
                throw JsonLdError(JsonLdError::InvalidIriMapping,
                                      "Non-absolute @reverse IRI: " + reverseStr);
            }
            definition[JsonLdConsts::ID] = reverseStr;
            if (value.contains(JsonLdConsts::CONTAINER)) {
                std::string container = value.at(JsonLdConsts::CONTAINER);
                if (container == JsonLdConsts::SET || container == JsonLdConsts::INDEX) { // todo was container == null
                    definition[JsonLdConsts::CONTAINER] = container;
                } else {
                    throw JsonLdError(JsonLdError::InvalidReverseProperty,
                                          "reverse properties only support set- and index-containers");
                }
            }
            definition[JsonLdConsts::REVERSE] = true;
            m_termDefinitions[term] = definition;
            defined[term] = true;
            return;
        }

        // 12)
        definition[JsonLdConsts::REVERSE] = false;

        // 13)
        if (value.contains(JsonLdConsts::ID) && term != value.at(JsonLdConsts::ID)) {
            auto id = value.at(JsonLdConsts::ID);
            if (!id.is_string()) {
                throw JsonLdError(JsonLdError::InvalidIriMapping, "expected value of @id to be a string");
            }

            std::string idStr = id.get<std::string>();

            idStr = expandIri(idStr, false, true, context, defined);
            if (JsonLdUtils::isKeyword(idStr) || JsonLdUtils::isAbsoluteIri(idStr)) {
                if (idStr == JsonLdConsts::CONTEXT) {
                    throw JsonLdError(JsonLdError::InvalidKeywordAlias, "cannot alias @context");
                }
                definition[JsonLdConsts::ID] = idStr;
            } else {
                throw JsonLdError(JsonLdError::InvalidIriMapping,
                                  "resulting IRI mapping should be a keyword, absolute IRI or blank node");
            }
        }

        // 14)
        else if (term.find(':') != std::string::npos) { // todo: use isabsoluteiri?
            auto colIndex = term.find(':');
            std::string prefix(term, 0, colIndex);
            std::string suffix(term, colIndex+1);
            if (context.contains(prefix)) {
                createTermDefinition(context, prefix, defined);
            }
            if (m_termDefinitions.find(prefix) != m_termDefinitions.end()) {
                auto id = m_termDefinitions.at(prefix).at(JsonLdConsts::ID);
                id = id.get<std::string>() + suffix;
                definition[JsonLdConsts::ID] = id;
            } else {
                definition[JsonLdConsts::ID] = term;
            }
            // 15)
        } else if (m_contextMap.find(JsonLdConsts::VOCAB) != m_contextMap.end()) {
            definition[JsonLdConsts::ID] = m_contextMap.at(JsonLdConsts::VOCAB) + term;
        } else if (term != JsonLdConsts::TYPE) {
            throw JsonLdError(JsonLdError::InvalidIriMapping,
                                  "relative term definition without vocab mapping");
        }

        // 16)
        if (value.contains(JsonLdConsts::CONTAINER)) {
            std::string container = value.at(JsonLdConsts::CONTAINER);
            if(container != JsonLdConsts::LIST &&
               container != JsonLdConsts::SET &&
               container != JsonLdConsts::INDEX &&
               container != JsonLdConsts::LANGUAGE) {
                throw JsonLdError(JsonLdError::InvalidContainerMapping,
                                  "@container must be either @list, @set, @index, or @language");
            }
            definition[JsonLdConsts::CONTAINER] = container;
            if (term == JsonLdConsts::TYPE) {
                definition[JsonLdConsts::ID] = "type";
            }
        }

        // 17)
        if (value.contains(JsonLdConsts::LANGUAGE) && !value.contains(JsonLdConsts::TYPE)) {
            auto language = value.at(JsonLdConsts::LANGUAGE);
            if (language.is_null() || language.is_string()) {
                definition[JsonLdConsts::LANGUAGE] = language; // todo: tolowercase or null?
            } else {
                throw JsonLdError(JsonLdError::InvalidLanguageMapping,
                                      "@language must be a string or null");
            }
        }

        // 18)
        m_termDefinitions[term] = definition;
        defined[term] = true;

}

std::string & Context::at(const std::string &s) {
    return m_contextMap.at(s);
}

size_t Context::erase(const std::string &key) {
    return m_contextMap.erase(key);
}

std::pair<Context::StringMap::iterator,bool> Context::insert( const StringMap::value_type& value ) {
    // unlike a normal c++ map, which does not insert a value if the key is already present,
    // we DO want to replace, so we have to erase first
    if (m_contextMap.find(value.first) != m_contextMap.end()) {
        m_contextMap.erase(value.first);
    }
    return m_contextMap.insert(value);
}

size_t Context::count(const std::string &key) const {
    return m_contextMap.count(key);
}

bool Context::isReverseProperty(const std::string &property) {
    if (!m_termDefinitions.count(property)) {
        return false;
    }

    auto td = m_termDefinitions.at(property);
    if (td.is_null()) {
        return false;
    }
    return td.contains(JsonLdConsts::REVERSE) && td.at(JsonLdConsts::REVERSE);
}

nlohmann::json Context::getTermDefinition(const std::string & key) {
    if (m_termDefinitions.count(key)) {
        return m_termDefinitions.at(key);
    }
    else
        return json::object();
}


json Context::expandValue(const std::string & activeProperty, const json& value)  {
    auto rval = ObjUtils::newMap();
    json td = getTermDefinition(activeProperty);
    // 1)
    if (!td.is_null() && td.contains(JsonLdConsts::TYPE) && td.at(JsonLdConsts::TYPE) == JsonLdConsts::ID) {
        // TODO: i'm pretty sure value should be a string if the @type is @id
        rval[JsonLdConsts::ID] = expandIri(value.get<std::string>(), true, false);
        return rval;
    }
    // 2)
    if (!td.is_null() && td.contains(JsonLdConsts::TYPE) && td.at(JsonLdConsts::TYPE) == JsonLdConsts::VOCAB) {
        // TODO: same as above
        rval[JsonLdConsts::ID] = expandIri(value.get<std::string>(), true, true);
        return rval;
    }
    // 3)
    rval[JsonLdConsts::VALUE] = value;
    // 4)
    if (!td.is_null() && td.contains(JsonLdConsts::TYPE)) {
        rval[JsonLdConsts::TYPE] = td.at(JsonLdConsts::TYPE);
    }
        // 5)
    else if (value.is_string()) {
        // 5.1)
        if (!td.is_null() && td.contains(JsonLdConsts::LANGUAGE)) {
            json lang = td.at(JsonLdConsts::LANGUAGE);
            if (!lang.is_null()) {
                rval[JsonLdConsts::LANGUAGE] = lang.get<std::string>();
            }
        }
            // 5.2)
        else if (m_contextMap.count(JsonLdConsts::LANGUAGE)) {
            rval[JsonLdConsts::LANGUAGE] = m_contextMap.at(JsonLdConsts::LANGUAGE);
        }
    }
    return rval;
}

Context::Context(const std::shared_ptr<JsonLdOptions>& options)
        : m_options(options)
{
    init();
}

Context::Context(std::map<std::string, std::string> map, const std::shared_ptr<JsonLdOptions>& options)
        : m_options(options), m_contextMap(std::move(map)) {
    checkEmptyKey(m_contextMap);
    init();
}

Context::Context(std::map<std::string, std::string> map)
        : m_contextMap(std::move(map)) {
    checkEmptyKey(m_contextMap);
    init();
}

