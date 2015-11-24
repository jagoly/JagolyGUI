#include <JagolyGUI/Assert.hpp>
#include <JagolyGUI/containers/BoxH.hpp>

using namespace jagolygui;

Vec2U BoxH::calc_minimum_size() {
    JGASSERT(less_equal(minimumSize, maximumSize), "");

    if (children.empty() == true) return minimumSize;

    Vec2U childrenMinSize = {0u, 0u};

    for (auto& child : children) {
        child->calculatedSize = child->calc_minimum_size();
        childrenMinSize.y = std::max(child->calculatedSize.y, childrenMinSize.y);
        childrenMinSize.x = childrenMinSize.x + child->calculatedSize.x;
    }

    childrenMinSize += margin + margin;
    childrenMinSize.x += (children.size() - 1u) * spacing;
    JGASSERT(less_equal(childrenMinSize, maximumSize), "");

    return max2(minimumSize, childrenMinSize);
}

void BoxH::update_layout_expanding() {
    if (children.empty() == true) return;

    uint remainingSpace = calculatedSize.x - margin.x * 2u;
    remainingSpace -= (children.size() - 1u) * spacing;

    std::vector<Widget*> widgetVec;

    for (auto& child : children) {
        remainingSpace -= child->calculatedSize.x;
        if (child->sizeModeH == SizeMode::Expanding &&
            child->calculatedSize.x != child->maximumSize.x)
            widgetVec.emplace_back(child.get());
    }

    while (remainingSpace && !widgetVec.empty()) {
        uint minOne = -1u, minTwo = -1u, count = 0u;

        for (const auto w : widgetVec) {
            if (w->calculatedSize.x < minTwo) {
                if (w->calculatedSize.x < minOne)
                    minTwo = minOne, minOne = w->calculatedSize.x;
                else if (w->calculatedSize.x != minOne)
                    minTwo = w->calculatedSize.x;
            }
        }

        for (auto w : widgetVec) count += w->calculatedSize.x == minOne;

        if (remainingSpace > count) {
            uint extra = std::min((minTwo - minOne) * count, remainingSpace) / count;

            for (auto iter = widgetVec.begin(); iter != widgetVec.end(); ++iter) {
                if ((*iter)->calculatedSize.x != minOne) continue;

                (*iter)->calculatedSize.x += extra;
                remainingSpace -= extra;

                if ((*iter)->calculatedSize.x > (*iter)->maximumSize.x) {
                    remainingSpace += (*iter)->calculatedSize.x - (*iter)->maximumSize.x;
                    (*iter)->calculatedSize.x = (*iter)->maximumSize.x;
                }

                if ((*iter)->calculatedSize.x == (*iter)->maximumSize.x)
                    iter = --widgetVec.erase(iter);
            }
        } else {
            for (auto w : widgetVec) {
                if (w->calculatedSize.x != minOne) continue;

                w->calculatedSize.x += 1u;
                if (--remainingSpace == 0u) break;
            }
        }
    }

    uint height = calculatedSize.y - margin.y * 2u;

    for (auto& child : children) {
        if (child->sizeModeV == SizeMode::Expanding)
            child->calculatedSize.y = std::min(height, child->maximumSize.y);

        if (auto container = dynamic_cast<Container*>(child.get()))
            container->update_layout_expanding();
    }
}

void BoxH::update_layout_positions() {
    if (children.empty() == true) return;

    //uint childrenSize = margin.x * 2u + (children.size() - 1u) * spacing;
    //for (auto& child : children) childrenSize -= child->calculatedSize.x;
    //if (childrenSize == calculatedSize.x) {

    auto iterFwd = children.begin();
    auto iterRev = children.rbegin();

    int crntPosFwd = calculatedPos.x + margin.x;
    int crntPosRev = calculatedPos.x + calculatedSize.x - margin.x;

    for (; iterFwd != children.end(); ++iterFwd) {
        if ((*iterFwd)->alignModeH != AlignMode::Negative) break;
        (*iterFwd)->calculatedPos.x = crntPosFwd;
        crntPosFwd += (*iterFwd)->calculatedSize.x + spacing;
    }

    for (; iterRev != children.rend(); ++iterRev) {
        if ((*iterRev)->alignModeH != AlignMode::Positive) break;
        (*iterRev)->calculatedPos.x = crntPosRev - (*iterRev)->calculatedSize.x;
        crntPosRev -= (*iterRev)->calculatedSize.x + spacing;
    }

    if (iterFwd != iterRev.base()) {
        uint count = std::distance(iterFwd, iterRev.base());
        uint centreSpace = crntPosRev - crntPosFwd;
        centreSpace -= (count - 1u) * spacing;

        for (auto iter = iterFwd; iter != iterRev.base(); ++iter)
            centreSpace -= (*iter)->calculatedSize.x;

        uint crntPos = crntPosFwd;
        uint spaceEach = centreSpace / (count + 1u);
        uint spaceRem = centreSpace % (count + 1u);

        for (auto iter = iterFwd; iter != iterRev.base(); ++iter) {
            if (spaceRem) { ++crntPos; --spaceRem; }
            crntPos = crntPos + spaceEach;

            (*iter)->calculatedPos.x = crntPos;
            crntPos += (*iter)->calculatedSize.x + spacing;
        }
    }

    for (auto& child : children) {
        if (child->alignModeV == AlignMode::Positive)
            child->calculatedPos.y = calculatedPos.y + calculatedSize.y - child->calculatedSize.y - margin.y;
        else if (child->alignModeV == AlignMode::Negative) child->calculatedPos.y = calculatedPos.y + margin.y;
        else child->calculatedPos.y = calculatedPos.y + calculatedSize.y / 2u - child->calculatedSize.y / 2u;

        if (auto container = dynamic_cast<Container*>(child.get()))
            container->update_layout_positions();
    }
}
