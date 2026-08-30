add_executable(utilsTest ./utilsTest.cpp)
add_test(NAME utils_Test COMMAND $<TARGET_FILE:utilsTest>)
target_link_libraries(utilsTest PRIVATE tutorial_lib)
