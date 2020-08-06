############################################################
# Target: libjsonld-cpp-core

add_library(jsonld-cpp-core STATIC
        IriUtils.cpp
        sha1.cpp
        JsonLdProcessor.cpp
        JsonLdUrl.cpp
        JsonLdOptions.cpp
        JsonLdError.cpp
        JsonLdApi.cpp
        RDFDataset.cpp
        JsonLdUtils.cpp
        RDFDatasetUtils.cpp
        DoubleFormatter.cpp
        ObjUtils.cpp
        NormalizeUtils.cpp
        Permutator.cpp
        Context.cpp
        UniqueNamer.cpp
        RemoteDocument.cpp
        network/CurlLoadDocumentCallback.cpp
        network/curl/impl/CurlHttpRequest.cpp)

target_include_directories(jsonld-cpp-core
        PUBLIC
            $<INSTALL_INTERFACE:include/libjsonld-cpp-core>
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include;${CMAKE_CURRENT_SOURCE_DIR}/../jsonld-cpp-core/network;${CMAKE_CURRENT_SOURCE_DIR}/../jsonld-cpp-core;${CMAKE_CURRENT_SOURCE_DIR}/../jsonld-cpp-core/network/curl/impl;${CMAKE_CURRENT_SOURCE_DIR}/../jsonld-cpp-core/network/curl>;${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/curl-7.71.1/include"
)

target_compile_features(jsonld-cpp-core PRIVATE cxx_std_17)
target_compile_options(jsonld-cpp-core PRIVATE ${DCD_CXX_FLAGS})
set_target_properties(jsonld-cpp-core PROPERTIES CXX_EXTENSIONS OFF)

install (TARGETS jsonld-cpp-core DESTINATION lib)
