#ifndef COUNT_LEVEL_H
#define COUNT_LEVEL_H

#include "level_holder.h"

#include <vector>

#include "enemy.h"

namespace dos_game
{

class CountLevel : public Level
{
public:
    CountLevel();

    // this method is called when the level loads
    virtual void onLoad(std::shared_ptr<LevelContext> context) override;

    // this method is called shortly before the level has ended
    virtual void onExit(std::shared_ptr<LevelContext> context) override;

    // this method is called regularily as long as the level is active
    // This is called at least once per drawn frame.
    virtual void act(std::shared_ptr<LevelContext> context) override;

private:
    std::shared_ptr<GfxObject> getIdleBullet();


private:
    std::shared_ptr<GfxObject> m_bg;
    std::shared_ptr<GfxObject> m_one;
    std::shared_ptr<GfxObject> m_two;
    std::shared_ptr<GfxObject> m_ship;

    std::shared_ptr<TextObject> m_levelName;

    std::vector<std::shared_ptr<GfxObject>> m_bullets;

    std::shared_ptr<Enemy> m_enemyOne;
    std::shared_ptr<Enemy> m_enemyTwo;
};

}

#endif // COUNT_LEVEL_H
