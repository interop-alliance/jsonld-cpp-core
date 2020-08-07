#include <fstream>
#include <gtest/gtest.h>

#include "JsonLdProcessor.h"
#include "testHelpers.h"
#include "JsonLdProcessorTest.h"
#include "testConstants.h"
#include "CurlLoadDocumentCallback.h"

#ifndef _WIN32
#pragma clang diagnostic push
#pragma GCC diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma clang diagnostic pop
#pragma GCC diagnostic pop
#endif

void performNormalizeTest(int testNumber, const std::string& testPrefix = jsonld::test::defaultExpandTestPrefix, const std::shared_ptr<JsonLdOptions>& options = std::make_shared<JsonLdOptions>()) {
    const std::string testNumberStr = getTestNumberStr(testNumber);
    const std::string testIdStr = testPrefix + testNumberStr;

    const std::string documentUri = getDocumentUri(jsonld::test::normalizeTestName, testNumberStr);
    const std::string inputJsonContentStr = getInputJsonContent(jsonld::test::normalizeTestName, jsonld::test::normalizeTestDirectory, testIdStr);
    const std::string expected = getExpectedRDF(jsonld::test::normalizeTestName, jsonld::test::normalizeTestDirectory, testIdStr);

    std::unique_ptr<ILoadDocumentCallback> dl = std::make_unique<CurlLoadDocumentCallback>();
    dl->addDocumentToCache(documentUri, inputJsonContentStr);

    options->setDocumentLoader(dl);

    const std::string str = JsonLdProcessor::normalize(documentUri, std::move(options));

    EXPECT_EQ(expected, str);
}

TEST(JsonLdProcessorTest, normalize_t0001) {
    performNormalizeTest(1);
}

TEST(JsonLdProcessorTest, normalize_t0002) {
    performNormalizeTest(2);
}

TEST(JsonLdProcessorTest, normalize_t0003) {
    performNormalizeTest(3);
}

TEST(JsonLdProcessorTest, normalize_t0004) {
    performNormalizeTest(4);
}

TEST(JsonLdProcessorTest, normalize_t0005) {
    performNormalizeTest(5);
}

TEST(JsonLdProcessorTest, normalize_t0006) {
    performNormalizeTest(6);
}

TEST(JsonLdProcessorTest, normalize_t0007) {
    performNormalizeTest(7);
}

TEST(JsonLdProcessorTest, normalize_t0008) {
    performNormalizeTest(8);
}

TEST(JsonLdProcessorTest, normalize_t0009) {
    performNormalizeTest(9);
}

TEST(JsonLdProcessorTest, normalize_t0010) {
    performNormalizeTest(10);
}

TEST(JsonLdProcessorTest, normalize_t0011) {
    performNormalizeTest(11);
}

TEST(JsonLdProcessorTest, normalize_t0012) {
    performNormalizeTest(12);
}

TEST(JsonLdProcessorTest, normalize_t0013) {
    performNormalizeTest(13);
}

TEST(JsonLdProcessorTest, normalize_t0014) {
    performNormalizeTest(14);
}

TEST(JsonLdProcessorTest, normalize_t0015) {
    performNormalizeTest(15);
}

TEST(JsonLdProcessorTest, normalize_t0016) {
    performNormalizeTest(16);
}

TEST(JsonLdProcessorTest, normalize_t0017) {
    performNormalizeTest(17);
}

TEST(JsonLdProcessorTest, normalize_t0018) {
    performNormalizeTest(18);
}

TEST(JsonLdProcessorTest, normalize_t0019) {
    performNormalizeTest(19);
}

TEST(JsonLdProcessorTest, normalize_t0020) {
    performNormalizeTest(20);
}

TEST(JsonLdProcessorTest, normalize_t0021) {
    performNormalizeTest(21);
}

TEST(JsonLdProcessorTest, normalize_t0022) {
    performNormalizeTest(22);
}

TEST(JsonLdProcessorTest, normalize_t0023) {
    performNormalizeTest(23);
}

TEST(JsonLdProcessorTest, normalize_t0024) {
    performNormalizeTest(24);
}

TEST(JsonLdProcessorTest, normalize_t0025) {
    performNormalizeTest(25);
}

TEST(JsonLdProcessorTest, normalize_t0026) {
    performNormalizeTest(26);
}

TEST(JsonLdProcessorTest, normalize_t0027) {
    performNormalizeTest(27);
}

TEST(JsonLdProcessorTest, normalize_t0028) {
    performNormalizeTest(28);
}

TEST(JsonLdProcessorTest, normalize_t0029) {
    performNormalizeTest(29);
}

TEST(JsonLdProcessorTest, normalize_t0030) {
    performNormalizeTest(30);
}

TEST(JsonLdProcessorTest, normalize_t0031) {
    performNormalizeTest(31);
}

TEST(JsonLdProcessorTest, normalize_t0032) {
    performNormalizeTest(32);
}

TEST(JsonLdProcessorTest, normalize_t0033) {
    performNormalizeTest(33);
}

TEST(JsonLdProcessorTest, normalize_t0034) {
    performNormalizeTest(34);
}

TEST(JsonLdProcessorTest, normalize_t0035) {
    performNormalizeTest(35);
}

TEST(JsonLdProcessorTest, normalize_t0036) {
    performNormalizeTest(36);
}

TEST(JsonLdProcessorTest, normalize_t0037) {
    performNormalizeTest(37);
}

TEST(JsonLdProcessorTest, normalize_t0038) {
    performNormalizeTest(38);
}

TEST(JsonLdProcessorTest, normalize_t0039) {
    performNormalizeTest(39);
}

TEST(JsonLdProcessorTest, normalize_t0040) {
    performNormalizeTest(40);
}

TEST(JsonLdProcessorTest, normalize_t0041) {
    performNormalizeTest(41);
}

TEST(JsonLdProcessorTest, normalize_t0042) {
    performNormalizeTest(42);
}

TEST(JsonLdProcessorTest, normalize_t0043) {
    performNormalizeTest(43);
}

TEST(JsonLdProcessorTest, normalize_t0044) {
    performNormalizeTest(44);
}

TEST(JsonLdProcessorTest, normalize_t0045) {
    performNormalizeTest(45);
}

TEST(JsonLdProcessorTest, normalize_t0046) {
    performNormalizeTest(46);
}

TEST(JsonLdProcessorTest, normalize_t0047) {
    performNormalizeTest(47);
}

TEST(JsonLdProcessorTest, normalize_t0048) {
    performNormalizeTest(48);
}

TEST(JsonLdProcessorTest, normalize_t0049) {
    performNormalizeTest(49);
}

TEST(JsonLdProcessorTest, normalize_t0050) {
    performNormalizeTest(50);
}

TEST(JsonLdProcessorTest, normalize_t0051) {
    performNormalizeTest(51);
}

TEST(JsonLdProcessorTest, normalize_t0052) {
    performNormalizeTest(52);
}

TEST(JsonLdProcessorTest, normalize_t0053) {
    performNormalizeTest(53);
}

TEST(JsonLdProcessorTest, normalize_t0054) {
    performNormalizeTest(54);
}

TEST(JsonLdProcessorTest, normalize_t0055) {
    performNormalizeTest(55);
}

TEST(JsonLdProcessorTest, normalize_t0056) {
    performNormalizeTest(56);
}

TEST(JsonLdProcessorTest, normalize_t0057) {
    performNormalizeTest(57);
}
