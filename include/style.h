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

private:
    std::string renderRectangle(std::shared_ptr<JsonElement> data, const std::string& prefix, bool getDisplayLength);
    int calculateDisplayWidth(std::string str) const;

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

#endif //STYLE_H
