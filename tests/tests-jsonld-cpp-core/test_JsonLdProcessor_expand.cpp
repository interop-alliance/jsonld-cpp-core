#include <fstream>

#include "JsonLdProcessor.h"
#include "testHelpers.h"
#include "JsonLdProcessorTest.h"
#include "testConstants.h"
#include "CurlLoadDocumentCallback.h"

using nlohmann::json;

#ifndef _WIN32
#pragma clang diagnostic push
#pragma GCC diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma clang diagnostic pop
#pragma GCC diagnostic pop
#endif // !_WIN32

void performExpandTest(int testNumber, const std::string& testPrefix = jsonld::test::defaultExpandTestPrefix, const std::shared_ptr<JsonLdOptions>& options = std::make_shared<JsonLdOptions>()) {
    const std::string testNumberStr = getTestNumberStr(testNumber);
    const std::string testIdStr = testPrefix + testNumberStr;

    const std::string documentUri = getDocumentUri(jsonld::test::expandTestName, testNumberStr);
    const std::string inputStr = getInputJsonContent(jsonld::test::expandTestName, jsonld::test::expandTestDirectory, testIdStr);
    const json expected = getExpectedJson(jsonld::test::expandTestName, jsonld::test::expandTestDirectory, testIdStr);

    std::unique_ptr<ILoadDocumentCallback> dl = std::make_unique<CurlLoadDocumentCallback>();
    dl->addDocumentToCache(documentUri, inputStr);

    options->setDocumentLoader(dl);

    const json expanded = JsonLdProcessor::expand(documentUri, std::move(options));
    std::string expandedString = expanded.dump();

    EXPECT_TRUE(JsonLdUtils::deepCompare(expected, expanded));
}

/*TEST(JsonLdProcessorTest, expand_t0001) {
    performExpandTest(1);
}

TEST(JsonLdProcessorTest, expand_t0002) {
    performExpandTest(2);
}

TEST(JsonLdProcessorTest, expand_t0003) {
    performExpandTest(3);
}

TEST(JsonLdProcessorTest, expand_t0004) {
    performExpandTest(4);
}

TEST(JsonLdProcessorTest, expand_t0005) {
    performExpandTest(5);
}

TEST(JsonLdProcessorTest, expand_t0006) {
    performExpandTest(6);
}

TEST(JsonLdProcessorTest, expand_t0007) {
    performExpandTest(7);
}

TEST(JsonLdProcessorTest, expand_t0008) {
    performExpandTest(8);
}

TEST(JsonLdProcessorTest, expand_t0009) {
    performExpandTest(9);
}

TEST(JsonLdProcessorTest, expand_t0010) {
    performExpandTest(10);
}

TEST(JsonLdProcessorTest, expand_t0011) {
    performExpandTest(11);
}

TEST(JsonLdProcessorTest, expand_t0012) {
    performExpandTest(12);
}

TEST(JsonLdProcessorTest, expand_t0013) {
    performExpandTest(13);
}

TEST(JsonLdProcessorTest, expand_t0014) {
    performExpandTest(14);
}

TEST(JsonLdProcessorTest, expand_t0015) {
    performExpandTest(15);
}

TEST(JsonLdProcessorTest, expand_t0016) {
    performExpandTest(16);
}

TEST(JsonLdProcessorTest, expand_t0017) {
    performExpandTest(17);
}

TEST(JsonLdProcessorTest, expand_t0018) {
    performExpandTest(18);
}

TEST(JsonLdProcessorTest, expand_t0019) {
    performExpandTest(19);
}

TEST(JsonLdProcessorTest, expand_t0020) {
    performExpandTest(20);
}

TEST(JsonLdProcessorTest, expand_t0021) {
    performExpandTest(21);
}

TEST(JsonLdProcessorTest, expand_t0022) {
    performExpandTest(22);
}

TEST(JsonLdProcessorTest, expand_t0023) {
    performExpandTest(23);
}

TEST(JsonLdProcessorTest, expand_t0024) {
    performExpandTest(24);
}

TEST(JsonLdProcessorTest, expand_t0025) {
    performExpandTest(25);
}

TEST(JsonLdProcessorTest, expand_t0026) {
    performExpandTest(26);
}

TEST(JsonLdProcessorTest, expand_t0027) {
    performExpandTest(27);
}

TEST(JsonLdProcessorTest, expand_t0028) {
    performExpandTest(28);
}

TEST(JsonLdProcessorTest, expand_t0029) {
    performExpandTest(29);
}

TEST(JsonLdProcessorTest, expand_t0030) {
    performExpandTest(30);
}

TEST(JsonLdProcessorTest, expand_t0031) {
    performExpandTest(31);
}

TEST(JsonLdProcessorTest, expand_t0032) {
    performExpandTest(32);
}

TEST(JsonLdProcessorTest, expand_t0033) {
    performExpandTest(33);
}

TEST(JsonLdProcessorTest, expand_t0034) {
    performExpandTest(34);
}

TEST(JsonLdProcessorTest, expand_t0035) {
    performExpandTest(35);
}

TEST(JsonLdProcessorTest, expand_t0036) {
    performExpandTest(36);
}

TEST(JsonLdProcessorTest, expand_t0037) {
    performExpandTest(37);
}

TEST(JsonLdProcessorTest, expand_t0038) {
    performExpandTest(38);
}

TEST(JsonLdProcessorTest, expand_t0039) {
    performExpandTest(39);
}

TEST(JsonLdProcessorTest, expand_t0040) {
    performExpandTest(40);
}

TEST(JsonLdProcessorTest, expand_t0041) {
    performExpandTest(41);
}

TEST(JsonLdProcessorTest, expand_t0042) {
    performExpandTest(42);
}

TEST(JsonLdProcessorTest, expand_t0043) {
    performExpandTest(43);
}

TEST(JsonLdProcessorTest, expand_t0044) {
    performExpandTest(44);
}

TEST(JsonLdProcessorTest, expand_t0045) {
    performExpandTest(45);
}

TEST(JsonLdProcessorTest, expand_t0046) {
    performExpandTest(46);
}

TEST(JsonLdProcessorTest, expand_t0047) {
    performExpandTest(47);
}

TEST(JsonLdProcessorTest, expand_t0048) {
    performExpandTest(48);
}

TEST(JsonLdProcessorTest, expand_t0049) {
    performExpandTest(49);
}

TEST(JsonLdProcessorTest, expand_t0050) {
    performExpandTest(50);
}

TEST(JsonLdProcessorTest, expand_t0051) {
    performExpandTest(51);
}

TEST(JsonLdProcessorTest, expand_t0052) {
    performExpandTest(52);
}

TEST(JsonLdProcessorTest, expand_t0053) {
    performExpandTest(53);
}

TEST(JsonLdProcessorTest, expand_t0054) {
    performExpandTest(54);
}

TEST(JsonLdProcessorTest, expand_t0055) {
    performExpandTest(55);
}

TEST(JsonLdProcessorTest, expand_t0056) {
    performExpandTest(56);
}

TEST(JsonLdProcessorTest, expand_t0057) {
    performExpandTest(57);
}

TEST(JsonLdProcessorTest, expand_t0058) {
    performExpandTest(58);
}

TEST(JsonLdProcessorTest, expand_t0059) {
    performExpandTest(59);
}

TEST(JsonLdProcessorTest, expand_t0060) {
    performExpandTest(60);
}

TEST(JsonLdProcessorTest, expand_t0061) {
    performExpandTest(61);
}

TEST(JsonLdProcessorTest, expand_t0062) {
    performExpandTest(62);
}

TEST(JsonLdProcessorTest, expand_t0063) {
    performExpandTest(63);
}

TEST(JsonLdProcessorTest, expand_t0064) {
    performExpandTest(64);
}

TEST(JsonLdProcessorTest, expand_t0065) {
    performExpandTest(65);
}

TEST(JsonLdProcessorTest, expand_t0066) {
    performExpandTest(66);
}

TEST(JsonLdProcessorTest, expand_t0067) {
    performExpandTest(67);
}

TEST(JsonLdProcessorTest, expand_t0068) {
    performExpandTest(68);
}

TEST(JsonLdProcessorTest, expand_t0069) {
    performExpandTest(69);
}

TEST(JsonLdProcessorTest, expand_t0070) {
    performExpandTest(70);
}

TEST(JsonLdProcessorTest, expand_t0071) {
    performExpandTest(71);
}

TEST(JsonLdProcessorTest, expand_t0072) {
    performExpandTest(72);
}

TEST(JsonLdProcessorTest, expand_t0073) {
    performExpandTest(73);
}

TEST(JsonLdProcessorTest, expand_t0074) {
    performExpandTest(74);
}

TEST(JsonLdProcessorTest, expand_t0075) {
    performExpandTest(75);
}

TEST_F(JsonLdProcessorTestWithOptions, expand_t0076) {
    m_jsonLdOptions->setBase("http://example/base/");
    performExpandTest(76, jsonld::test::defaultExpandTestPrefix, m_jsonLdOptions);
}*/

// Disabled this test because we need to implement standard testing scaffold and the
// expandContext option
//TEST(JsonLdProcessorTest, expand_t0077) {
//    performExpandTest(77);
//}

/*TEST(JsonLdProcessorTest, expand_our0300) {
    // this is an extra test Dan added while trying to debug issues with normalize test 0008
    performExpandTest(300, jsonld::test::ourExpandTestPrefix);
}

TEST(JsonLdProcessorTest, expand_our0301) {
    // this is an extra test Dan added while trying to debug issues with normalize test 0020
    performExpandTest(301, jsonld::test::ourExpandTestPrefix);
}

TEST(JsonLdProcessorTest, expand_our0302) {
    // this is an extra test Dan added while trying to debug issues with normalize test 0044
    performExpandTest(302, jsonld::test::ourExpandTestPrefix);
}*/

TEST(JsonLdProcessorTest, expand_our0400) {
    // this is an extra test for testing remote context
    performExpandTest(400, jsonld::test::ourExpandTestPrefix);
}

//TEST(JsonLdProcessorTest, expand_our0401) {
//    // this is an extra test for testing nested context
//    performExpandTest(401, jsonld::test::ourExpandTestPrefix);
//}
