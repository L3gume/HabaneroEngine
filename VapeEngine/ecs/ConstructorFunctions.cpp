//
// Created by l3gume on 19/02/18.
//
#include <VapeGL.h>
#include <ConstructorFunctions.h>
#include <script/LookAtScript.h>
#include <components/BoxColliderComponent.h>
#include <components/ColliderComponent.h>
#include <components/RigidBodyComponent.h>
#include <physics/AABB.h>
#include <physics/Sphere.h>

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
    VapeRenderer::PrimitiveShapes shape;
    std::string prefix("shape=");
    for (auto &s : _args) {
        if (boost::starts_with(s, prefix)) {
            shape = (VapeRenderer::PrimitiveShapes) boost::lexical_cast<int>(s.substr(prefix.size()));
        }
    }
    _ent.addComponent<RenderableComponent>(shape);
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
    Script *p;
    for (auto &s : _args) {
        std::string scriptName;
        if (boost::starts_with(s, "script=")) {
            scriptName = s.substr(7);
            if (scriptName == "PlayerMovementScript") p = new PlayerMovementScript();
            if (scriptName == "LookAtScript") p = new LookAtScript();
            // else if (scriptName == "SomeOtherScript") p = new SomeOtherScript();
        }
    }
    _ent.addComponent<ScriptComponent>(p);
}

void constructColliderComponent(Entity& _ent, std::vector<std::string>& _args) {
    std::string substr;
    glm::vec3 c(0.f, 0.f, 0.f);
    glm::vec3 h(0.f, 0.f, 0.f);
    float r = 0.f;
    colType type;
    bool isTrigger = false, isStatic = false;
    
    for (auto& s : _args) {
        if (boost::starts_with(s, "type=")) {
            substr = s.substr(5);
            if (substr == "BOX") {
                type = BOX;    
            } else if (substr == "SPHERE") {
                type = SPHERE;
            }
        } else if (boost::starts_with(s, "center=")) {
            substr = s.substr(7);
            std::istringstream fss(substr);
            if (!(fss >> c.x >> c.y >> c.z)) {}
        } else if (boost::starts_with(s, "halfwidths=") && type == BOX) {
            substr = s.substr(11);
            std::istringstream fss(substr);
            if (!(fss >> h.x >> h.y >> h.z)) {/* error */}
        } else if (boost::starts_with(s, "radius=") && type == SPHERE) {
            r = boost::lexical_cast<float>(s.substr(7));
        } else if (boost::starts_with(s, "istrigger=")) {
            substr = s.substr(10);
            isTrigger = (substr == "true");
        } else if (boost::starts_with(s, "isstatic=")) {
            substr = s.substr(9);
            isStatic = (substr == "true");
        }
    } 
    if (type == BOX) {
        _ent.addComponent<ColliderComponent>(c, h, isTrigger, isStatic);
    } else if (type = SPHERE) {
        _ent.addComponent<ColliderComponent>(c, r, isTrigger, isStatic);
    }
}

void constructRigidBodyComponent(Entity& _ent, std::vector<std::string>& _args) {
    std::string substr;
    float grav, mass, fric;
    bool lckpx, lckpy, lckpz, lckrx, lckry, lckrz, kin;
    
    for (auto &s : _args) {
        if (boost::starts_with(s, "gravityScale=")) {
            grav = boost::lexical_cast<float>(s.substr(13));
        } else if (boost::starts_with(s, "mass=")) {
            mass = boost::lexical_cast<float>(s.substr(5));
        } else if (boost::starts_with(s, "friction=")) {
            fric = boost::lexical_cast<float>(s.substr(9));
        } else if (boost::starts_with(s, "lockPos_x=")) {
            substr = s.substr(10);
            lckpx = (substr == "true");
        } else if (boost::starts_with(s, "lockPos_y=")) {
            substr = s.substr(10);
            lckpy = (substr == "true");
        } else if (boost::starts_with(s, "lockPos_z=")) {
            substr = s.substr(10);
            lckpz = (substr == "true");
        } else if (boost::starts_with(s, "lockRot_x=")) {
            substr = s.substr(10);
            lckrx = (substr == "true");
        } else if (boost::starts_with(s, "lockRot_y=")) {
            substr = s.substr(10);
            lckry = (substr == "true");
        } else if (boost::starts_with(s, "lockRot_z=")) {
            substr = s.substr(10);
            lckrz = (substr == "true");
        } else if (boost::starts_with(s, "isKinematic=")) {
            substr = s.substr(12);
            kin = (substr == "true");
        }
    }
    _ent.addComponent<RigidBodyComponent>(grav, mass, fric, lckpx, lckpy, lckpz, lckrx, lckry, lckrz, kin);
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
    if (_ent.hasComponent<RenderableComponent>()) {
        auto &comp = _ent.getComponent<RenderableComponent>();
        _oss << "[RenderableComponent]" << "\n";
        _oss << "shape=" << static_cast<int>(comp.m_shape) << "\n";
        _oss << "[/RenderableComponent]" << "\n";
    }
}

void saveCameraComponent(Entity &_ent, std::ostringstream &_oss) {
    if (_ent.hasComponent<CameraComponent>()) {
        auto &comp = _ent.getComponent<CameraComponent>();
        _oss << "[CameraComponent]" << "\n"; _oss << "fov=" << comp.m_fov << "\n";
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

void saveColliderComponent(Entity &_ent, std::ostringstream &_oss) {
    if (_ent.hasComponent<ColliderComponent>()) {
        auto& comp = _ent.getComponent<ColliderComponent>();
        std::string type; 
        AABB aabb;
        Sphere sphere;
        if (comp.type == BOX) {
            aabb = comp.collider.boxCollider; 
            type = "BOX";
        } else if (comp.type == SPHERE) {
            sphere = comp.collider.sphereCollider;
            type = "SPHERE";
        }
        _oss << "[ColliderComponent]" << "\n";
        _oss << "type=" << type << "\n";
        if (comp.type == BOX) {
            _oss << "center=" << aabb.c.x << " " << aabb.c.y << " " << aabb.c.z << "\n";
            _oss << "halfwidths=" << aabb.r.x << " " << aabb.r.y << " " << aabb.r.z << "\n";
        } else if (comp.type == SPHERE) {
            _oss << "center=" << sphere.c.x << " " << sphere.c.y << " " << sphere.c.z << "\n";
            _oss << "radius=" << sphere.r << "\n";
        }
        _oss << "istrigger=" << (comp.isTrigger ? "true" : "false") << "\n";
        _oss << "isstatic=" << (comp.isStatic ? "true" : "false") << "\n";
        _oss << "[/ColliderComponent]" << "\n";
    } 
} 

void saveRigidBodyComponent(Entity& _ent, std::ostringstream& _oss) {
    if (_ent.hasComponent<RigidBodyComponent>()) {
        auto &comp = _ent.getComponent<RigidBodyComponent>();
        _oss << "[RigidBodyComponent]" << "\n";
        _oss << "gravityScale=" << comp.gravityScale << "\n";
        _oss << "mass=" << comp.gravityScale << "\n";
        _oss << "friction=" << comp.gravityScale << "\n";
        _oss << "lockPos_x=" << (comp.lockPos_x ? "true" : "false") << "\n";
        _oss << "lockPos_y=" << (comp.lockPos_y ? "true" : "false") << "\n";
        _oss << "lockPos_z=" << (comp.lockPos_z ? "true" : "false") << "\n";
        _oss << "lockRot_x=" << (comp.lockRot_x ? "true" : "false") << "\n";
        _oss << "lockRot_y=" << (comp.lockRot_y ? "true" : "false") << "\n";
        _oss << "lockRot_z=" << (comp.lockRot_z ? "true" : "false") << "\n";
        _oss << "isKinematic=" << (comp.isKinematic ? "true" : "false") << "\n";
        _oss << "[/RigidBodyComponent]" << "\n";
    }
}
