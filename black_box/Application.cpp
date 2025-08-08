#include "Application.hpp"
#include "../World.hpp"
#include <SFML/Window/Event.hpp>
#include <chrono>
#include <map>

// Application::Application(const char* name)
//     : window{{1280u, 960u},
//              name,
//              sf::Style::Titlebar | sf::Style::Close,
//              sf::ContextSettings(0, 0, 4)},
//       view({0., 0.}, 1280, 960, 0.2) {}
Application::Application(const char *name)
    : window(sf::VideoMode({1280u, 960u}),           // Размер окна
             name,                                   // Заголовок
             sf::Style::Titlebar | sf::Style::Close, // Стиль
             sf::State::Windowed, // Режим окна (новый параметр в SFML 3.0)
                                  // Windowed, Fullscreen, FullscreenExclusive
             []() {
               sf::ContextSettings settings;
               settings.antiAliasingLevel = 4; // 4x сглаживание
               return settings;
             }() // Настройки контекста
             ),
      view{{0., 0.}, 1280, 960, 0.2} // Камера/вид
{}

void Application::run(World &world) {
  time = std::chrono::system_clock::now();
  totalTime = 0.;

  while (window.isOpen()) {
    processEvents();
    updateWorld(world);
    drawWorld(world);
  }
}

// void Application::processEvents() {
//   for (sf::Event event{}; window.pollEvent(event); /**/) {
//     if (event.type == sf::Event::EventType::Closed) {
//       window.close();
//     } else if (event.type == sf::Event::EventType::MouseWheelScrolled) {
//       view.onZoom(event.mouseWheelScroll.delta);
//     }
//   }
// }
void Application::processEvents() {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        else if (event->is<sf::Event::MouseWheelScrolled>()) {
            view.onZoom(event->getIf<sf::Event::MouseWheelScrolled>()->delta);
        }
    }
}

void Application::updateWorld(World &world) {
  const auto currentTime = std::chrono::system_clock::now();
  const double delta =
      std::chrono::duration_cast<std::chrono::duration<double>>(currentTime -
                                                                time)
          .count();
  time = currentTime;

  totalTime += delta;

  if (totalTime < 10.) {
    world.update(delta);
  }
}

void Application::drawWorld(const World &world) {
  Painter painter(window, view);
  world.show(painter);
}
