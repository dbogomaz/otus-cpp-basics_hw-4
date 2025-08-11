#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Star {
public:
    Star(const Point &center, 
         const Velocity &velocity, 
         double radius, 
         bool isCollidable = false);

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
    bool m_isCollidable{false}; // Флаг, указывающий, нужно ли обрабатывать столкновения
};
