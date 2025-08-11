#include "PainterImpl.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <algorithm>

PainterImpl::PainterImpl(sf::RenderWindow& window, const View& view)
    : window{window}, view{view} {
    window.clear();
}

PainterImpl::~PainterImpl() {
    window.display();
}

void PainterImpl::draw(const Point& center, double radius, const Color& color) {
    const sf::Vector2f pos = toVector(view.toScreen(center));
    const float scaledRadius = float(radius * view.scale());
    // Эмпирическая формула. При таком количестве точек получаем гладкие
    // окружности
    const size_t pointsCount = std::max(int(scaledRadius / 2), 20);

    sf::CircleShape shape(scaledRadius, pointsCount);
    shape.setPosition(pos - sf::Vector2f{scaledRadius, scaledRadius});
    shape.setFillColor(toSFMLColor(color));

    window.draw(shape);
}

void PainterImpl::draw(const Point& topLeft, const Point& bottomRight,
                       const Color& color) {
    const sf::Vector2f tl = toVector(view.toScreen(topLeft));
    const sf::Vector2f br = toVector(view.toScreen(bottomRight));

    sf::RectangleShape rect(br - tl);
    rect.setPosition(tl);
    rect.setFillColor(toSFMLColor(color));

    window.draw(rect);
}

void PainterImpl::draw(const Point &center, const float outerRadius, 
                       const float innerRadius, const Color &color) {
    const sf::Vector2f pos = toVector(view.toScreen(center)); // Преобразуем координаты центра в экранные
    const float scaledOuterRadius = float(outerRadius * view.scale());
    const float scaledInnerRadius = float(innerRadius * view.scale());

    const size_t starVerticesCount{8}; // Количество вершин звезды
                                       // потом можно будет передать как параметр
    sf::ConvexShape star;
    star.setPosition(sf::Vector2f{scaledOuterRadius, scaledOuterRadius});
    // star.setPosition(pos);
    star.setFillColor(toSFMLColor(color)); // цвет заливки
    star.setOutlineColor(sf::Color::Red); // цвет контура
    star.setOutlineThickness(2); // толщина контура

    size_t pointsCount{starVerticesCount * 2}; // 5 внешних и 5 внутренних вершин

    star.setPointCount(pointsCount);
    for (size_t i = 0; i < pointsCount; ++i) {
        float angle = static_cast<float>(i) * 2.f * M_PI / pointsCount - M_PI_2;
        float radius = (i % 2 == 0) ? scaledOuterRadius : scaledInnerRadius; // чередуем радиусы
        float x = pos.x + cos(angle) * radius;
        float y = pos.y + sin(angle) * radius;
        star.setPoint(i, sf::Vector2(x, y));        
    }

    window.draw(star);
 }

// sf::Color PainterImpl::toSFMLColor(const Color& color) const {
//     auto toColorComponent = [](double value) {
//         return sf::Uint8(std::clamp(value, 0., 1.) * 255);
//     };

//     return sf::Color{
//         toColorComponent(color.red()),
//         toColorComponent(color.green()),
//         toColorComponent(color.blue()),
//     };
// }
sf::Color PainterImpl::toSFMLColor(const Color& color) const {
    auto toColorComponent = [](double value) {
        return static_cast<uint8_t>(std::clamp(value, 0., 1.) * 255);
    };

    return sf::Color{
        toColorComponent(color.red()),
        toColorComponent(color.green()),
        toColorComponent(color.blue()),
    };
}

sf::Vector2f PainterImpl::toVector(const Point& point) const {
    return {float(point.x), float(point.y)};
}
