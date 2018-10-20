#pragma once
#ifndef ECS_HXMLENTITYSERIALIZER_H
#define ECS_HXMLENTITYSERIALIZER_H

#include <iosfwd>
#include <string>

#include "entitymanager.h"
#include "engine/core/components/TransformComponent.h"

namespace ecs
{
    
template <typename T>
struct TXmlField {
    TXmlField(std::string _name, T _value) : name(std::move(_name)), value(std::move(_value)) {
        valueTypeName = typeid(T).name();
    }

    std::string xmlFieldStart() const {
        std::stringstream ss;
        ss << "<" << name << " type=\"" << valueTypeName << "\">";
        return ss.str();
    }

    std::string xmlFieldEnd() const {
        std::stringstream ss;
        ss << "</" << name << ">";
        return ss.str();
    }

    template <typename U>
    std::string serializeType(U _obj) const {
        std::stringstream ss;
        ss << _obj;
        return ss.str();
    }

    template <>
    std::string serializeType(const DirectX::Vector3& _obj) const {
        std::stringstream ss;
        ss << _obj.x << ", " << _obj.y << ", " << _obj.z;
        return ss.str();
    }

    std::string toString() const {
        std::stringstream ss;
        ss << xmlFieldStart() << serializeType<decltype(value)>(value) << xmlFieldEnd() << "\n";
        return ss.str();
    }

    std::string name;
    T value;

    const char* valueTypeName;
};

struct SSerializedEntity {
    std::string name;

    std::vector<SSerializedEntity> children;
    std::vector<std::string> components;
    
    std::string toString(const std::string& _indent = "") const {
        const auto tab = _indent + "    ";
        std::stringstream ss;
        ss << "<Entity name=\"" << name << "\">\n";
        for (const auto& comp : components) {
            ss << comp;
        }
        for (const auto& child : children) {
            ss << tab << child.toString(tab);
        }
        ss << "</Entity>\n";
        return ss.str();
    }
};

class HXmlEntitySerializer {
public:
    void saveScene(const Entity* _sceneEntity) const;

private:   
    template <typename ComponentType>
    std::string serializeComponent(const ComponentType& _component, const std::string& _indent = "") const {
        const auto& thing = typeid(ComponentType);
        const auto classname = thing.name();
        std::string s(classname);

        // remove the "struct " part of the type name
        if (boost::starts_with(s, "struct ")) {
            s = s.substr(strlen("struct "));
        }
        else {
            // if the object being saved isn't a struct (shouldn't happen), immediately return
            return std::string("");
        }

        const auto tab = _indent + "    "; // identation
        std::stringstream ss;
        ss << _indent << TXmlField<ComponentType>(s, _component).xmlFieldStart() << "\n";
        visit_struct::for_each(_component, [s, tab, &ss](const auto& name, const auto& value) {
            ss << tab << TXmlField<decltype(value)>(name, value).toString();
        });
        ss << _indent << TXmlField<ComponentType>(s, _component).xmlFieldEnd() << "\n";

        return ss.str();
    }

    SSerializedEntity serializeEntity(const Entity* _ent, const std::string& _indent = "") const;

    static void writeEntityToFile(const std::string& _filename, const SSerializedEntity& _ent);
};

}
#endif
