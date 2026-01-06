#pragma once

#include "symbol.h"

#include <string>
#include <vector>

void code_write(const std::string& op);
void code_write_assignment(const std::string& varName);

void process_declaration(const std::string& varName);
void process_declaration_and_assignment(const std::string& varName);

void process_array_declaration(const std::string& type, const std::string& varName, std::vector<int>* dims);
void code_write_array_element_assignment(const std::string& varName, std::vector<Symbol>* indices);
void process_array_value(const std::string& varName, std::vector<Symbol>* indices);

void process_and_print_nonvariables();

void handleIncrement(const std::string& varName);

std::string generate_label(const std::string& base);

void write_if_condition();
void write_if_true_condition();
void write_else_start();
void write_if_end();

void write_for_label();
void write_for_condition();
void write_for_end();

void handle_increment(const std::string& varName);
void process_dynamic_array_declaration(const std::string& type, const std::string& name, const Symbol& size);
