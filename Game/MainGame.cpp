
#include "SDL.h"
#include "Minigin.h"
#include <SceneManager.h>
#include "Scenes/DemoScene.h"
#include "Scenes/CommandAssignmentScene.h"
#include "Scenes/BubbleBobbleScene.h"
int main(int, char* []) {

	LVB::Minigin engine;
	engine.Initialize();
	LVB::SceneManager::GetInstance().CreateScene(new LVB::BubbleBobbleScene{});
	//LVB::SceneManager::GetInstance().CreateScene(new LVB::DemoScene{});
	//engine.LoadGame();
	engine.Run();
	engine.Cleanup();
	return 0;
}