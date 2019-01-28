#include "GraphicsManager.h"
#include "../Window/WindowManager.h"

/**
	Constructor
 */
GraphicsManager::GraphicsManager()
{
	gameobjectList = std::vector<Gameobject*>();
}

/**
	Event delegate function that is called every time a new gameobject is created.
	This function takes care of adding the gameobject to list of gameobject to be 
	utilized by the graphics engine.
 */
void GraphicsManager::OnNewGameobjectCreated(IEventDataPtr _event)
{
	std::shared_ptr<EvtDat_On_GO_Created> pCastEventData = std::static_pointer_cast<EvtDat_On_GO_Created>(_event);
	gameobjectList.push_back(pCastEventData->GetOwnedGameobject());
}

/** 
	Creates and sets references
 */
void GraphicsManager::Initialize()
{
	window = WindowManager::Instance()->GetWindow();

	//Subscribe to gameobject created event
	EventListenerDelegate delegateFunc = fastdelegate::MakeDelegate(this, &GraphicsManager::OnNewGameobjectCreated);
	EventManager::Instance()->AddListener(delegateFunc, EvtDat_On_GO_Created::eventType);
}

/**
	Calls start on all currently held gameobjects
 */
void GraphicsManager::Start()
{
	for (auto go : gameobjectList)
	{
		go->Start();
	}
}

/**
	Updates and display the SFML window contents
 */
void GraphicsManager::Update()
{
	window->clear(sf::Color::Red);
	for (auto go : gameobjectList)
	{
		window->draw(go->GetRenderComponent()->GetSprite());
	}
	window->display();
}
