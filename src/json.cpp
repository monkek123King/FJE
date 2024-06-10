#include "json.h"

// 组合组件：对象
void JsonObject::add(const std::string& key, std::shared_ptr<JsonElement> value) {
    keys.emplace_back(key);
    values.emplace_back(std::move(value));
}

const std::vector<std::string>& JsonObject::getKeys() const {
    return keys;
}

const std::vector<std::shared_ptr<JsonElement>>& JsonObject::getValues() const {
    return values;
}

void JsonObject::setIcon(std::shared_ptr<IconFamily> icon_family) {
    std::string internal_icon = icon_family->getInternalNodeIcon();
    std::string leaf_icon = icon_family->getLeafNodeIcon();
    int len = (int)keys.size();
    for (int i = 0; i < len; ++i) {
        std::string prefix = leaf_icon;
        auto& value = values[i];
        if (auto* child_obj = dynamic_cast<JsonObject*>(value.get())) {
            prefix = internal_icon;
            child_obj->setIcon(icon_family);
        }
        keys[i].insert(0, prefix);
    }
}

// 叶子组件：值
JsonValue::JsonValue(std::string value) : value(std::move(value)) {}

const std::string& JsonValue::getValue() const {
    return value;
}