#include <JagolyGUI/Assert.hpp>
#include <JagolyGUI/Widget.hpp>

using namespace jagolygui;

Vec2U Widget::calc_minimum_size() {
    JGASSERT(less_equal(minimumSize, maximumSize), "");
    return minimumSize;
}
