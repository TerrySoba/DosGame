#include "first_enemy.h"

#include <algorithm>

namespace dos_game
{

FirstEnemy::FirstEnemy(int width, int height, const Point& pos) :
    m_width(width),
    m_height(height),
    m_pos(pos)
{
}

void FirstEnemy::act(const Rect& playerPos, const std::vector<Rect>& bullets)
{
    if (playerPos.x > m_pos.x)
    {
        ++m_speed.x;
    }
    else
    {
        --m_speed.x;
    }

    m_pos = m_pos + Point({m_speed.x >> 4, m_speed.y >> 4});
}

void FirstEnemy::hurt(int amount)
{
    m_health = std::max(0, m_health - amount);

    if (isDead())
    {
        m_pos.y = -100;
    }

}

Rect FirstEnemy::getBoundingBox()
{
    return {m_pos.x, m_pos.y, m_width, m_height};
}

bool FirstEnemy::isDead()
{
    return (m_health <= 0);
}

}
