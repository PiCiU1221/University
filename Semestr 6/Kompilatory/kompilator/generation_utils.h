#pragma once

#include "symbol.h"

#include <string>
#include <fstream>
#include <map>

void generatePrintCode(const std::string& line, std::ofstream& out, const std::map<std::string, Symbol>& symbolTable);
void generateInputCode(const std::string& line, std::ofstream& out, const std::map<std::string, Symbol>& symbolTable);
void generateExpressionCode(const std::string& line, std::ofstream& out, const std::map<std::string, Symbol>& symbolTable);
void generateArrayAssignmentCode(const std::string& line, std::ofstream& out, const std::map<std::string, Symbol>& symbolTable);
void generateAssignmentCode(const std::string& line, std::ofstream& out, const std::map<std::string, Symbol>& symbolTable);
void generateDeclarationCode(const std::string& line, std::ofstream& out, const std::map<std::string, Symbol>& symbolTable);
void generateIfTrue(const std::string& line, std::ofstream& out);
void generateIfFalse(const std::string& line, std::ofstream& out);
void generateGoto(const std::string& line, std::ofstream& out);
void generateLabel(const std::string& line, std::ofstream& out);
