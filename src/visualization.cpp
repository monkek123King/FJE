#include "visualization.h"

// 具体的建造者类实现
void ConcreteVisualizationBuilder::setStyle(std::shared_ptr<Style> style) {
    this->style = std::move(style);
}

void ConcreteVisualizationBuilder::setIconFamily(std::shared_ptr<IconFamily> icon_family) {
    this->icon_family = std::move(icon_family);
}

void ConcreteVisualizationBuilder::setJsonData(std::shared_ptr<JsonElement> json_data) {
    this->json_data = std::move(json_data);
}

std::string ConcreteVisualizationBuilder::build() const {
    if (!style || !icon_family || !json_data) {
        throw std::runtime_error("Style, icon family, and JSON data must be set before building.");
    }

    auto* obj = dynamic_cast<JsonObject*>(this->json_data.get());
    obj->setIcon(this->icon_family);

    std::string rendered_output = style->render(json_data);
    return rendered_output;
}

// 指导者类（Director）实现
void VisualizationDirector::setBuilder(std::shared_ptr<VisualizationBuilder> builder) {
    this->builder = std::move(builder);
}

std::string VisualizationDirector::construct(std::shared_ptr<JsonElement> json_data) const {
    if (!builder) {
        throw std::runtime_error("Builder is not set.");
    }
    builder->setJsonData(std::move(json_data));
    return builder->build();
}
