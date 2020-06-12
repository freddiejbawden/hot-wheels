set(HEADER_LIST "${HotWheels_SOURCE_DIR}/include/preprocessor/preprocessor.hpp")

add_library(preprocessor_lib preprocessor.cpp ${HEADER_LIST})

target_include_directories(preprocessor_lib PUBLIC ${HotWheels_SOURCE_DIR}/include)

target_compile_features(preprocessor_lib PUBLIC cxx_std_11)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})