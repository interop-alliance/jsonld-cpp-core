#ifndef LIBJSONLD_CPP_JSONLDAPI_H
#define LIBJSONLD_CPP_JSONLDAPI_H

#include "jsoninc.h"
#include "JsonLdOptions.h"
#include "Context.h"
#include "RDFDataset.h"

class JsonLdApi {
private:
    std::shared_ptr<JsonLdOptions> m_options;
    UniqueNamer m_blankNodeUniqueNamer;

public:

    JsonLdApi() = default;
    explicit JsonLdApi(const std::shared_ptr<JsonLdOptions>& options);

    const std::shared_ptr<JsonLdOptions> getOptions() const;

    /**
     * Expansion Algorithm
     *
     * http://json-ld.org/spec/latest/json-ld-api/#expansion-algorithm
     *
     * @param activeCtx
     *            The Active Context
     * @param activeProperty
     *            The Active Property
     * @param element
     *            The current element
     * @return The expanded JSON-LD object.
     */
    nlohmann::json expand(Context activeCtx, std::string *activeProperty, nlohmann::json element);

    /**
     * Expansion Algorithm
     *
     * http://json-ld.org/spec/latest/json-ld-api/#expansion-algorithm
     *
     * @param activeCtx
     *            The Active Context
     * @param element
     *            The current element
     * @return The expanded JSON-LD object.
     */
    nlohmann::json expand(Context activeCtx, nlohmann::json element);

    /**
     * Adds RDF triples for each graph in the current node map to an RDF
     * dataset.
     *
     * @return the RDF dataset.
     */
    RDF::RDFDataset toRDF(nlohmann::json element);

    /**
     * Performs RDF normalization on the given JSON-LD input.
     *
     * @param dataset
     *            the expanded JSON-LD object to normalize.
     * @return The normalized JSON-LD object
     * @throws JsonLdError
     *             If there was an error while normalizing.
     */
    std::string normalize(const RDF::RDFDataset& dataset);

private:

    nlohmann::json expandArrayElement(Context activeCtx, std::string *activeProperty, const nlohmann::json& element);

    nlohmann::json expandObjectElement(Context activeCtx, std::string *activeProperty, nlohmann::json element);

    void generateNodeMap(nlohmann::json &element, nlohmann::json &nodeMap);

    void generateNodeMap(nlohmann::json &element, nlohmann::json &nodeMap, std::string *activeGraph,
                         nlohmann::json *activeSubject, std::string *activeProperty, nlohmann::json *list);
};

#endif //LIBJSONLD_CPP_JSONLDAPI_H
