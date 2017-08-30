#include "level_holder.h"

#include "logging.h"

namespace dos_game
{

LevelContext::LevelContext(std::shared_ptr<Engine> engine) :
    m_engine(engine)
{
}

void LevelContext::setActiveLevel(std::shared_ptr<Level> level)
{
    m_nextLevel = level;
}

void LevelContext::checkTransiton()
{
    if (m_nextLevel)
    {
        if (m_currentLevel)
        {
            m_currentLevel->onExit(shared_from_this());
            m_currentLevel.reset();
        }
        std::swap(m_nextLevel, m_currentLevel);
        m_currentLevel->onLoad(shared_from_this());
    }
}

void LevelContext::act()
{
    if (!m_currentLevel)
    {
        THROW_EXCEPTION("There is no current level.");
    }
    m_currentLevel->act(shared_from_this());
}

std::shared_ptr<Engine> LevelContext::getEngine()
{
    return m_engine;
}

LevelHolder::LevelHolder(std::shared_ptr<Engine> engine, std::shared_ptr<Level> initialLevel)
{
    m_context = std::make_shared<LevelContext>(engine);
    m_context->setActiveLevel(initialLevel);
}

void LevelHolder::act()
{
    m_context->checkTransiton();
    m_context->act();
}


}
