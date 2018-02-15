//
// Created by l3gume on 15/02/18.
//

#include <components/TransformComponent.h>
//#include <render/PrimitiveShapes.h>
#include <components/RenderableComponent.h>
#include <core/Engine.h>
#include "EntityConstructor.h"

using namespace ECS;

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
    Entity& newEnt = Core::Engine::getInstance().getEntityManager().addEntity("");

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
        }
        if (_args[i] == "[TransformComponent]") {
            std::string substr;
            float xpos = 0.f, ypos = 0.f, zpos = 0.f;
            float xrot = 0.f, yrot = 0.f, zrot = 0.f;
            float xscl = 1.f, yscl = 1.f, zscl = 1.f;
            while (_args[i] != "}") {
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
            newEnt.addComponent<TransformComponent>(glm::vec3(xpos, ypos, zpos), glm::vec3(xrot, yrot, zrot), glm::vec3(xscl, yscl, zscl));
        }
        if (_args[i] == "[RenderableComponent]") {
            VapeRenderer::PrimitiveShapes shape;
            std::string prefix("shape=");
            i += 2;
            if (boost::starts_with(_args[i], prefix)) {
                shape = (VapeRenderer::PrimitiveShapes)boost::lexical_cast<int>(_args[i].substr(prefix.size()));
            }
            newEnt.addComponent<RenderableComponent>(shape);
        }
    }

//    return newEntity;
}