#pragma once

#include <JagolyGUI/Helpers.hpp>
#include <JagolyGUI/Container.hpp>

namespace jagolygui {

class ChildMulti : public Container {
public:
    template<class Type = Widget> Type* get(const std::string& _name);

    template<class Type = Widget> Type* pop(const std::string& _name);

    void erase(const std::string& _name) { do_erase(hash(_name)); }

protected:
    virtual Widget* do_get(ulong _handle) = 0;
    virtual Widget* do_pop(ulong _handle) = 0;
    virtual void do_erase(ulong _handle) = 0;
};


// Method Definitions /////

template<class Type> inline
Type* ChildMulti::get(const std::string& _name) {
    static_assert(std::is_base_of<Widget, Type>::value, "");
    return &dynamic_cast<Type&>(*do_get(hash(_name)));
}

template<class Type> inline
Type* ChildMulti::pop(const std::string& _name) {
    static_assert(std::is_base_of<Widget, Type>::value, "");
    return &dynamic_cast<Type&>(*do_pop(hash(_name)));
}

}
