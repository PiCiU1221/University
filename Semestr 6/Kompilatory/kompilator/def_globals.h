#pragma once

#include "symbol.h"

#include <stack>
#include <map>
#include <string>
#include <fstream>

extern std::stack<Symbol> basicStack;
extern std::map<std::string, Symbol> symbolTable;
extern std::ofstream threesFile;
