set(HEADER_LIST "${HotWheels_SOURCE_DIR}/include/engine/engine.hpp")

add_library(engine_lib engine.cpp ${HEADER_LIST})

target_include_directories(engine_lib PUBLIC ${HotWheels_SOURCE_DIR}/include)

target_compile_features(engine_lib PUBLIC cxx_std_11)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})