set(HEADER_LIST "${HotWheels_SOURCE_DIR}/include/cssnodes/values/color.hpp" "${HotWheels_SOURCE_DIR}/include/cssnodes/values/value.hpp" "${HotWheels_SOURCE_DIR}/include/cssnodes/values/keyword.hpp" "${HotWheels_SOURCE_DIR}/include/cssnodes/values/length.hpp")

add_library(cssvalues_lib color.cpp keyword.cpp length.cpp value.cpp ${HEADER_LIST})

target_include_directories(cssvalues_lib PUBLIC ${HotWheels_SOURCE_DIR}/include)

target_compile_features(cssvalues_lib PUBLIC cxx_std_11)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})