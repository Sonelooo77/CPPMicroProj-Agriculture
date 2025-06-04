#pragma once
#include <memory>
#include "Group.h"

class Drawing {
public:
  explicit Drawing(const pugi::xml_node &node);
  void draw(SFML_output* out) const;
  [[nodiscard]] std::string dump(std::string const& indent) const;
private:
  std::unique_ptr<Group> root;
};
