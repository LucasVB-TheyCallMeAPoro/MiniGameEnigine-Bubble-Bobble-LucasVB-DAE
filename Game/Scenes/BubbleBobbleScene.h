#pragma once
#include <GameScene.h>
namespace LVB
{
	class GameObject;
	class BubbleBobbleScene : public LVB::GameScene
	{		
	public:
		BubbleBobbleScene();

		BubbleBobbleScene(const BubbleBobbleScene& other) = delete;
		BubbleBobbleScene(BubbleBobbleScene&& other) noexcept = delete;
		BubbleBobbleScene& operator=(const BubbleBobbleScene& other) = delete;
		BubbleBobbleScene& operator=(BubbleBobbleScene&& other) noexcept = delete;

	protected:
		void Initialize() override;
		void Update(float) override;
		void LateUpdate(float) override;
		void Render() const override;
	};
}

