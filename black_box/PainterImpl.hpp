#pragma once
#include "../Color.hpp"
#include "View.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace sf {
    class RenderWindow;
}

class PainterImpl {
  public:
    PainterImpl(sf::RenderWindow& window, const View& view);
    ~PainterImpl();
    /**
     * @brief Отрисовывает круг
     * @param center Центр круга
     * @param radius Радиус круга
     * @param color Цвет круга
     *
     * Отрисовывает круг с заданным центром, радиусом и цветом.
     */
    void draw(const Point& center, double radius, const Color& color);

    /**
     * @brief Отрисовывает прямоугольник
     * @param topLeft Верхний левый угол прямоугольника
     * @param bottomRight Нижний правый угол прямоугольника
     * @param color Цвет прямоугольника
     *
     * Отрисовывает прямоугольник с заданными углами и цветом
     */
    void draw(const Point& topLeft, const Point& bottomRight,
              const Color& color);

    /**
     * @brief Отрисовывает звезду
     * @param center Центр звезды 
     * @param outerRadius Внешний радиус звезды
     * @param innerRadius Внутренний радиус звезды
     * @param color Цвет звезды
     *
     * Отрисовывает звезду с заданными параметрами.
     */
    void drawStar(const Point& center, const float outerRadius);

  private:
    sf::Color toSFMLColor(const Color& color) const;
    sf::Vector2f toVector(const Point& point) const;

  private:
    sf::RenderWindow& window;

    const View& view;
};
