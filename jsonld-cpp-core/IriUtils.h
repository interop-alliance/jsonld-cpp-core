#ifndef LIBJSONLD_CPP_IRIUTILS_H
#define LIBJSONLD_CPP_IRIUTILS_H

#include <string>

namespace IriUtils {
    std::string removeDotSegments(const std::string& path, bool hasAuthority);
    std::string prependBase(std::string base, std::string iri);
    bool isValidIri(const std::string& value);
}

#endif //LIBJSONLD_CPP_IRIUTILS_H
