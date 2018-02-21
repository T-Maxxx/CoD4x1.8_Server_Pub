cmake_minimum_required(VERSION 3.10)
project(cod4x)

set(CMAKE_CXX_GLOBAL_FLAGS "-m32")
set(CMAKE_EXE_LINKER_GLOBAL_FLAGS "")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(SRC_DIR src_mod)
set(PRJ_SRC src)
set(PRJ_INC include)

#add_subdirectory(${SRC_DIR}/core)
#add_subdirectory(${SRC_DIR}/mbedtls)
add_subdirectory(${SRC_DIR}/phandler)
#add_subdirectory(${SRC_DIR}/tomcrypt)
add_subdirectory(${SRC_DIR}/versioning)
add_subdirectory(${SRC_DIR}/xassets)
add_subdirectory(${SRC_DIR}/zlib)

if (WIN32)
    add_subdirectory(${SRC_DIR}/win32)
else()
    #add_subdirectory(${SRC_DIR}/linux32)
endif()