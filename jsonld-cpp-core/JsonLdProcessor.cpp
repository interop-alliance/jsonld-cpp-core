#include "JsonLdProcessor.h"
#include "RDFDataset.h"
#include "RDFDatasetUtils.h"
#include "IHttpRequest.h"

using RDF::RDFDataset;
using nlohmann::json;

nlohmann::json JsonLdProcessor::expand(nlohmann::json input, const std::shared_ptr<JsonLdOptions> options, const std::string& baseUrl) {
    // 3) Initialize a new empty active context.
    // The base IRI of the active context is set to the IRI of the currently being processed document,
    // if available; otherwise to null. If set, the base option from options overrides the base IRI.
    Context activeCtx(options);

    // 4) If an expandContext option has been passed, update the active context using the Context Processing algorithm,
    // passing the expandContext as local context. If expandContext is a dictionary having an
    // @context member, pass that member's value instead.
    if (!options->getExpandContext().empty()) {
        json exCtx = options->getExpandContext();
        if (exCtx.contains(JsonLdConsts::CONTEXT)) {
            exCtx = exCtx[JsonLdConsts::CONTEXT];
        }

        activeCtx = activeCtx.parse(baseUrl, exCtx);
    }

    // 5) Once input has been retrieved, the response has an HTTP Link Header [RFC5988] using
    // the http://www.w3.org/ns/json-ld#context link relation and a content type of application/json
    // or any media type with a +json suffix as defined in [RFC6839] except application/ld+json,
    // update the active context using the Context Processing algorithm, passing the context referenced
    // in the HTTP Link Header as local context. The HTTP Link Header is ignored for documents served as
    // application/ld+json If multiple HTTP Link Headers using the http://www.w3.org/ns/json-ld#context
    // link relation are found, the promise is rejected with a JsonLdError whose code is set to
    // multiple context link headers and processing is terminated.
    // TODO: add support for getting a context from HTTP when content-type
    // is set to a jsonld compatible format
    // jsonld::network::CurlHttpRequest request;

    // 6) If necessary, transform input into the internal representation.
    // If input cannot be transformed to the internal representation,
    // reject promise passing a loading document failed error.

    // 7) Set expanded output to the result of using the Expansion algorithm,
    // passing the active context and input as element, and, if the frameExpansion
    // option is set, pass the frame expansion flag as true.
    JsonLdApi api(options);
    json expanded = api.expand(activeCtx, input);

    // 8) Fulfill the promise passing expanded output. transforming expanded output from the
    // internal representation to a JSON serialization.

    // final step of Expansion Algorithm
    if (expanded.is_object() && expanded.contains(JsonLdConsts::GRAPH)
        && expanded.size() == 1) {
        expanded = expanded.at(JsonLdConsts::GRAPH);
    } else if (expanded.is_null()) {
        expanded = json::array();
    }

    // normalize to an array
    if (!expanded.is_array()) {
        json tmp = json::array();
        tmp.push_back(expanded);
        expanded = tmp;
    }

    return expanded;
}

nlohmann::json JsonLdProcessor::expand(const std::string& input, const std::shared_ptr<JsonLdOptions> options, const std::string& baseUrl) {
    // 1) Create a new Promise promise and return it. The following steps are then executed asynchronously.

    // 2) If the passed input is a string representing the IRI of a remote document, dereference it.
    // If the retrieved document's content type is neither application/json, nor application/ld+json,
    // nor any other media type using a +json suffix as defined in [RFC6839],
    // reject the promise passing an loading document failed error.
    // TODO: better verification of DOMString IRI
    if (input.find(':') != std::string::npos) {
        try {
            auto remoteDocument = options->getDocumentLoader()->retrieveRemoteDocument(input);
            if (!remoteDocument)
                throw std::runtime_error("Error: remote document is empty!");
            const json& json_input = remoteDocument->getDocument();
            // TODO: figure out how to deal with remote context

            // if set the base in options should override the base iri in the
            // active context
            // thus only set this as the base iri if it's not already set in
            // options
            if (options->getBase().empty()) {
                options->setBase(input);
            }

            return expand(json_input, options, baseUrl);

        }
        catch (const std::exception &e) {
            throw JsonLdError(JsonLdError::LoadingDocumentFailed, e.what());
        }
    }
    else
        return json::array(); // todo: what else should happen?
}

RDFDataset JsonLdProcessor::toRDF(const std::string& input, const std::shared_ptr<JsonLdOptions> options) {

    nlohmann::json expandedInput = expand(input, options, "");

    JsonLdApi api(options);
    RDFDataset dataset = api.toRDF(expandedInput);

//
//    // generate namespaces from context
//    if (options.useNamespaces) {
//        List<Map<String, Object>> _input;
//        if (input instanceof List) {
//            _input = (List<Map<String, Object>>) input;
//        } else {
//            _input = new ArrayList<Map<String, Object>>();
//            _input.add((Map<String, Object>) input);
//        }
//        for (final Map<String, Object> e : _input) {
//            if (e.containsKey(JsonLdConsts.CONTEXT)) {
//                dataset.parseContext(e.get(JsonLdConsts.CONTEXT));
//            }
//        }
//    }
//
//    if (callback != null) {
//        return callback.call(dataset);
//    }
//
    return dataset;
}

std::string JsonLdProcessor::toRDFString(const std::string& input, const std::shared_ptr<JsonLdOptions> options) {

    nlohmann::json expandedInput = expand(input, options, "");

    JsonLdApi api(options);
    RDFDataset dataset = api.toRDF(expandedInput);
    // todo: while present in the java version, none of the toRdf() tests needed this namespace
    // stuff, so come back to it
//    // generate namespaces from context
//    if (options.useNamespaces) {
//        List<Map<String, Object>> _input;
//        if (input instanceof List) {
//            _input = (List<Map<String, Object>>) input;
//        } else {
//            _input = new ArrayList<Map<String, Object>>();
//            _input.add((Map<String, Object>) input);
//        }
//        for (final Map<String, Object> e : _input) {
//            if (e.containsKey(JsonLdConsts.CONTEXT)) {
//                dataset.parseContext(e.get(JsonLdConsts.CONTEXT));
//            }
//        }
//    }
//
//    if (callback != null) {
//        return callback.call(dataset);
//    }
//
    return RDFDatasetUtils::toNQuads(dataset);
}

std::string JsonLdProcessor::normalize(const std::string& input, const std::shared_ptr<JsonLdOptions> options) {

    RDFDataset dataset = toRDF(input, options);
    JsonLdApi api(options);
    return api.normalize(dataset);
}

nlohmann::json JsonLdProcessor::expand(nlohmann::json input, const std::string& baseUrl) {
    std::shared_ptr<JsonLdOptions> options = std::make_shared<JsonLdOptions>();
    return expand(std::move(input), options, baseUrl);
}

nlohmann::json JsonLdProcessor::expand(std::string input, const std::string& baseUrl) {
    std::shared_ptr<JsonLdOptions> options = std::make_shared<JsonLdOptions>();
    return expand(std::move(input), options, baseUrl);
}
