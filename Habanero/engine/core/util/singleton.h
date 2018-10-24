#pragma once
#ifndef CORE_SINGLETON_H
#define CORE_SINGLETON_H

#define HSINGLETON(class_name)                      \
public:                                             \
    static class_name& getInstance() {              \
        static class_name instance;                 \
        return instance;                            \
    }                                               \
    class_name(class_name const&)      = delete;    \
    void operator=(class_name const&)  = delete;    \
private:                                            \
    class_name() = default;                             
       
#endif
