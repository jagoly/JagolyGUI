#pragma once

#include <vector>

#include <JagolyGUI/Widget.hpp>
#include <JagolyGUI/RenderTree.hpp>

namespace jagolygui {

class Container : public Widget {
public:
    virtual Vec2U calc_minimum_size() override = 0;

    virtual void update_layout_expanding() = 0;

    virtual void update_layout_positions() = 0;

    virtual std::vector<Widget*> get_children() = 0;

    void propogate_func(std::function<void(Widget*)> _func);
};

}
