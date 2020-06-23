set(HEADER_LIST 
  "${HotWheels_SOURCE_DIR}/include/layout/anonymousBox.hpp"
  "${HotWheels_SOURCE_DIR}/include/layout/blockBox.hpp"
  "${HotWheels_SOURCE_DIR}/include/layout/dimensions.hpp"
  "${HotWheels_SOURCE_DIR}/include/layout/inlineBox.hpp"
  "${HotWheels_SOURCE_DIR}/include/layout/layoutBox.hpp"
  "${HotWheels_SOURCE_DIR}/include/layout/lineBox.hpp"
  "${HotWheels_SOURCE_DIR}/include/layout/rect.hpp"
)

add_library(layout_lib 
  anonymousBox.cpp 
  blockBox.cpp 
  dimensions.cpp 
  inlineBox.cpp
  layoutBox.cpp
  lineBox.cpp
  rect.cpp
  ${HEADER_LIST})

target_include_directories(layout_lib PUBLIC ${HotWheels_SOURCE_DIR}/include)

target_compile_features(layout_lib PUBLIC cxx_std_11)

source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})