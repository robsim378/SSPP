find_package(Catch2 3 REQUIRED)

add_executable(tests Test.cpp ../src/ProcessingUnit1.cpp ../src/ProcessingUnit2.cpp ../src/ProcessingUnit3.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE ../include)
