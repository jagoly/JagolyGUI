#pragma once

#include <JagolyGUI/Widget.hpp>
#include <JagolyGUI/text/FontFace.hpp>

namespace jagolygui {

class Label : public Widget {
public:
    Label(const FontFace* _font) : font(_font) {}

    Vec2U calc_minimum_size();

    std::string str = u8"Hello, World!";

    const FontFace* font;
};

}
