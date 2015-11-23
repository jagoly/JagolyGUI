#include <JagolyGUI/Assert.hpp>
#include <JagolyGUI/containers/BoxH.hpp>

using namespace jagolygui;

Vec2U BoxH::calc_minimum_size() {
    JGASSERT(less_equal(minimumSize, maximumSize), "");

    if (children.empty() == true) return minimumSize;

    minWithExtra = {0u, 0u};

    for (auto& child : children) {
        child->calculatedSize = child->calc_minimum_size();
        minWithExtra.y = std::max(child->calculatedSize.y, minWithExtra.y);
        minWithExtra.x += child->calculatedSize.x;
    }

    minWithExtra += margin + margin;
    minWithExtra.x += (children.size() - 1u) * spacing;
    JGASSERT(less_equal(minWithExtra, maximumSize), "");

    return max2(minimumSize, minWithExtra);
}

void BoxH::update_layout_expanding() {
    if (children.empty() == true) return;

    std::vector<Widget*> expandableVec;
    expandableVec.reserve(children.size());

    Vec2U extraTotal = calculatedSize - minWithExtra;

    while (extraTotal.x != 0u) {
        expandableVec.clear();

        for (auto& child : children)
            if (child->sizeModeH == SizeMode::Expanding
                && child->calculatedSize.x < child->maximumSize.x)
                    expandableVec.push_back(child.get());

        if (expandableVec.empty() == true) break;

        if (extraTotal.x >= expandableVec.size()) {
            uint extraSingle = extraTotal.x / expandableVec.size();

            for (auto child : expandableVec) {
                child->calculatedSize.x += extraSingle;
                extraTotal.x -= extraSingle;

                if (child->calculatedSize.x > child->maximumSize.x) {
                    extraTotal.x += child->calculatedSize.x - child->maximumSize.x;
                    child->calculatedSize.x = child->maximumSize.x;
                }
            }
        } else {
            for (auto child : expandableVec) {
                child->calculatedSize.x += 1u;
                if (--extraTotal.x == 0u) break;
            }
        }
    }

    uint childrenHeight = calculatedSize.y - margin.y * 2u;

    for (auto& child : children) {
        if (child->sizeModeV == SizeMode::Expanding)
            child->calculatedSize.y = std::min(childrenHeight, child->maximumSize.y);

        if (auto container = dynamic_cast<Container*>(child.get()))
            container->update_layout_expanding();
    }
}

void BoxH::update_layout_positions() {
    int crntPos = calculatedPos.x;

    for (auto& child : children) {
        child->calculatedPos.x = crntPos + margin.x;
        child->calculatedPos.y = calculatedPos.y + margin.y;
        crntPos += child->calculatedSize.x + spacing;

        if (auto container = dynamic_cast<Container*>(child.get()))
            container->update_layout_positions();
    }
}
