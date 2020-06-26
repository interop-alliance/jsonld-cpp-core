#include "ObjUtils.h"

ObjUtils::json ObjUtils::newMap() {
    return json::object();
}

ObjUtils::json ObjUtils::newMap(const std::string& key, ObjUtils::json value) {
    auto result = newMap();
    result[key] = value;
    return result;
}


