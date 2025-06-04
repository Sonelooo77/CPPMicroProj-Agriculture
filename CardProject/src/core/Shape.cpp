#include "Shape.h"

#include <sstream>

using namespace std;

Shape::Shape(const pugi::xml_node& node)
    : label{node.attribute("label").as_string()},
      x{node.attribute("x").as_double()},
      y{node.attribute("y").as_double()} {}

std::string Shape::dump(std::string const& indent) const {
  ostringstream oss;
  oss << "\"" << label << "\", " << "x: " << x << ", " << "y: " << y << ", ";
  return oss.str();
}

double Shape::get_x() const { return x; }
double Shape::get_y() const { return y; }
