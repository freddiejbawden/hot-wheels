set(HEADER_LIST "${HotWheels_SOURCE_DIR}/include/parser/parser.hpp")

add_library(parser_lib parser.cpp ${HEADER_LIST})

target_include_directories(parser_lib PUBLIC ${HotWheels_SOURCE_DIR}/include)

target_compile_features(parser_lib PUBLIC cxx_std_11)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})