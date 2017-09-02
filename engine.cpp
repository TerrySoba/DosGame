#include "engine.h"

#include "image_utils.h"

namespace dos_game
{

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
    auto ptr = std::make_shared<GfxObject>();

    ptr->bitmap = image;
    ptr->hasTransparency = hasTransparency;
    ptr->z = z;

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
        const auto& pos = obj->pos;
        if (obj->hasTransparency)
        {
            draw_sprite(m_buffer.get(), obj->bitmap.get(), pos.x, pos.y);
        }
        else
        {
            blit(obj->bitmap.get(), m_buffer.get(), 0, 0, pos.x, pos.y, obj->width(), obj->height());
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

void Engine::playMusic(const char *filepath, bool loop)
{
    m_sound.play(filepath, loop);
}


}
