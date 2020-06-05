#pragma once
#include "Singleton.h"
#include <string>
#include <vector>
namespace LVB
{
	class GameScene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void CreateScene(GameScene* gs);
		void SetNbOfFrames(int frames);
		void Update(float elapsed);
		void LateUpdate(float elapsed);
		
		void SetActiveGameScene(std::string name);
		int GetNumberOfFrames() const;
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		~SceneManager();
		std::vector<GameScene*> m_GameScenes;
		GameScene* m_ActiveScene, * m_NewActiveScene;
		int m_NrOfFrames = 0;
	};
}
