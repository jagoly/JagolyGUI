#pragma once

#include <JagolyGUI/Helpers.hpp>
#include <JagolyGUI/Container.hpp>

namespace jagolygui {

class ChildSingle : public Container {
public:
    std::vector<Widget*> get_children() override;

    template<class Type = Widget> Type* get();

    template<class Type = Widget> Type* pop();

    void erase() { child.reset(); }

protected:
    WidgetPtr child;
};


// Method Definitions /////

inline std::vector<Widget*> ChildSingle::get_children() {
    if (child.get() == nullptr) return {};
    else return { child.get() };
}

template<class Type> inline Type* ChildSingle::get() {
    static_assert(std::is_base_of<Widget, Type>::value, "");
    return &dynamic_cast<Type&>(*child.get());
}

template<class Type> inline Type* ChildSingle::pop() {
    static_assert(std::is_base_of<Widget, Type>::value, "");
    return &dynamic_cast<Type&>(*child.release());
}

}
