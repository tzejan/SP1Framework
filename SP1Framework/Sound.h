#pragma once
#include <vector>
#include <SDL_mixer.h>

class Sound
{
public:
	Sound();
	~Sound();
	void addSoundEffect(const char* path);
	void playSoundEffect(const int which);

private:
	std::vector<Mix_Chunk*> mSoundEffectBank;

};