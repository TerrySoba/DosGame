#ifndef FIRST_ENEMY_H
#define FIRST_ENEMY_H

#include "enemy.h"

namespace dos_game
{

class FirstEnemy : public Enemy
{
public:
    FirstEnemy(int width, int height, const Point& pos = {200, 40});

    // Enemy interface
    virtual void act(const Rect& playerPos, const std::vector<Rect>& bullets) override;
    virtual void hurt(int amount) override;
    virtual Rect getBoundingBox() override;
    virtual Point getPos() override { return m_pos; }
    virtual bool isDead() override;

private:
    Point m_pos;
    int m_health = 5;
    int m_width;
    int m_height;

    // speed vector
    Point m_speed = {0,0};
};

}

#endif // FIRST_ENEMY_H
