/*
 * 用工厂方法模式来设计style类
 * 如果要加新的风格，只需要加一个新的工厂即可，不需要修改已有代码
*/

#ifndef STYLE_H
#define STYLE_H

#include <iostream>
#include <string>
#include <memory>
#include <locale>
#include <codecvt>
#include <cwchar>

#include "json.h"

// 风格接口（抽象产品）
class Style {
public:
    virtual std::string render(std::shared_ptr<JsonElement> json_data) = 0;
    virtual ~Style() = default;
};

// 树形风格（具体产品）
class TreeStyle : public Style {
public:
    std::string render(std::shared_ptr<JsonElement> json_data) override;

private:
    std::string renderTree(std::shared_ptr<JsonElement> data, const std::string& prefix) const;
};

// 矩形风格（具体产品）
class RectangleStyle : public Style {
public:
    std::string render(std::shared_ptr<JsonElement> json_data) override;
    static int calculateDisplayWidth(std::string str);

private:
    std::string renderRectangle(std::shared_ptr<JsonElement> data, const std::string& prefix, bool getDisplayLength);

    int displayLength = 0;
};

// 风格工厂接口（抽象工厂）
class StyleFactory {
public:
    virtual std::shared_ptr<Style> createStyle() const = 0;
    virtual ~StyleFactory() = default;
};

// 树形风格工厂（具体工厂）
class TreeStyleFactory : public StyleFactory {
public:
    std::shared_ptr<Style> createStyle() const override;
};

// 矩形风格工厂（具体工厂）
class RectangleStyleFactory : public StyleFactory {
public:
    std::shared_ptr<Style> createStyle() const override;
};

// 树形策略接口（抽象策略）
class TreeStrategy {
public:
    virtual std::string renderElement(std::string prefix, std::string key, std::string value, bool isLast) = 0;
};

// 矩形策略接口（抽象策略）
class RectangleStrategy {
public:
    virtual std::string renderElement(std::string prefix, std::string key, std::string value, int displayLength,bool getDisplayLength) = 0;
};

// 树形叶子节点策略
class ConcreteStrategyTreeLeaf : public TreeStrategy {
public:
    std::string renderElement(std::string prefix, std::string key, std::string value, bool isLast) override;
};

// 树形中间节点策略
class ConcreteStrategyTreeObject : public TreeStrategy {
public:
    std::string renderElement(std::string prefix, std::string key, std::string value, bool isLast) override;
};

// 矩形叶子节点策略
class ConcreteStrategyRectangleLeaf : public RectangleStrategy {
public:
    std::string renderElement(std::string prefix, std::string key, std::string value, int displayLength,bool getDisplayLength) override;
};

// 矩形中间节点策略
class ConcreteStrategyRectangleObject : public RectangleStrategy {
public:
    std::string renderElement(std::string prefix, std::string key, std::string value, int displayLength,bool getDisplayLength) override;
};

// 树形上下文接口
class TreeContext {
public:
    void setStrategy(std::shared_ptr<TreeStrategy> strategy);

    std::string executeStrategy(std::string prefix, std::string key, std::string value, bool isLast);

private:
    std::shared_ptr<TreeStrategy> strategy;
};

// 矩形上下文接口
class RectangleContext {
public:
    void setStrategy(std::shared_ptr<RectangleStrategy> strategy);

    std::string executeStrategy(std::string prefix, std::string key, std::string value, int displayLength,bool getDisplayLength);

private:
    std::shared_ptr<RectangleStrategy> strategy;
};

#endif //STYLE_H
