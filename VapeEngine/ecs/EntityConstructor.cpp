//
// Created by l3gume on 15/02/18.
//

#include <components/TransformComponent.h>
#include <components/RenderableComponent.h>
#include <core/Engine.h>
#include <components/CameraComponent.h>
#include <components/ScriptComponent.h>
#include <script/PlayerMovementScript.h>
#include "EntityConstructor.h"
#include "ConstructorFunctions.h"

using namespace ECS;

/*
 * TODO: make this useable and safer lul
 */

std::vector<std::string> EntityConstructor::loadFile(std::ifstream &_ifs) {
    std::vector<std::string> ret;
    std::string line;
    while (std::getline(_ifs, line)) {
        ret.emplace_back(line);
    }
    return ret;
}

void
EntityConstructor::constructEntity(std::vector<std::string> _args, /*const std::shared_ptr<Entity> &*/ Entity* _parent) noexcept {
    assert(!_args.empty());
    Entity &newEnt = Core::Engine::getInstance().getEntityManager().addEntity("");
    newEnt.m_parent = _parent; // May be nullptr, but that's intended!
    if (_parent) {
        _parent->m_children.emplace_back(&newEnt);
    }
    std::string entity_name;
    for (int i = 0; i < _args.size(); i++) {
        if (i == 0) {
            std::string prefix("ENTITY:");
            if (boost::starts_with(_args[i], prefix)) {
                entity_name = _args[i].substr(prefix.size());
                newEnt.m_sName = entity_name;
            } else {
                fprintf(stderr, "Invalid entity file.\n");
            }
        } else if (_args[i] == "[TransformComponent]") {
            std::vector<std::string> args;
            while (_args[++i] != "[/TransformComponent]") {
                args.emplace_back(_args[i]);
            }
            constructTransformComponent(newEnt, args);
        } else if (_args[i] == "[RenderableComponent]") {
            std::vector<std::string> args;
            while (_args[++i] != "[/RenderableComponent]") {
                args.emplace_back(_args[i]);
            }
            constructRenderableComponent(newEnt, args);
        } else if (_args[i] == "[CameraComponent]") {
            std::vector<std::string> args;
            while (_args[++i] != "[/CameraComponent]") {
                args.emplace_back(_args[i]);
            }
            constructCameraComponent(newEnt, args);
        } else if (_args[i] == "[ScriptComponent]") {
            std::vector<std::string> args;
            while (_args[++i] != "[/ScriptComponent]") {
                args.emplace_back(_args[i]);
            }
            constructScriptComponent(newEnt, args);
        } else if (boost::starts_with(_args[i], "ENTITY:")) {
            std::vector<std::string> args;
            args.emplace_back(_args[i]); // don't forget that part.
            while (_args[++i] != ")") {
                args.emplace_back(_args[i]);
            }
            constructEntity(args, &newEnt);
        }
    }
}

void EntityConstructor::saveEntityFile(Entity& _ent, std::string _filename) {
    std::ofstream of(_filename);
    std::ostringstream oss;

    saveEntity(_ent, &oss);

    of << oss.str() << "\n";
    of.close();
}

void EntityConstructor::saveEntity(Entity &_ent, std::ostringstream* _oss) {
//    std::ofstream of(_filename);
//    std::ostringstream oss;

    *_oss << "ENTITY:" << _ent.m_sName << "\n{\n";
    saveTransformComponent(_ent, *_oss);
    saveRenderableComponent(_ent, *_oss);
    saveCameraComponent(_ent, *_oss);
    saveScriptComponent(_ent, *_oss);
    for (auto& child : _ent.m_children) {
        saveEntity(*child, _oss);
    }
    if (_ent.getParent()) *_oss << ")\n";
    else *_oss << "}\n";


//    (*_of).close();
}
