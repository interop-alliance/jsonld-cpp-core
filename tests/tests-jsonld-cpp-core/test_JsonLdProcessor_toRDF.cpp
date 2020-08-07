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

void performToRDFTest(int testNumber, const std::string& testPrefix = jsonld::test::defaultExpandTestPrefix, const std::shared_ptr<JsonLdOptions>& options = std::make_shared<JsonLdOptions>()) {

    const std::string testNumberStr = getTestNumberStr(testNumber);
    const std::string testIdStr = testPrefix + testNumberStr;

    const std::string documentUri = getDocumentUri(jsonld::test::toRDFTestName, testNumberStr);
    const std::string inputStr = getInputJsonContent(jsonld::test::toRDFTestName, jsonld::test::toRDFTestDirectory, testIdStr);
    const std::string expected = getExpectedRDF(jsonld::test::toRDFTestName, jsonld::test::toRDFTestDirectory, testIdStr);

    std::unique_ptr<ILoadDocumentCallback> dl = std::make_unique<CurlLoadDocumentCallback>();
    dl->addDocumentToCache(documentUri, inputStr);

    options->setDocumentLoader(dl);

    const std::string str = JsonLdProcessor::toRDFString(documentUri, std::move(options));
    EXPECT_EQ(expected, str);
}

TEST(JsonLdProcessorTest, toRDF_t0001) {
    performToRDFTest(1);
}

TEST(JsonLdProcessorTest, toRDF_t0002) {
    performToRDFTest(2);
}

TEST(JsonLdProcessorTest, toRDF_t0003) {
    performToRDFTest(3);
}

TEST(JsonLdProcessorTest, toRDF_t0004) {
    performToRDFTest(4);
}

// skip until I have better utf8 char handling
//TEST(JsonLdProcessorTest, toRDF_0005) {
//    performToRDFTest(5);
//}

TEST(JsonLdProcessorTest, toRDF_t0006) {
    performToRDFTest(6);
}

TEST(JsonLdProcessorTest, toRDF_t0007) {
    performToRDFTest(7);
}

TEST(JsonLdProcessorTest, toRDF_t0008) {
    performToRDFTest(8);
}

TEST(JsonLdProcessorTest, toRDF_t0009) {
    performToRDFTest(9);
}

TEST(JsonLdProcessorTest, toRDF_t0010) {
    performToRDFTest(10);
}

TEST(JsonLdProcessorTest, toRDF_t0011) {
    performToRDFTest(11);
}

TEST(JsonLdProcessorTest, toRDF_t0012) {
    performToRDFTest(12);
}

TEST(JsonLdProcessorTest, toRDF_t0013) {
    performToRDFTest(13);
}

TEST(JsonLdProcessorTest, toRDF_t0014) {
    performToRDFTest(14);
}

TEST(JsonLdProcessorTest, toRDF_t0015) {
    performToRDFTest(15);
}

TEST(JsonLdProcessorTest, toRDF_t0016) {
    performToRDFTest(16);
}

TEST(JsonLdProcessorTest, toRDF_t0017) {
    performToRDFTest(17);
}

TEST(JsonLdProcessorTest, toRDF_t0018) {
    performToRDFTest(18);
}

TEST(JsonLdProcessorTest, toRDF_t0019) {
    performToRDFTest(19);
}

TEST(JsonLdProcessorTest, toRDF_t0020) {
    performToRDFTest(20);
}

// case 21 doesn't exist

TEST(JsonLdProcessorTest, toRDF_t0022) {
    performToRDFTest(22);
}

TEST(JsonLdProcessorTest, toRDF_t0023) {
    performToRDFTest(23);
}

TEST(JsonLdProcessorTest, toRDF_t0024) {
    performToRDFTest(24);
}

TEST(JsonLdProcessorTest, toRDF_t0025) {
    performToRDFTest(25);
}

TEST(JsonLdProcessorTest, toRDF_t0026) {
    performToRDFTest(26);
}

TEST(JsonLdProcessorTest, toRDF_t0027) {
    performToRDFTest(27);
}

TEST(JsonLdProcessorTest, toRDF_t0028) {
    performToRDFTest(28);
}

TEST(JsonLdProcessorTest, toRDF_t0029) {
    performToRDFTest(29);
}

TEST(JsonLdProcessorTest, toRDF_t0030) {
    performToRDFTest(30);
}

TEST(JsonLdProcessorTest, toRDF_t0031) {
    performToRDFTest(31);
}

TEST(JsonLdProcessorTest, toRDF_t0032) {
    performToRDFTest(32);
}

TEST(JsonLdProcessorTest, toRDF_t0033) {
    performToRDFTest(33);
}

TEST(JsonLdProcessorTest, toRDF_t0034) {
    performToRDFTest(34);
}

TEST(JsonLdProcessorTest, toRDF_t0035) {
    performToRDFTest(35);
}

TEST(JsonLdProcessorTest, toRDF_t0036) {
    performToRDFTest(36);
}

// cases 37-40 don't exist

TEST(JsonLdProcessorTest, toRDF_t0041) {
    performToRDFTest(41);
}

TEST(JsonLdProcessorTest, toRDF_t0042) {
    performToRDFTest(42);
}

TEST(JsonLdProcessorTest, toRDF_t0043) {
    performToRDFTest(43);
}

TEST(JsonLdProcessorTest, toRDF_t0044) {
    performToRDFTest(44);
}

TEST(JsonLdProcessorTest, toRDF_t0045) {
    performToRDFTest(45);
}

TEST(JsonLdProcessorTest, toRDF_t0046) {
    performToRDFTest(46);
}

TEST(JsonLdProcessorTest, toRDF_t0047) {
    performToRDFTest(47);
}

TEST(JsonLdProcessorTest, toRDF_t0048) {
    performToRDFTest(48);
}

TEST(JsonLdProcessorTest, toRDF_t0049) {
    performToRDFTest(49);
}

TEST(JsonLdProcessorTest, toRDF_t0050) {
    performToRDFTest(50);
}

TEST(JsonLdProcessorTest, toRDF_t0051) {
    performToRDFTest(51);
}

TEST(JsonLdProcessorTest, toRDF_t0052) {
    performToRDFTest(52);
}

TEST(JsonLdProcessorTest, toRDF_t0053) {
    performToRDFTest(53);
}

TEST(JsonLdProcessorTest, toRDF_t0054) {
    performToRDFTest(54);
}

TEST(JsonLdProcessorTest, toRDF_t0055) {
    performToRDFTest(55);
}

TEST(JsonLdProcessorTest, toRDF_t0056) {
    performToRDFTest(56);
}

TEST(JsonLdProcessorTest, toRDF_t0057) {
    performToRDFTest(57);
}

TEST(JsonLdProcessorTest, toRDF_t0058) {
    performToRDFTest(58);
}

TEST(JsonLdProcessorTest, toRDF_t0059) {
    performToRDFTest(59);
}

TEST(JsonLdProcessorTest, toRDF_t0060) {
    performToRDFTest(60);
}

TEST(JsonLdProcessorTest, toRDF_t0061) {
    performToRDFTest(61);
}

TEST(JsonLdProcessorTest, toRDF_t0062) {
    performToRDFTest(62);
}

TEST(JsonLdProcessorTest, toRDF_t0063) {
    performToRDFTest(63);
}

TEST(JsonLdProcessorTest, toRDF_t0064) {
    performToRDFTest(64);
}

TEST(JsonLdProcessorTest, toRDF_t0065) {
    performToRDFTest(65);
}

TEST(JsonLdProcessorTest, toRDF_t0066) {
    performToRDFTest(66);
}

TEST(JsonLdProcessorTest, toRDF_t0067) {
    performToRDFTest(67);
}

TEST(JsonLdProcessorTest, toRDF_t0068) {
    performToRDFTest(68);
}

TEST(JsonLdProcessorTest, toRDF_t0069) {
    performToRDFTest(69);
}

// skip until I have better utf8 char handling
//TEST(JsonLdProcessorTest, toRDF_0070) {
//    performToRDFTest(70);
//}

TEST(JsonLdProcessorTest, toRDF_t0071) {
    performToRDFTest(71);
}

TEST(JsonLdProcessorTest, toRDF_t0072) {
    performToRDFTest(72);
}

TEST(JsonLdProcessorTest, toRDF_t0073) {
    performToRDFTest(73);
}

TEST(JsonLdProcessorTest, toRDF_t0074) {
    performToRDFTest(74);
}

// skip until I have better utf8 char handling
//TEST(JsonLdProcessorTest, toRDF_0075) {
//    performToRDFTest(75);
//}

TEST(JsonLdProcessorTest, toRdf_t0076) {
    performToRDFTest(76);
}

TEST(JsonLdProcessorTest, toRdf_t0077) {
    performToRDFTest(77);
}

TEST(JsonLdProcessorTest, toRdf_t0078) {
    performToRDFTest(78);
}

TEST(JsonLdProcessorTest, toRdf_t0079) {
    performToRDFTest(79);
}

TEST(JsonLdProcessorTest, toRdf_t0080) {
    performToRDFTest(80);
}

TEST(JsonLdProcessorTest, toRdf_t0081) {
    performToRDFTest(81);
}

TEST(JsonLdProcessorTest, toRdf_t0082) {
    performToRDFTest(82);
}

TEST(JsonLdProcessorTest, toRdf_t0083) {
    performToRDFTest(83);
}

TEST(JsonLdProcessorTest, toRdf_t0084) {
    performToRDFTest(84);
}

TEST(JsonLdProcessorTest, toRdf_t0085) {
    performToRDFTest(85);
}

TEST(JsonLdProcessorTest, toRdf_t0086) {
    performToRDFTest(86);
}

TEST(JsonLdProcessorTest, toRdf_t0087) {
    performToRDFTest(87);
}

TEST(JsonLdProcessorTest, toRdf_t0088) {
    performToRDFTest(88);
}

TEST(JsonLdProcessorTest, toRdf_t0089) {
    performToRDFTest(89);
}

TEST(JsonLdProcessorTest, toRdf_t0090) {
    performToRDFTest(90);
}

TEST(JsonLdProcessorTest, toRdf_t0091) {
    performToRDFTest(91);
}

TEST(JsonLdProcessorTest, toRdf_t0092) {
    performToRDFTest(92);
}

TEST(JsonLdProcessorTest, toRdf_t0093) {
    performToRDFTest(93);
}

TEST(JsonLdProcessorTest, toRdf_0094) {
    performToRDFTest(94);
}

TEST(JsonLdProcessorTest, toRdf_t0095) {
    performToRDFTest(95);
}

TEST(JsonLdProcessorTest, toRdf_t0096) {
    performToRDFTest(96);
}

TEST(JsonLdProcessorTest, toRdf_t0097) {
    performToRDFTest(97);
}

TEST(JsonLdProcessorTest, toRdf_t0098) {
    performToRDFTest(98);
}

TEST(JsonLdProcessorTest, toRdf_t0099) {
    performToRDFTest(99);
}

TEST(JsonLdProcessorTest, toRdf_t0100) {
    performToRDFTest(100);
}

TEST(JsonLdProcessorTest, toRdf_t0101) {
    performToRDFTest(101);
}

TEST(JsonLdProcessorTest, toRdf_t0102) {
    performToRDFTest(102);
}

TEST(JsonLdProcessorTest, toRdf_t0103) {
    performToRDFTest(103);
}

TEST(JsonLdProcessorTest, toRdf_t0104) {
    performToRDFTest(104);
}

TEST(JsonLdProcessorTest, toRdf_t0105) {
    performToRDFTest(105);
}

TEST(JsonLdProcessorTest, toRdf_t0106) {
    performToRDFTest(106);
}

TEST(JsonLdProcessorTest, toRdf_t0107) {
    performToRDFTest(107);
}

TEST(JsonLdProcessorTest, toRdf_t0108) {
    performToRDFTest(108);
}

TEST(JsonLdProcessorTest, toRdf_t0109) {
    performToRDFTest(109);
}

TEST(JsonLdProcessorTest, toRdf_t0110) {
    performToRDFTest(110);
}

TEST(JsonLdProcessorTest, toRdf_t0111) {
    performToRDFTest(111);
}

TEST(JsonLdProcessorTest, toRdf_t0112) {
    performToRDFTest(112);
}

TEST(JsonLdProcessorTest, toRdf_t0113) {
    performToRDFTest(113);
}

TEST(JsonLdProcessorTest, toRdf_t0114) {
    performToRDFTest(114);
}

TEST(JsonLdProcessorTest, toRdf_t0115) {
    performToRDFTest(115);
}

TEST(JsonLdProcessorTest, toRdf_t0116) {
    performToRDFTest(116);
}

TEST(JsonLdProcessorTest, toRdf_t0117) {
    performToRDFTest(117);
}

//
//TEST(JsonLdProcessorTest, toRdf_0118) {
//    performToRDFTest(118);
//}

TEST(JsonLdProcessorTest, toRdf_t0119) {
    performToRDFTest(119);
}

//TEST(JsonLdProcessorTest, toRdf_loop) {
//
//    for(auto i = 1; i <= 119; ++i) {
//        switch(i) {
//            case 5:  // skip until I have better utf8 char handling
//            case 21: // doesn't exist
//            case 37: // doesn't exist
//            case 38: // doesn't exist
//            case 39: // doesn't exist
//            case 40: // doesn't exist
//            case 70: // skip until I have better utf8 char handling
//            case 75: // skip until I have better utf8 char handling
//            case 118:// skip until I have generalized RDF flag implemented
//                continue;
//            default:
//                performToRDFTest(i);
//        }
//    }
//}

TEST(JsonLdProcessorTest, toRdf_our0300) {
    // this is an extra test Dan added while trying to debug issues with normalize test 0008
    performToRDFTest(300, jsonld::test::ourExpandTestPrefix);
}

TEST(JsonLdProcessorTest, toRdf_our0301) {
    // this is an extra test Dan added while trying to debug issues with normalize test 0020
    performToRDFTest(301, jsonld::test::ourExpandTestPrefix);
}

TEST(JsonLdProcessorTest, toRdf_our0302) {
    // this is an extra test Dan added while trying to debug issues with normalize test 0044
    performToRDFTest(302, jsonld::test::ourExpandTestPrefix);
}

