

set(HEADER_LIST "${HotWheels_SOURCE_DIR}/include/layoutpainter/layoutpainter.hpp")

add_library(layoutpainter_lib layoutpainter.cpp ${HEADER_LIST})
target_include_directories(layoutpainter_lib PUBLIC ${HotWheels_SOURCE_DIR}/include ${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR})
target_link_libraries(layoutpainter_lib  ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})

target_compile_features(layoutpainter_lib PUBLIC cxx_std_11)


source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})