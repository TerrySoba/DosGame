#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "level_holder.h"
#include <vector>

namespace dos_game
{

class TitleScreen : public Level
{
public:
    TitleScreen();

    // this method is called when the level loads
    virtual void onLoad(std::shared_ptr<LevelContext> context) override;

    // this method is called shortly before the level has ended
    virtual void onExit(std::shared_ptr<LevelContext> context) override;

    // this method is called regularily as long as the level is active
    // This is called at least once per drawn frame.
    virtual void act(std::shared_ptr<LevelContext> context) override;

private:
    std::vector<std::shared_ptr<GfxObject>> m_enemies;
    std::shared_ptr<TextObject> m_text;
    size_t frameCount = 0;

};

}

#endif // TITLE_SCREEN_H
