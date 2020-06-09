#pragma once
#include <GameScene.h>
#include "../GameBase/Level.h"
#include "Box2D.h"
class PhysicsDebugRenderer;
namespace LVB
{
	class GameObject;
	class BubbleBobbleScene : public LVB::GameScene
	{		
	public:
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
		Level m_Level;
		b2World* m_PhysicsWorld;
		PhysicsDebugRenderer* m_DebugRenderer;
	};
}

