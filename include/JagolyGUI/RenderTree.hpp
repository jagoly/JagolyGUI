#pragma once

#include <map>

#include <JagolyGUI/Widget.hpp>

namespace jagolygui {

class RenderTree {
public:
    template<class Type> void register_widget(WidgetFunc _func);

    template<class Type, class Base> void register_widget(WidgetFunc _func);

    void render_widget(Widget* _widget);

protected:
    struct RenderPair { const WidgetFunc func; const RenderPair* const base; };
    std::map<const std::type_info*, RenderPair> renderPairMap;
};


// Method Definitions /////

template<class Type> inline
void RenderTree::register_widget(WidgetFunc _func) {
    static_assert(std::is_base_of<Widget, Type>::value, "");
    renderPairMap.emplace(&typeid(Type), RenderPair{_func, nullptr});
}

template<class Type, class Base> inline
void RenderTree::register_widget(WidgetFunc _func) {
    static_assert(std::is_base_of<Widget, Type>::value, "");
    static_assert(std::is_base_of<Widget, Base>::value, "");
    renderPairMap.emplace(&typeid(Type), RenderPair{_func, &renderPairMap.at(&typeid(Base))});
}

}
