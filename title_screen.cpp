#include "title_screen.h"

#include "image_utils.h"

#include "enemy_level.h"

#include "logging.h"

#include <cstdlib>

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
    for (size_t i = 0; i < 10; ++i)
    {
        m_enemies.push_back(context->getEngine()->createGfxObject(enemyImage, true));
        m_enemies.back()->pos = {rand() % 320, rand() % 240};
    }

    m_text = context->getEngine()->createTextObject("Press SPACEBAR to start game!");
    m_text->pos = {50, 80};

}

// this method is called shortly before the level has ended
void TitleScreen::onExit(std::shared_ptr<LevelContext> context)
{
    context->getEngine()->unloadGfx(m_bg);
    for (auto& enemy : m_enemies)
    {
        context->getEngine()->unloadGfx(enemy);
    }

    context->getEngine()->unloadText(m_text);

}

// this method is called regularily as long as the level is active
// This is called at least once per drawn frame.
void TitleScreen::act(std::shared_ptr<LevelContext> context)
{
    for (auto& enemy : m_enemies)
    {
        auto& pos = enemy->pos;
        pos = {(pos.x + 1) % 320, (pos.y + 1) % 240};
    }


    if (key[KEY_SPACE] != 0)
    {
        context->setActiveLevel(std::make_shared<EnemyLevel>());
    }
}


}
