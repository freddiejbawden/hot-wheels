

include_directories(${SDL2_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR})

add_executable(hotwheels main.cpp)

target_link_libraries(hotwheels 
  ${SDL2_LIBRARY} 
  ${SDL2_TTF_LIBRARIES}
  preprocessor_lib 
  domnodes_lib 
  htmlparser_lib 
  parser_lib 
  cssnodes_lib 
  cssparser_lib
  styletree_lib
  fontmanager_lib
  layout_lib
  layoutpainter_lib
  utils_lib
  engine_lib
  )
  