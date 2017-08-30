#ifndef LEVEL_HOLDER_H
#define LEVEL_HOLDER_H

#include "engine.h"
#include <memory>

namespace dos_game
{

class Level;

class LevelContext : public std::enable_shared_from_this<LevelContext>
{
public:
    LevelContext(std::shared_ptr<Engine> m_engine);

    void setActiveLevel(std::shared_ptr<Level> level);
    void checkTransiton();
    void act();

    std::shared_ptr<Engine> getEngine();

private:
    std::shared_ptr<Level> m_currentLevel;
    std::shared_ptr<Level> m_nextLevel;
    std::shared_ptr<Engine> m_engine;
};


class Level
{
public:
    virtual ~Level() {}

    // this method is called when the level loads
    virtual void onLoad(std::shared_ptr<LevelContext> context) = 0;

    // this method is called shortly before the level has ended
    virtual void onExit(std::shared_ptr<LevelContext> context) = 0;

    // this method is called regularily as long as the level is active
    // This is called at least once per drawn frame.
    virtual void act(std::shared_ptr<LevelContext> context) = 0;
};


class LevelHolder
{
public:
    LevelHolder(std::shared_ptr<Engine> engine, std::shared_ptr<Level> initialLevel);

    void act();

private:
    std::shared_ptr<LevelContext> m_context;

};

}

#endif // LEVEL_HOLDER_H
