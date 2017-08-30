#include "engine.h"

#include "image_utils.h"

namespace dos_game
{

GfxObject::GfxObject(std::shared_ptr<BITMAP> image, const Point& pos, bool transparency, int z) :
    m_bitmap(image),
    m_pos(pos),
    m_hasTransparency(transparency),
    m_z(z)
{
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


Engine::Engine(int screenWidth, int screenHeight) :
    m_screenWidth(screenWidth),
    m_screenHeight(screenHeight)
{
    m_buffer = std::shared_ptr<BITMAP>(create_bitmap(m_screenWidth, m_screenHeight), [](auto ptr){ destroy_bitmap(ptr);});
}

Engine::~Engine()
{

}


std::shared_ptr<GfxObject> Engine::createGfxObject(std::shared_ptr<BITMAP> image, bool hasTransparency, int z)
{
    auto ptr = std::shared_ptr<GfxObject>(new GfxObject(image, {0,0}, hasTransparency, z));

    m_gfxObjects.insert(ptr);

    return ptr;
}

std::shared_ptr<TextObject> Engine::createTextObject(const std::string& text)
{
    auto txt = std::make_shared<TextObject>();
    txt->text = text;
    txt->pos = {0,0};
    m_textObjects.insert(txt);

    return txt;
}


void Engine::unloadText(std::shared_ptr<TextObject> text)
{
    auto it = m_textObjects.find(text);
    if (it != m_textObjects.end()) m_textObjects.erase(it);
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

    for (const auto& obj : m_textObjects)
    {
        auto& pos = obj->pos;
        textout_ex(m_buffer.get(), font, obj->text.c_str(), pos.x, pos.y,
                         makecol(255, 255, 255), -1);
    }

    vsync();
    blit(m_buffer.get(), screen, 0, 0, 0, 0, m_buffer->w, m_buffer->h);
}


}
