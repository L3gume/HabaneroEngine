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

using namespace ECS;

/*
 * TODO: make this useable lul
 */

std::vector<std::string> EntityConstructor::loadFile(std::ifstream &_ifs) {
    std::vector<std::string> ret;
    std::string line;
    while (std::getline(_ifs, line)) {
        ret.emplace_back(line);
    }
    return ret;
}

void EntityConstructor::constructEntity(std::vector<std::string> _args) noexcept {
    assert(!_args.empty());
    Entity &newEnt = Core::Engine::getInstance().getEntityManager().addEntity("");

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
            std::string substr;
            float xpos = 0.f, ypos = 0.f, zpos = 0.f;
            float xrot = 0.f, yrot = 0.f, zrot = 0.f;
            float xscl = 1.f, yscl = 1.f, zscl = 1.f;
            while (_args[i] != "[/TransformComponent]") {
                if (boost::starts_with(_args[i], "position=")) {
                    substr = _args[i].substr(9);
                    std::istringstream fss(substr);
                    if (!(fss >> xpos >> ypos >> zpos)) {/* error */}
                } else if (boost::starts_with(_args[i], "rotation=")) {
                    substr = _args[i].substr(9);
                    std::istringstream fss(substr);
                    if (!(fss >> xrot >> yrot >> zrot)) {/* error */}
                } else if (boost::starts_with(_args[i], "scale=")) {
                    substr = _args[i].substr(6);
                    std::istringstream fss(substr);
                    if (!(fss >> xscl >> yscl >> zscl)) {/* error */}
                }
                i++;
            }
            newEnt.addComponent<TransformComponent>(glm::vec3(xpos, ypos, zpos),
                                                    glm::vec3(glm::radians(xrot), glm::radians(yrot),
                                                              glm::radians(zrot)), glm::vec3(xscl, yscl, zscl));
        } else if (_args[i] == "[RenderableComponent]") {
            VapeRenderer::PrimitiveShapes shape;
            std::string prefix("shape=");
            while (_args[i] != "[/RenderableComponent]") {
                if (boost::starts_with(_args[i], prefix)) {
                    shape = (VapeRenderer::PrimitiveShapes) boost::lexical_cast<int>(_args[i].substr(prefix.size()));
                }
                i++;
            }
            newEnt.addComponent<RenderableComponent>(shape);
        } else if (_args[i] == "[CameraComponent]") {
            float fov = 90.f, hRes = 16.f, vRes = 9.f, zNear = 0.1f, zFar = 100.f; // default values
            while (_args[i] != "[/CameraComponent]") {
                if (boost::starts_with(_args[i], "fov=")) {
                    fov = boost::lexical_cast<float>(_args[i].substr(4));
                } else if (boost::starts_with(_args[i], "hRes=")) {
                    hRes = boost::lexical_cast<float>(_args[i].substr(5));
                } else if (boost::starts_with(_args[i], "vRes=")) {
                    vRes = boost::lexical_cast<float>(_args[i].substr(5));
                } else if (boost::starts_with(_args[i], "zNear=")) {
                    zNear = boost::lexical_cast<float>(_args[i].substr(6));
                } else if (boost::starts_with(_args[i], "zFar=")) {
                    zFar = boost::lexical_cast<float>(_args[i].substr(5));
                }
                i++;
            }
            newEnt.addComponent<CameraComponent>(fov, hRes, vRes, zNear, zFar);
        } else if (_args[i] == "[ScriptComponent]") {
            Script *p;
            while (_args[i] != "[/ScriptComponent]") {
                std::string scriptName;
                if (boost::starts_with(_args[i], "script=")) {
                    scriptName = _args[i].substr(7);
                    if (scriptName == "PlayerMovementScript") p = new PlayerMovementScript();
                    // else if (scriptName == "SomeOtherScript") p = new SomeOtherScript();
                }
                i++;
            }
            newEnt.addComponent<ScriptComponent>(p);
        }
    }

//    return newEntity;
}