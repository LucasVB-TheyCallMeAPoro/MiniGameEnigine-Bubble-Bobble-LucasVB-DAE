#pragma once
#include "GameScene.h"
#include "BubbleBobbleScene.h"
#include "../GameBase/Button.h"
class MainMenu : public LVB::GameScene
{
public:
	MainMenu();
	~MainMenu() override;
	MainMenu(const MainMenu& other) = delete;
	MainMenu(MainMenu&& other) noexcept = delete;
	MainMenu& operator=(const MainMenu& other) = delete;
	MainMenu& operator=(MainMenu&& other) noexcept = delete;
protected:
	void Initialize() override;
	void Update(float elapsedSec) override;
	void LateUpdate(float elapsedSec) override;
	void Render() const override;

private:

	Button* m_LoadCoop;
	Button* m_LoadSolo;

	static void LoadGame(LVB::BubbleBobbleScene::GameType type);

};
