#include "MiniginPCH.h"
#include "Audio.h"
#include <iostream>
NullAudio ServiceLocator::defaultAudioService{};
Audio* ServiceLocator::audioService = new NullAudio();
void NullAudio::PlaySound(int soundID)
{
	std::cout << "Play sound number " << soundID << "\n";
}
void NullAudio::StopAllSound()
{
	std::cout << "Stop all sounds \n";
}

void NullAudio::StopSound(int soundID)
{
	std::cout << "Stop sound number " << soundID << "\n";
}

void ServiceLocator::RegisterAudioService(Audio* service)
{
	audioService = (service == nullptr) ? &defaultAudioService : service;
}
