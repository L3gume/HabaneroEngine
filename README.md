# VapeEngine

A simple C++ 3D game engine for Linux (and maybe windows) made with OpenGL

## Team

* Justin Tremblay
* Evan Laflamme

## Dependencies

* C++17
* glfw-x11 3.2.1-1 (Available on Arch repos) - Documentation found [here](http://www.glfw.org/docs/latest/)
* glew 2.1.0-1 (Available on Arch repos)
* cmake 3.9 or higher
* glm 0.9.8.5-1
* Qt 5.10

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

## Practices

* Don't use smart pointers, use raw pointers instead
    * `unique_ptr` is allowed when creating a pointer only for the scope of a function, but pretty much useless
* No exception handling (no try/catch blocks)
* Use `nullptr` instead of `NULL`
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

## TODO

* Encapsulate rendering in its own system [Evan]
    * Entities, hierarchies of entities (composite design pattern, anyone?)
* Game loop [Justin, on hold]
* Game Objects [Justin]
* Physics (Collisions, etc.)

## NEXT MILESTONE

For version 0.1:

* Working Camera - **MOSTLY DONE**
* Working Rendering system
    * Simple shapes and volumes
* Working Input system - **DONE**
* Simple Physics engine
    * Basic collsions
    * Gravity
    * Forces
* Simple debug log system - **DONE**
