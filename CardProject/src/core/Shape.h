#pragma once
#include <string>

#include "SFML_output.h"
#include "pugixml.hpp"

class Shape {
 public:
  explicit Shape(const pugi::xml_node& node);
  [[nodiscard]] virtual std::string dump(std::string const& indent)
      const;  // We cannot have a default argument anymore (otherwise
              // "Clang-Tidy: Default arguments on virtual or override methods
              // are prohibited")
  virtual ~Shape() = default;
  virtual void draw(SFML_output* out, double x_origin,
                    double y_origin) const = 0;
  [[nodiscard]] double get_x() const;
  [[nodiscard]] double get_y() const;

 private:
  std::string label;
  double x;
  double y;
};
