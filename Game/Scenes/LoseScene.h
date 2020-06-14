#pragma once
#include "GameScene.h"
class LoseScene : public LVB::GameScene
{
public:
	LoseScene();
protected:
	void Initialize() override;
	void Update(float elapsedSec) override;
	void LateUpdate(float elapsedSec) override;
	void Render() const override;

private:
};