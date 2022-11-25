# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.10.2)

# Set the project name
project(xml_parser VERSION 0.1.0)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/XmlParser.cpp
    tests/ParserTest.cpp
)

# Find the Apache Xerces-C++ validating XML parser headers and libraries.
find_package(XercesC REQUIRED)
if(XercesC_FOUND)
    message("Xerces found. Version: " ${XercesC_VERSION})
    message("Directory containing the Xerces headers: " ${XercesC_INCLUDE_DIRS})
    message("Xerces libraries to be linked: " ${XercesC_LIBRARIES})
else()
    message (FATAL_ERROR "Cannot find Boost")
endif()

# Locate the Google C++ Testing Framework.
enable_testing()
find_package(GTest REQUIRED)
if(GTest_FOUND)
    message("\nGTest found. Version: ")
    message("Directory containing the GTest headers: " ${GTEST_INCLUDE_DIRS})
    message("GTest libraries to be linked: " ${GTEST_BOTH_LIBRARIES})
else()
    message (FATAL_ERROR "Cannot find GTest")
endif()

find_package(Threads REQUIRED)
if(Threads_FOUND)
    message("\nThe thread library to use: " ${CMAKE_THREAD_LIBS_INIT})
else()
    message (FATAL_ERROR "Cannot find Threads library")
endif()

# Add an executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Set the directories that should be included in the build command for this target. When running g++ these will be included as -I/directory/path/
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
    ${XercesC_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
)

# Link against 3p libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${XercesC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTEST_BOTH_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_THREAD_LIBS_INIT})

# add_test(AllTests ${PROJECT_NAME})

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
