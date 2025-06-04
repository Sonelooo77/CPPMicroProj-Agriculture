#include "Circle.h"

#include <sstream>

using namespace std;

Circle::Circle(const pugi::xml_node& node)
    : Shape{node},
      r{node.attribute("r").as_double()},
      color{node.attribute("color").as_string()} {}

std::string Circle::dump(std::string const& indent) const {
  ostringstream oss;
  oss << indent << "Circle " << Shape::dump(indent) << "r: " << r << ", "
      << "color: " << "\"" << color << "\"" << endl;
  return oss.str();
}

void Circle::draw(SFML_output* out, const double x_origin, const double y_origin) const {
  out->draw_circle(x_origin + get_x(), y_origin + get_y(), r, color);
}
