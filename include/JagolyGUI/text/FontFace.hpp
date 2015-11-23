#pragma once

#include <string>
#include <vector>

#include <JagolyGUI/DataTypes.hpp>

namespace jagolygui {

class FontFace {
public:
    uint get_charHeight() const { return charHeight; }

    uint calc_string_width(const std::string& _str) const {
        return _str.size() * 10u;
    }

protected:
    uint charHeight = 6u;
};

}
