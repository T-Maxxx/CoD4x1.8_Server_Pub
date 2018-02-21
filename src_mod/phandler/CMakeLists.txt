project(phandler)
###############################################################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_GLOBAL_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_GLOBAL_FLAGS}")
###############################################################################

file(GLOB SOURCE_CPP ${PRJ_SRC}/*.cpp)
file(GLOB SOURCE_C ${PRJ_SRC}/*.c)
file(GLOB SOURCE_H ${PRJ_INC}/${PROJECT_NAME}/*.h)

set(MODULES "${MODULES} ${PROJECT_NAME}")

add_library(${PROJECT_NAME} STATIC ${SOURCE_CPP} ${SOURCE_C} ${SOURCE_H})
