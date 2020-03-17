#pragma once
#include "Singleton.h"

namespace dae
{
	class GameScene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void CreateScene(GameScene* gs);
		void SetNbOfFrames(int frames);
		void Update(float elapsed);
		
		int GetNumberOfFrames() const;
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		~SceneManager();
		std::vector<GameScene*> m_GameScenes;
		int m_NrOfFrames = 0;
	};
}
