/*
 * 用组合模式来实现json的层次结构
 */

#ifndef JSON_H
#define JSON_H

#include "icon.h"

#include <any>
#include <string>
#include <vector>
#include <memory>

// 抽象组件
class JsonElement {
public:
    virtual ~JsonElement() = default;
};

// 组合组件：对象
class JsonObject : public JsonElement {
public:
    void add(const std::string& key, std::shared_ptr<JsonElement> value);
    const std::vector<std::string>& getKeys() const;
    const std::vector<std::shared_ptr<JsonElement>>& getValues() const;
    void setIcon(std::shared_ptr<IconFamily> icon_family);

private:
    std::vector<std::string> keys;
    std::vector<std::shared_ptr<JsonElement>> values;
};

// 叶子组件：值
class JsonValue : public JsonElement {
public:
    explicit JsonValue(std::string value);
    const std::string& getValue() const;

private:
    std::string value;
};

#endif //JSON_H
