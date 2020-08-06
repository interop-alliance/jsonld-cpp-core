//
// Created by user on 06.08.20.
//

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "CurlLoadDocumentCallback.h"
#include "RemoteDocument.h"

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
