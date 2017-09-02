#ifndef ENEMY_H
#define ENEMY_H

#include "point.h"

#include <vector>

namespace dos_game
{

class Enemy
{
public:
    virtual ~Enemy() {}
    virtual void act(const Rect& playerPos, const std::vector<Rect>& bullets) = 0;
    virtual void hurt(int amount) = 0;
    virtual Rect getBoundingBox() = 0;
    virtual Point getPos() = 0;
    virtual bool isDead() = 0;
};

}

#endif // ENEMY_H
