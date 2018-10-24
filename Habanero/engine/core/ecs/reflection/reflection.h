#pragma once
#ifndef REFLECTION_H
#define REFLECTION_H

#include <tuple>
#include <type_traits>
#include <utility>

/*
 * Implementation of a reflection system for easier serialization
 * and manipulation of properties for ecs components and entities
 * 
 * This is very heavily inspired by DonerReflection, a project on github:
 * https://github.com/Donerkebap13/DonerReflection
 *
 * It is almost identical as I am learning about the concepts that
 * are used in this file and I will do my best to explain how it works.
 * 
 * It is a very minimal system and will be kept as minimal as possible.
 * 
 * - Justin
 */

// ----------------------- MACROS -----------------------------------------

// Main macro, initializes reflection data with a variadic list of properties
// This one takes a name as an arg
#define H_DEFINE_NAMED_REFLECTION_DATA(class_name, base_class, ...)         \
    template <> struct SReflectionProperties<base_class> {                  \
        using T = base_class;                                               \
        constexpr static auto s_className = class_name;                     \
        constexpr static auto s_properties = std::make_tuple(__VA_ARGS__);  \
        constexpr static std::size_t s_propertiesCount =                    \
            std::tuple_size<decltype(s_properties)>::value;                 \
    };

// Same as other macro, except it is unnamed
#define H_DEFINE_REFLECTION_DATA(base_class, ...)                           \
    template <> struct SReflectionProperties<base_class> {                  \
        using T = base_class;                                               \
        constexpr static auto s_properties = std::make_tuple(__VA_ARGS__);  \
        constexpr static std::size_t s_propertiesCount =                    \
            std::tuple_size<decltype(s_properties)>::value;                 \
    };



// Defines a named property, nameless properties are not supported in Habanero
#define H_ADD_NAMED_PROPERTY(prop, name)                                    \
    hreflection::SProperty<T, decltype(T::prop)> { &T::prop, name }

// To be added in the body of the components so that the ReflectionProperites
// struct can access it's members
//
// Funny how macros are essentially just code-shortcuts
#define H_DECLARE_AS_REFLECTABLE(base_class)                                \
    friend struct SReflectionProperties<base_class>;

// ----------------------- REFLECTION -------------------------------------

template <typename T> struct SReflectionProperties {
    // The members are static, which mean they weill only be initialized once per type T
    // since templates are initialized at compile-time
    constexpr static auto s_className = "Undefined";
    constexpr static auto s_properties = std::tuple<>();
    constexpr static std::size_t s_propertiesCount = std::tuple_size<decltype(s_properties)>::value;
};

// this is going to have its own namespace
namespace hreflection
{
    // Property type: this is the backbone of this whole system.
    // Components are registered witht their set of properties,
    // which can be accessed at runtime to gain knowledge of a
    // member's type
    template <typename Class, typename T>
    struct SProperty {
        // Properties are generated at compile-time using a macro, hence the constexpr
        constexpr SProperty(T Class::*member, const char* name) : m_member(member), m_name(name) {}

        using Type = T;
        
        T Class::*m_member; // pointer to the class's member, this allows for some funky stuff, see below
        const char* m_name; // name of the property
    };
    
    /*
     * HOW TO USE PROPERTIES:
     *
     * SReflectionProperties<Foo>::s_properties; // gives access to the properties
     * 
     * each elem in the s_properties tuple is of type SProperty<ClassType, MemberType>
     * 
     * hreflection::SProperty<Foo, int32> prop;
     * prop.m_name;
     * prop.m_member; // pointer to class member
     * 
     * To use the member:
     *
     * Foo obj;
     * obj.*(prop.m_member) = 420;
     *
     */
    
    // TODO- add a applyfunctiontoobject function (if needed)
}

#endif
