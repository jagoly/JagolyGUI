#pragma once

#include <JagolyGUI/ChildMulti.hpp>

namespace jagolygui {

class BoxBase : public ChildMulti {
public:
    Vec2U calc_minimum_size() override = 0;

    void update_layout_expanding() override = 0;

    void update_layout_positions() override = 0;

    std::vector<Widget*> get_children() override;

    template<class Type> Type* append(const std::string& _name, Type* _child);

    Vec2U margin = {8u, 8u};
    uint spacing = 8u;

protected:
    std::vector<WidgetPtr> children;
    Vec2U minWithExtra = {0u, 0u};

private:
    Widget* do_get(ulong _handle) override;
    Widget* do_pop(ulong _handle) override;
    void do_erase(ulong _handle) override;

    void impl_append(ulong _handle, Widget* _widget);
};


// Method Definitions /////

template<class Type> inline Type*
BoxBase::append(const std::string& _name, Type* _child) {
    static_assert(std::is_base_of<Widget, Type>::value, "");
    impl_append(hash(_name), _child); return _child;
}

}
