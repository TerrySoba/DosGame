#include "engine.h"

#include "image_utils.h"

namespace dos_game
{

Engine::Engine(int screenWidth, int screenHeight) :
    m_screenWidth(screenWidth),
    m_screenHeight(screenHeight),
    m_startTime(uclock())
{
    m_buffer = std::shared_ptr<BITMAP>(create_bitmap(m_screenWidth, m_screenHeight), [](auto ptr){ destroy_bitmap(ptr);});
    // m_buffer.reset(screen);


    m_screens =
    {
        {0, 0,   320, 240, {}, create_sub_bitmap(screen, 0, 0,   320, 240)},
        {0, 240, 320, 240, {}, create_sub_bitmap(screen, 0, 240, 320, 240)},
    };

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
    auto& curentScreen = m_screens[m_currentScreen];
    for (const Rect& dirtyRect : curentScreen.dirty)
    {
        if (m_bg)
        {
            blit(m_bg.get(), curentScreen.myScreen, dirtyRect.x, dirtyRect.y, dirtyRect.x, dirtyRect.y, dirtyRect.width, dirtyRect.height);
        }
        else
        {
            rectfill(curentScreen.myScreen, dirtyRect.x, dirtyRect.y, dirtyRect.x + dirtyRect.width, dirtyRect.y + dirtyRect.height, 0);
        }
    }

    curentScreen.dirty.clear();

    for (const auto& obj : m_gfxObjects)
    {
        const auto& pos = obj->pos;
        curentScreen.dirty.push_back({pos.x, pos.y, obj->bitmap.get()->w, obj->bitmap.get()->h});
        if (obj->hasTransparency)
        {
            draw_sprite(curentScreen.myScreen, obj->bitmap.get(), pos.x, pos.y);
        }
        else
        {
            blit(obj->bitmap.get(), screen, 0, 0, pos.x, pos.y, obj->width(), obj->height());
        }
    }

    for (const auto& obj : m_textObjects)
    {
        auto& pos = obj->pos;
        textout_ex(curentScreen.myScreen, font, obj->text.c_str(), pos.x, pos.y,
                         makecol(255, 255, 255), -1);
    }

#if 1
    auto diff = uclock() - m_startTime;
    auto runtime = diff / (double)UCLOCKS_PER_SEC;
    if (runtime > 0)
    {
        auto fps = m_frameCounter / runtime;
        textprintf_ex(curentScreen.myScreen, font, 0, 0, makecol(255, 255, 255), 0, "fps: %3.1f", fps);
    }

    ++m_frameCounter;
#endif

    scroll_screen(curentScreen.x, curentScreen.y);
    m_currentScreen = (m_currentScreen + 1) % m_screens.size();
}

void Engine::setBgImage(std::shared_ptr<BITMAP> bg)
{
    m_bg = bg;

    // set screen to be redrawn
    for (auto& curentScreen : m_screens)
    {
        curentScreen.dirty.push_back({0, 0, 320, 240});
    }
}

void Engine::playMusic(const char *filepath, bool loop)
{
    m_sound.play(filepath, loop);
}


}
