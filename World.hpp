#pragma once
#include "Ball.hpp"
#include "star.hpp"
#include "Physics.hpp"
#include <string>
#include <vector>

class Painter;

class World {
  public:
    World(const std::string& worldFilePath);
    void show(Painter& painter) const;
    void update(double time);


  private:
    // Границы мира заданы углами прямоугольника
    Point topLeft;
    Point bottomRight;
    // Объект физического движка
    Physics physics;
    // Контейнер с шарами
    std::vector<Ball> balls;
    // Длина отрезка времени, который не был
    // учтен при прошлой симуляции. См. реализацию update
    double restTime = 0.;
    // Контейнер со звездами
    std::vector<Star> stars;
};

std::ifstream& operator>>(std::ifstream& stream, Point& point);
std::ifstream& operator>>(std::ifstream& stream, Velocity& velocity);
std::ifstream& operator>>(std::ifstream& stream, Color& color);