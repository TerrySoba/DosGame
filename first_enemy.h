#ifndef FIRST_ENEMY_H
#define FIRST_ENEMY_H

#include "sprite.h"
#include "enemy.h"

#include <memory>

class FirstEnemy : public EnemyBase
{
public:
    FirstEnemy(const char* imagePath);

    // EnemyBase interface
    virtual Rect getBoundingBox() override;
    virtual void act(const Rect& playerPos, const std::vector<Bullet>& bullets) override;

    // Sprite interface
    virtual BITMAP* getBitmap() override;
    virtual Point getPos() override;

private:
    std::shared_ptr<BITMAP> m_bitmap;
    Point m_pos;
    size_t m_actCount = 0;
};

#endif // FIRST_ENEMY_H
