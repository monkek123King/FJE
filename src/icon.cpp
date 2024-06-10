#include "icon.h"

// Poker Face 图标族（具体产品）实现
std::string PokerFaceIconFamily::getInternalNodeIcon() const {
    return "♢";
}

std::string PokerFaceIconFamily::getLeafNodeIcon() const {
    return "♤";
}

// JSON 图标族（具体产品）实现
JsonIconFamily::JsonIconFamily(std::string internalNodeIcon, std::string leafNodeIcon) {
    this->internalNodeIcon = internalNodeIcon;
    this->leafNodeIcon = leafNodeIcon;
}

std::string JsonIconFamily::getInternalNodeIcon() const {
    return internalNodeIcon;
}

std::string JsonIconFamily::getLeafNodeIcon() const {
    return leafNodeIcon;
}

// Poker Face 图标族工厂（具体工厂）实现
std::shared_ptr<IconFamily> PokerFaceIconFamilyFactory::createIconFamily() const {
    return std::make_shared<PokerFaceIconFamily>();
}

// JSON 图标族工厂（具体工厂）实现
JsonIconFamilyFactory::JsonIconFamilyFactory(std::string internalNodeIcon, std::string leafNodeIcon) {
    this->internalNodeIcon = internalNodeIcon;
    this->leafNodeIcon = leafNodeIcon;
}

std::shared_ptr<IconFamily> JsonIconFamilyFactory::createIconFamily() const {
    return std::make_shared<JsonIconFamily>(internalNodeIcon, leafNodeIcon);
}
