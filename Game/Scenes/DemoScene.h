#pragma once
#include "GameScene.h"
namespace LVB
{
	class GameObject;
	class DemoScene : public GameScene
	{
	public:
		DemoScene();

		DemoScene(const DemoScene& other) = delete;
		DemoScene(DemoScene&& other) noexcept = delete;
		DemoScene& operator=(const DemoScene& other) = delete;
		DemoScene& operator=(DemoScene&& other) noexcept = delete;

	protected:
		void Initialize() override;
		void Update(float) override;
		void LateUpdate(float) override;
		void Render() const override;

		GameObject* m_fpsCounter;
	};
}

