#ifndef LIBJSONLD_CPP_JSONLDERROR_H
#define LIBJSONLD_CPP_JSONLDERROR_H

#include "jsoninc.h"

class JsonLdError : public std::runtime_error {
public:

    static const char LoadingDocumentFailed[];
    static const char ListOfLists[];
    static const char InvalidIndexValue[];
    static const char ConflictingIndexes[];
    static const char InvalidIdValue[];
    static const char InvalidLocalContext[];
    static const char MultipleContextLinkHeaders[];
    static const char LoadingRemoteContextFailedError[];
    static const char InvalidRemoteContextError[];
    static const char RecursiveContextInclusion[];
    static const char InvalidBaseIri[];
    static const char InvalidVocabMapping[];
    static const char InvalidDefaultLanguage[];
    static const char KeywordRedefinition[];
    static const char InvalidTermDefinition[];
    static const char InvalidReverseProperty[];
    static const char InvalidIriMapping[];
    static const char CyclicIriMapping[];
    static const char InvalidKeywordAlias[];
    static const char InvalidTypeMapping[];
    static const char InvalidLanguageMapping[];
    static const char CollidingKeywords[];
    static const char InvalidContainerMapping[];
    static const char InvalidTypeValue[];
    static const char InvalidValueObject[];
    static const char InvalidValueObjectValue[];
    static const char InvalidLanguageTaggedString[];
    static const char InvalidLanguageTaggedValue[];
    static const char InvalidTypedValue[];
    static const char InvalidSetOrListObject[];
    static const char InvalidLanguageMapValue[];
    static const char CompactionToListOfLists[];
    static const char InvalidReversePropertyMap[];
    static const char InvalidReverseValue[];
    static const char InvalidReversePropertyValue[];
    static const char SyntaxError[];
    static const char NotImplemented[];
    static const char UnknownFormat[];
    static const char InvalidInput[];
    static const char ParseError[];
    static const char UnknownError[];
    static const char ContextOverflowError[];

private:
    nlohmann::json detail;

public:
    JsonLdError(const std::string& itype, const nlohmann::json& idetail);
    explicit JsonLdError(const std::string& itype);

    const char* what() const noexcept override;

};


#endif //LIBJSONLD_CPP_JSONLDERROR_H
