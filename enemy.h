#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "point.h"
#include "gm_state.h"

#include <vector>

namespace dos_game
{

class EnemyBase
{
public:
    virtual ~EnemyBase() {}
    virtual Rect getBoundingBox() = 0;
    virtual void act(const Rect& playerPos, const std::vector<Bullet>& bullets) = 0;
    virtual BITMAP* getBitmap() = 0;
    virtual Point getPos() = 0;
};

}

#endif
