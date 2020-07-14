if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
    file(GLOB LIB_CURL ${PROJECT_SOURCE_DIR}/3rdparty/curl-7.71.1/build/linux/libcurl.so.4)
elseif(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    file(GLOB LIB_CURL ${PROJECT_SOURCE_DIR}/3rdparty/curl-7.71.1/build/mac/libcurl.a)
    file(GLOB LIB_SSL ${PROJECT_SOURCE_DIR}/3rdparty/curl-7.71.1/build/mac/libssl.a)
    file(GLOB LIB_CRYPTO ${PROJECT_SOURCE_DIR}/3rdparty/curl-7.71.1/build/mac/libcrypto.a)
endif()

add_executable(UnitTests_jsonld-cpp-core main.cpp test_IriUtils.cpp test_JsonLdApi.cpp test_JsonLdUtils.cpp test_DocumentLoader.cpp testHelpers.cpp testHelpers.h test_NodeComparisons.cpp test_ObjectComparisons.cpp test_UniqueNamer.cpp test_DoubleFormatter.cpp test_Permutator.cpp test_NormalizeUtils.cpp test_Sha1.cpp)

target_compile_features(UnitTests_jsonld-cpp-core PRIVATE cxx_std_17)
target_compile_options(UnitTests_jsonld-cpp-core PRIVATE ${DCD_CXX_FLAGS})
set_target_properties(UnitTests_jsonld-cpp-core PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(UnitTests_jsonld-cpp-core
        PUBLIC
        ${PROJECT_SOURCE_DIR}/jsonld-cpp-core)

target_link_libraries(UnitTests_jsonld-cpp-core jsonld-cpp-core gtest gmock rapidcheck_gtest ${LINKAGE_OPTIONS})

add_test(NAME UnitTests_jsonld-cpp-core COMMAND UnitTests_jsonld-cpp-core)

####

add_executable(UnitTests_JsonLdProcessor_expand_jsonld-cpp-core main.cpp test_JsonLdProcessor_expand.cpp testHelpers.cpp testHelpers.h)

target_compile_features(UnitTests_JsonLdProcessor_expand_jsonld-cpp-core PRIVATE cxx_std_17)
target_compile_options(UnitTests_JsonLdProcessor_expand_jsonld-cpp-core PRIVATE ${DCD_CXX_FLAGS})
set_target_properties(UnitTests_JsonLdProcessor_expand_jsonld-cpp-core PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(UnitTests_JsonLdProcessor_expand_jsonld-cpp-core
        PUBLIC
        ${PROJECT_SOURCE_DIR}/jsonld-cpp-core)

target_link_libraries(UnitTests_JsonLdProcessor_expand_jsonld-cpp-core jsonld-cpp-core gtest gmock rapidcheck_gtest ${LIB_SSL} ${LIB_CRYPTO} ${LIB_CURL} ${LINKAGE_OPTIONS})

add_test(NAME UnitTests_JsonLdProcessor_expand_jsonld-cpp-core
        COMMAND UnitTests_JsonLdProcessor_expand_jsonld-cpp-core)

####

add_executable(UnitTests_JsonLdProcessor_toRdf_jsonld-cpp-core main.cpp test_JsonLdProcessor_toRDF.cpp testHelpers.cpp testHelpers.h)

target_compile_features(UnitTests_JsonLdProcessor_toRdf_jsonld-cpp-core PRIVATE cxx_std_17)
target_compile_options(UnitTests_JsonLdProcessor_toRdf_jsonld-cpp-core PRIVATE ${DCD_CXX_FLAGS})
set_target_properties(UnitTests_JsonLdProcessor_toRdf_jsonld-cpp-core PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(UnitTests_JsonLdProcessor_toRdf_jsonld-cpp-core
        PUBLIC
        ${PROJECT_SOURCE_DIR}/jsonld-cpp-core)

target_link_libraries(UnitTests_JsonLdProcessor_toRdf_jsonld-cpp-core jsonld-cpp-core gtest gmock ${LINKAGE_OPTIONS})

add_test(NAME UnitTests_JsonLdProcessor_toRdf_jsonld-cpp COMMAND UnitTests_JsonLdProcessor_toRdf_jsonld-cpp-core)

####

add_executable(UnitTests_JsonLdProcessor_normalize_jsonld-cpp-core main.cpp test_JsonLdProcessor_normalize.cpp testHelpers.cpp testHelpers.h)

target_compile_features(UnitTests_JsonLdProcessor_normalize_jsonld-cpp-core PRIVATE cxx_std_17)
target_compile_options(UnitTests_JsonLdProcessor_normalize_jsonld-cpp-core PRIVATE ${DCD_CXX_FLAGS})
set_target_properties(UnitTests_JsonLdProcessor_normalize_jsonld-cpp-core PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(UnitTests_JsonLdProcessor_normalize_jsonld-cpp-core
        PUBLIC
        ${PROJECT_SOURCE_DIR}/jsonld-cpp-core)

target_link_libraries(UnitTests_JsonLdProcessor_normalize_jsonld-cpp-core jsonld-cpp-core gtest gmock ${LINKAGE_OPTIONS})

add_test(NAME UnitTests_JsonLdProcessor_normalize_jsonld-cpp-core COMMAND UnitTests_JsonLdProcessor_normalize_jsonld-cpp-core)

####

file(COPY ${PROJECT_SOURCE_DIR}/tests/tests-jsonld-cpp-core/test_data DESTINATION ${CMAKE_BINARY_DIR})
