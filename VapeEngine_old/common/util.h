//
// Created by notjustin on 12/31/17.
//

#ifndef VAPEENGINE_UTIL_H
#define VAPEENGINE_UTIL_H

#include <memory>

static float x_res = 1920.f;
static float y_res = 1080.f;

/*
 * This is Java now!
 *
 * CAUTION: use this as little as you can; dynamic_cast is costly.
 */
template<typename Base, typename T>
inline bool instanceOf(const T* ptr) {
    return static_cast<const Base*>(ptr) != nullptr;
}

template <typename T>
T* clone(const T & obj) {
    return new T(obj);
}

static uint64_t ID = 0;
static uint64_t generateUniqueID() {
    return ++ID;
}

#endif //VAPEENGINE_UTIL_H
