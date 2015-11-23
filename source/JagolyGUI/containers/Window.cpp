#include <JagolyGUI/Assert.hpp>
#include <JagolyGUI/containers/Frame.hpp>

using namespace jagolygui;

Vec2U Frame::calc_minimum_size() {
    JGASSERT(less_equal(minimumSize, maximumSize), "");

    if (child.get() == nullptr) return minimumSize;

    child->calculatedSize = child->calc_minimum_size();

    Vec2U minWithExtra = child->calculatedSize + margin * 2u;
    JGASSERT(less_equal(minWithExtra, maximumSize), "");

    return max2(minimumSize, minWithExtra);
}

void Frame::update_layout_expanding() {
    if (child.get() == nullptr) return;

    Vec2U minWithExtra = child->calculatedSize + margin * 2u;
    Vec2U extraTotal = calculatedSize - minWithExtra;

    if (extraTotal.x != 0u && child->sizeModeX != SizeMode::Minimum) {
        child->calculatedSize.x = child->calculatedSize.x + extraTotal.x;
        child->calculatedSize.x = std::min(child->maximumSize.x, child->calculatedSize.x);
    }

    if (extraTotal.y != 0u && child->sizeModeY != SizeMode::Minimum) {
        child->calculatedSize.y = child->calculatedSize.y + extraTotal.y;
        child->calculatedSize.y = std::min(child->maximumSize.y, child->calculatedSize.y);
    }

    if (auto container = dynamic_cast<Container*>(child.get()))
        container->update_layout_expanding();
}

void Frame::update_layout_positions() {
    if (child.get() == nullptr) return;

    child->calculatedPos = calculatedPos + Vec2I(margin.x, margin.y);

    if (auto container = dynamic_cast<Container*>(child.get()))
        container->update_layout_positions();
}
