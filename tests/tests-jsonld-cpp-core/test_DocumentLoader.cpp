#include "DocumentLoader.cpp"
#include "testHelpers.h"

#include <gtest/gtest.h>

#ifndef _WIN32
#pragma clang diagnostic push
#pragma GCC diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma clang diagnostic pop
#pragma GCC diagnostic pop
#endif

namespace
{
#ifdef _WIN32
    const std::string sampleDocumentPath = "tests\\tests-jsonld-cpp-core\\test_data\\pi-is-four.json";
#else
    const std::string sampleDocumentPath = "test_data/pi-is-four.json";
#endif
}

TEST(DocumentLoaderTest, load_sample_document_from_filesystem) {
    DocumentLoader dl;

    std::string docPath = resolvePath(sampleDocumentPath);

    RemoteDocument d = dl.loadDocument(docPath);
    json j = d.getDocument();
    EXPECT_FALSE(j == nullptr);
    EXPECT_FALSE(j.is_null());
    EXPECT_EQ(4, j["pi"]);
}

TEST(DocumentLoaderTest, load_sample_document_from_cache) {
    DocumentLoader dl;
    dl.addDocumentToCache("foo.json", R"({ "pi": 3 })");

    RemoteDocument d = dl.loadDocument("foo.json");
    EXPECT_EQ(3, d.getDocument()["pi"]);
}

TEST(DocumentLoaderTest, load_document_from_cache_miss) {
    DocumentLoader dl;
    dl.addDocumentToCache("foo.json", R"({ "pi": 3 })");

    EXPECT_THROW(dl.loadDocument("bar.json"), std::runtime_error);
}



