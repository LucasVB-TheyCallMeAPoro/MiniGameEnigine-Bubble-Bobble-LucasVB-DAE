#pragma once
#include <GameScene.h>

#include "Box2D.h"
#include "../GameBase/UI.h"
#include "../GameBase/Level.h"
class PhysicsDebugRenderer;
namespace LVB
{
	class ContactListener;
	class GameObject;
	class BubbleBobbleScene : public LVB::GameScene
	{		
	public:
		enum entityType {
			BOUNDARY = 0x0001,
			PLATFORM = 0x0002,
			CHARACTER = 0x0004,
			ENEMY = 0x0008,
			BUBBLE = 0x0010,
		};
		BubbleBobbleScene();
		~BubbleBobbleScene() override;
		BubbleBobbleScene(const BubbleBobbleScene& other) = delete;
		BubbleBobbleScene(BubbleBobbleScene&& other) noexcept = delete;
		BubbleBobbleScene& operator=(const BubbleBobbleScene& other) = delete;
		BubbleBobbleScene& operator=(BubbleBobbleScene&& other) noexcept = delete;

	protected:
		void Initialize() override;
		void Update(float elapsedSec) override;
		void LateUpdate(float elapsedSec) override;
		void Render() const override;
	private:
		b2World* m_PhysicsWorld;
		PhysicsDebugRenderer* m_DebugRenderer;
		ContactListener* m_Listener;
		UI* m_Player1UI;
		UI* m_Player2UI;
		Character* m_Player1;
		std::size_t m_LevelNumber;
		std::vector<Level> m_Levels;

		void InitLevel();
		void InitPlayer();

		void LoadNewLevel();


		//Level
		std::vector<GameObject*> m_LevelObjects;
		std::vector<b2Body*> m_LevelBodies;
	};
}

