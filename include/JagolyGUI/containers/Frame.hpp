#pragma once

#include <JagolyGUI/ChildSingle.hpp>

namespace jagolygui {

class Frame : public ChildSingle {
public:
    Vec2U calc_minimum_size() override;

    void update_layout_expanding() override;

    void update_layout_positions() override;

    template<class Type> Type* set(Type* _child);

    Vec2U margin = {8u, 8u};
};


// Method Definitions /////

template<class Type> inline
Type* Frame::set(Type* _child) {
    static_assert(std::is_base_of<Widget, Type>::value, "");
    _child->parent = this; child.reset(_child); return _child;
}

}
