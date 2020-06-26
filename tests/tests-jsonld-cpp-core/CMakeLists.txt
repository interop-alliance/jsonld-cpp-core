add_executable(UnitTests_jsonld-cpp-core main.cpp test_IriUtils.cpp)

target_compile_features(UnitTests_jsonld-cpp-core PRIVATE cxx_std_11)
target_compile_options(UnitTests_jsonld-cpp-core PRIVATE ${DCD_CXX_FLAGS})
set_target_properties(UnitTests_jsonld-cpp-core PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(UnitTests_jsonld-cpp-core
        PUBLIC
        ${PROJECT_SOURCE_DIR}/jsonld-cpp-core)

target_link_libraries(UnitTests_jsonld-cpp-core jsonld-cpp-core gtest gmock rapidcheck_gtest)

add_test(NAME UnitTests_jsonld-cpp-core COMMAND UnitTests_jsonld-cpp-core)
