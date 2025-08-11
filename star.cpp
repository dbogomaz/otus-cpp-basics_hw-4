#include "star.hpp"
#include <cmath>
#include <iostream>

Star::Star(const Point &center, 
           const Velocity &velocity, 
           double radius,
           bool isCollidable)
    : m_center{center}, 
      m_velocity{velocity}, 
      m_radius{radius}, 
      m_isCollidable{isCollidable} {}

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Star::setVelocity(const Velocity& velocity) {
   m_velocity = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Star::getVelocity() const {
    return m_velocity;
}

/**
 * @brief Выполняет отрисовку объекта
 * @param painter контекст отрисовки
 */
void Star::draw(Painter& painter) const {
    painter.drawStar(m_center, m_radius); // Отрисовка звезды
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Star::setCenter(const Point& center) {
    // TODO: место для доработки
    m_center = center;
}

/**
 * @return центр объекта
 */
Point Star::getCenter() const {
    return m_center;
}

/**
 * @brief Возвращает радиус объекта
 */
double Star::getRadius() const {
    return m_radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все масса звезды
 * эквивалента массе шара с таким же диаметром.
 * PI * radius^3 * 4. / 3.
 */
double Star::getMass() const {
    return M_PI * std::pow(m_radius, 3) * 4.0 / 3.0;
}

bool Star::isCollidable() const { return m_isCollidable; }
