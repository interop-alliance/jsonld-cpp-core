#include <gtest/gtest.h>

#include "CurlLoadDocumentCallback.h"
#include "testHelpers.h"

#ifndef _WIN32
#pragma clang diagnostic push
#pragma GCC diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma clang diagnostic pop
#pragma GCC diagnostic pop
#endif

using json = nlohmann::json;

namespace
{
#ifdef _WIN32
    const std::string sampleDocumentPath = "tests\\tests-jsonld-cpp-core\\test_data\\pi-is-four.json";
#else
    const std::string sampleDocumentPath = "test_data/pi-is-four.json";
#endif
}

TEST(DocumentLoaderTest, load_sample_document_from_filesystem) {
    std::unique_ptr<CurlLoadDocumentCallback> dl = std::make_unique<CurlLoadDocumentCallback>();

    std::string docPath = resolvePath(sampleDocumentPath);

    auto d = dl->retrieveRemoteDocument(docPath);
    json j = d->getDocument();
    EXPECT_FALSE(j == nullptr);
    EXPECT_FALSE(j.is_null());
    EXPECT_EQ(4, j["pi"]);
}

TEST(DocumentLoaderTest, load_sample_document_from_cache) {
    std::unique_ptr<CurlLoadDocumentCallback> dl = std::make_unique<CurlLoadDocumentCallback>();
    dl->addDocumentToCache("foo.json", R"({ "pi": 3 })");

    auto d = dl->retrieveRemoteDocument("foo.json");
    EXPECT_EQ(3, d->getDocument()["pi"]);
}

TEST(DocumentLoaderTest, load_document_from_cache_miss) {
    std::unique_ptr<CurlLoadDocumentCallback> dl = std::make_unique<CurlLoadDocumentCallback>();
    dl->addDocumentToCache("foo.json", R"({ "pi": 3 })");

    EXPECT_THROW(dl->retrieveRemoteDocument("bar.json"), std::runtime_error);
}
