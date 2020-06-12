set(HEADER_LIST "${HotWheels_SOURCE_DIR}/include/htmlparser/htmlparser.hpp")

add_library(htmlparser_lib htmlparser.cpp ${HEADER_LIST})

target_include_directories(htmlparser_lib PUBLIC ${HotWheels_SOURCE_DIR}/include)

target_compile_features(htmlparser_lib PUBLIC cxx_std_11)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})