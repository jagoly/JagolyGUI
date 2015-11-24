#pragma once

#include <map>
#include <typeindex>

#include <JagolyGUI/Widget.hpp>

namespace jagolygui {

class RenderTree {
public:
    template<class Type, class Base = std::nullptr_t>
    void register_widget(WidgetFunc _drawFunc = nullptr);

    template<class Type, class Base = std::nullptr_t, class MFClass>
    void register_widget(void(MFClass::* _mFunc)(Widget*), MFClass* _this);

    void render_widget(Widget* _widget);

protected:
    struct RenderData { const WidgetFunc drawFunc; const std::type_index base; };

    void impl_register_widget(WidgetFunc _drawFunc, std::type_index _type, std::type_index _base);

    std::map<std::type_index, RenderData> renderDataMap;
};


// Method Definitions /////

template<class Type, class Base> inline
void RenderTree::register_widget(WidgetFunc _drawFunc) {
    static_assert(std::is_base_of<Widget, Type>::value, "");
    static_assert(std::is_same<std::nullptr_t, Base>::value ||
                  std::is_base_of<Widget, Base>::value, "");
    impl_register_widget(_drawFunc, typeid(Type), typeid(Base));
}

template<class Type, class Base, class MFClass> inline
void RenderTree::register_widget(void(MFClass::* _mFunc)(Widget*), MFClass* _this) {
    auto drawFunc = std::bind(_mFunc, _this, std::placeholders::_1);
    register_widget<Type, Base>(drawFunc);
}

}
