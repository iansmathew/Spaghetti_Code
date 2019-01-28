#include "Engine.h"
#include "Window/WindowManager.h"
#include "Input/InputManager.h"
#include "Events/EventManager.h"
#include "Graphics/GraphicsManager.h"
#include "Components/Gameobject.h"
#include "../Helper/SysCheck.h"
#include <iostream>

/**
	Default destructor for Engine.
*/
IridiumEngine::~IridiumEngine()
{

}

/**
	Main update loop that takes care of handling events.
 */
void IridiumEngine::Run()
{
	while (WindowManager::Instance()->GetWindow()->isOpen())
	{
		HandleWindowEvents();
		//Handle event manager update queue
		eventManager->Update(); 

		//Choose which update loop to run
		if (engineState == ENGINE_STATE::Start)
		{
			Start();
			engineState = ENGINE_STATE::Update;
		}
		else if (engineState == ENGINE_STATE::Update)
		{
			graphicsManager->Update();
		}
	}
}

/**
	Dispatch and handle various SFML events
*/
void IridiumEngine::HandleWindowEvents()
{
	sf::Event event;
	while (WindowManager::Instance()->GetWindow()->pollEvent(event)) //poll all events for open window
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			Shutdown();
			break;

		case sf::Event::KeyPressed:
			inputManager->OnKeyPressed(event);
			break;

		case sf::Event::KeyReleased:
			inputManager->OnKeyReleased(event);
			break;

		default:
			break;
		}
	}
}

/**
	Takes care of releasing and destroying various engine components.
 */
void IridiumEngine::Shutdown()
{
	//Destroying components in reverse order of initialization
	inputManager->Shutdown();
	windowManager->Shutdown();
}

/**
	Called before update runs. 
	Create gameobjects here
 */
void IridiumEngine::Create()
{
	Gameobject* test = new Gameobject();

	//Letting the engine know to go onto start
	engineState = ENGINE_STATE::Start;
}

/**
	Called right before update.
	It calls start on all objects that require it.
 */
void IridiumEngine::Start()
{
	graphicsManager->Start();
}

/**
	Default base constructor for Engine. 
 */
IridiumEngine::IridiumEngine()
{
	//Initialize engine components
	windowManager = WindowManager::Instance();
	graphicsManager = GraphicsManager::Instance();
	inputManager = InputManager::Instance();
	eventManager = EventManager::Instance();
}

/**
	Checks if an instance of the engine is already running,
	performs various spec checks and 
	initializes various components of the Engine. 

	@return Returns the success value of initialization.
 */
bool IridiumEngine::Initialize()
{
	if (!CheckSystemRequirements())
		return false;

	engineState = ENGINE_STATE::Initialization;

	windowManager->Initialize();
	graphicsManager->Initialize();

	Create();

	return true;
}


/**
	Creates an instance of the system checker and uses it to 
	checks if the user's system has the required hardware/software capabilities 
	to run the program.

	@return Returns true if system check passes. 
 */
bool IridiumEngine::CheckSystemRequirements()
{
	SysCheck systemCheck;
	systemCheck.DisplayCPUStats();

	if (!systemCheck.HasFreeMemory())
		return false;

	if (!systemCheck.HasFreeDiskSpace())
		return false;

	return true;
}

