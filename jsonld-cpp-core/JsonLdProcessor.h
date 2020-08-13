#ifndef LIBJSONLD_CPP_JSONLDPROCESSOR_H
#define LIBJSONLD_CPP_JSONLDPROCESSOR_H

#include "jsoninc.h"
#include "JsonLdOptions.h"
#include "JsonLdError.h"
#include "Context.h"
#include "RDFDataset.h"
#include "JsonLdApi.h"
#include "JsonldPromise.h"

/**
 * This class implements the
 * <a href="http://json-ld.org/spec/latest/json-ld-api/#the-jsonldprocessor-interface" >
 * JsonLdProcessor interface</a>.
 */

namespace JsonLdProcessor {

    /**
     * Expands the given input according to the steps in the
     * <a href="http://www.w3.org/TR/json-ld-api/#expansion-algorithm">Expansion
     * algorithm</a>.
     *
     * @param input
     *            The input JSON-LD object.
     * @param opts
     *            The {@link JsonLdOptions} that are to be sent to the expansion
     *            algorithm.
     * @return The expanded JSON-LD document
     * @throws JsonLdError
     *             If there is an error while expanding.
     */
    nlohmann::json expand(nlohmann::json input, const std::shared_ptr<JsonLdOptions> options, const std::string& baseUrl = "");
    nlohmann::json expand(const std::string& input, const std::shared_ptr<JsonLdOptions> options, const std::string& baseUrl = "");

    /**
     * Expands the given input according to the steps in the
     * <a href="http://www.w3.org/TR/json-ld-api/#expansion-algorithm">Expansion
     * algorithm</a>, using the default {@link JsonLdOptions}.
     *
     * @param input
     *            The input JSON-LD object.
     * @return The expanded JSON-LD document
     * @throws JsonLdError
     *             If there is an error while expanding.
     */
    nlohmann::json expand(nlohmann::json input, const std::string& baseUrl = "");
    nlohmann::json expand(std::string input, const std::string& baseUrl = "");

    RDF::RDFDataset toRDF(const std::string& input, const std::shared_ptr<JsonLdOptions> options);
    std::string toRDFString(const std::string& input, const std::shared_ptr<JsonLdOptions> options);
    std::string normalize(const std::string& input, const std::shared_ptr<JsonLdOptions> options);
}

#endif //LIBJSONLD_CPP_JSONLDPROCESSOR_H
