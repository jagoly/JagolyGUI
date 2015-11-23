#pragma once

#include <JagolyGUI/assert.hpp>

namespace jagolygui {

class Variant {
public:
    Variant() = default;

    ~Variant() { if (deleter != nullptr) deleter(dataPtr); }

    template<class T> Variant(const T& _data) { set(_data); }

    template<class T> Variant& operator=(const T& _data) { set(_data); return *this; }

    template<class T> void set(const T& _data) {
        dataPtr = new T(_data); typeInfo = &typeid(T);
        deleter = [](void* p){ delete static_cast<T*>(p); };
    }

    template<class T> T& get() {
        JGASSERT(typeInfo == &typeid(T), "");
        return *static_cast<T*>(dataPtr);
    }

    template<class T> const T& get() const {
        JGASSERT(typeInfo == &typeid(T), "");
        return *static_cast<T*>(dataPtr);
    }

    template<class T> bool type_equals() const {
        return &typeid(T) == typeInfo;
    }

private:
    void* dataPtr = nullptr;
    const std::type_info* typeInfo = &typeid(void);
    void(*deleter)(void*) = nullptr;
};


}
