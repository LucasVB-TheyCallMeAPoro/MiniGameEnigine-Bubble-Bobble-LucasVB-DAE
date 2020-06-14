#include "VictorySCENE.h"
#include "GameObject.h"
VictorySCENE::VictorySCENE()
	:GameScene{"VictoryScene"}
{
	auto go = new LVB::GameObject{};
	go->SetTexture("BBSprites/VictoryScreen.png");
	this->AddGameObject(go);
}

void VictorySCENE::Initialize()
{
}

void VictorySCENE::Update(float elapsedSec)
{
}

void VictorySCENE::LateUpdate(float elapsedSec)
{
}

void VictorySCENE::Render() const
{
}
