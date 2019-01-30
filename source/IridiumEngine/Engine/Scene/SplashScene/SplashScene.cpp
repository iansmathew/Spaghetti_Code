#include "SplashScene.h"
#include "../SceneManager.h"

SplashScene::SplashScene()
{
}

void SplashScene::Start()
{
	auto splashImage = SceneManager::Instance()->CreateNewGameobject<Gameobject>(true, this);
	__super::Start();
}

void SplashScene::Update(float _deltaTime)
{
	__super::Update(_deltaTime);
}

void SplashScene::Shutdown()
{
	throw std::logic_error("The method or operation is not implemented.");
}
