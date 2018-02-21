project(cod4x_lnxded)
###############################################################################
file(GLOB SOURCE_CPP ${PRJ_SRC}/*.cpp)
file(GLOB SOURCE_C ${PRJ_SRC}/*.c)
file(GLOB SOURCE_H ${PRJ_INC}/*.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_GLOBAL_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_GLOBAL_FLAGS}")
###############################################################################
add_executable(${PROJECT_NAME} ${SOURCE_CPP} ${SOURCE_C} ${SOURCE_H})
target_link_libraries(${PROJECT_NAME} ${MODULES} ${EXT_MODULES})
