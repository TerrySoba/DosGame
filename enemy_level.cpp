#include "enemy_level.h"
#include "count_level.h"
#include "image_utils.h"
#include "first_enemy.h"

#include "stageclearlevel.h"

namespace dos_game
{


EnemyLevel::EnemyLevel() :
    m_enemyActor(new FirstEnemy(16, 16))
{

}

void EnemyLevel::onLoad(std::shared_ptr<LevelContext> context)
{
    auto bgImage = loadBitmap("gfx/space_bg.pcx");
    context->getEngine()->setBgImage(bgImage);

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


    m_levelName = context->getEngine()->createTextObject("Know how to shoot?");
    m_levelName->pos = {10, 230};

    context->getEngine()->playMusic("music/test.xm", true);


}


void EnemyLevel::onExit(std::shared_ptr<LevelContext> context)
{
    auto& engine = *context->getEngine();

    // engine.unloadGfx(m_bg);
    engine.unloadGfx(m_enemy);
    engine.unloadGfx(m_ship);
    for (auto bullet : m_bullets)
    {
        engine.unloadGfx(bullet);
    }

    engine.unloadText(m_levelName);

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
    // move player ship on keypresses
    auto& shipPos = m_ship->pos;
    if (key[KEY_LEFT] != 0)
    {
        m_ship->pos = {shipPos.x - 2, shipPos.y};
    }
    else if (key[KEY_RIGHT] != 0)
    {
        m_ship->pos = {shipPos.x + 2, shipPos.y};
    }    

    // limit horizontal movement of player ship
    auto& engine = *context->getEngine();
    if (shipPos.x < 0) shipPos.x = 0;
    if (shipPos.x + m_ship->bitmap->w > engine.screenWidth())
        shipPos.x = engine.screenWidth() - m_ship->bitmap->w;

    // shoot on space key press
    if (key[KEY_SPACE] != 0)
    {
        auto bullet = getIdleBullet();
        if (bullet)
        {
            bullet->pos = {shipPos.x + m_ship->width() / 2 - 2, shipPos.y};
        }
    }

    // move bullets
    for (auto& bullet : m_bullets)
    {
        auto& pos = bullet->pos;
        bullet->pos = {pos.x, pos.y - 5};
    }

    std::vector<Rect> bulletBounds;

    // check for bullet collisions
    for (auto& bullet : m_bullets)
    {
        if (collision(bullet->getBoundingBox(), m_enemy->getBoundingBox()))
        {
            bullet->pos = {-100, -100};
            // m_enemy->pos = {100,100};
            m_enemyActor->hurt(1);
        }

        bulletBounds.push_back(bullet->getBoundingBox());
    }

    if (m_enemyActor->isDead())
    {
        // go to next level
        context->setActiveLevel(std::make_shared<StageClearLevel>(std::make_shared<CountLevel>()));
    }

    m_enemyActor->act(m_ship->getBoundingBox(), bulletBounds);
    m_enemy->pos = m_enemyActor->getPos();
}



}
