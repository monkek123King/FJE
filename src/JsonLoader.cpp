#include "JsonLoader.h"

// 跳过空白字符
void JsonLoader::skipWhitespace(const std::string& str, size_t& pos) {
    while (pos < str.size() && std::isspace(str[pos])) {
        ++pos;
    }
}

// 解析 JSON 对象
std::shared_ptr<JsonObject> JsonLoader::parseJsonObject(const std::string& str, size_t& pos) {
    auto jsonObject = std::make_shared<JsonObject>();
    ++pos;  // 跳过 '{'
    skipWhitespace(str, pos);
    while (pos < str.size() && str[pos] != '}') {
        skipWhitespace(str, pos);
        if (str[pos] == '"') {
            ++pos;  // 跳过 '"'
            size_t start = pos;
            while (pos < str.size() && str[pos] != '"') {
                ++pos;
            }
            std::string key = str.substr(start, pos - start);   // 键的内容
            ++pos;  // 跳过 '"'
            skipWhitespace(str, pos);
            if (str[pos] != ':') {
                throw std::runtime_error("Expected ':' after key in JSON object");
            }
            ++pos;  // 跳过 ':'
            skipWhitespace(str, pos);
            jsonObject->add(key, parseJson(str, pos));
            skipWhitespace(str, pos);
            if (str[pos] == ',') {
                ++pos;  // 跳过 ','
            }
        }
        skipWhitespace(str, pos);
    }
    ++pos;  // 跳过 '}'
    return jsonObject;
}

// 解析 JSON 值
std::shared_ptr<JsonValue> JsonLoader::parseJsonValue(const std::string& str, size_t& pos) {
    if (str[pos] == '"') {
        ++pos;  // 跳过 '"'
        size_t start = pos;
        while (pos < str.size() && str[pos] != '"') {
            ++pos;
        }
        std::string value = str.substr(start, pos - start);
        ++pos;  // 跳过 '"'
        return std::make_shared<JsonValue>(value);
    } else {
        size_t start = pos;
        while (pos < str.size() && !std::isspace(str[pos]) && str[pos] != ',' && str[pos] != ']' && str[pos] != '}') {
            ++pos;
        }
        std::string value = str.substr(start, pos - start);
        return std::make_shared<JsonValue>(value);
    }
}

// 解析 JSON
std::shared_ptr<JsonElement> JsonLoader::parseJson(const std::string& str, size_t& pos) {
    skipWhitespace(str, pos);
    if (pos >= str.size()) {
        throw std::runtime_error("Unexpected end of JSON string");
    }
    if (str[pos] == '{') {
        return parseJsonObject(str, pos);
    } else {
        return parseJsonValue(str, pos);
    }
}

// 从文件中加载 JSON 并返回自定义的 JSON 类型
std::shared_ptr<JsonElement> JsonLoader::loadJson(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open JSON file");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    size_t pos = 0;
    return parseJson(buffer.str(), pos);
}
