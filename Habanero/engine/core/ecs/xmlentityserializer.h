#pragma once
#ifndef ECS_HXMLENTITYSERIALIZER_H
#define ECS_HXMLENTITYSERIALIZER_H

#include <iosfwd>
#include <string>

#include "entitymanager.h"
#include "engine/core/components/TransformComponent.h"

namespace ecs
{
    
template<typename T>
struct TXmlField {
    TXmlField(std::string _name, const T& _value) : name(std::move(_name)), value(_value) {
		valueTypeName = typeid(T).name();
    }

    std::string xmlFieldStart() const {
        std::stringstream ss;
        ss << "<" << name << " type=" << valueTypeName << ">";
        return ss.str();
    }

    std::string xmlFieldEnd() const {
        std::stringstream ss;
        ss << "</" << name << ">";
        return ss.str();
    }
    
    template<typename T>
    std::string serializeType(T _obj) const {
        std::stringstream ss;
        ss << _obj;
        return ss.str();
    }

    template<>
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
    
};

class HXmlEntitySerializer
{
public:
	HXmlEntitySerializer() = default;
	~HXmlEntitySerializer() = default;

	void saveScene(const Entity* _sceneEntity);
     
    // everything made public for testing purposes
//private:   
    template<typename ComponentType>
    std::string serializeComponent(const ComponentType& _component) {
        const auto& thing = typeid(ComponentType);
        auto classname = thing.name();
        std::string s(classname);
	
        // remove the "struct " part of the type name
        if (boost::starts_with(s, "struct ")) {
            s = s.substr(strlen("struct "));
        } else {
			// if the object being saved isn't a struct (shouldn't happen), immediately return
            return "";
        }
        
		const std::string tab = "    "; // identation
		std::stringstream ss;
		ss << TXmlField<ComponentType>(s, _component).xmlFieldStart() << "\n";
        visit_struct::for_each(_component, [s, tab, &ss](const auto& name, const auto& value) {
            ss << tab << TXmlField<decltype(value)>(name, value).toString();
        });
		ss << TXmlField<ComponentType>(s, _component).xmlFieldEnd() << "\n";
        
		std::cerr << ss.str() << '\n';
        
        std::ofstream of("test.entity");

        of << ss.str() << "\n";
        of.close();
        
		return ss.str();
    }
};

}
#endif
