message(STATUS "CMake version ${CMAKE_VERSION}")

# -----------------------------------------------------------------------------
# Modules
# -----------------------------------------------------------------------------

include(CTest)
include(CodeTools)
include(GenerateExportHeader)
include(GNUInstallDirs)

# -----------------------------------------------------------------------------
# Directories
# -----------------------------------------------------------------------------

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(BUILD_INC_DIR ${CMAKE_BINARY_DIR}/inc)
set(TEST_OUTPUT_DIR ${CMAKE_BINARY_DIR}/test_output)

file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${BUILD_INC_DIR})
file(MAKE_DIRECTORY ${TEST_OUTPUT_DIR})

# -----------------------------------------------------------------------------
# Dependencies
# -----------------------------------------------------------------------------

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 5.12 COMPONENTS Widgets Core Gui PrintSupport REQUIRED)
find_package(Threads)

get_target_property(Qt5Widgets_location Qt5::Widgets LOCATION_Release)
message(STATUS " Qt5 libraries : ${Qt5Widgets_LIBRARIES} ${Qt5Widgets_location}")
message(STATUS " Qt5 Includes  : ${Qt5Widgets_INCLUDE_DIRS}")

# -----------------------------------------------------------------------------
# Generating config files
# -----------------------------------------------------------------------------

configure_file(${CMAKE_SOURCE_DIR}/cmake/scripts/testconfig.h.in  ${BUILD_INC_DIR}/testconfig.h @ONLY)
add_definitions(-I${BUILD_INC_DIR})

if (MVVM_BUMP_VERSION)
    configure_file(${CMAKE_SOURCE_DIR}/cmake/scripts/mvvm_version.h.in  ${CMAKE_SOURCE_DIR}/source/libmvvm_model/mvvm/core/version.h @ONLY)
endif()

# -----------------------------------------------------------------------------
# Compile options
# -----------------------------------------------------------------------------

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
