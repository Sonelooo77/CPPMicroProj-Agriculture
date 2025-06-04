#include "Group.h"

#include <cassert>
#include <sstream>
#include <string_view>  // string_view requires C++17 (either defined in CMakeLists.txt, or in Visual Studio, /Project properties -> Configuration properties->C / C++->Language->C++ Language standard / and select "ISO C++ 17 Standard"

#include "Circle.h"

using namespace std;

Group::Group(const pugi::xml_node& node) : Shape{node} {
  for (auto child : node.children()) {
    assert(
        (child.name() == "Circle"sv) ||
        (child.name() ==
         "Group"sv));  // "Circle"sv" equivalent to std::string_view{ "Circle" }
    // thanks to : using namespace std::literals;
    if (child.name() == "Circle"sv)
      children.push_back(std::make_unique<Circle>(child));
    else  // child.name() == "Group"sv
      children.push_back(std::make_unique<Group>(child));
  }
}

void Group::draw(SFML_output* out, const double x_origin, const double y_origin) const {
  for (auto const& child : children) {
    child->draw(out, x_origin + get_x(), y_origin + get_y());
  }
}

std::string Group::dump(std::string const& indent) const {
  ostringstream oss;
  oss << indent << "Group " << Shape::dump(indent) << "children: [" << endl;
  for (auto const& c : children) {
    oss << c->dump(indent + "| ");
  }
  oss << indent << "]" << endl;
  return oss.str();
}
