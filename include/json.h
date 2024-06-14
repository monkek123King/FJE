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

// json节点
struct jsonNode {
    std::string key;
    std::shared_ptr<JsonElement> value;
};


// 抽象迭代器
class AbsIterator {
public:
    virtual bool hasNext() = 0;
    virtual bool isLast() = 0;
    virtual jsonNode getNext() = 0;
    virtual ~AbsIterator() = default;
};

// 组合组件：对象
class JsonObject : public JsonElement {
public:
    void add(const std::string& key, std::shared_ptr<JsonElement> value);
    void setIcon(std::shared_ptr<IconFamily> icon_family);
    std::shared_ptr<AbsIterator> getIterator();

private:
    std::vector<jsonNode> jsonNodes;
};

// 叶子组件：值
class JsonValue : public JsonElement {
public:
    explicit JsonValue(std::string value);
    const std::string& getValue() const;

private:
    std::string value;
};

// 具体迭代器
class JsonIterator : public AbsIterator {
public:
    JsonIterator(std::vector<jsonNode>& jsonNodes);

    bool hasNext() override;

    bool isLast() override;

    jsonNode getNext() override;

private:
    std::vector<jsonNode> jsonNodes;
    int curIndex;
};

#endif //JSON_H