#ifndef BULLET_FACTORY_H
#define BULLET_FACTORY_H

#include "splashkit.h"
#include <vector>

enum class ProjectileType {
    NORMAL,
    FAST,
    EXPLOSIVE
};

class BulletFactory {
public:
    static std::vector<sprite> SprayProjectiles(ProjectileType type, point_2d origin, vector_2d direction, int count, float spread);

private:
    static sprite CreateBullet(ProjectileType type, point_2d origin, vector_2d direction);
    static vector_2d RotateVector(vector_2d vec, float angle);
};

#endif // BULLET_FACTORY_H