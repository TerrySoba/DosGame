#include "count_level.h"
#include "enemy_level.h"
#include "image_utils.h"
#include "first_enemy.h"

#include "stageclearlevel.h"

namespace dos_game
{


CountLevel::CountLevel() :
    m_enemyOne(new FirstEnemy(16, 16)),
    m_enemyTwo(new FirstEnemy(16, 16, {100, 100}))
{

}

void CountLevel::onLoad(std::shared_ptr<LevelContext> context)
{
    auto bgImage = loadBitmap("gfx/space_bg.pcx");
    m_bg = context->getEngine()->createGfxObject(bgImage, false, -1);

    auto oneImage = loadBitmap("gfx/one.pcx");
    m_one = context->getEngine()->createGfxObject(oneImage, true);

    auto twoImage = loadBitmap("gfx/two.pcx");
    m_two = context->getEngine()->createGfxObject(twoImage, true);

    auto shipImage = loadBitmap("gfx/ship.pcx");
    m_ship = context->getEngine()->createGfxObject(shipImage, true);

    m_ship->pos = {100, 200};

    auto bulletImage = loadBitmap("gfx/bullet.pcx");
    for (size_t i = 0; i < 5; ++i)
    {
        m_bullets.push_back(context->getEngine()->createGfxObject(bulletImage, true));
        m_bullets.back()->pos = {-100, -100};
    }


    m_levelName = context->getEngine()->createTextObject("Also know how to count?");
    m_levelName->pos = {10, 230};

    context->getEngine()->playMusic("music/test.xm", true);


}


void CountLevel::onExit(std::shared_ptr<LevelContext> context)
{
    auto& engine = *context->getEngine();

    engine.unloadGfx(m_bg);
    engine.unloadGfx(m_one);
    engine.unloadGfx(m_two);
    engine.unloadGfx(m_ship);
    for (auto bullet : m_bullets)
    {
        engine.unloadGfx(bullet);
    }

    engine.unloadText(m_levelName);

}


std::shared_ptr<GfxObject> CountLevel::getIdleBullet()
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

void CountLevel::act(std::shared_ptr<LevelContext> context)
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
        if (collision(bullet->getBoundingBox(), m_enemyOne->getBoundingBox()))
        {
            bullet->pos = {-100, -100};
            // m_enemy->pos = {100,100};
            m_enemyOne->hurt(1);
        }

        if (collision(bullet->getBoundingBox(), m_enemyTwo->getBoundingBox()))
        {
            bullet->pos = {-100, -100};
            // m_enemy->pos = {100,100};
            if (m_enemyOne->isDead())
            {
                m_enemyTwo->hurt(1);
            }
        }

        bulletBounds.push_back(bullet->getBoundingBox());
    }

    if (m_enemyTwo->isDead())
    {
        // go to next level
        context->setActiveLevel(std::make_shared<StageClearLevel>(std::make_shared<EnemyLevel>()));
    }

    m_enemyOne->act(m_ship->getBoundingBox(), bulletBounds);
    m_enemyTwo->act(m_ship->getBoundingBox(), bulletBounds);
    m_one->pos = m_enemyOne->getPos();
    m_two->pos = m_enemyTwo->getPos();
}



}
