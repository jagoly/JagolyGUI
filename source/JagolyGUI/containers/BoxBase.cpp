#include <JagolyGUI/Assert.hpp>
#include <JagolyGUI/Helpers.hpp>
#include <JagolyGUI/containers/BoxBase.hpp>

using namespace jagolygui;

std::vector<Widget*> BoxBase::get_children() {
    std::vector<Widget*> retVec; retVec.reserve(children.size());
    for (auto& child : children) retVec.push_back(child.get());
    return retVec;
}

Widget* BoxBase::do_get(ulong _handle) {
    auto iter = find_widget(_handle, children);
    JGASSERT(iter != children.end(), "");
    return iter->get();
}

Widget* BoxBase::do_pop(ulong _handle) {
    auto iter = find_widget(_handle, children);
    JGASSERT(iter != children.end(), "");
    Widget* child = iter->release();
    child->parent = nullptr; child->handle = 0u;
    children.erase(iter); return child;
}

void BoxBase::do_erase(ulong _handle) {
    auto iter = find_widget(_handle, children);
    JGASSERT(iter != children.end(), "");
    children.erase(iter);
}

void BoxBase::impl_append(ulong _handle, Widget* _widget) {
    JGASSERT(find_widget(_handle, children) == children.end(), "");
    _widget->parent = this; _widget->handle = _handle;
    children.emplace_back(_widget);
}
