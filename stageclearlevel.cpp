#include "stageclearlevel.h"

#include "image_utils.h"

#include <time.h>

namespace dos_game
{

StageClearLevel::StageClearLevel(std::shared_ptr<Level> nextLevel) :
    m_nextLevel(nextLevel)
{
}

void StageClearLevel::onLoad(std::shared_ptr<LevelContext> context)
{
    auto bgImage = loadBitmap("gfx/space_bg.pcx");
    m_bg = context->getEngine()->createGfxObject(bgImage, false, -1);
    auto clear1Image = loadBitmap("gfx/clear1.pcx");
    m_clear1 = context->getEngine()->createGfxObject(clear1Image, true, 2);
    auto clear2Image = loadBitmap("gfx/clear2.pcx");
    m_clear2 = context->getEngine()->createGfxObject(clear2Image, true, 1);


    m_clear1->pos = {70, 60};
    m_clear2->pos = {40, 80};

    context->getEngine()->playMusic("music/victory.xm", false);

    m_startTime = uclock();
}

void StageClearLevel::onExit(std::shared_ptr<LevelContext> context)
{
    auto& engine = *context->getEngine();
    engine.unloadGfx(m_bg);
    engine.unloadGfx(m_clear1);
    engine.unloadGfx(m_clear2);
}

void StageClearLevel::act(std::shared_ptr<LevelContext> context)
{
    if (m_clear2->pos.x < m_clear1->pos.x) ++m_speed.x;
    else --m_speed.x;

    if (m_clear2->pos.y < m_clear1->pos.y) ++m_speed.y;
    else --m_speed.y;

    m_clear2->pos = m_clear2->pos + m_speed;


    if (((uclock() - m_startTime) / UCLOCKS_PER_SEC) > 4)
    {
        m_clear1->pos.y += dy;
        dy++;
    }

    if (((uclock() - m_startTime) / UCLOCKS_PER_SEC) > 6)
    {
        context->setActiveLevel(m_nextLevel);
        m_nextLevel.reset();
    }


}

}
