//
//  CurlHttpRequest.cpp
//
//
//  Created by Oleg Kuzenko on 7/09/20.
//  Copyright © 2020 Oleg. All rights reserved.
//

#include <iostream>
#include <assert.h>

#include "CurlHttpRequest.h"
#include "CurlHelper.h"

namespace
{
    // ptr points to the delivered data, and the size of that data is bufferSize; elementSize is always 1.
    size_t WriteData(void* ptr, size_t elementSize, size_t bufferSize, std::string* s)
    {
        const size_t newLength = elementSize * bufferSize;
        try
        {
            s->append(reinterpret_cast<char*>(ptr), newLength);
        }
        catch(std::bad_alloc& e)
        {
            return 0;
        }

        return newLength;
    }

    // The size of the data pointed to by buffer is size multiplied with nItems. Do not assume that the header line is zero terminated!
    size_t HeaderReceived(char* buffer, size_t size, size_t nItems, void* userData)
    {
        jsonld::network::HttpHeader* httpHeader = reinterpret_cast<jsonld::network::HttpHeader*>(userData);
        std::string headersString(buffer, nItems);
        jsonld::curl::CleanResponseHeaderString(headersString);
        auto delimiterPos = headersString.find(':');
        if (delimiterPos != std::string::npos)
        {
            httpHeader->emplace(headersString.substr(0, delimiterPos), headersString.substr(delimiterPos + 1, headersString.size()));
        }
        else
        {
            if (headersString.size() > 0)
            {
                httpHeader->emplace(headersString, "");
            }
        }

        return nItems * size;
    }
}

jsonld::network::CurlHttpRequest::CurlHttpRequest() : m_curl(curl_easy_init(), curl_easy_cleanup)
{
}

void jsonld::network::CurlHttpRequest::setProxy(const std::string& proxyUrl, const std::string& login, const std::string& password)
{
    m_proxyUrl = proxyUrl;
    m_proxyUserName = login;
    m_proxyPassword = password;
}

void jsonld::network::CurlHttpRequest::performRequest(jsonld::network::HttpRequestParameters params, jsonld::network::IHttpRequest::IHttpRequestCallback responseCallback)
{
    assert(m_curl && "Logic error: curl pointer is not empty!");

    int32_t retCode = 0;
    std::string response;
    std::string url = params.host + params.path;
    jsonld::network::HttpHeader headers;

    try
    {
        if (!m_curl)
        {
            throw std::runtime_error("Could not create curl object.");
        }

        jsonld::curl::CheckCurlError(curl_easy_setopt(m_curl.get(), CURLOPT_URL, url.c_str()));
        jsonld::curl::CheckCurlError(curl_easy_setopt(m_curl.get(), CURLOPT_FOLLOWLOCATION, 1));
        jsonld::curl::CheckCurlError(curl_easy_setopt(m_curl.get(), CURLOPT_TIMEOUT, 20L));

        if (!m_proxyUrl.empty())
        {
            jsonld::curl::CheckCurlError(curl_easy_setopt(m_curl.get(), CURLOPT_PROXY, m_proxyUrl.c_str()));
            jsonld::curl::CheckCurlError(curl_easy_setopt(m_curl.get(), CURLOPT_PROXYUSERNAME, m_proxyUserName.c_str()));
            jsonld::curl::CheckCurlError(curl_easy_setopt(m_curl.get(), CURLOPT_PROXYPASSWORD, m_proxyPassword.c_str()));
        }

        jsonld::curl::CheckCurlError(curl_easy_setopt(m_curl.get(), CURLOPT_WRITEFUNCTION, ::WriteData));
        jsonld::curl::CheckCurlError(curl_easy_setopt(m_curl.get(), CURLOPT_WRITEDATA, &response));

        jsonld::curl::CheckCurlError(curl_easy_setopt(m_curl.get(), CURLOPT_HEADERFUNCTION, ::HeaderReceived));
        jsonld::curl::CheckCurlError(curl_easy_setopt(m_curl.get(), CURLOPT_HEADERDATA, &headers));

        jsonld::curl::CheckCurlError(curl_easy_perform(m_curl.get()));

        jsonld::curl::CheckCurlError(curl_easy_getinfo(m_curl.get(), CURLINFO_RESPONSE_CODE, &retCode));
        if (retCode != jsonld::network::HttpResponseCode::HttpResponseCodeOk)
        {
            throw std::runtime_error("Could not get response from url: " + url);
        }
    }
    catch(...)
    {
        std::cout << "Curl exception rised. Getting response failed." << std::endl;
    }

    responseCallback(retCode, response, headers);
}
