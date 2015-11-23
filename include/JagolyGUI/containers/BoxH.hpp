#pragma once

#include <JagolyGUI/containers/BoxBase.hpp>

namespace jagolygui {

class BoxH : public BoxBase {
public:
    Vec2U calc_minimum_size() override;

    void update_layout_expanding() override;

    void update_layout_positions() override;
};

}
