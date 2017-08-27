#ifndef SPRITE_H
#define SPRITE_H

#include "point.h"

#include <allegro.h>

namespace dos_game
{

class Sprite
{
public:
    virtual ~Sprite() {}
    virtual BITMAP* getBitmap() = 0;
    virtual Point getPos() = 0;
};

}

#endif // SPRITE_H
