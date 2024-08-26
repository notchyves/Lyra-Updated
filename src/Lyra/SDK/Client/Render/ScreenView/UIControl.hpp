#pragma once

#include "../../../../../Utils/Memory/Memory.hpp"
#include "UIComponent.hpp"

class UIControl {
public:
    BUILD_ACCESS(this, std::string, LayerName, 0x20);
    BUILD_ACCESS(this, float, scale, 0x48);
    BUILD_ACCESS(this, float, x, 0x10);
    BUILD_ACCESS(this, float, y, 0x14);
    BUILD_ACCESS(this, std::vector<std::shared_ptr<UIControl>>, children, 0x90);
    BUILD_ACCESS(this, std::vector<std::shared_ptr<UIControl>>, components, 0xB0);

    void getAllControls(std::vector<std::shared_ptr<UIControl>>& list) {
        for (auto& control : this->children) {
            list.emplace_back(control);
            control->getAllControls(list);
        }
    }

    void forEachControl(std::function<void(std::shared_ptr<UIControl>&)>&& func) {

        std::vector<std::shared_ptr<UIControl>> writeList;
        this->getAllControls(writeList);

        for (auto& control : writeList) {
            func(control);
        }
    }
};