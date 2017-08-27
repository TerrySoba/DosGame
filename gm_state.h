#ifndef GM_STATE_H
#define GM_STATE_H

#include <vector>

namespace dos_game
{

extern long long gameTicks;
extern int score;
extern int lives;

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
} Bullet;

extern std::vector<Bullet> bullets;

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
} Enemy;

extern Enemy enemy;

}

#endif
