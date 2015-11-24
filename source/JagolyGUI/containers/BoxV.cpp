#include <JagolyGUI/Assert.hpp>
#include <JagolyGUI/containers/BoxV.hpp>

using namespace jagolygui;

Vec2U BoxV::calc_minimum_size() {
    JGASSERT(less_equal(minimumSize, maximumSize), "");

    if (children.empty() == true) return minimumSize;

    Vec2U childrenMinSize = {0u, 0u};

    for (auto& child : children) {
        child->calculatedSize = child->calc_minimum_size();
        childrenMinSize.x = std::max(child->calculatedSize.x, childrenMinSize.x);
        childrenMinSize.y = childrenMinSize.y + child->calculatedSize.y;
    }

    childrenMinSize += margin + margin;
    childrenMinSize.y += (children.size() - 1u) * spacing;
    JGASSERT(less_equal(childrenMinSize, maximumSize), "");

    return max2(minimumSize, childrenMinSize);
}

void BoxV::update_layout_expanding() {
    if (children.empty() == true) return;

    uint remainingSpace = calculatedSize.y - margin.y * 2u;
    remainingSpace -= (children.size() - 1u) * spacing;

    std::vector<Widget*> widgetVec;

    for (auto& child : children) {
        remainingSpace -= child->calculatedSize.y;
        if (child->sizeModeV == SizeMode::Expanding &&
            child->calculatedSize.y != child->maximumSize.y)
            widgetVec.emplace_back(child.get());
    }

    while (remainingSpace && !widgetVec.empty()) {
        uint minOne = -1u, minTwo = -1u, count = 0u;

        for (const auto w : widgetVec) {
            if (w->calculatedSize.y < minTwo) {
                if (w->calculatedSize.y < minOne)
                    minTwo = minOne, minOne = w->calculatedSize.y;
                else if (w->calculatedSize.y != minOne)
                    minTwo = w->calculatedSize.y;
            }
        }

        for (auto w : widgetVec) count += w->calculatedSize.y == minOne;

        if (remainingSpace > count) {
            uint extra = std::min((minTwo - minOne) * count, remainingSpace) / count;

            for (auto iter = widgetVec.begin(); iter != widgetVec.end(); ++iter) {
                if ((*iter)->calculatedSize.y != minOne) continue;

                (*iter)->calculatedSize.y += extra;
                remainingSpace -= extra;

                if ((*iter)->calculatedSize.y > (*iter)->maximumSize.y) {
                    remainingSpace += (*iter)->calculatedSize.y - (*iter)->maximumSize.y;
                    (*iter)->calculatedSize.y = (*iter)->maximumSize.y;
                }

                if ((*iter)->calculatedSize.y == (*iter)->maximumSize.y)
                    iter = --widgetVec.erase(iter);
            }
        } else {
            for (auto w : widgetVec) {
                if (w->calculatedSize.y != minOne) continue;

                w->calculatedSize.y += 1u;
                if (--remainingSpace == 0u) break;
            }
        }
    }

    uint width = calculatedSize.x - margin.x * 2u;

    for (auto& child : children) {
        if (child->sizeModeH == SizeMode::Expanding)
            child->calculatedSize.x = std::min(width, child->maximumSize.x);

        if (auto container = dynamic_cast<Container*>(child.get()))
            container->update_layout_expanding();
    }
}

void BoxV::update_layout_positions() {
    if (children.empty() == true) return;

    //uint childrenSize = margin.y * 2u + (children.size() - 1u) * spacing;
    //for (auto& child : children) childrenSize -= child->calculatedSize.x;
    //if (childrenSize == calculatedSize.y) {

    auto iterFwd = children.begin();
    auto iterRev = children.rbegin();

    int crntPosFwd = calculatedPos.y + margin.y;
    int crntPosRev = calculatedPos.y + calculatedSize.y - margin.y;

    for (; iterFwd != children.end(); ++iterFwd) {
        if ((*iterFwd)->alignModeV != AlignMode::Negative) break;
        (*iterFwd)->calculatedPos.y = crntPosFwd;
        crntPosFwd += (*iterFwd)->calculatedSize.y + spacing;
    }

    for (; iterRev != children.rend(); ++iterRev) {
        if ((*iterRev)->alignModeV != AlignMode::Positive) break;
        (*iterRev)->calculatedPos.y = crntPosRev - (*iterRev)->calculatedSize.y;
        crntPosRev -= (*iterRev)->calculatedSize.y + spacing;
    }

    if (iterFwd != iterRev.base()) {
        uint count = std::distance(iterFwd, iterRev.base());
        uint centreSpace = crntPosRev - crntPosFwd;
        centreSpace -= (count - 1u) * spacing;

        for (auto iter = iterFwd; iter != iterRev.base(); ++iter)
            centreSpace -= (*iter)->calculatedSize.y;

        uint crntPos = crntPosFwd;
        uint spaceEach = centreSpace / (count + 1u);
        uint spaceRem = centreSpace % (count + 1u);

        for (auto iter = iterFwd; iter != iterRev.base(); ++iter) {
            if (spaceRem) { ++crntPos; --spaceRem; }
            crntPos = crntPos + spaceEach;

            (*iter)->calculatedPos.y = crntPos;
            crntPos += (*iter)->calculatedSize.y + spacing;
        }
    }

    for (auto& child : children) {
        if (child->alignModeH == AlignMode::Positive)
            child->calculatedPos.x = calculatedPos.x + calculatedSize.x - child->calculatedSize.x - margin.x;
        else if (child->alignModeH == AlignMode::Negative) child->calculatedPos.x = calculatedPos.x + margin.x;
        else child->calculatedPos.x = calculatedPos.x + calculatedSize.x / 2u - child->calculatedSize.x / 2u;

        if (auto container = dynamic_cast<Container*>(child.get()))
            container->update_layout_positions();
    }
}
