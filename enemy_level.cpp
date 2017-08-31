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

    m_ship->pos = {100, 200};

    auto bulletImage = loadBitmap("gfx/bullet.pcx");
    for (size_t i = 0; i < 5; ++i)
    {
        m_bullets.push_back(context->getEngine()->createGfxObject(bulletImage, true));
        m_bullets.back()->pos = {-100, -100};
    }
}


void EnemyLevel::onExit(std::shared_ptr<LevelContext> context)
{
    auto& engine = *context->getEngine();

    engine.unloadGfx(m_bg);
    engine.unloadGfx(m_enemy);
    engine.unloadGfx(m_ship);
    for (auto bullet : m_bullets)
    {
        engine.unloadGfx(bullet);
    }
}


std::shared_ptr<GfxObject> EnemyLevel::getIdleBullet()
{
    for (auto& bullet : m_bullets)
    {
        if (bullet->pos.y <= -4)
        {
            return bullet;
        }
    }

    return std::shared_ptr<GfxObject>();
}

void EnemyLevel::act(std::shared_ptr<LevelContext> context)
{
    auto& shipPos = m_ship->pos;
    if (key[KEY_LEFT] != 0)
    {
        m_ship->pos = {shipPos.x - 2, shipPos.y};
    }
    else if (key[KEY_RIGHT] != 0)
    {
        m_ship->pos = {shipPos.x + 2, shipPos.y};
    }

    if (key[KEY_SPACE] != 0)
    {
        auto bullet = getIdleBullet();
        if (bullet)
        {
            auto& pos = m_ship->pos;
            bullet->pos = pos;
        }
    }


    for (auto& bullet : m_bullets)
    {
        auto& pos = bullet->pos;
        bullet->pos = {pos.x, pos.y - 5};
    }

}



}
