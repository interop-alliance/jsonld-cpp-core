//
// Created by user on 06.08.20.
//

#ifndef JSONLD_CPP_CORE_CURLLOADDOCUMENTCALLBACK_H
#define JSONLD_CPP_CORE_CURLLOADDOCUMENTCALLBACK_H

#include "ILoadDocumentCallback.h"

class CurlLoadDocumentCallback : public ILoadDocumentCallback {
    using json = nlohmann::json;

public:
    std::optional<RemoteDocument> retrieveRemoteDocument(const std::string& url,
                                                    const LoadDocumentOptions& loadDocumentOptions = LoadDocumentOptions()) override;

    void addDocumentToCache(const std::string& url, const std::string& contents) override;
private:


private:
    std::map<std::string, json> m_cache;
};


#endif //JSONLD_CPP_CORE_CURLLOADDOCUMENTCALLBACK_H
