#ifndef _SOUND_H
#define _SOUND_H
#define _USE_MATH_DEFINES

#include <Windows.h>
#include <map>
#include <string>
#include <iostream>
#include <fstream>



struct WaveHeader
{
    DWORD chunkID;       // 0x52494646 "RIFF" in big endian
    DWORD chunkSize;     // 4 + (8 + subChunk1Size) + (8 + subChunk2Size)
    DWORD format;        // 0x57415645 "WAVE" in big endian

    DWORD subChunk1ID;   // 0x666d7420 "fmt " in big endian
    DWORD subChunk1Size; // 16 for PCM
    WORD  audioFormat;   // 1 for PCM
    WORD  numChannels;   // 1 for mono, 2 for stereo
    DWORD sampleRate;    // 8000, 22050, 44100, etc...
    DWORD byteRate;      // sampleRate * numChannels * bitsPerSample/8
    WORD  blockAlign;    // numChannels * bitsPerSample/8
    WORD  bitsPerSample; // number of bits (8 for 8 bits, etc...)

    DWORD subChunk2ID;   // 0x64617461 "data" in big endian
    DWORD subChunk2Size; // numSamples * numChannels * bitsPerSample/8 (this is the actual data size in bytes)
};

class Sound
{
    private:
        std::map<std::string, char*> soundData;

    public:
        Sound();
        ~Sound();
        void playSound(std::string key, bool async = true);
        bool loadWave(std::string key, char* filename);


};




#endif // _SOUND_H