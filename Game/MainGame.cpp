
#include "SDL.h"
#include "Minigin.h"
#include <SceneManager.h>
#include "Scenes/DemoScene.h"
#include "Scenes/CommandAssignmentScene.h"
#include "Scenes/BubbleBobbleScene.h"
#include "Scenes/VictorySCENE.h"
#include "Scenes/LoseScene.h"
int main(int, char* []) {

	LVB::Minigin engine;
	engine.Initialize();
	LVB::SceneManager::GetInstance().CreateScene(new LVB::BubbleBobbleScene{});
	LVB::SceneManager::GetInstance().CreateScene(new VictorySCENE{});
	LVB::SceneManager::GetInstance().CreateScene(new LoseScene{});
	
	//engine.LoadGame();
	engine.Run();
	engine.Cleanup();
	return 0;
}