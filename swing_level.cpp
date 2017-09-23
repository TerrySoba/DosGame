#include "swing_level.h"
#include "count_level.h"
#include "image_utils.h"
#include "first_enemy.h"
#include <cmath>

#include "stageclearlevel.h"

namespace dos_game
{


SwingLevel::SwingLevel() :
    m_enemyActor(new FirstEnemy(16, 16))
{

}

void SwingLevel::onLoad(std::shared_ptr<LevelContext> context)
{
    auto bgImage = loadBitmap("gfx/space_bg.pcx");
    context->getEngine()->setBgImage(bgImage);

    auto enemyImage = loadBitmap("gfx/enemy.pcx");
    m_enemy = context->getEngine()->createGfxObject(enemyImage, true);

    m_enemy->pos = {100,100};
    m_speed = 1;
    m_angle = 0;

    auto shipImage = loadBitmap("gfx/ship.pcx");
    m_ship = context->getEngine()->createGfxObject(shipImage, true);

    m_ship->pos = {100, 200};

    auto bulletImage = loadBitmap("gfx/bullet.pcx");
    for (size_t i = 0; i < 5; ++i)
    {
        m_bullets.push_back(context->getEngine()->createGfxObject(bulletImage, true));
        m_bullets.back()->pos = {-100, -100};
    }


    m_levelName = context->getEngine()->createTextObject("Can't shoot?");
    m_levelName->pos = {10, 230};

    context->getEngine()->playMusic("music/test.xm", true);


}


void SwingLevel::onExit(std::shared_ptr<LevelContext> context)
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


std::shared_ptr<GfxObject> SwingLevel::getIdleBullet()
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

void SwingLevel::act(std::shared_ptr<LevelContext> context)
{
    const auto c = 100;

    m_angle += m_speed/100;

    int x = std::sin(m_angle)*c;
    int y = std::cos(m_angle)*c;


    m_enemy->pos = {x+100,y+100};


}



}
