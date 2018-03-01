#include <SFML/Graphics.hpp>
#include "Chip8.hpp"
#include <iostream>

#define PIXEL_SIZE 15
#define WINDOW_NAME "Chip 8 Emulator"

void display_screen(sf::RenderWindow &w, GPU const &gpu) {
  static sf::RectangleShape rect(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
  static sf::Color cs[2] = {
    sf::Color(0,0,0),
    sf::Color(255,255,255)
  };

  for (size_t y = 0; y < GPU_HEIGHT; y++) {
    for (size_t x = 0; x < GPU_WIDTH; x++) {
      uint8_t c = gpu[x + (y * GPU_WIDTH)];
      rect.setFillColor(cs[c]);
      rect.setPosition(x * PIXEL_SIZE, y * PIXEL_SIZE);
      w.draw(rect);
    }
  }
}

int main()
{
  Chip8 device;

  sf::RenderWindow window(sf::VideoMode(GPU_WIDTH * PIXEL_SIZE, GPU_HEIGHT * PIXEL_SIZE), WINDOW_NAME);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    display_screen(window, device.getGraphics());
    window.display();
  }

  return 0;
}
