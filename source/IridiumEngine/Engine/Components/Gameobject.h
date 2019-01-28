#pragma once
#include "RenderComponent.h"
#include "Transform.h"

#include <SFML/Graphics.hpp>
#include <vector>


class Gameobject
{
public:

private:
	Transform* transform;
	RenderComponent* renderComponent;

	Gameobject* parent;
	std::vector<Gameobject*> children;
	
private:

public:
	Gameobject(bool _isRendered = true);

	Transform* GetTransform() const;
	RenderComponent* GetRenderComponent() const;

	void Start();

	void AddChild(Gameobject* _child);

	void Draw(sf::RenderWindow& _windowRef);

	//TODO:[iansmathew] Create a remove child
};