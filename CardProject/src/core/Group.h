#pragma once
#include <memory>
#include <vector>

#include "Shape.h"

class Group : public Shape {
 public:
  explicit Group(const pugi::xml_node& node);
  void draw(SFML_output* out, double x_origin, double y_origin) const override;
  [[nodiscard]] std::string dump(std::string const& indent) const override;

 private:
  std::vector<std::unique_ptr<Shape>> children;
};
