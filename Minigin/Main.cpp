#include "MiniginPCH.h"
//#include < dxgidebug.h >
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "Minigin.h"

int main(int, char*[]) {
	//_CrtSetBreakAlloc(41192);
	dae::Minigin engine;
	engine.Run();
    return 0;
}