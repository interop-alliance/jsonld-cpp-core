//
// Created by user on 06.08.20.
//

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "CurlLoadDocumentCallback.h"
#include "RemoteDocument.h"
#include "IriUtils.h"
#include "CurlHttpRequest.h"

using json = nlohmann::json;
using namespace std::filesystem;

namespace {
    std::string getFileContents(const path &p) {
        std::ifstream f{p};
        const auto size = file_size(p);
        std::string buffer(size, ' ');
        f.read(&buffer[0], static_cast<std::streamsize>(size));
        return buffer;
    }
}

std::optional<RemoteDocument> CurlLoadDocumentCallback::retrieveRemoteDocument(const std::string& url, const LoadDocumentOptions& loadDocumentOptions) {
    // 1) Create a new Promise promise and return it. The following steps are then deferred.

    // 2) Set document to the body retrieved from the resource identified by url,
    // or by otherwise locating a resource associated with url. When requesting remote
    // documents the request MUST prefer Content-Type application/ld+json followed by application/json.
    // If requestProfile is set, it MUST be added as a profile on application/ld+json.
    // Processors MAY include other media types using a +json suffix as defined in [RFC6839].

    // 3) Set documentUrl to the location of the retrieved resource considering redirections (exclusive
    // of HTTP status 303 "See Other" redirects as discussed in [cooluris]).

    // 4) If the retrieved resource's Content-Type is not application/json nor any media type with
    // a +json suffix as defined in [RFC6839], and the response has an HTTP Link Header [RFC8288] using
    // the alternate link relation with type application/ld+json, set url to the associated href relative
    // to the previous url and restart the algorithm from step 2.

    // 5) If the retrieved resource's Content-Type is application/json or any media type with
    // a +json suffix as defined in [RFC6839] except application/ld+json, and the response has
    // an HTTP Link Header [RFC8288] using the http://www.w3.org/ns/json-ld#context link relation,
    // set contextUrl to the associated href.
    // If multiple HTTP Link Headers using the http://www.w3.org/ns/json-ld#context link relation are found,
    // the promise is rejected with a JsonLdError whose code is set to multiple context link headers and processing is terminated.

    // first check the cache
    auto it = m_cache.find(url);
    if (it != m_cache.end())
        return RemoteDocument(url, it->second);

    // do something to load
    path p(url);
    if (exists(p)) {
        // read file into string
        std::string fileContents = getFileContents(p);

        // create the json object
        json j = json::parse(fileContents);

        // add to cache
        m_cache[url] = j;

        return RemoteDocument(url, j);
    }
    else if (IriUtils::isValidIri(url)) {
        std::unique_ptr<jsonld::network::IHttpRequest> httpRequest = std::make_unique<jsonld::network::CurlHttpRequest>();
        jsonld::network::HttpRequestParameters parameters;
        parameters.host = url;

        std::string remoteContext;
        try {
            httpRequest->performRequest(parameters, [&remoteContext](const uint32_t errorCode, std::string response, jsonld::network::HttpHeader responseHeaders) {
                remoteContext = response;
            });
        }
        catch (const std::exception& e) {
            throw;
        }

        return RemoteDocument(url, json::parse(remoteContext));
    }
    else {
        std::stringstream ss;
        ss << "Error: Url not found: [" << url << "]";
        throw std::runtime_error(ss.str());
    }
}

void CurlLoadDocumentCallback::addDocumentToCache(const std::string& url, const std::string& contents) {
    json j = json::parse(contents);
    m_cache.insert(std::make_pair(url, j));
}
