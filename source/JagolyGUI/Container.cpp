#include <JagolyGUI/Container.hpp>

using namespace jagolygui;

void Container::propogate_func(std::function<void(Widget*)> _func) {
    for (auto widget : get_children()) { _func(widget);
        if (auto container = dynamic_cast<Container*>(widget))
            container->propogate_func(_func); }
}
