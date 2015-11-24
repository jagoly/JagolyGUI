#include <JagolyGUI/Assert.hpp>
#include <JagolyGUI/Container.hpp>
#include <JagolyGUI/RenderTree.hpp>

using namespace jagolygui;

void RenderTree::render_widget(Widget* _widget) {
    auto rdata = &renderDataMap.at(typeid(*_widget));
    std::vector<WidgetFunc> funcs;

    while (true) {
        if (rdata->drawFunc) funcs.push_back(rdata->drawFunc);
        if (rdata->base == typeid(std::nullptr_t)) break;
        rdata = &renderDataMap.at(rdata->base);
    }

    for (auto it = funcs.rbegin(); it != funcs.rend(); ++it)
        it->operator()(_widget);

    if (auto container = dynamic_cast<Container*>(_widget))
        for (auto child : container->get_children())
            render_widget(child);
}

void RenderTree::impl_register_widget(WidgetFunc _drawFunc, std::type_index _type, std::type_index _base) {
    JGASSERT(_base == typeid(std::nullptr_t) || renderDataMap.count(_base), "");
    JGASSERT(_base != typeid(std::nullptr_t) || _drawFunc != nullptr, "");
    renderDataMap.emplace(_type, RenderData{_drawFunc, _base});
}
