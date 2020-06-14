#include "VictorySCENE.h"
#include "GameObject.h"
#include "Renderer.h"
VictorySCENE::VictorySCENE()
	:GameScene{"VictoryScene"}
{
	LVB::Renderer::GetInstance().SetScale(1.f);
	LVB::Renderer::GetInstance().SetOrigin(0,0);
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
