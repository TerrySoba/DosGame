#include "image_utils.h"
#include "mikmod_sound.h"
#include "engine.h"
#include "level_holder.h"
#include "title_screen.h"


#include "logging.h"

namespace dos_game
{

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;

void initAllegro()
{
    if (allegro_init() != 0)
        THROW_EXCEPTION("Could not init allegro: " << allegro_error);

    if (install_timer() != 0)
        THROW_EXCEPTION("Could not install timer: " << allegro_error);

    if (install_keyboard() != 0)
        THROW_EXCEPTION("Could not install keyboard: " << allegro_error);
}

void setPaletteToGreen()
{
    PALETTE palette;

    int i = 0;

    for (i = 0; i < PAL_SIZE; ++i)
    {
        palette[i].r = (i >> 2) * 0;
        palette[i].g = (i >> 2);
        palette[i].b = (i >> 2) / 1.5;
    }

    set_palette(palette);
}


int game_main(int argc, char* argv[])
{
    try
    {
        printf("Starting game!\n");

        initAllegro();
        set_color_depth(8);

        if (set_gfx_mode(GFX_AUTODETECT, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT * 2) != 0)
           THROW_EXCEPTION("Could not set gfx mode: " << allegro_error);

        setPaletteToGreen();

        auto engine = std::make_shared<Engine>(SCREEN_WIDTH, SCREEN_HEIGHT);

        engine->playMusic("music/test2.xm", true);

        LevelHolder levels(engine, std::make_shared<TitleScreen>());

        // enter event loop
        while(key[KEY_ESC]==0)
        {
            levels.act();
            engine->drawScreen();
        }

        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        printf("Game by yoshi252 (2017)\nThank you for playing!\n");
    }
    catch (std::exception& ex)
    {
        if (screen != NULL)
            set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        printf("Caught exception. what(): %s\n", ex.what());
        return 1;
    }
    catch (...)
    {
        if (screen != NULL)
            set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        printf("Caught unknown exception.");
        return 1;
    }

    return 0;
}

}

int main(int argc, char* argv[])
{
    return dos_game::game_main(argc, argv);
}

