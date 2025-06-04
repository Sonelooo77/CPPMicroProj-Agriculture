#include <sstream>
#include "Drawing.h"

using namespace std;

Drawing::Drawing(const pugi::xml_node& node) :
  root{ make_unique<Group>(node) }
{
}

void Drawing::draw(SFML_output* out) const {
  root->draw(out, 0, 0);
}

std::string Drawing::dump(std::string const& indent) const {
  ostringstream oss;
  oss << indent << "Drawing with root = " << root->dump(indent);
  return oss.str();
}
