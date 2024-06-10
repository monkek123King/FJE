/*
 * 用建造者模式来实现可视化类
 */

#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "style.h"
#include "icon.h"
#include <string>
#include <map>
#include <memory>
#include <stdexcept>

// 建造者接口（抽象建造者）
class VisualizationBuilder {
public:
    virtual void setStyle(std::shared_ptr<Style> style) = 0;
    virtual void setIconFamily(std::shared_ptr<IconFamily> icon_family) = 0;
    virtual void setJsonData(std::shared_ptr<JsonElement> json_data) = 0;
    virtual std::string build() const = 0;
    virtual ~VisualizationBuilder() = default;
};

// 具体的建造者类
class ConcreteVisualizationBuilder : public VisualizationBuilder {
public:
    void setStyle(std::shared_ptr<Style> style) override;
    void setIconFamily(std::shared_ptr<IconFamily> icon_family) override;
    void setJsonData(std::shared_ptr<JsonElement> json_data) override;
    std::string build() const override;

private:
    std::shared_ptr<Style> style;
    std::shared_ptr<IconFamily> icon_family;
    std::shared_ptr<JsonElement> json_data;
};

// 指导者类（Director）
class VisualizationDirector {
public:
    void setBuilder(std::shared_ptr<VisualizationBuilder> builder);
    std::string construct(std::shared_ptr<JsonElement> json_data) const;

private:
    std::shared_ptr<VisualizationBuilder> builder;
};

#endif //VISUALIZATION_H
