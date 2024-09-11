
set(TEST "sum-T")
add_executable(${TEST} sum-T.cpp)
target_link_libraries(${TEST} PRIVATE ${LIBRARY} GTest::gtest_main)
gtest_discover_tests(${TEST})

set(TEST "rubiks_cube-T")
add_executable(${TEST} rubiks_cube-T.cpp)
target_link_libraries(${TEST} PRIVATE ${LIBRARY} GTest::gtest_main)
gtest_discover_tests(${TEST})
