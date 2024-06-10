#ifndef JSON_LOADER_H
#define JSON_LOADER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <memory>

#include "json.h"

class JsonLoader {
public:
    // 从文件中加载 JSON 并返回自定义的 JSON 类型
    std::shared_ptr<JsonElement> loadJson(const std::string& file_path);

private:
    // 跳过空白字符
    void skipWhitespace(const std::string& str, size_t& pos);

    // 解析 JSON 对象
    std::shared_ptr<JsonObject> parseJsonObject(const std::string& str, size_t& pos);

    // 解析 JSON 值
    std::shared_ptr<JsonValue> parseJsonValue(const std::string& str, size_t& pos);

    // 解析 JSON
    std::shared_ptr<JsonElement> parseJson(const std::string& str, size_t& pos);
};

#endif // JSON_LOADER_H
