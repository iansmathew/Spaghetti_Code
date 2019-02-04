#pragma once

/*************************/
/* FORWARD DECLARATIONS  */
/*************************/
class Gameobject;

class BaseComponent
{
protected:
	bool isUpdated;

private:
	Gameobject* owner;

public:
	BaseComponent(Gameobject* _owner);

	virtual void Start();

	virtual void Update();

	virtual void Shutdown();

	Gameobject* GetGameobject() const;
};