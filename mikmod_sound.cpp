#include "mikmod_sound.h"

#include "logging.h"

#include <mikmod.h>
#include <unistd.h>

namespace dos_game
{

MikmodSound::MikmodSound()
{
    /* register all the drivers */
    MikMod_RegisterAllDrivers();

    /* register all the module loaders */
    MikMod_RegisterAllLoaders();

    /* initialize the library */
    md_mode |= DMODE_SOFT_MUSIC;
    if (MikMod_Init("")) {
        THROW_EXCEPTION("Could not initialize sound, reason: " <<
                        MikMod_strerror(MikMod_errno));
    }


}

MikmodSound::~MikmodSound()
{
    if(m_module)
    {
        Player_Stop();
        Player_Free((MODULE*)m_module);
    }

    /* give up */
    MikMod_Exit();
}

void MikmodSound::play(const char *modulePath, bool loop)
{
    if (m_module)
    {
        Player_Free((MODULE*)m_module);
    }

    /* load module */
    m_module = (void*)Player_Load(modulePath, 64, 0);

    if (m_module) {
        Player_Stop();
        ((MODULE*)m_module)->loop = loop;
        ((MODULE*)m_module)->wrap = loop;

        /* start module */
        Player_Start((MODULE*)m_module);
    }
    else
    {
        THROW_EXCEPTION("Could not load module, reason: " <<
                        MikMod_strerror(MikMod_errno));
    }
}

void MikmodSound::update()
{
    MikMod_Update();
}

}
