#ifndef POINT_H
#define POINT_H

#include <array>

namespace dos_game
{

struct Point
{
    int x;
    int y;
};


struct Rect
{
    int x;
    int y;
    int width;
    int height;
};


static inline bool collision(const Rect& smallerObject, const Rect& largerObject)
{
    // check if at least one of the corners of the smallerObject
    // lies inside of the largerObject
    std::array<Point, 4> corners;
    corners[0].x = smallerObject.x;
    corners[0].y = smallerObject.y;
    corners[1].x = smallerObject.x + smallerObject.width;
    corners[1].y = smallerObject.y;
    corners[2].x = smallerObject.x + smallerObject.width;
    corners[2].y = smallerObject.y + smallerObject.height;
    corners[3].x = smallerObject.x;
    corners[3].y = smallerObject.y + smallerObject.height;

    for (const auto& corner : corners)
    {
        if (corner.x >= largerObject.x && corner.x < largerObject.x + largerObject.width &&
            corner.y >= largerObject.y && corner.y < largerObject.y + largerObject.height)
        {
            return true;
        }
    }
    return false;
}



}

#endif // POINT_H
