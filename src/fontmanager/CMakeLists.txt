

set(HEADER_LIST "${HotWheels_SOURCE_DIR}/include/fontmanager/fontmanager.hpp")

add_library(fontmanager_lib fontmanager.cpp ${HEADER_LIST})
target_include_directories(fontmanager_lib PUBLIC ${HotWheels_SOURCE_DIR}/include ${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR})
target_link_libraries(fontmanager_lib  ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})

target_compile_features(fontmanager_lib PUBLIC cxx_std_11)


source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})