cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(CppDebugger VERSION 1.0.0 DESCRIPTION "Simple library used for debugging C++-code")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define all include directories
# SET(INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/lib")

# Load the libraries
# add_subdirectory(src)



##### CPPDEBUGGER TARGET #####
# Specify which file will compile to the library
add_library(cppdbg SHARED ${PROJECT_SOURCE_DIR}/src/CppDebugger.cpp)
# Set some version numbering & the public header properties
set_target_properties(cppdbg PROPERTIES
                      VERSION ${PROJECT_VERSION}
                      SOVERSION 1
                      PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/src/CppDebugger.hpp)

# Get some file locations
include(GNUInstallDirs)

# Configure the pc file, so that GNU systems may easier include it
configure_file(${PROJECT_SOURCE_DIR}/templates/cppdbg.pc.in cppdbg.pc @ONLY)

# Finally, note the library & pc file as install candidate
install(TARGETS cppdbg
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/cppdbg.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
# Export the CMake files as well
install(TARGETS cppdbg EXPORT CppDebuggerConfig
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static)
install(EXPORT CppDebuggerConfig DESTINATION cmake)
