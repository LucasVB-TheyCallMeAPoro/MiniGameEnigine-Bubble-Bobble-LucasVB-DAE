#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextComponent.h"
#include "GameObject.h"
#include "DemoScene.h"
using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	SceneManager::GetInstance().CreateScene(new DemoScene());
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");


}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		int fps = 60;
		std::chrono::high_resolution_clock::duration updateDuration{ 1'000'000'000 / fps };
		auto previousTime = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::duration catchUp{};
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			const std::chrono::high_resolution_clock::duration elapsed = currentTime - previousTime;
			previousTime = currentTime;
			catchUp += elapsed;
			doContinue = input.ProcessInput();
			
			while (catchUp >= updateDuration)
			{
				sceneManager.Update(std::chrono::duration_cast<std::chrono::duration<float>>(updateDuration).count());
				catchUp -= updateDuration;
			}
			renderer.Render();	
		}
	}

	Cleanup();
}
