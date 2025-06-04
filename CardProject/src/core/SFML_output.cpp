#include "SFML_output.h"

#include <map>
#include <string>

#include "Drawing.h"

static constexpr unsigned int WINDOW_WIDTH(1000);
static constexpr unsigned int WINDOW_HEIGHT(700);

SFML_output::SFML_output()
    : window{sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
             "Outil visualisation"} {
  // To use less CPU, we limit framerate to 30 fps
  // (On Michel Simatic's PC, under Windows, the execution of this code
  // drops down from 9% of CPU (without `window.setFramerateLimit(30);`)
  // to 0,2% de CPU (with `window.setFramerateLimit(30);`).
  // We could have preferred to `use window.setVerticalSyncEnabled(true);`
  // as mentioned in
  // https://www.sfml-dev.org/tutorials/3.0/window/window/#playing-with-the-window
  // But, on Linux (WSL2) used by Michel Simatic, there is the error
  // message "Setting vertical sync not supported" displayed by SFML:
  // This message signifies that `window.setVerticalSyncEnabled(true);`
  // instruction cannot be considered on this Linux.
  // Note: With SFML v3.0.0 (and WSL2 Ubuntu 24.04 ?), message
  // "Setting vertical sync not supported" is still displayed with
  // `window.setFramerateLimit(30);`
  window.setFramerateLimit(30);
}

void SFML_output::draw_circle(const double absolute_x, const double absolute_y, const double r,
                              std::string const& color) {
  sf::CircleShape shape(static_cast<float>(r));
  shape.setFillColor(string2color(color));
  // In the following setPosition(), we use window.getSize().x instead of
  // WINDOW_WIDTH and window.getSize().y instead of WINDOW_HEIGHT, so that if
  // window is resized by user, drawing remains the same. Actually, it does not
  // work properly as SFML seems to keep an internal scale linked to initial
  // size of the window (e.g.     // a circle becomes an ellipse when you resize
  // horizontally the window).
  shape.setPosition(
      {static_cast<float>(absolute_x + window.getSize().x / 2. - r),
       static_cast<float>(window.getSize().y / 2. - (absolute_y + r))});
  window.draw(shape);
}

void SFML_output::display(Drawing const& d) {
  while (window.isOpen()) {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    while (const std::optional event = window.pollEvent()) {
      // "close requested" event: we close the window
      if (event->is<sf::Event::Closed>()) window.close();

      // Catch the resize events
      if (const auto* resized = event->getIf<sf::Event::Resized>()) {
        // Update the view to the new size of the window, so that contents is
        // not distorted by resizing See
        // https://www.sfml-dev.org/tutorials/3.0/graphics/view/#using-a-view
        sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
        window.setView(sf::View(visibleArea));
      }
    }
    window.clear(sf::Color::White);
    d.draw(this);
    window.display();
  }
}

sf::Color SFML_output::string2color(std::string const& s) {
  std::map<std::string_view, sf::Color, std::less<>> msc = {
      {"Black", sf::Color::Black},     {"White", sf::Color::White},
      {"Red", sf::Color::Red},         {"Green", sf::Color::Green},
      {"Blue", sf::Color::Blue},       {"Yellow", sf::Color::Yellow},
      {"Magenta", sf::Color::Magenta}, {"Cyan", sf::Color::Cyan}};

  return msc[s];  // Notice that we return the equivalent of sf::Color:Black if
                  // s was not found in msc
}
