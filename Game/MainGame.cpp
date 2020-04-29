
#include "SDL.h"
#include "Minigin.h"
#include "Scenes/DemoScene.h"
#include "Scenes/CommandAssignmentScene.h"

int main(int, char* []) {

	LVB::Minigin engine;
	engine.Initialize();
	engine.LoadGame(new LVB::CommandAssignmentScene{});
	engine.Run();
	engine.Cleanup();
	return 0;
}