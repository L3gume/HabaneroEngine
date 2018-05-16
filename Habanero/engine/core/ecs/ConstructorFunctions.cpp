//
// Created by l3gume on 19/02/18.
//
//#include <VapeGL.h>
#include "ConstructorFunctions.h"

void constructTransformComponent(Entity &_ent, std::vector<std::string> &_args) {
    std::string substr;
    float xpos = 0.f, ypos = 0.f, zpos = 0.f;
    float xrot = 0.f, yrot = 0.f, zrot = 0.f;
    float xscl = 1.f, yscl = 1.f, zscl = 1.f;
    for (auto &s : _args) {
        if (boost::starts_with(s, "position=")) {
            substr = s.substr(9);
            std::istringstream fss(substr);
            if (!(fss >> xpos >> ypos >> zpos)) {/* error */}
        } else if (boost::starts_with(s, "rotation=")) {
            substr = s.substr(9);
            std::istringstream fss(substr);
            if (!(fss >> xrot >> yrot >> zrot)) {/* error */}
        } else if (boost::starts_with(s, "scale=")) {
            substr = s.substr(6);
            std::istringstream fss(substr);
            if (!(fss >> xscl >> yscl >> zscl)) {/* error */}
        }
    }
    _ent.addComponent<TransformComponent>(glm::vec3(xpos, ypos, zpos),
                                          glm::vec3(glm::radians(xrot), glm::radians(yrot),
                                                    glm::radians(zrot)), glm::vec3(xscl, yscl, zscl));
}

void constructRenderableComponent(Entity &_ent, std::vector<std::string> &_args) {
/*
    VapeRenderer::PrimitiveShapes shape;
    std::string prefix("shape=");
    for (auto &s : _args) {
        if (boost::starts_with(s, prefix)) {
            shape = (VapeRenderer::PrimitiveShapes) boost::lexical_cast<int>(s.substr(prefix.size()));
        }
    }
    _ent.addComponent<RenderableComponent>(shape);
*/
}

void constructCameraComponent(Entity &_ent, std::vector<std::string> &_args) {
    float fov = 90.f, hRes = 16.f, vRes = 9.f, zNear = 0.1f, zFar = 100.f; // default values
    for (auto &s : _args) {
        if (boost::starts_with(s, "fov=")) {
            fov = boost::lexical_cast<float>(s.substr(4));
        } else if (boost::starts_with(s, "hRes=")) {
            hRes = boost::lexical_cast<float>(s.substr(5));
        } else if (boost::starts_with(s, "vRes=")) {
            vRes = boost::lexical_cast<float>(s.substr(5));
        } else if (boost::starts_with(s, "zNear=")) {
            zNear = boost::lexical_cast<float>(s.substr(6));
        } else if (boost::starts_with(s, "zFar=")) {
            zFar = boost::lexical_cast<float>(s.substr(5));
        }
    }
    _ent.addComponent<CameraComponent>(fov, hRes, vRes, zNear, zFar);
}

void constructScriptComponent(Entity &_ent, std::vector<std::string> &_args) {
	/*
    Script *p;
    for (auto &s : _args) {
        std::string scriptName;
        if (boost::starts_with(s, "script=")) {
            scriptName = s.substr(7);
            if (scriptName == "PlayerMovementScript") p = new PlayerMovementScript();
            // else if (scriptName == "SomeOtherScript") p = new SomeOtherScript();
        }
    }
    _ent.addComponent<ScriptComponent>(p);
	*/
}


void saveTransformComponent(Entity &_ent, std::ostringstream &_oss) {
    if (_ent.hasComponent<TransformComponent>()) {
        auto &comp = _ent.getComponent<TransformComponent>();
        _oss << "[TransformComponent]" << "\n";
        _oss << "position=" << comp.position.x << " " << comp.position.y << " " << comp.position.z << "\n";
        _oss << "rotation=" << glm::degrees(comp.rotation.x) << " " << glm::degrees(comp.rotation.y) << " "
             << glm::degrees(comp.rotation.z) << "\n";
        _oss << "scale=" << comp.scale.x << " " << comp.scale.y << " " << comp.scale.z << "\n";
        _oss << "[/TransformComponent]" << "\n";
    }
}
void saveRenderableComponent(Entity &_ent, std::ostringstream &_oss) {
/*
    if (_ent.hasComponent<RenderableComponent>()) {
        auto &comp = _ent.getComponent<RenderableComponent>();
        _oss << "[RenderableComponent]" << "\n";
        _oss << "shape=" << (int) comp.m_shape << "\n";
        _oss << "[/RenderableComponent]" << "\n";
    }
*/
}

void saveCameraComponent(Entity &_ent, std::ostringstream &_oss) {
    if (_ent.hasComponent<CameraComponent>()) {
        auto &comp = _ent.getComponent<CameraComponent>();
        _oss << "[CameraComponent]" << "\n";
        _oss << "fov=" << comp.m_fov << "\n";
        _oss << "hRes=" << comp.m_hRes << "\n";
        _oss << "vRes=" << comp.m_vRes << "\n";
        _oss << "zNear=" << comp.m_zNear << "\n";
        _oss << "zFar=" << comp.m_zFar << "\n";
        _oss << "[/CameraComponent]" << "\n";
    }
}

void saveScriptComponent(Entity &_ent, std::ostringstream &_oss) {
    if (_ent.hasComponent<ScriptComponent>()) {
        auto &comp = _ent.getComponent<ScriptComponent>();
        _oss << "[ScriptComponent]" << "\n";
        _oss << "script=" << comp.m_script->m_sName << "\n";
        _oss << "[/ScriptComponent]" << "\n";
    }
}

