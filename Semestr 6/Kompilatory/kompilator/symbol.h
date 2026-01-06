#pragma once

#include <string>
#include <vector>

struct Symbol {
    std::string name;
    std::string type;
    int integerValue;
    float floatValue;
    std::string stringValue;
    std::vector<int> dims;
    std::vector<int> sizes;
};
