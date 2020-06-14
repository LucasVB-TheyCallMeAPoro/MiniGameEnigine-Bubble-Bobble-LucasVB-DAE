#pragma once
#include <GameScene.h>

class VictorySCENE : public LVB::GameScene
{
public:
	VictorySCENE();
protected:
	void Initialize() override;
	void Update(float elapsedSec) override;
	void LateUpdate(float elapsedSec) override;
	void Render() const override;

private:
};

