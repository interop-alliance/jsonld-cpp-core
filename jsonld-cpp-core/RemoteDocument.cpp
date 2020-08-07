#include <utility>
#include <iostream>

#include "RemoteDocument.h"

RemoteDocument::RemoteDocument(std::string iurl, nlohmann::json idocument)
: url(std::move(iurl)), document(std::move(idocument))
{
    const std::string documentString = document.dump();
    std::cout << documentString << std::endl;
}

const std::string &RemoteDocument::getUrl() const {
    return url;
}

const nlohmann::json &RemoteDocument::getDocument() const {
    return document;
}
