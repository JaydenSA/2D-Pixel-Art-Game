#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component; 
class Entity; 

using ComponentID = std::size_t; 

/* Notes for inline functions
===============================
When using an inline in your function declaration, what this tells the compiler
is to essentially move the contents of the code included in function you just created 
and move it in place of the function call you made somewhere else. 

Example is as follows: 

Main.cpp 
========
void GettingComponentID() 
{
	getComponentID();
}

COMPILER VERSION: (what the compiler does with inline)
=================
void GettingComponentID()
{
	static ComponentID lastID = 0;
	return lastID++; 
}
*/
inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID; 
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	/* Notes for static functions: 
	==============================
	This is based on it not being included in a class/struct. If included in a class of struct
	please check the guides below or placed elsewhere in documentation on how those work. 

	When calling a static function, not part of a class/struct, that means that it will only be 
	visible to that file, which means that if we include it in different file(translation unit), that each file
	would have it's own version of the function. 
	*/
	static ComponentID typeID = getComponentTypeID();
	return typeID; 
}

constexpr std::size_t maxComponents = 32; 

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public: 
	Entity* entity; 

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual	~Component() {}
};

class Entity
{
private: 
	bool active = true; 
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
public: 
	void update()
	{
		for (auto& c : components) c->update();
		for (auto& c : components) c->draw();
	}
	void draw() {}
	bool isActive() const { return active; }
	void destroy() { active = false; }

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentID<T>];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true; 

		c->init();
		return *c; 
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private: 
	std::vector<std::unique_ptr<Entity>> entities;

public: 
	void update()
	{
		for (auto& e : entities) e->update();
	}
	void draw()
	{
		/* This below auto& is a referrance. A referrance is just an alias for the variable you 
			decide to set it to. 
			
			Example: 
			=========================
			int a = 6; 
			int& ref = a; 
			ref = 10;
			
			std::cout << a << endl; 
			
			COMPILED:
			=========================
			10
			*/
		for (auto& e : entities) e->draw();
	}
	void refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities)); 
	}

	// please add some notes on what this is below 
	// Entity& addEntity()
	Entity& addEntity()
	{
		/* 
		Pointers 
		==========================
		Pointers are just a referrance to the memory address. 
		*/
		Entity* e = new Entity(); 
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		/* 
		Dereferrancing a pointer will allow you to the value 
		of the variable. But if you were to write the below line 
		of code like this: 
		
		return e; 
		
		Then it will return the memory address, as opposed to 
		the value of the variable
		*/
		return *e; 
	}
};