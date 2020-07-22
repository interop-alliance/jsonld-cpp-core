#ifndef LIBJSONLD_CPP_TESTHELPERS_H
#define LIBJSONLD_CPP_TESTHELPERS_H

#include "jsoninc.h"
#include <string>

std::string resolvePath(const std::string &relPath);

std::string getTestNumberStr(int i);

std::string getDocumentUri(const std::string& testName, const std::string& testNumber);

std::string getInputJsonContent(const std::string& testName, const std::string& testDirectory, const std::string& testNumber);

nlohmann::json getExpectedJson(const std::string& testName, const std::string& testDirectory, const std::string& testNumber);

std::string getExpectedRDF(const std::string& testName, const std::string& testDirectory, const std::string& testNumber);


#endif //LIBJSONLD_CPP_TESTHELPERS_H
