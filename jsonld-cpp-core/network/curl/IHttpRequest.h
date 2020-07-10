//
//  IHttpRequest.h
//
//
//  Created by Oleg Kuzenko on 7/09/20.
//  Copyright © 2020 Oleg. All rights reserved.
//

#pragma once

#include <map>
#include <string>
#include <functional>
#include <memory>

namespace jsonld
{
    namespace network
    {
        enum class HttpMethod
        {
            Get,
            Post
        };

        using HttpHeader = std::map<std::string, std::string>;
        using QueryParameters = std::map<std::string, std::string>;

        enum HttpResponseCode
        {
            HttpResponseCodeOk = 200,
            HttpResponseCodeBadRequest = 400
        };

        class HttpRequestParameters
        {
        public:
            HttpMethod method = HttpMethod::Get;
            std::string host;
            std::string path;

            std::string body;
        };

        class IHttpRequest
        {
        public:
            using IHttpRequestCallback = std::function<void(const uint32_t errorCode,
                                                                    std::string response,
                                                                    HttpHeader responseHeaders)>;
            virtual ~IHttpRequest() = default;
            virtual void performRequest(HttpRequestParameters params, IHttpRequestCallback responseCallback) = 0;
        };

        using IHttpRequestPtr = std::shared_ptr<IHttpRequest>;
    }
}
