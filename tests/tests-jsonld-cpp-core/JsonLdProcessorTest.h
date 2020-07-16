//
// Created by Oleg Kuzenko on 16.07.2020.
//

#ifndef JSONLDPROCESSORTEST_H
#define JSONLDPROCESSORTEST_H

#include <gtest/gtest.h>

class JsonLdProcessorTestWithOptions : public ::testing::Test
{
protected:
    std::shared_ptr<JsonLdOptions> m_jsonLdOptions;

    virtual void SetUp()
    {
        m_jsonLdOptions = std::make_shared<JsonLdOptions>();
    }

    virtual void TearDown()
    {
    }
};

#endif JSONLDPROCESSORTEST_H
