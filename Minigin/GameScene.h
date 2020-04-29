#pragma once
#include <string>
#include <vector>

namespace LVB
{
	class GameObject;
	class SceneManager;

	class GameScene
	{
	public:
		GameScene(std::string sceneName);
		GameScene(const GameScene& other) = delete;
		GameScene(GameScene&& other) noexcept = delete;
		GameScene& operator=(const GameScene& other) = delete;
		GameScene& operator=(GameScene&& other) noexcept = delete;
		virtual ~GameScene();

		void AddGameObject(GameObject* obj);
		void RemoveGameObject(GameObject* obj);

		const std::vector<GameObject*>& GetGameObjects() const;
	protected:
		virtual void Initialize() = 0;
		virtual void Update(float) = 0;
		virtual void LateUpdate(float) = 0;
		virtual void Render() = 0;

		virtual void SceneActivated() {}
		virtual void SceneDeactivated() {}

	private:
		friend class SceneManager;
		std::vector<GameObject*> m_pGameObjects;
		std::string m_SceneName;
	};
}

