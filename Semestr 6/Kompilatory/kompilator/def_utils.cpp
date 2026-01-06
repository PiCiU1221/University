#include "def_utils.h"
#include "def_globals.h"

#include <iostream>
#include <sstream>

using namespace std;

int resultCounter = 0;
int labelCounter = 0;
stack<string> labelStack;

void code_write(const string& op) {
    Symbol right = basicStack.top(); basicStack.pop();
    Symbol left = basicStack.top(); basicStack.pop();

    string resultType = (left.type == "FLOAT" || right.type == "FLOAT") ? "FLOAT" : "INT";

    if (resultType == "FLOAT") {
        if (left.type == "INT") {
            string newLeftName = "int_as_float_" + to_string(resultCounter++);
            symbolTable[newLeftName] = {newLeftName, "FLOAT", 0, static_cast<float>(left.integerValue)};
            left.name = newLeftName;
            left.type = "FLOAT";
        }

        if (right.type == "INT") {
            string newRightName = "int_as_float_" + to_string(resultCounter++);
            symbolTable[newRightName] = {newRightName, "FLOAT", 0, static_cast<float>(right.integerValue)};
            right.name = newRightName;
            right.type = "FLOAT";
        }
    }

    if (right.type == "FLOAT" && symbolTable.find(right.name) == symbolTable.end()) {
        string newRightName = "literal_float_" + to_string(resultCounter++);
        symbolTable[newRightName] = {newRightName, "FLOAT", 0, right.floatValue};
        right.name = newRightName;
    }

    if (left.type == "FLOAT" && symbolTable.find(left.name) == symbolTable.end()) {
        string newLeftName = "literal_float_" + to_string(resultCounter++);
        symbolTable[newLeftName] = {newLeftName, "FLOAT", 0, left.floatValue};
        left.name = newLeftName;
    }

    string result = "result" + to_string(resultCounter++);
    string threes = result + " = " + left.name + " " + op + " " + right.name + "\n";
    threesFile << threes;

    Symbol resultSymbol;
    resultSymbol.name = result;
    resultSymbol.type = resultType;
    resultSymbol.integerValue = 0;
    resultSymbol.floatValue = 0.0f;
    resultSymbol.stringValue = "";

    basicStack.push(resultSymbol);
    symbolTable[result] = resultSymbol;
}

void code_write_assignment(const string& varName) {
    Symbol value = basicStack.top(); basicStack.pop();
    
    threesFile << varName + " = " + value.name + "\n";
}

void process_declaration(const string& varName) {
    Symbol value = basicStack.top(); basicStack.pop();
    Symbol typeInfo = basicStack.top(); basicStack.pop();

    threesFile << "DECL " << value.type << " " << varName << " = " << value.name << "\n";

    value.name = varName;

    symbolTable[varName] = value;
}


string generate_label(const string& base) {
    return base + "_" + to_string(labelCounter++);
}

void write_if_condition() {
    Symbol condition = basicStack.top(); basicStack.pop();

    string label_false = generate_label("LBL_FALSE");

    threesFile << "IF_FALSE " << condition.name << " GOTO " << label_false << "\n";

    labelStack.push(label_false);
}

void write_else_start() {
    string label_end = generate_label("LBL_END");
    threesFile << "GOTO " << label_end << "\n";

    string label_false = labelStack.top(); labelStack.pop();
    threesFile << label_false << ":\n";

    labelStack.push(label_end);
}

void write_if_end() {
    string label = labelStack.top(); labelStack.pop();

    threesFile << label << ":\n";
}

void process_and_print_nonvariables() {
    Symbol literalValue = basicStack.top(); basicStack.pop();

    string baseName = literalValue.name;
    size_t pos = baseName.find('[');
    if (pos != string::npos) {
        baseName = baseName.substr(0, pos);
    }

    if (symbolTable.find(baseName) == symbolTable.end()) {
        if (literalValue.type == "INT") {
            threesFile << "PRINT " << literalValue.integerValue << "\n";
            return;
        }

        string newName = "literal_" + to_string(resultCounter++);

        if (literalValue.type == "STRING") {
            symbolTable[newName] = {newName, "STRING", 0, 0.0f, literalValue.stringValue};
        } else if (literalValue.type == "CHAR") {
            symbolTable[newName] = {newName, "CHAR", 0, 0.0f, literalValue.stringValue};
        } else if (literalValue.type == "FLOAT") {
            symbolTable[newName] = {newName, "FLOAT", 0, literalValue.floatValue};
        } else if (literalValue.type == "BOOL") {
            symbolTable[newName] = {newName, "BOOL", literalValue.integerValue, 0.0f};
        }

        literalValue.name = newName;
    }

    threesFile << "PRINT " << literalValue.name << "\n";
}

void write_if_true_condition() {
    Symbol condition = basicStack.top(); basicStack.pop();

    string label_true = generate_label("LBL_TRUE");

    threesFile << "IF_TRUE " << condition.name << " GOTO " << label_true << "\n";

    labelStack.push(label_true);
}

void write_for_label() {
    string label_loop = generate_label("LBL_FOR_START");
    string label_end = generate_label("LBL_FOR_END");

    threesFile << label_loop << ":\n";

    labelStack.push(label_end);
    labelStack.push(label_loop);
}

void write_for_condition() {
    Symbol condition = basicStack.top(); basicStack.pop();

    string label_loop = labelStack.top(); labelStack.pop();
    string label_end = labelStack.top(); labelStack.pop();

    labelStack.push(label_end);
    labelStack.push(label_loop);

    threesFile << "IF_FALSE " << condition.name << " GOTO " << label_end << "\n";
}

void write_for_end() {
    Symbol assignment = basicStack.top(); basicStack.pop();

    string label_loop = labelStack.top(); labelStack.pop();
    string label_end = labelStack.top(); labelStack.pop();

    code_write_assignment(assignment.name);

    threesFile << "GOTO " << label_loop << "\n";
    threesFile << label_end << ":\n";
}

void process_declaration_and_assignment(const string& varName) {
    Symbol value = basicStack.top(); basicStack.pop();
    Symbol typeInfo = basicStack.top(); basicStack.pop();

    threesFile << "DECL " << typeInfo.type << " " << varName << " = " << value.name << "\n";
    threesFile << varName + " = " + value.name + "\n";

    value.name = varName;
    symbolTable[varName] = value;
}

void process_array_declaration(const string& type, const string& varName, vector<int>* dims) {
    Symbol symbol;
    symbol.name = varName;
    symbol.dims = *dims;

    if (type == "INT") {
        symbol.type = "ARRAY_INT";
    } else if (type == "FLOAT") {
        symbol.type = "ARRAY_FLOAT";
    }

    int currentSize = 4;

    for (int i = (int)dims->size() - 1; i >= 0; i--) {
        symbol.sizes.insert(symbol.sizes.begin(), currentSize);
        currentSize = currentSize * (*dims)[i];
    }

    symbolTable[varName] = symbol;
}

void code_write_array_element_assignment(const string& varName, vector<Symbol>* indices) {
    Symbol value = basicStack.top(); basicStack.pop();

    if (value.type == "FLOAT" && symbolTable.find(value.name) == symbolTable.end()) {
        string newName = "literal_float_" + to_string(resultCounter++);
        Symbol namedLiteral = value;
        namedLiteral.name = newName;
        symbolTable[newName] = namedLiteral;
        value.name = newName;
    }

    threesFile << varName;
    for (int i = 0; i < indices->size(); i++) {
        threesFile << "[" << indices->at(i).name << "]";
    }
    threesFile << " = " << value.name << "\n";

    delete indices;
}

void process_array_value(const string& varName, vector<Symbol>* indices) {
    auto it = symbolTable.find(varName);

    Symbol arraySymbol = it->second;

    string fullName = varName;
    for (const Symbol& idx : *indices) {
        fullName += "[" + idx.name + "]";
    }

    Symbol elementSymbol;
    elementSymbol.name = fullName;
    elementSymbol.type = arraySymbol.type;

    basicStack.push(elementSymbol);

    delete indices;
}

void handle_increment(const string& varName) {
    Symbol oneSymbol = {"1", "INT", 1, 0.0f};

    Symbol varSymbol = symbolTable[varName];
    varSymbol.name = varName;

    basicStack.push(varSymbol);
    basicStack.push(oneSymbol);

    code_write("+");

    Symbol result = basicStack.top(); basicStack.pop();
    symbolTable[varName] = result;

    threesFile << varName << " = " << result.name << endl;

    basicStack.push({varName});
}

void process_dynamic_array_declaration(const string& type, const string& varName, const Symbol& size) {
    string array_type;
    if (type == "PTR_INT") {
        array_type = "ARRAY_INT";
    } else if (type == "PTR_FLOAT") {
        array_type = "ARRAY_FLOAT";
    }
    
    string allocationExpr = "new " + array_type + "[" + size.name + "]";

    threesFile << "DECL " << type << " " << varName << " = " << allocationExpr << "\n";

    Symbol symbol;
    symbol.name = varName;
    symbol.type = type;
    symbolTable[varName] = symbol;

    basicStack.push(symbol);
}
