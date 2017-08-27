#ifndef MIKMOD_SOUND_H
#define MIKMOD_SOUND_H

namespace dos_game
{

class MikmodSound
{
public:
    MikmodSound(const char* modulePath);
    virtual ~MikmodSound();

    void update();

private:
    void* m_module;

};

}

#endif // MIKMOD_SOUND_H
