#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    Ball(const Point &center, 
         const Velocity &velocity, 
         double radius,
         Color color = Color(0, 0, 0), 
         bool isCollidable = true);

    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;  
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool isCollidable() const;

private:
    Point m_center;
    Velocity m_velocity;
    double m_radius{0.0};
    Color m_color{0, 0, 0}; // Цвет шара, по умолчанию черный
    bool m_isCollidable{true}; // Флаг, указывающий, нужно ли обрабатывать столкновения
    double m_mass{0.0}; // Масса шара   
};
