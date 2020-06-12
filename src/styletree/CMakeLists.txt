set(HEADER_LIST "${HotWheels_SOURCE_DIR}/include/styletree/styletree.hpp")

add_library(styletree_lib styletree.cpp ${HEADER_LIST})

target_include_directories(styletree_lib PUBLIC ${HotWheels_SOURCE_DIR}/include)

target_compile_features(styletree_lib PUBLIC cxx_std_11)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})