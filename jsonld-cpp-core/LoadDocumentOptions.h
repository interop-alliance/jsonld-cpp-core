//
// Created by user on 01.08.20.
//

#ifndef JSONLD_CPP_CORE_LOADDOCUMENTOPTIONS_H
#define JSONLD_CPP_CORE_LOADDOCUMENTOPTIONS_H

class LoadDocumentOptions {
public:
    LoadDocumentOptions() : m_extractAllScripts(false) {}
    LoadDocumentOptions(const std::string& profile, const std::string& requestProfile, const bool extractAllScripts = false) :
                        m_profile(profile), m_requestProfile(requestProfile), m_extractAllScripts(extractAllScripts) {}

    bool doExtractAllScripts() const { return m_extractAllScripts; }
    std::string getProfile() const { return m_profile; }
    std::string getRequestProfile() const { return m_requestProfile; }

private:
    bool m_extractAllScripts;
    std::string m_profile;
    std::string m_requestProfile;
};

#endif //JSONLD_CPP_CORE_LOADDOCUMENTOPTIONS_H
