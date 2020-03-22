#pragma once

class Audio
{
public:
	virtual ~Audio() = default;
	virtual void PlaySound(int soundID) = 0;
	virtual  void StopSound(int soundID) = 0;
	virtual void StopAllSound() = 0;
};
class NullAudio final : public Audio
{
public:
	void PlaySound(int soundID)  override;
	
	void StopAllSound() override;

	void StopSound(int soundID) override;
};

class ServiceLocator
{
public:
	static void Init() { audioService = &defaultAudioService; }
	static  Audio& GetAudio() { return *audioService; }
	static void RegisterAudioService(Audio* service);
private:
	static Audio* audioService;
	static NullAudio defaultAudioService;
};
