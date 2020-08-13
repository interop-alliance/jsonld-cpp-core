//
// Created by user on 01.08.20.
//

#ifndef JSONLD_CPP_CORE_ILOADDOCUMENTCALLBACK_H
#define JSONLD_CPP_CORE_ILOADDOCUMENTCALLBACK_H

#include <optional>

#include "RemoteDocument.h"
#include "LoadDocumentOptions.h"

class ILoadDocumentCallback {
public:
    virtual ~ILoadDocumentCallback() = default;

    virtual std::optional<RemoteDocument> retrieveRemoteDocument(const std::string& url,
            const LoadDocumentOptions& loadDocumentOptions = LoadDocumentOptions()) = 0;

    virtual void addDocumentToCache(const std::string& url, const std::string& contents) = 0;
};

#endif //JSONLD_CPP_CORE_ILOADDOCUMENTCALLBACK_H
