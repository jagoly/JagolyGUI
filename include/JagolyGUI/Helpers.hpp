#pragma once

#include <JagolyGUI/Widget.hpp>
#include <JagolyGUI/Container.hpp>

namespace jagolygui {

inline ulong hash(const std::string& _name) {
    return std::hash<std::string>()(_name);
}

inline std::vector<WidgetPtr>::iterator find_widget(ulong _handle, std::vector<WidgetPtr>& _vec) {
    std::vector<WidgetPtr>::iterator iter = _vec.begin();
    while (iter != _vec.end() && (*iter)->handle != _handle) ++iter;
    return iter;
}

}
