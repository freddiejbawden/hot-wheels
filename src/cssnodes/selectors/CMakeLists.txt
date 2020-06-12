set(HEADER_LIST "${HotWheels_SOURCE_DIR}/include/cssnodes/selectors/selector.hpp" "${HotWheels_SOURCE_DIR}/include/cssnodes/selectors/simple_selector.hpp")

add_library(cssselectors_lib selector.cpp simple_selector.cpp ${HEADER_LIST})

target_include_directories(cssselectors_lib PUBLIC ${HotWheels_SOURCE_DIR}/include)

target_compile_features(cssselectors_lib PUBLIC cxx_std_11)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})