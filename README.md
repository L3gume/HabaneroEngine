# Habanero Engine 

A simple C++ 3D game engine for windows

## Team

* Justin Tremblay
* Evan Laflamme
* Micheal Sukkarieh

## Dependencies

* C++17 (:D)
* Boost 
* Bullet 2.87
* DirectX

## Code Style

* camelCase for functions, methods and variables.
    * Member variables should be prefixed by : `m_x`, where x refers to its type
        * `int m_iVarInCamelCase;`
        * If the variables aren't a primitive type (ex: glm::mat4), choose descriptive names: `glm::mat4 m_someMat;`
* Function arguments: prefix with `_` : `_arg`
* Brackets start to the side of the function definition:
    * `int foo() { ...`
    * Same for logic blocks:
        * `if { ...`
        * ` } else { ...`
* Always put brackets around `if` statements, even if only one line
* Tab length is 4 spaces
* Header files should look something like this:

```cpp
#pragma once
#ifndef HABANERO_CLASSNAME_H
#define HABANERO_CLASSNAME_H

// ...

#endif
```

## Practices

* Don't use smart pointers, use raw pointers instead
    * `unique_ptr` is allowed when creating a pointer only for the scope of a function, but pretty much useless
        * Ignore this, use unique_ptr when possible
    * `share_ptr` is also allowed in cases where memory management would be a nightmare
* No exception handling (no try/catch blocks)
* Use `nullptr` instead of `NULL`
* Until we have a stack-based allocator, heap allocations are OK, but keep to a minimum (avoid calling `new`)
* Whenever you can, use `const`
    * never return `const` from function, as that apparently leads to weird stuff
        * You can definitely cast the return to const though
    * If passing pointers, you can pass const pointers
    * Make getters const
    * If a method/function doesn't change any members of an object, you can make it const
* Classes implement functionality, structs and unions carry data
    * Structs can have some functions, but mostly setters/getters
    * Member variable naming applies to structs
* When possible, convert booleans to bit maps
* standard library features are allowed, but make sure you know what you're doing
* Surround debug statement, procedures with DEBUG preprocessor tag:

*EDIT: I'm an idiot, you have to write `#if DEBUG`, `#ifdef` will always be true*

```C++
#if DEBUG
    printf("Debug statement...\n");
#endif
```

*These don't have to ALWAYS be followed, they're basically just tips*

*Stuff can be added to this list and the style list*
