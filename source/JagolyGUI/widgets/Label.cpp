#include <JagolyGUI/Assert.hpp>
#include <JagolyGUI/widgets/Label.hpp>

using namespace jagolygui;

Vec2U Label::calc_minimum_size() {
    JGASSERT(less_equal(minimumSize, maximumSize), "");

    Vec2U textMinSize(font->calc_string_width(str), font->get_charHeight());

    JGASSERT(less_equal(textMinSize, maximumSize), "");

    return max2(minimumSize, textMinSize);
}
