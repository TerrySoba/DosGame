#include "first_enemy.h"

#include "image_utils.h"

namespace dos_game
{

FirstEnemy::FirstEnemy(const char* imagePath)
{
    m_bitmap = loadBitmap(imagePath);
    m_pos = {100, 20};
}

Rect FirstEnemy::getBoundingBox()
{
    return {m_pos.x, m_pos.y, m_bitmap->w, m_bitmap->h};
}

void FirstEnemy::act(const Rect& playerPos, const std::vector<Bullet>& bullets)
{
    if (m_actCount++ % 4 == 0)
    {
        if (m_pos.x > playerPos.x) m_pos.x--;
        if (m_pos.x < playerPos.x) m_pos.x++;
    }
}

BITMAP* FirstEnemy::getBitmap()
{
    return m_bitmap.get();
}

Point FirstEnemy::getPos()
{
    return m_pos;
}

}
