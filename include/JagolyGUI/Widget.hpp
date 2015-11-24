#pragma once

#include <memory>

#include <JagolyGUI/DataTypes.hpp>
#include <JagolyGUI/EnumTypes.hpp>

namespace jagolygui {

class Widget {
public:
    SizeMode sizeModeH = SizeMode::Expanding;
    SizeMode sizeModeV = SizeMode::Expanding;
    AlignMode alignModeH = AlignMode::Centre;
    AlignMode alignModeV = AlignMode::Centre;

    Vec2U minimumSize = {0u, 0u};
    Vec2U maximumSize = {-1u, -1u};

    Widget* parent = nullptr;
    ulong handle = 0u;

    Vec2U calculatedSize;
    Vec2I calculatedPos;

    virtual Vec2U calc_minimum_size();
};

using WidgetPtr = std::unique_ptr<Widget>;
using WidgetFunc = std::function<void(Widget*)>;

template<class T> using if_Widget = typename
std::enable_if<std::is_base_of<Widget, T>::value>::type;

}
