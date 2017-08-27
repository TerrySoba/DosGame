#include "engine.h"

#include "image_utils.h"

namespace dos_game
{

GfxObject::GfxObject(const char* imagePath, const Point& pos, bool transparency, int z) :
    m_pos(pos),
    m_hasTransparency(transparency),
    m_z(z)
{
    m_bitmap = loadBitmap(imagePath);
}

int GfxObject::getZ() const
{
    return m_z;
}

Rect GfxObject::getBoundingBox() const
{
    return {m_pos.x, m_pos.y, m_bitmap->w, m_bitmap->w};
}

bool GfxObject::isActive() const
{
    return m_isActive;
}

bool GfxObject::hasTransparency() const
{
    return m_hasTransparency;
}

void GfxObject::setPos(const Point& pos)
{
    m_pos = pos;
}

void GfxObject::setActive(bool active)
{
    m_isActive = active;
}


Engine::Engine()
{
    m_buffer = std::shared_ptr<BITMAP>(create_bitmap(320,240), [](auto ptr){ destroy_bitmap(ptr);});
}

Engine::~Engine()
{

}


std::shared_ptr<GfxObject> Engine::loadGfx(const char* filename, bool hasTransparency, int z)
{
    auto ptr = std::shared_ptr<GfxObject>(new GfxObject(filename, {0,0}, hasTransparency, z));

    m_gfxObjects.insert(ptr);

    return ptr;
}

void Engine::unloadGfx(std::shared_ptr<GfxObject> gfxObject)
{
    auto it = m_gfxObjects.find(gfxObject);
    if (it != m_gfxObjects.end()) m_gfxObjects.erase(it);
}

void Engine::drawScreen()
{
    for (const auto& obj : m_gfxObjects)
    {
        const auto bb = obj->getBoundingBox();
        if (obj->hasTransparency())
        {
            draw_sprite(m_buffer.get(), obj->getBitmap().get(), bb.x, bb.y);
        }
        else
        {
            blit(obj->getBitmap().get(), m_buffer.get(), 0, 0, bb.x, bb.y, bb.width, bb.height);
        }
    }

    vsync();
    blit(m_buffer.get(), screen, 0, 0, 0, 0, m_buffer->w, m_buffer->h);

}


}
