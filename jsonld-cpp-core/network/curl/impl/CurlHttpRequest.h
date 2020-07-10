//
//  CurlHttpCommunicator.h
//
//
//  Created by Oleg Kuzenko on 7/09/20.
//  Copyright © 2020 Oleg. All rights reserved.
//

#ifndef CURL_HTTP_COMMUNICATOR_H
#define CURL_HTTP_COMMUNICATOR_H

#include <curl/curl.h>

#include <string>

#include "IHttpRequest.h"

namespace jsonld
{
    namespace network
    {
        class CurlHttpRequest: public jsonld::network::IHttpRequest
        {
        public:
            CurlHttpRequest();

            void performRequest(jsonld::network::HttpRequestParameters params, IHttpRequestCallback responseCallback) override;
            void setProxy(const std::string& proxyUrl, const std::string& user, const std::string& password);

        private:
            std::string m_proxyUserName;
            std::string m_proxyPassword;
            std::string m_proxyUrl;

            std::unique_ptr<CURL, void(*)(CURL*)> m_curl;
        };
    }
}

#endif //CURL_HTTP_COMMUNICATOR_H
