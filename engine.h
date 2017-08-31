#ifndef ENGINE_H
#define ENGINE_H

#include "point.h"

#include "allegro.h"

#include <memory>
#include <set>


namespace dos_game
{

class GfxObject
{
public:
    GfxObject(std::shared_ptr<BITMAP> image, const Point& pos = {0,0}, bool transparency = false, int z = 0);

    virtual Rect getBoundingBox() const;
    virtual bool isActive() const;
    virtual bool hasTransparency() const;

    virtual void setPos(const Point& pos);
    virtual void setActive(bool active);
    virtual int getZ() const;

    virtual std::shared_ptr<BITMAP> getBitmap() const
    {
        return m_bitmap;
    }

private:
    std::shared_ptr<BITMAP> m_bitmap;
    Point m_pos;
    bool m_isActive = true;
    const bool m_hasTransparency;
    const int m_z;
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
        return lhs->getZ() < rhs->getZ();
    }
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

    void drawScreen();

private:
    int m_screenWidth;
    int m_screenHeight;
    std::multiset<std::shared_ptr<GfxObject>, ZCompare> m_gfxObjects;
    std::multiset<std::shared_ptr<TextObject>> m_textObjects;
    std::shared_ptr<BITMAP> m_buffer;
};

}

#endif // ENGINE_H