#include "mikmod_sound.h"

#include <mikmod.h>
#include <unistd.h>

MikmodSound::MikmodSound(const char* modulePath)
{
    /* register all the drivers */
    MikMod_RegisterAllDrivers();

    /* register all the module loaders */
    MikMod_RegisterAllLoaders();

    /* initialize the library */
    md_mode |= DMODE_SOFT_MUSIC;
    if (MikMod_Init("")) {
        fprintf(stderr, "Could not initialize sound, reason: %s\n",
                MikMod_strerror(MikMod_errno));
        return;
    }

    /* load module */
    m_module = (void*)Player_Load(modulePath, 64, 0);

    if (m_module) {
        ((MODULE*)m_module)->loop = 1;
        ((MODULE*)m_module)->wrap = 1;

        /* start module */
        Player_Start((MODULE*)m_module);
    }
    else
    {
        fprintf(stderr, "Could not load module, reason: %s\n",
                MikMod_strerror(MikMod_errno));
    }
}

MikmodSound::~MikmodSound()
{
    Player_Stop();
    Player_Free((MODULE*)m_module);

    /* give up */
    MikMod_Exit();
}

void MikmodSound::update()
{
    MikMod_Update();
}
