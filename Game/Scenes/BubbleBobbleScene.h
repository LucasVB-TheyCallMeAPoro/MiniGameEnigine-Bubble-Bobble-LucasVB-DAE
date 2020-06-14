#pragma once
#include <GameScene.h>

#include "Box2D.h"
#include "../GameBase/UI.h"
#include "../GameBase/Level.h"
#include "../GameBase/Enemies.h"
#include "Font.h"
class PhysicsDebugRenderer;
namespace LVB
{
	class ContactListener;
	class GameObject;
	class BubbleBobbleScene : public LVB::GameScene
	{		
	public:
		static const int keyPlatform;
		static const int keyWall;
		enum entityType {
			BOUNDARY = 0x0001,
			PLATFORM = 0x0002,
			CHARACTER = 0x0004,
			ENEMY = 0x0008,
			BUBBLE = 0x000a,
			PICKUP = 0x000c
		};
		enum GameType
		{
			solo,
			coop,
			vs
		};
		BubbleBobbleScene(GameType type);
		~BubbleBobbleScene() override;
		BubbleBobbleScene(const BubbleBobbleScene& other) = delete;
		BubbleBobbleScene(BubbleBobbleScene&& other) noexcept = delete;
		BubbleBobbleScene& operator=(const BubbleBobbleScene& other) = delete;
		BubbleBobbleScene& operator=(BubbleBobbleScene&& other) noexcept = delete;

		void EnemyKilled() { m_NumberOfEnemies--; }

		ContactListener* GetListener() const;
	protected:
		void Initialize() override;
		void Update(float elapsedSec) override;
		void LateUpdate(float elapsedSec) override;
		void Render() const override;
	private:
		GameType m_Type;
		b2World* m_PhysicsWorld;
		PhysicsDebugRenderer* m_DebugRenderer;
		ContactListener* m_Listener;
		UI* m_Player1UI;
		UI* m_Player2UI;
		Character* m_Player1;
		Character* m_Player2;
		std::size_t m_LevelNumber;
		std::vector<Level> m_Levels;
		int m_NumberOfEnemies;
		float m_EnemySpawnOffsetTime{ 1.f };
		float m_EnemySpawnTimer{ 0.f };

		float m_LevelSwapTimer = 0;
		float m_LevelSwapTime = 5.f;

		void InitLevel();
		void InitPlayer();

		void LoadNewLevel();
		void LoadLevel(const std::vector<glm::ivec2>& positions);

		void SpawnEnemies();

		void InitControls();
		void CheckEnemies(float elapsedSec);
		//Level
		std::vector<GameObject*> m_LevelObjects;
		std::vector<b2Body*> m_LevelBodies;

		GameObject* m_LevelText;
	};
}

