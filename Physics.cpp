#include "Physics.hpp"

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

void Physics::update(std::vector<Ball>& balls, std::vector<Star>& stars, const size_t ticks) const {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls, stars);
        collideWithBox(balls);
        collideBalls(balls, stars);
    }
}

void Physics::collideBalls(std::vector<Ball>& balls, std::vector<Star>& stars) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        if (!a->isCollidable()) {
            continue; // Пропускаем неколлизионные шары
        }
        for (auto b = std::next(a); b != balls.end(); ++b) {
            const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 =
                collisionDistance * collisionDistance;

            if (distanceBetweenCenters2 < collisionDistance2 &&
                a->isCollidable() && b->isCollidable()) {
                processCollision(*a, *b, distanceBetweenCenters2, stars);
            }
        }
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        const Point p = ball.getCenter();
        const double r = ball.getRadius();
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;
            ball.setVelocity(vector);
        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            ball.setVelocity(vector);
        }
    }
}

void Physics::move(std::vector<Ball>& balls, std::vector<Star>& stars) const {
    // Обновляем позиции шаров
    for (Ball& ball : balls) {
        Point newPos = ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
    
    // Обновляем позиции звёзд и их время жизни
    for (auto it = stars.begin(); it != stars.end();) {
        // Уменьшаем время жизни звезды
        size_t currentLifeTime = it->getLifeTime();
        if (currentLifeTime > 0) {
            it->setLifeTime(currentLifeTime - 1);
            // Обновляем позицию
            Point newPos = it->getCenter() + it->getVelocity().vector() * timePerTick;
            it->setCenter(newPos);
            ++it; // Переходим к следующей звезде
        } else {
            it = stars.erase(it); // Удаляем звезду с нулевым временем жизни
        }
    }
}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2, 
                               std::vector<Star>& stars) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));

    // вычисляем точку соприкосновения с учетом разных радиусов
    const double rA = a.getRadius();
    const double rB = b.getRadius();
    const Point collisionPoint = a.getCenter() + (b.getCenter() - a.getCenter()) * (rA / (rA + rB));
    // радиус звезды можно оставить фиксированным или средним
    const double radius = 6.0;
    // вычисляем касательный вектор (перпендикуляр к normal)
    Point tangent(-normal.y, normal.x); // повернули normal на 90 градусов
    double starSpeed = 1000.0; // модуль скорости звезды
    // создаем две звезды с противоположными скоростями по касательной
    Star star1(collisionPoint, Velocity(tangent * starSpeed), radius, true);
    Star star2(collisionPoint, Velocity(tangent * -starSpeed), radius, true);
    stars.push_back(star1);
    stars.push_back(star2);
}
