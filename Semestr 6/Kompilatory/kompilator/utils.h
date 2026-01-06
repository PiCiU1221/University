#pragma once

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "symbol.h"

bool isVariable(const std::string& operand, const std::map<std::string, Symbol>& symbolTable);
bool isLabel(const std::string& line);
bool isGoto(const std::string& line);
bool isIfFalse(const std::string& line);
bool isIfTrue(const std::string& line);

std::string getLineType(const std::string& line);

std::string stripArrayAccess(const std::string& s);
std::string toFloatLiteral(const std::string& val);
std::vector<std::string> extractIndexStrings(const std::string& arrayAccess);
bool isArrayAccess(const std::string& s);

void emitOffsetComputation(std::ofstream& out,
                           const std::vector<std::string>& indexStrings,
                           const std::vector<int>& strides,
                           const std::map<std::string, Symbol>& symbolTable);
