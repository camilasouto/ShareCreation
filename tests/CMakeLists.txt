cmake_minimum_required(VERSION 3.10)
project(npu_backend_tests)

# Enable testing
enable_testing()

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Include directories
include_directories(../npu_backend)

# Add the source files
set(SOURCE_FILES
    ../npu_backend/AuthorizationModule.cpp
    ../npu_backend/CreationController.cpp
    ../npu_backend/FanItem.cpp
    ../npu_backend/CreationItem.cpp
    ../npu_backend/LoginController.cpp
)

# Add the test files
set(TEST_FILES
    ../tests/main.cpp
    ../tests/AuthorizationModuleTest.cpp
    ../tests/CreationControllerTest.cpp
    ../tests/FanItemTest.cpp
)

# Create the test executable
add_executable(runTests ${SOURCE_FILES} ${TEST_FILES})

# Link the test executable with Google Test
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

# Add a test
add_test(NAME runTests COMMAND runTests)
