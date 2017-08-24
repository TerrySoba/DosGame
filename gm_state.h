#ifndef GM_STATE_H
#define GM_STATE_H


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

#define MAX_BULLETS 5
extern Bullet bullets[MAX_BULLETS];

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
} Enemy;

extern Enemy enemy;


#endif
