#ifndef FIRST_ENEMY_H
#define FIRST_ENEMY_H

#include "sprite.h"
#include "enemy.h"


#include <memory>

namespace dos_game
{

class FirstEnemy : public EnemyBase
{
public:
    FirstEnemy(std::shared_ptr<GfxObject> image);

    // EnemyBase interface
    virtual Rect getBoundingBox() override;
    virtual void act(const Rect& playerPos, const std::vector<Bullet>& bullets) override;
    virtual std::shared_ptr<GfxObject> getGfxObject() override;
    virtual Point getPos() override;

private:
    std::shared_ptr<GfxObject> m_image;
    Point m_pos;
    size_t m_actCount = 0;
};

}

#endif // FIRST_ENEMY_H
