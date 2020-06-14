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
		virtual void Render() const = 0;

		virtual void SceneActivated() {}
		virtual void SceneDeactivated() {}

	private:

		void RootRender() const;
		void RootUpdate(float elapsed);

		
		friend class SceneManager;
		std::vector<GameObject*> m_pGameObjects;
		std::vector<GameObject*> m_pToRemove;
		std::string m_SceneName;

		//For Threading
		static void UpdateGameObjects(GameScene* scene,float elapsed, std::size_t begin, std::size_t end);
		void pRemoveGameObject(GameObject* obj);
	};
}

