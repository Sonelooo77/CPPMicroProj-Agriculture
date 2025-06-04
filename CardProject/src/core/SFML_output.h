#pragma once
#include <SFML/Graphics.hpp>
class Drawing;
class SFML_output {
 public:
  SFML_output();
  void draw_circle(double absolute_x, double absolute_y, double r,
                   std::string const& color);
  void display(Drawing const& d);

 private:
  static sf::Color string2color(std::string const& s);
  sf::RenderWindow window;
};
