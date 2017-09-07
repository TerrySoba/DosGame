#ifndef STAGECLEARLEVEL_H
#define STAGECLEARLEVEL_H

#include "level_holder.h"

#include <time.h>

namespace dos_game
{

class StageClearLevel : public Level
{
public:
    StageClearLevel(std::shared_ptr<Level> nextLevel);

    // this method is called when the level loads
    virtual void onLoad(std::shared_ptr<LevelContext> context) override;

    // this method is called shortly before the level has ended
    virtual void onExit(std::shared_ptr<LevelContext> context) override;

    // this method is called regularily as long as the level is active
    // This is called at least once per drawn frame.
    virtual void act(std::shared_ptr<LevelContext> context) override;

private:
    std::shared_ptr<GfxObject> m_clear1;
    std::shared_ptr<GfxObject> m_clear2;

    Point m_speed = {0, 0};

    decltype(uclock()) m_startTime;
    int dy = 0;

    std::shared_ptr<Level> m_nextLevel;
};

}

#endif // STAGECLEARLEVEL_H
