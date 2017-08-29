#include "first_enemy.h"

#include "image_utils.h"

namespace dos_game
{

FirstEnemy::FirstEnemy(std::shared_ptr<GfxObject> image)
{
    m_image = image;
    m_pos = {100, 20};
}

Rect FirstEnemy::getBoundingBox()
{

    return m_image->getBoundingBox();
}

void FirstEnemy::act(const Rect& playerPos, const std::vector<Bullet>& bullets)
{
    if (m_actCount++ % 4 == 0)
    {
        if (m_pos.x > playerPos.x) m_pos.x--;
        if (m_pos.x < playerPos.x) m_pos.x++;
    }
}

std::shared_ptr<GfxObject> FirstEnemy::getGfxObject()
{
    return m_image;
}

Point FirstEnemy::getPos()
{
    return m_pos;
}

}
