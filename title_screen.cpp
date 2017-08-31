#include "title_screen.h"

#include "image_utils.h"

#include "enemy_level.h"

namespace dos_game
{

TitleScreen::TitleScreen()
{

}

// this method is called when the level loads
void TitleScreen::onLoad(std::shared_ptr<LevelContext> context)
{
    auto bgImage = loadBitmap("gfx/space_bg.pcx");
    m_bg = context->getEngine()->createGfxObject(bgImage, false, -1);

    auto enemyImage = loadBitmap("gfx/enemy.pcx");
    m_enemy = context->getEngine()->createGfxObject(enemyImage, true);
}

// this method is called shortly before the level has ended
void TitleScreen::onExit(std::shared_ptr<LevelContext> context)
{
    context->getEngine()->unloadGfx(m_bg);
    context->getEngine()->unloadGfx(m_enemy);
}

// this method is called regularily as long as the level is active
// This is called at least once per drawn frame.
void TitleScreen::act(std::shared_ptr<LevelContext> context)
{
    auto bb = m_enemy->getBoundingBox();
    m_enemy->setPos({(bb.x + 1) % 320, (bb.y + 1) % 240});


    if (key[KEY_SPACE] != 0)
    {
        context->setActiveLevel(std::make_shared<EnemyLevel>());
    }
}


}
