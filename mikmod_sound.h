#ifndef MIKMOD_SOUND_H
#define MIKMOD_SOUND_H

namespace dos_game
{

class MikmodSound
{
public:
    MikmodSound();
    virtual ~MikmodSound();

    void play(const char* modulePath, bool loop);

    void update();

private:
    void* m_module = nullptr;

};

}

#endif // MIKMOD_SOUND_H
