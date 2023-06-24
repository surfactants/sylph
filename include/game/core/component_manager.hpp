#pragma once

#include <cassert>
#include <map>
#include <memory>
#include <vector>

#include <game/component/component_library.hpp>
#include <game/component/component.hpp>

#include <game/component/body_info.hpp>
#include <game/component/date.hpp>
#include <game/component/entity_data.hpp>
#include <game/component/transform.hpp>
#include <game/component/collision_rect.hpp>
#include <game/component/polygon_tile.hpp>
#include <game/component/tile.hpp>
#include <game/component/hierarchy.hpp>
#include <game/component/resource.hpp>

#include <game/component/entity_data.hpp>
#include <game/component/civilization_data.hpp>

#include <game/core/entity.hpp>

#include <game/system/system.hpp>

class Component_Manager {
public:
	template<typename T>
	std::function<T(Entity)> registerComponent()
	{
		const char* name = typeid(T).name();
		assert(mComponent_Types.find(name) == mComponent_Types.end() && "Registering component type more than once." );

		// Add this component type to the component type map
		mComponent_Types.insert({name, mNextComponent_Type});

		// Create a Component_Library pointer and add it to the component arrays map
		mComponent_Librarys.insert({name, std::make_shared<Component_Library<T>>()});

		// Increment the value so that the next component registered will be different
		++mNextComponent_Type;

		return std::bind(getComponent<T>, this, std::placeholders::_1);
	}

	template<typename T>
	Component_Type getComponentType()
	{
		const char* name = typeid(T).name();

		assert(mComponent_Types.find(name) != mComponent_Types.end() && "Component not registered before use.");

		// Return this component's type - used for creating signatures
		return mComponent_Types[name];
	}

	template<typename T>
	void addComponent(Entity entity, T component)
	{
		// Add a component to the array for an entity
		getComponentLibrary<T>()->insertData(entity, component);
	}

	template<typename T>
	void removeComponent(Entity entity)
	{
		// Remove a component from the array for an entity
		getComponentLibrary<T>()->removeData(entity);
	}

	template<typename T>
	T& getComponent(Entity entity)
	{
		// Get a reference to a component from the array for an entity
		return getComponentLibrary<T>()->getData(entity);
	}

	void entityDestroyed(Entity entity)
	{
		// Notify each component array that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		for (const auto& pair : mComponent_Librarys) {
			pair.second->entityDestroyed(entity);
		}
	}

private:
	// Map from type string pointer to a component type
	std::unordered_map<const char*, Component_Type> mComponent_Types {};

	// Map from type string pointer to a component array
	std::unordered_map<const char*, std::shared_ptr<IComponent_Library>> mComponent_Librarys {};

	// The component type to be assigned to the next registered component - starting at 0
	Component_Type mNextComponent_Type{};

	// Convenience function to get the statically casted pointer to the Component_Library of type T.
	template<typename T>
	std::shared_ptr<Component_Library<T>> getComponentLibrary()
	{
		const char* name = typeid(T).name();

		assert(mComponent_Types.find(name) != mComponent_Types.end() && "Component not registered before use.");

		return std::static_pointer_cast<Component_Library<T>>(mComponent_Librarys[name]);
	}
};
