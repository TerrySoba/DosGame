#include "gm_state.h"

#include "point.h"
#include "image_utils.h"
#include "first_enemy.h"
#include "mikmod_sound.h"

#include <allegro.h>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <memory>
#include <exception>
#include <cstring>
#include <array>

namespace dos_game
{

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



#define SINE_TABLE_SIZE 256

int sineTable[SINE_TABLE_SIZE];

bool collision(const Rect& smallerObject, const Rect& largerObject)
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


void calcPhysics()
{
    for (auto& bullet : bullets)
    {
        bullet.x += bullet.dx;
        bullet.y += bullet.dy;
    }

    // check for collision
    for (auto& bullet : bullets)
    {
        if (collision(Rect{bullet.x, bullet.y, 4, 4},
                      Rect{enemy.x, enemy.y, 16, 16}))
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
    for (auto& bullet : bullets)
    {
        if (bullet.y + 4 < 0)
            return &bullet;
    }
    return NULL;
}

void clearBullets()
{
    for (auto& bullet :  bullets)
    {
        bullet.y = -100;
    }
}

#define SPINNER_COUNT 8
#define SPINNER_OFFSET (SINE_TABLE_SIZE / SPINNER_COUNT)


int startScreenSkew = 0;

void drawStartScreen(BITMAP* buffer, BITMAP* bg, BITMAP* spinner)
{
    // draw bg image to buffer
    blit(bg, buffer, 0, 0, 0, 0, bg->w, bg->h);

    startScreenSkew++;

    for (size_t i = 0; i < SPINNER_COUNT; ++i)
    {
        int x = sineTable[(gameTicks + SPINNER_OFFSET * i + (startScreenSkew >> 2)) % SINE_TABLE_SIZE] + 150;
        int y = sineTable[(gameTicks + SPINNER_OFFSET * i + SINE_TABLE_SIZE/4)      % SINE_TABLE_SIZE] + 110;

        draw_sprite(buffer, spinner, x, y);
    }

    textprintf_ex(buffer, font, 50, 100, makecol(255, 255, 255), makecol(0, 0, 0), "Press SPACEBAR to start game!");
}

void fillSineTable()
{
    for (int i = 0; i < SINE_TABLE_SIZE; ++i)
    {
        sineTable[i] = sin(1.0 / SINE_TABLE_SIZE * i * M_PI * 2) * 100;
    }
}


enum class GameState
{
    START_SCREEN,
    LEVEL1,
    DEATH,
};


GameState gameState;



int game_main(int argc, char* argv[])
{
    MikmodSound sound("music/test2.xm");

    try
    {
        fillSineTable();

        long long physicsCount = 0;
        score = 0;
        lives = 0;
        gameTicks = 0;

        Point shipPos = {0, 0};

        printf("Starting game!\n");

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

//        if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0)
//            abort_on_error("Could not install sound.");

        set_color_depth(8);

        if (set_gfx_mode(GFX_AUTODETECT, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0) != 0)
           abort_on_error("Could not set gfx mode.");


        install_int_ex(incrementTicks, BPS_TO_TIMER(120));


        PALETTE palette;

        int i = 0;

        for (i = 0; i < PAL_SIZE; ++i)
        {
            palette[i].r = (i >> 2) * 0;
            palette[i].g = (i >> 2);
            palette[i].b = (i >> 2) / 1.5;
        }

        set_palette(palette);

        auto ship = loadBitmap("gfx/ship.pcx");
        auto enemySprite = loadBitmap("gfx/enemy.pcx");
        auto bulletImage = loadBitmap("gfx/bullet.pcx");
        auto bg = loadBitmap("gfx/space_bg.pcx");

        std::shared_ptr<BITMAP> buffer(create_bitmap(320,240), [](auto ptr){ destroy_bitmap(ptr);});

        clearBullets();

        enemy.x = 100;
        enemy.y = 100;

        // load music
//        MIDI *music;
//        music = load_midi("music/61dws.mid");
        // music = load_midi("skm3.mid");
        // music = load_midi("smf.mid");
        // music = load_midi("jab.mid");
        // music = load_midi("thttts.mid");
        // music = load_midi("mm2wily1.mid");
//        if (!music)
//           abort_on_error("Couldn't load background music!");


        std::vector<std::shared_ptr<EnemyBase>> enemies;


        enemies.push_back(std::make_shared<FirstEnemy>("gfx/enemy.pcx"));


        // play_midi(music, 1);

        shipPos.y = SCREEN_HEIGHT - 50;


        gameState = GameState::START_SCREEN;

        // enter event loop
        while(key[KEY_ESC]==0)
        {
            switch(gameState)
            {
            case GameState::START_SCREEN:
                drawStartScreen(buffer.get(), bg.get(), enemySprite.get());

                if (key[KEY_SPACE])
                {
                    gameState = GameState::LEVEL1;
                }

                break;

            case GameState::LEVEL1:
                if (key[KEY_RIGHT])
                    shipPos.x += 4;

                if (key[KEY_LEFT])
                    shipPos.x -= 4;

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

                // shipPos.y = mouse_y;

                // now calc physics
                while (physicsCount < gameTicks)
                {
                    calcPhysics();
                    ++physicsCount;
                }

                for (auto enemy : enemies)
                {
                    enemy->act(Rect{shipPos.x,shipPos.y, ship->w, ship->h}, bullets);
                }

                // draw bg image to buffer
                blit(bg.get(), buffer.get(), 0, 0, 0, 0, bg->w, bg->h);

                // draw bullets
                for (const auto& bullet : bullets)
                {
                    draw_sprite(buffer.get(), bulletImage.get(), bullet.x, bullet.y);
                }


                // draw enemies
                for (auto enemy : enemies)
                {
                    const auto& pos = enemy->getPos();
                    draw_sprite(buffer.get(), enemy->getBitmap(), pos.x, pos.y);
                }


                // draw enemy
                draw_sprite(buffer.get(), enemySprite.get(), enemy.x, enemy.y);

                // draw the player ship
                draw_sprite(buffer.get(), ship.get(), shipPos.x, shipPos.y);

                // draw score text
                textprintf_ex(buffer.get(), font, 200, 230, makecol(255, 255, 255), makecol(0, 0, 0), "Score: %06d", score);
                textprintf_ex(buffer.get(), font, 10, 230, makecol(255, 255, 255), makecol(0, 0, 0), "Lives: %2d", lives);
                break;
            }


            // wait for vsync, then blit buffer to video memory
            vsync();
            blit(buffer.get(), screen, 0, 0, 0, 0, buffer->w, buffer->h);

            sound.update();

        }

        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        printf("Game by yoshi252 (2017)\nThank you for playing!\n");
    }
    catch (std::exception& ex)
    {
        printf("Caught exception. what(): %s\n", ex.what());
        return 1;
    }
    catch (...)
    {
        printf("Caught unknown exception.");
        return 1;
    }

    return 0;
}
END_OF_MAIN()

}

int main(int argc, char* argv[])
{
    return dos_game::game_main(argc, argv);
}
