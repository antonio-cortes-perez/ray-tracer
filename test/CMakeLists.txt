include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(TupleTest TupleTest.cpp)
target_link_libraries(TupleTest GTest::gtest_main)

add_executable(ColorTest ColorTest.cpp)
target_link_libraries(ColorTest GTest::gtest_main)

add_executable(CanvasTest CanvasTest.cpp)
target_link_libraries(CanvasTest GTest::gtest_main Canvas)

include(GoogleTest)
gtest_discover_tests(TupleTest)
gtest_discover_tests(ColorTest)
gtest_discover_tests(CanvasTest)