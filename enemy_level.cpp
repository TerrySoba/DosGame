#include "enemy_level.h"

#include "image_utils.h"

namespace dos_game
{


EnemyLevel::EnemyLevel()
{

}

void EnemyLevel::onLoad(std::shared_ptr<LevelContext> context)
{
    auto bgImage = loadBitmap("gfx/space_bg.pcx");
    m_bg = context->getEngine()->createGfxObject(bgImage, false, -1);

    auto enemyImage = loadBitmap("gfx/enemy.pcx");
    m_enemy = context->getEngine()->createGfxObject(enemyImage, true);

    auto shipImage = loadBitmap("gfx/ship.pcx");
    m_ship = context->getEngine()->createGfxObject(shipImage, true);

    m_ship->setPos({100, 200});

    auto bulletImage = loadBitmap("gfx/bullet.pcx");
    for (size_t i = 0; i < 5; ++i)
    {
        m_bullets.push_back(context->getEngine()->createGfxObject(bulletImage, true));
        m_bullets.back()->setPos({-100, -100});
    }
}


void EnemyLevel::onExit(std::shared_ptr<LevelContext> context)
{

}


std::shared_ptr<GfxObject> EnemyLevel::getIdleBullet()
{
    for (auto& bullet : m_bullets)
    {
        auto bb = bullet->getBoundingBox();
        if (bb.y <= -4)
        {
            return bullet;
        }
    }

    return std::shared_ptr<GfxObject>();
}

void EnemyLevel::act(std::shared_ptr<LevelContext> context)
{
    auto bb = m_ship->getBoundingBox();
    if (key[KEY_LEFT] != 0)
    {
        m_ship->setPos({bb.x - 2, bb.y});
    }
    else if (key[KEY_RIGHT] != 0)
    {
        m_ship->setPos({bb.x + 2, bb.y});
    }

    if (key[KEY_SPACE] != 0)
    {
        auto bullet = getIdleBullet();
        if (bullet)
        {
            auto bb = m_ship->getBoundingBox();
            bullet->setPos({bb.x, bb.y});
        }
    }


    for (auto& bullet : m_bullets)
    {
        auto bb = bullet->getBoundingBox();
        bullet->setPos({bb.x, bb.y - 5});
    }

}



}
