#include <JagolyGUI/Container.hpp>
#include <JagolyGUI/RenderTree.hpp>

using namespace jagolygui;

void RenderTree::render_widget(Widget* _widget) {
    const RenderPair* rp = &renderPairMap.at(&typeid(*_widget));

    std::vector<WidgetFunc> funcs; const RenderPair* base = rp;

    while (base) { if (base->func) funcs.push_back(base->func); base = base->base; }

    for (auto it = funcs.rbegin(); it != funcs.rend(); ++it) (*it)(_widget);

    if (auto container = dynamic_cast<Container*>(_widget))
        for (auto child : container->get_children()) render_widget(child);
}
