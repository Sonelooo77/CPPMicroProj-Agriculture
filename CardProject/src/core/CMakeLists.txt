add_library(lib_core
  myMain.cpp
  myMain.h
  Circle.cpp
  Circle.h
  Drawing.cpp
  Drawing.h
  Group.cpp
  Group.h
  SFML_output.cpp
  SFML_output.h
  Shape.cpp
  Shape.h
)
target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC pugixml sfml-graphics)
