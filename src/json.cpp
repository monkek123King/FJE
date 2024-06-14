#include "json.h"

// 组合组件：对象
void JsonObject::add(const std::string& key, std::shared_ptr<JsonElement> value) {
    jsonNode node = {key, value};
    jsonNodes.emplace_back(node);
}

std::shared_ptr<AbsIterator> JsonObject::getIterator() {
    return std::make_shared<JsonIterator>(jsonNodes);
}  


void JsonObject::setIcon(std::shared_ptr<IconFamily> icon_family) {
    std::string internal_icon = icon_family->getInternalNodeIcon();
    std::string leaf_icon = icon_family->getLeafNodeIcon();
    int len = (int)jsonNodes.size();
    for (int i = 0; i < len; ++i) {
        std::string prefix = leaf_icon;
        auto& value = jsonNodes[i].value;
        if (auto* child_obj = dynamic_cast<JsonObject*>(value.get())) {
            prefix = internal_icon;
            child_obj->setIcon(icon_family);
        }
        jsonNodes[i].key.insert(0, prefix);
    }
}

// 叶子组件：值
JsonValue::JsonValue(std::string value) : value(std::move(value)) {}

const std::string& JsonValue::getValue() const {
    return value;
}

// 迭代器
JsonIterator::JsonIterator(std::vector<jsonNode>& jsonNodes) {
    this->jsonNodes = jsonNodes;
    this->curIndex = 0;
}

bool JsonIterator::hasNext() {
    return curIndex < (int)(jsonNodes.size());
}  

bool JsonIterator::isLast() {
    return curIndex == (int)(jsonNodes.size()) - 1;
}

jsonNode JsonIterator::getNext() {
    jsonNode node = jsonNodes[curIndex];
    curIndex++;
    return node;
}