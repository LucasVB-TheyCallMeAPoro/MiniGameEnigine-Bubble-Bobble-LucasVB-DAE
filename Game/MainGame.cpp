#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
//#include <vld.h>
#endif

#include "SDL.h"
#include "Minigin.h"
#include "Scenes/DemoScene.h"
#include "Scenes/CommandAssignmentScene.h"

int main(int, char* []) {

	dae::Minigin engine;
	engine.Initialize();
	engine.LoadGame(new dae::CommandAssignmentScene{});
	engine.Run();
	engine.Cleanup();
	return 0;
}