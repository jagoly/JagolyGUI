#include <JagolyGUI/Assert.hpp>
#include <JagolyGUI/containers/BoxV.hpp>

using namespace jagolygui;

Vec2U BoxV::calc_minimum_size() {
    JGASSERT(less_equal(minimumSize, maximumSize), "");

    if (children.empty() == true) return minimumSize;

    minWithExtra = {0u, 0u};

    for (auto& child : children) {
        child->calculatedSize = child->calc_minimum_size();
        minWithExtra.x = std::max(child->calculatedSize.x, minWithExtra.x);
        minWithExtra.y += child->calculatedSize.y;
    }

    minWithExtra += margin + margin;
    minWithExtra.y += (children.size() - 1u) * spacing;
    JGASSERT(less_equal(minWithExtra, maximumSize), "");

    return max2(minimumSize, minWithExtra);
}

void BoxV::update_layout_expanding() {
    if (children.empty() == true) return;

    std::vector<Widget*> expandableVec;
    expandableVec.reserve(children.size());

    Vec2U extraTotal = calculatedSize - minWithExtra;

    while (extraTotal.y != 0u) {
        expandableVec.clear();

        for (auto& child : children)
            if (child->sizeModeV == SizeMode::Expanding
                && child->calculatedSize.y < child->maximumSize.y)
                    expandableVec.push_back(child.get());

        if (expandableVec.empty() == true) break;

        if (extraTotal.y >= expandableVec.size()) {
            uint extraSingle = extraTotal.y / expandableVec.size();

            for (auto child : expandableVec) {
                child->calculatedSize.y += extraSingle;
                extraTotal.y -= extraSingle;

                if (child->calculatedSize.y > child->maximumSize.y) {
                    extraTotal.y += child->calculatedSize.y - child->maximumSize.y;
                    child->calculatedSize.y = child->maximumSize.y;
                }
            }
        } else {
            for (auto child : expandableVec) {
                child->calculatedSize.y += 1u;
                if (--extraTotal.y == 0u) break;
            }
        }
    }

    uint childrenWidth = calculatedSize.x - margin.x * 2u;

    for (auto& child : children) {
        if (child->sizeModeH == SizeMode::Expanding)
            child->calculatedSize.x = std::min(childrenWidth, child->maximumSize.x);

        if (auto container = dynamic_cast<Container*>(child.get()))
            container->update_layout_expanding();
    }
}

void BoxV::update_layout_positions() {
    int crntPos = calculatedPos.y;

    for (auto& child : children) {
        child->calculatedPos.y = crntPos + margin.y;
        child->calculatedPos.x = calculatedPos.x + margin.x;
        crntPos += child->calculatedSize.y + spacing;

        if (auto container = dynamic_cast<Container*>(child.get()))
            container->update_layout_positions();
    }
}
