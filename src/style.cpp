#include "style.h"

// 树形风格（具体产品）实现
std::string TreeStyle::render(std::shared_ptr<JsonElement> json_data) {
    return renderTree(std::move(json_data), "");
}

std::string TreeStyle::renderTree(std::shared_ptr<JsonElement> data, const std::string& prefix) const {
    std::string result;
    auto* obj = dynamic_cast<JsonObject*>(data.get());
    if (obj) {
        auto iter = obj->getIterator();
        TreeContext context;
        while(iter->hasNext()) {
            bool isLast = iter->isLast();
            const auto& jsonNode = iter->getNext();
            const auto& key = jsonNode.key;
            const auto& value = jsonNode.value;
            if (const auto* child_obj = dynamic_cast<const JsonObject*>(value.get())) {
                context.setStrategy(std::make_shared<ConcreteStrategyTreeObject>());
                result += context.executeStrategy(prefix, key, "", isLast);
                std::string newPrefix = prefix + (isLast ? "   " : "│  ");
                result += renderTree(value, newPrefix);
            } else if (const auto* child_obj = dynamic_cast<const JsonValue*>(value.get())) {
                context.setStrategy(std::make_shared<ConcreteStrategyTreeLeaf>());
                result += context.executeStrategy(prefix, key, child_obj->getValue(), isLast);
            }
        }
    }
    return result;
}

std::string RectangleStyle::render(std::shared_ptr<JsonElement> json_data) {
    std::string result = renderRectangle(json_data, "", true);
    result = renderRectangle(json_data, "", false);
    result.replace(0, 3, "┌");
    result.replace(result.find("┤"), 3, "┐");
    result.replace((int)result.size() - 4, 3, "┘");

    size_t secondLastPos = result.rfind('\n', (int)result.size()-2);

    size_t foundPos = result.find("│", secondLastPos);
    while (foundPos != std::string::npos) {
        result.replace(foundPos, 3, "└");
        foundPos = result.find("│", foundPos + std::string("│").length());
    }

    foundPos = result.find("├", secondLastPos);
    while (foundPos != std::string::npos) {
        result.replace(foundPos, 3, "└");
        foundPos = result.find("├", foundPos + std::string("├").length());
    }

    foundPos = result.find(" ", secondLastPos);
    while (foundPos != std::string::npos) {
        result.replace(foundPos, 1, "─");
        foundPos = result.find(" ", foundPos + std::string("│").length());
    }
    return result;
}

std::string RectangleStyle::renderRectangle(std::shared_ptr<JsonElement> data, const std::string& prefix, bool getDisplayLength) {
    std::string result;
    auto* obj = dynamic_cast<JsonObject*>(data.get());
    if (obj) {
        auto iter = obj->getIterator();
        RectangleContext context;
        while(iter->hasNext()) {
            bool isLast = iter->isLast();
            const auto& jsonNode = iter->getNext();
            const auto& key = jsonNode.key;
            const auto& value = jsonNode.value;
            if (const auto* child_obj = dynamic_cast<const JsonObject*>(value.get())) {
                context.setStrategy(std::make_shared<ConcreteStrategyRectangleObject>());
                std::string curRow = context.executeStrategy(prefix, key, "", this->displayLength, getDisplayLength);
                if (getDisplayLength) 
                    this->displayLength = std::max(this->displayLength, calculateDisplayWidth(curRow));
                result += curRow + "┤\n";
                result += renderRectangle(value, prefix + "│  ", getDisplayLength);
            } else if (const auto* child_value = dynamic_cast<const JsonValue*>(value.get())) {
                context.setStrategy(std::make_shared<ConcreteStrategyRectangleLeaf>());
                std::string curRow = context.executeStrategy(prefix, key, child_value->getValue(), this->displayLength, getDisplayLength);
                if (getDisplayLength)
                    this->displayLength = std::max(this->displayLength, calculateDisplayWidth(curRow));
                result += curRow + "┤\n";
            }
        }
    }
    return result;
}

int RectangleStyle::calculateDisplayWidth(std::string str) {
    double width = 0;
    for (char ch : str) {
        if ((unsigned char)ch > 127) {
            // 假设特殊字符的 ASCII 码大于 127，且其显示宽度为0.5
            width += 1.0 / 3;
        } else {
            // 普通英文字符的显示宽度为1
            width += 1;
        }
    }
    return (int)(width + 1.0 / 3);  // 向上取整
}

// 树形风格工厂（具体工厂）实现
std::shared_ptr<Style> TreeStyleFactory::createStyle() const {
    return std::make_unique<TreeStyle>();
}

// 矩形风格工厂（具体工厂）实现
std::shared_ptr<Style> RectangleStyleFactory::createStyle() const {
    return std::make_unique<RectangleStyle>();
}

// 策略实现
std::string ConcreteStrategyTreeObject::renderElement(std::string prefix, std::string key, std::string value, bool isLast) {
    std::string curRow;
    curRow += prefix;
    if (isLast) {
        curRow += "└─";
    } else {
        curRow += "├─";
    }
    curRow += key + "\n";
    return curRow;
}

std::string ConcreteStrategyTreeLeaf::renderElement(std::string prefix, std::string key, std::string value, bool isLast) {
    std::string curRow;
    curRow += prefix;
    if (isLast) {
        curRow += "└─";
    } else {
        curRow += "├─";
    }
    curRow += key;
    if (value != "null") {
        curRow += ": " + value;
    }
    curRow += "\n";
    return curRow;
}

std::string ConcreteStrategyRectangleObject::renderElement(std::string prefix, std::string key, std::string value, int displayLength,bool getDisplayLength) {
    std::string curRow;
    curRow += prefix;
    curRow += "├─";
    curRow += key;
    if (getDisplayLength) {
        return curRow;
    } else {
        int num = displayLength + 10 - RectangleStyle::calculateDisplayWidth(curRow);
        for (int k = 0; k < num; ++k) {
            curRow += "─";
        }
    }
    return curRow;
}

std::string ConcreteStrategyRectangleLeaf::renderElement(std::string prefix, std::string key, std::string value, int displayLength, bool getDisplayLength) {
    std::string curRow;
    curRow += prefix;
    curRow += "├─";
    curRow += key;
    if (value != "null") {
        curRow += ": " + value;
    }
    if (getDisplayLength) {
        return curRow;
    } else {
        int num = displayLength + 10 - RectangleStyle::calculateDisplayWidth(curRow);
        for (int k = 0; k < num; ++k) {
            curRow += "─";
        }
    }
    return curRow;   
}

// 上下文接口实现
void TreeContext::setStrategy(std::shared_ptr<TreeStrategy> strategy) {
    this->strategy = strategy;
}

std::string TreeContext::executeStrategy(std::string prefix, std::string key, std::string value, bool isLast) {
    return this->strategy->renderElement(prefix, key, value, isLast);
}

void RectangleContext::setStrategy(std::shared_ptr<RectangleStrategy> strategy) {
    this->strategy = strategy;
}

std::string RectangleContext::executeStrategy(std::string prefix, std::string key, std::string value, int displayLength,bool getDisplayLength) {
    return this->strategy->renderElement(prefix, key, value, displayLength, getDisplayLength);
}