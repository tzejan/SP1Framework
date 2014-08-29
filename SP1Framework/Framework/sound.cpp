#include "sound.h"
#include <stdlib.h>

Sound::Sound()
{
}

Sound::~Sound()
{
    // free up memory used by the sound buffer
    for (std::map<std::string,char *>::iterator it = soundData.begin(); it != soundData.end(); ++it)
    {
        delete [] it->second;
    }

}

void Sound::playSound(std::string key, bool async)
{
    std::map<std::string, char*>::iterator it = soundData.find(key);
    if (it != soundData.end())
    {
        DWORD flag = async? SND_MEMORY | SND_ASYNC : SND_MEMORY;
        PlaySound(it->second, NULL, flag );
    }
}

bool Sound::loadWave(std::string key, char* filename)
{
    std::ifstream waveFile(filename, std::ios::in | std::ios::binary | std::ios::ate);

    if (!waveFile.is_open())
    {
        return false;
    }

    std::streampos size = waveFile.tellg();
    char * memblock = new char [size];
    waveFile.seekg (0, std::ios::beg);
    waveFile.read (memblock, size);
  
    waveFile.close();
    soundData[key] = memblock;

    return true;
}


