set(HEADER_LIST "${HotWheels_SOURCE_DIR}/include/cssparser/cssparser.hpp")

add_library(cssparser_lib cssparser.cpp ${HEADER_LIST})

target_include_directories(cssparser_lib PUBLIC ${HotWheels_SOURCE_DIR}/include)

target_compile_features(cssparser_lib PUBLIC cxx_std_11)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})