set(HEADER_LIST "${HotWheels_SOURCE_DIR}/include/utils/utils.hpp")

add_library(utils_lib utils.cpp ${HEADER_LIST})

target_include_directories(utils_lib PUBLIC ${HotWheels_SOURCE_DIR}/include)

target_compile_features(utils_lib PUBLIC cxx_std_11)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})