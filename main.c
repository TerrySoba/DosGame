#include "gm_state.h"

#include <stdio.h>
#include <allegro.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void abort_on_error(const char* message)
{
    if (screen != NULL)
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
    allegro_message("%s.\nLast Allegro error ‘%s’\n", message, allegro_error);
    exit(1);
}

void incrementTicks()
{
    ++gameTicks;
}

typedef struct
{
    int x;
    int y;
} Point;


#define SINE_TABLE_SIZE 256

int sineTable[SINE_TABLE_SIZE];


int collision(Bullet* bullet, Enemy* enemy)
{
    int bulletWidth = 4;
    int bulletHeight = 4;

    int enemyWidth = 16;
    int enemyHeight = 16;

    // check if at least one of the corners of the bullets lies inside of the enemy
    Point corners[4];
    corners[0].x = bullet->x;
    corners[0].y = bullet->y;
    corners[1].x = bullet->x + bulletWidth;
    corners[1].y = bullet->y;
    corners[2].x = bullet->x + bulletWidth;
    corners[2].y = bullet->y + bulletHeight;
    corners[2].x = bullet->x;
    corners[2].y = bullet->y + bulletHeight;

    for (int i = 0; i < 4; ++i)
    {
        if (corners[i].x >= enemy->x && corners[i].x < enemy->x + enemyWidth &&
            corners[i].y >= enemy->y && corners[i].y < enemy->y + enemyHeight)
        {
            return 1;
        }
    }
    return 0;
}


void calcPhysics()
{
    for (int i = 0; i < MAX_BULLETS; ++i)
    {
        bullets[i].x += bullets[i].dx;
        bullets[i].y += bullets[i].dy;
    }

    // check for collision
    for (int i = 0; i < MAX_BULLETS; ++i)
    {
        if (collision(&bullets[i], &enemy))
        {
            ++score;
            enemy.x = rand() % (SCREEN_WIDTH - 16);
            enemy.y = rand() % (SCREEN_HEIGHT - 70);
            break;
        }
    }
}


Bullet* getAvailableBullet()
{
    for (int i = 0; i < MAX_BULLETS; ++i)
    {
        if (bullets[i].y + 4 < 0)
            return &bullets[i];
    }
    return NULL;
}

void clearBullets()
{
    for (int i = 0; i < MAX_BULLETS; ++i)
    {
        bullets[i].y = -100;
    }
}


void drawStartScreen(BITMAP* buffer, BITMAP* bg, BITMAP* spinner)
{
    // draw bg image to buffer
    blit(bg, buffer, 0, 0, 0, 0, bg->w, bg->h);

    int x = sineTable[gameTicks % SINE_TABLE_SIZE] + 100;
    int y = sineTable[(gameTicks + SINE_TABLE_SIZE/4) % SINE_TABLE_SIZE] + 100;

    draw_sprite(buffer, spinner, x, y);

    textprintf_ex(buffer, font, 150, 230, makecol(255, 255, 255), makecol(0, 0, 0), "x:%3d y:%3d", x, y);

}

void fillSineTable()
{
    for (int i = 0; i < SINE_TABLE_SIZE; ++i)
    {
        sineTable[i] = sin(1.0 / SINE_TABLE_SIZE * i * M_PI * 2) * 100;
    }
}


int main(int argc, char* argv[])
{
    fillSineTable();


    long long physicsCount = 0;
    score = 0;
    lives = 0;
    gameTicks = 0;

    Point shipPos = {0, 0};

    printf("Starting game!");

    if (allegro_init() != 0)
    {
        fprintf(stderr, "Could not init allegro...");
        exit(1);
    }

    if (install_timer() != 0)
        abort_on_error("Could not install timer.");

    if (install_keyboard() != 0)
        abort_on_error("Could not install keyboard.");

    // if (install_mouse() == -1)
    //     abort_on_error("Could not install mouse.");

    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0)
        abort_on_error("Could not install sound.");

    set_color_depth(8);

    if (set_gfx_mode(GFX_MODEX, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0) != 0)
       abort_on_error("Could not set gfx mode.");


    install_int_ex(incrementTicks, BPS_TO_TIMER(120));


    PALETTE palette;

    int i = 0;

    for (i = 0; i < PAL_SIZE; ++i)
    {
        palette[i].r = (i >> 2) * 0;
        palette[i].g = (i >> 2);
        palette[i].b = (i >> 2) / 2;
    }

    set_palette(palette);

    BITMAP* ship = load_bitmap("ship.pcx", NULL);
    BITMAP* enemySprite = load_bitmap("enemy.pcx", NULL);
    BITMAP* bullet = load_bitmap("bullet.pcx", NULL);
    BITMAP* bg = load_bitmap("space_bg.pcx", NULL);
    BITMAP* buffer = create_bitmap(320,240);


    memset(bullets, 0, sizeof(Bullet) * MAX_BULLETS);
    clearBullets();

    enemy.x = 100;
    enemy.y = 100;

    // load music
    MIDI *music;
    music = load_midi("61dws.mid");
    // music = load_midi("skm3.mid");
    // music = load_midi("smf.mid");
    // music = load_midi("jab.mid");
    // music = load_midi("thttts.mid");
    // music = load_midi("mm2wily1.mid");
    if (!music)
       abort_on_error("Couldn't load background music!");



    play_midi(music, 1);

    shipPos.y = SCREEN_HEIGHT - 50;

    while(key[KEY_ESC]==0)
    {


        if (key[KEY_RIGHT])
            shipPos.x += 4;

        if (key[KEY_LEFT])
            shipPos.x -= 4;


        // shipPos.y = mouse_y;


        // now calc physics
        while (physicsCount < gameTicks)
        {
            calcPhysics();
            ++physicsCount;
        }

        // draw bg image to buffer
        blit(bg, buffer, 0, 0, 0, 0, bg->w, bg->h);

        // draw bullets
        for (int i = 0; i < MAX_BULLETS; ++i)
        {
            draw_sprite(buffer, bullet, bullets[i].x, bullets[i].y);
        }

        // draw enemy
        draw_sprite(buffer, enemySprite, enemy.x, enemy.y);

        // draw the player ship
        draw_sprite(buffer, ship, shipPos.x, shipPos.y);

        // draw score text
        textprintf_ex(buffer, font, 200, 230, makecol(255, 255, 255), makecol(0, 0, 0), "Score: %06d", score);
        textprintf_ex(buffer, font, 10, 230, makecol(255, 255, 255), makecol(0, 0, 0), "Lives: %2d", lives);

        // drawStartScreen(buffer, bg, enemySprite);

        // wait for vsync, then blit buffer to video memory
        vsync();
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);

        if (key[KEY_SPACE])
        {
            Bullet* bullet = getAvailableBullet();
            if (bullet)
            {
                bullet->dy = -3;
                bullet->x = shipPos.x + 14;
                bullet->y = shipPos.y;
            }
        }

    }

    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
    printf("Game by yoshi252 (2017)\nThank you for playing!\n");

    return 0;
}
END_OF_MAIN()
