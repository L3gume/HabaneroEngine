//
// Created by notjustin on 2/8/18.
//

/*
 * TODO: implement allocators
 */
#pragma once
#ifndef ECS_ECS_H
#define ECS_ECS_H

#include <vector>
#include <memory>
#include <bitset>
#include <cassert>
#include <algorithm>
#include <fstream>


#include "boost/algorithm/string/predicate.hpp"
#include "boost/lexical_cast.hpp"
#include "engine/core/logging/LogManager.h"
#include "engine/core/logging/LogMessage.h"
#include "../util.h"

using HabaneroLog::LogManager;
using HabaneroLog::LogMessage;
using HabaneroLog::LogTag;
using HabaneroLog::LogType;
using HabaneroLog::LogSeverity;

namespace ECS {
    /*
     * Forward delarations
     */
    struct Component; // This one is a struct because it has no logic to begin with.
    class Entity;
    class EntityManager;
    class System; // just in case I guess
    class SystemManager;

    /*
     * Constexpr and typedef
     */
    constexpr std::size_t MAX_COMPS{32};
    constexpr std::size_t MAX_GROUPS{32};

    using ComponentBitset = std::bitset<MAX_COMPS>;
    using ComponentArray = std::array<Component *, MAX_COMPS>;
    using ComponentID = std::size_t;
    using Group = std::size_t;
    using GroupBitset = std::bitset<MAX_GROUPS>;

    /*
     * Stuff
     */

    inline ComponentID getUniqueComponentID() noexcept {
        static ComponentID lastID{0u};
        return lastID++;
    }

    // Template Magic, have fun trying to figure it out!
    template<typename T>
    inline ComponentID getComponentTypeID() noexcept {
        static ComponentID typeID{getUniqueComponentID()};
        return typeID;
    }

    /*
     * Component Implementation
     *
     * A component is a logic-less data object. it only contains data that will be handled by a system.
     */
    struct Component {
        Entity *m_entity{nullptr};

        // ... stuff ...
        bool m_bEnabled;

        virtual ~Component() {}
    };

    class Entity {
        friend class EntityManager;
        friend class EntityConstructor;
    private:
        EntityManager* m_manager;
        /*
         * Unique_ptrs make it so we don't leak any memory
         */
        std::vector<std::unique_ptr<Component>> m_components;
        ComponentBitset m_componentBitset;
        ComponentArray m_componentArray;
        GroupBitset m_groupBitset;

        std::vector<Entity*> m_children;
        Entity* m_parent;

        std::string m_sName;
        uint64_t m_iId;

        bool m_bDestroyed = false; // entity will be removed from manager when this is true. Components are unique_ptr
                                   // so no need to worry about them
    public:
        inline std::string getName() { return m_sName; }
        inline uint64_t getID() { return m_iId; }
//        inline const std::shared_ptr<Entity>& getParent() const { return m_parent; }
        inline const Entity* getParent() const { return m_parent; }
        inline const std::vector<Entity*>& getChildren() const { return m_children; };
        inline void destroy() { m_bDestroyed = true; }
        /*
         * Check if the entity already has an instance of component T
         */
        template<typename T>
        bool hasComponent() const {
            return m_componentBitset[getComponentTypeID<T>()];
        }

        /*
         * Check if entity belongs to a group
         */
        bool hasGroup(Group _group) const noexcept {
            return m_groupBitset[_group];
        }

        /*
         * Add entity to group
         */
        void addGroup(Group _group) noexcept;

        /*
         * Remove entity from group, the manager will automatically get rid of it
         */
        void deleteFromGroup(Group _group) noexcept {
            m_groupBitset[_group] = false;
        }

        /*
         * Add a component to the entity
         */
        template<typename T, typename... TArgs>
        T &addComponent(TArgs &&... _args) {
            assert(!hasComponent<T>()); // Make sure the entity doesn't already have this type of component.

            T *c(new T(std::forward<TArgs>(_args)...));
            c->m_entity = this;
            std::unique_ptr<Component> uPtr(std::move(c));
            m_components.emplace_back(std::move(uPtr));

            ComponentID id = getComponentTypeID<T>();
            m_componentArray[id] = c;
            m_componentBitset[id] = true;

            this->addGroup(id);
//            c->init(); TODO
            c->m_bEnabled = true;

            return *c;
        }

        /*
         * Get the entity's component T, if it has one.
         */
        template<typename T>
        T &getComponent() const {
            assert(hasComponent<T>()); // will throw an error
            auto ptr(m_componentArray[getComponentTypeID<T>()]);
            return *static_cast<T *>(ptr);
        }
    };

    class EntityManager {
    private:
        std::vector<std::shared_ptr<Entity>> m_entities;
        std::array<std::vector<Entity *>, MAX_GROUPS> m_groupedEntities;

		// This is used in the case where an invalid group is passed to
		// getEntitiesByGroup. Since that method return a reference, it's best
		// to return a reference to this empty vector (which will remain in scope)
		// than returning a reference to a local variable.
		// TODO: once there's a way to properly terminate the program, replace the use
		// of this vector with a program termination
		const std::vector<Entity*> m_emptyVector;
    public:
        /* Add a function to remove entities that have to be removed */
        void refresh() {
            /*
             * Remove entites that don't belong to groups anymore and those that have been destroyed.
             */
            for (auto i{0u}; i < MAX_GROUPS; i++) {
                auto &v{m_groupedEntities[i]};
                v.erase(std::remove_if(std::begin(v), std::end(v),
                                       [i](Entity *_ent) {
                                           return !_ent->hasGroup(i) || _ent->m_bDestroyed;
                                       }), std::end(v));
            }
        }

        /*
         * Add an entity to the manager.
         */
        Entity &addEntity(std::string _name) {
            Entity *e{new Entity{}};

            e->m_manager = this;
            e->m_sName = std::move(_name); // since we're passing by copy and only copying once.
            e->m_iId = generateUniqueID(); // may be useful

            std::shared_ptr<Entity> sPtr(e);
            m_entities.emplace_back(std::move(sPtr));
            return *e;
        }

        /*
         * Add an Entity to a group
         */
        void addToGroup(Entity *_ent, Group _group) {
            m_groupedEntities[_group].emplace_back(_ent);
        }

		/*
		 * Helper method to check if any entities of a given group exist
		*/
		bool hasEntitiesInGroup(Group _group) {
			return (_group < MAX_GROUPS) && !m_groupedEntities[_group].empty();
		}

        /*
         * Get a group of entities, this will be handy for separating entites by the components they have.
         */
        const std::vector<Entity *> &getEntitiesByGroup(Group _group) {
			if (_group >= MAX_GROUPS) {
				LogManager::getInstance().printMessage(
					LogMessage(
						LogTag::ECS, LogType::BUG, LogSeverity::CRITICAL,
						"Group given to getEntitiesByGroup is larger than max group"));
				
				return m_emptyVector;
			}

            return m_groupedEntities[_group];
        }

		std::vector<Entity *> *getMutableEntitiesByGroup(Group _group) {
			if (_group >= MAX_GROUPS) {
				LogManager::getInstance().printMessage(
					LogMessage(
						LogTag::ECS, LogType::BUG, LogSeverity::CRITICAL,
						"Group given to getMutableEntitiesByGroup is larger than max group"));
				return nullptr;
			}
			return &m_groupedEntities[_group];
		}

        std::vector<std::shared_ptr<Entity>> &getEntities() { return m_entities; }

//        void saveEntity(Entity *_ent);
        void loadEntity(std::string _path);

    };

    /*
     * System class, templated to only handle one type of component, only the manager can construct one
     */
//    template<typename T>
    class System {
        friend class SystemManager;

    public:
        virtual ~System() {}

        inline void enable() noexcept { m_enabled = true; }
        inline void disable() noexcept { m_enabled = false; }
    protected:
        System() : /*typeID(getComponentTypeID<T>()),*/ m_enabled(true) {} // = default?

        ComponentID typeID;
        bool m_enabled;
#if EDITOR
        bool m_enabledInEditorMode;
#endif
        uint8_t m_priority;
    private:
        SystemManager *systemManager; // hold ref to sys manager

        virtual void preUpdate(float _deltaTime) {}
        virtual void update(float _deltaTime) {}
        virtual void postUpdate(float _deltaTime) {}
    };

    /*
     * SystemManager class, handles the various systems
     */
    class SystemManager {
    private:
        std::vector<System*> m_systems;
    public:
        SystemManager() = default;
        ~SystemManager() = default;

        template<typename T, typename... TArgs>
        T &addSystem(TArgs&&... _args) {
            ComponentID _typeID = getComponentTypeID<T>();
            if (auto found = std::find_if(std::begin(m_systems), std::end(m_systems),
                                           [_typeID](System* _sys) { return _sys->typeID == _typeID; });
            found != std::end(m_systems)) {
                // System already exists.
                assert(false);
            }

            auto system = new T(std::forward<TArgs>(_args)...);
            system->systemManager = this;
            system->typeID = getComponentTypeID<T>();
//            std::unique_ptr<System> uPtr(std::move(system));
            m_systems.emplace_back(system);

            // Sort the systems by priority
            std::sort(std::begin(m_systems), std::end(m_systems), [](System* _s1, System* _s2){
                return _s1->m_priority > _s2->m_priority;
            });

            return *system;
        };

        template<typename T>
        T* getSystem() const
        {
            ComponentID _typeID = getComponentTypeID<T>();
            auto found = std::find_if(std::begin(m_systems), std::end(m_systems),
                                       [_typeID](System* _sys) { return _sys->typeID == _typeID; });
            return found != this->m_systems.end() ? static_cast<T*>(*found) : nullptr;
        }

        template<typename T>
        void setSystemPriority(uint8_t _priority) {
            ComponentID _typeID = getComponentTypeID<T>();
            if (auto found = std::find_if(std::begin(m_systems), std::end(m_systems),
                                           [_typeID](System* _sys) { return _sys->typeID == _typeID; });
            found != std::end(m_systems)) {
                // System already exists.
                (*found)->m_priority = _priority;
            } else {
                // system isn't in there.
                assert(false);
                return;
            }

            // Sort the systems by priority
            std::sort(std::begin(m_systems), std::end(m_systems), [](System* _s1, System* _s2){
                return _s1->m_priority > _s2->m_priority;
            });
        }

        void preUpdate(const float _deltaTime) {
            for (auto& sys : m_systems) {
                sys->preUpdate(_deltaTime);
            }
        }

        void update(const float _deltaTime) {
            for (auto& sys : m_systems) {
                sys->update(_deltaTime);
            }
        }

        void postUpdate(const float _deltaTime) {
            for (auto& sys : m_systems) {
                sys->postUpdate(_deltaTime);
            }
        }
    };
}
#endif //ECS_ECS_H
