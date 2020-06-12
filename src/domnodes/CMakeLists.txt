set(HEADER_LIST 
  "${HotWheels_SOURCE_DIR}/include/domnodes/element.hpp"
  "${HotWheels_SOURCE_DIR}/include/domnodes/node.hpp"
  "${HotWheels_SOURCE_DIR}/include/domnodes/text.hpp"

)

add_library(domnodes_lib element.cpp node.cpp text.cpp ${HEADER_LIST})

target_include_directories(domnodes_lib PUBLIC ${HotWheels_SOURCE_DIR}/include)

target_compile_features(domnodes_lib PUBLIC cxx_std_11)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})