add_subdirectory(selectors)
add_subdirectory(values)

set(HEADER_LIST "${HotWheels_SOURCE_DIR}/include/cssnodes/declaration.hpp" "${HotWheels_SOURCE_DIR}/include/cssnodes/rule.hpp")

add_library(cssnodes_lib declaration.cpp rule.cpp ${HEADER_LIST})

target_include_directories(cssnodes_lib PUBLIC ${HotWheels_SOURCE_DIR}/include)

target_compile_features(cssnodes_lib PUBLIC cxx_std_11)

target_link_libraries(cssnodes_lib cssselectors_lib cssvalues_lib)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})