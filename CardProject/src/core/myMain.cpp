#include "myMain.h"

#include <iostream>

#include "Drawing.h"

int myMain() {
  pugi::xml_document doc;
  if (const auto result = doc.load_file("res/visage.xml"); !result) {
    std::cerr << "Could not open file visage.xml because "
              << result.description() << std::endl;
    return 1;
  }

  const Drawing d{doc.child("Drawing")};
  std::cout << d.dump("");

  SFML_output out;
  out.display(d);

  return EXIT_SUCCESS;
}
