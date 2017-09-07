#ifndef ENGINE_H
#define ENGINE_H

#include "point.h"
#include "mikmod_sound.h"

#include "allegro.h"

#include <memory>
#include <set>
#include <vector>

#include <time.h>


namespace dos_game
{

struct GfxObject
{
    std::shared_ptr<BITMAP> bitmap;
    Point pos = {0,0};
    bool isActive = true;
    bool hasTransparency = false;
    int z = 0;

    int width()
    {
        return bitmap->w;
    }

    int height()
    {
        return bitmap->h;
    }

    Rect getBoundingBox()
    {
        return {pos.x, pos.y, bitmap->w, bitmap->h};
    }    
};

struct TextObject
{
    std::string text;
    Point pos;
};

class ZCompare
{
public:
    bool operator()(std::shared_ptr<GfxObject> lhs, std::shared_ptr<GfxObject> rhs) const
    {
        return lhs->z < rhs->z;
    }
};

struct MyScreen
{
    int x;
    int y;
    int w;
    int h;
    std::vector<Rect> dirty;
    BITMAP* myScreen;
};

class Engine
{
public:
    Engine(int screenWidth, int screenHeight);
    virtual ~Engine();

    std::shared_ptr<TextObject> createTextObject(const std::string& text);
    std::shared_ptr<GfxObject> createGfxObject(std::shared_ptr<BITMAP> image, bool hasTransparency = false, int z = 0);
    void unloadGfx(std::shared_ptr<GfxObject>);
    void unloadText(std::shared_ptr<TextObject>);

    void setBgImage(std::shared_ptr<BITMAP> bg);

    void drawScreen();

    int screenWidth() const
    {
        return m_screenWidth;
    }

    int screenHeight() const
    {
        return m_screenHeight;
    }

    void playMusic(const char* filepath, bool loop);

private:
    int m_screenWidth;
    int m_screenHeight;
    std::multiset<std::shared_ptr<GfxObject>, ZCompare> m_gfxObjects;
    std::multiset<std::shared_ptr<TextObject>> m_textObjects;
    std::shared_ptr<BITMAP> m_buffer;
    MikmodSound m_sound;

    std::shared_ptr<BITMAP> m_bg;

    decltype(uclock()) m_startTime;
    size_t m_frameCounter = 0;

    std::vector<MyScreen> m_screens;
    size_t m_currentScreen;
};

}

#endif // ENGINE_H
