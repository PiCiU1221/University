#pragma once

#include "symbol.h"

#include <string>
#include <map>

void generateMIPS(const std::string& inputFile, const std::string& outputFile, const std::map<std::string, Symbol>& symbolTable);
