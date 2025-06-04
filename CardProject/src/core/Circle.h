#pragma once
#include "Shape.h"

class Circle : public Shape {
 public:
  explicit Circle(const pugi::xml_node& node);
  [[nodiscard]] std::string dump(std::string const& indent) const override;
  void draw(SFML_output* out, double x_origin, double y_origin) const override;

 private:
  double r;
  std::string color;
};
