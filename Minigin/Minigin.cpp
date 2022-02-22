#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "FPSComponent.h"

using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
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
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//Background
	auto goBackground = std::make_shared<GameObject>();
	goBackground->AddComponent(std::make_shared<RenderComponent>());
	goBackground->GetComponent<RenderComponent>()->SetTexture("background.jpg");
	scene.Add(goBackground);

	//DAE Logo
	auto goLogo = std::make_shared<GameObject>();
	goLogo->AddComponent(std::make_shared<RenderComponent>());
	goLogo->GetComponent<RenderComponent>()->SetTexture("logo.png");
	goLogo->GetComponent<TransformComponent>()->SetPosition(216, 180);
	scene.Add(goLogo);

	//Assignment text
	auto goText = std::make_shared<GameObject>();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	goText->AddComponent(std::make_shared<TextComponent>("Programming 4 Assignment", font));
	goText->GetComponent<TransformComponent>()->SetPosition(80, 20);
	scene.Add(goText);

	//FPS Counter
	auto goFps = std::make_shared<GameObject>();
	goFps->GetComponent<TransformComponent>()->SetPosition(0, 0);
	auto fpsFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	goFps->AddComponent(std::make_shared<TextComponent>("FPS", fpsFont, SDL_Color{ 255,255,0 }));
	goFps->AddComponent(std::make_shared<FPSComponent>());
	scene.Add(goFps);
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

		// todo: this update loop could use some work.
		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);
			renderer.Render();

			lastTime = currentTime;
		}
	}

	Cleanup();
}
