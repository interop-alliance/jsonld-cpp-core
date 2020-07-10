//
//  CurlGuard.h
//
//
//  Created by Oleg Kuzenko on 7/09/20.
//  Copyright © 2020 Oleg. All rights reserved.
//

#ifndef CURL_GUARD_H
#define CURL_GUARD_H

#include <curl/curl.h>
#include <exception>
#include <iostream>
#include <string>

namespace jsonld
{
    namespace curl
    {
        static void CheckCurlError(CURLcode res)
        {
            if (res != CURLE_OK)
            {
                fprintf(stderr, "Curl error: %s\n", curl_easy_strerror(res));
                throw std::runtime_error(curl_easy_strerror(res));
            }
        }

        static void EraseAllSubStrings(std::string& mainString, const std::string& toErase)
        {
            size_t pos = std::string::npos;
            while ((pos  = mainString.find(toErase) )!= std::string::npos)
            {
                mainString.erase(pos, toErase.length());
            }
        }

        static void CleanResponseHeaderString(std::string& headerString)
        {
            EraseAllSubStrings(headerString, "\r");
            EraseAllSubStrings(headerString, "\n");
        }
    }
}

#endif //CURL_GUARD_H
