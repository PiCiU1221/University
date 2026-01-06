#include "utils.h"
#include "generation_utils.h"

#include <sstream>

using namespace std;

void generatePrintCode(const string& line, ofstream& out, const map<string, Symbol>& symbolTable) {
    stringstream ss(line);
    string printKeyword, value;
    ss >> printKeyword >> value;

    if (isdigit(value[0]) || (value[0] == '-' && isdigit(value[1]))) {
        out << "    li $a0, " << value << "\n";
        out << "    li $v0, 1\n";
        out << "    syscall\n";
    } else {
        auto it = symbolTable.find(value);
        if (it != symbolTable.end()) {
            const Symbol& symbol = it->second;
            const string& type = symbol.type;

            if (type == "INT" || type == "BOOL") {
                out << "    lw $a0, " << value << "\n";
                out << "    li $v0, 1\n";
                out << "    syscall\n";
            } else if (type == "CHAR") {
                out << "    lb $a0, " << value << "\n";
                out << "    li $v0, 11\n";
                out << "    syscall\n";
            } else if (type == "FLOAT") {
                out << "    lwc1 $f12, " << value << "\n";
                out << "    li $v0, 2\n";
                out << "    syscall\n";
            } else if (type == "STRING") {
                out << "    la $a0, " << value << "\n";
                out << "    li $v0, 4\n";
                out << "    syscall\n";
            }
        }
    } 

    // newline
    out << "    li $a0, '\\n'\n";
    out << "    li $v0, 11\n";
    out << "    syscall\n\n";
}

void generateInputCode(const string& line, ofstream& out, const map<string, Symbol>& symbolTable) {
    stringstream ss(line);
    string inputKeyword, varName;
    ss >> inputKeyword >> varName;

    auto it = symbolTable.find(varName);
    if (it == symbolTable.end()) return;

    const Symbol& symbol = it->second;
    const string& type = symbol.type;

    if (type == "INT" || type == "BOOL") {
        out << "    li $v0, 5\n";
        out << "    syscall\n";
        out << "    sw $v0, " << varName << "\n";
    } else if (type == "STRING") {
        out << "    li $v0, 8\n";
        out << "    la $a0, " << varName << "\n";
        out << "    li $a1, 100\n";
        out << "    syscall\n";
    } else if (type == "CHAR") {
        out << "    li $v0, 12\n";
        out << "    syscall\n";
        out << "    sb $v0, " << varName << "\n";
    } else if (type == "FLOAT") {
        out << "    li $v0, 6\n";
        out << "    syscall\n";
        out << "    swc1 $f0, " << varName << "\n";
    }

    // newline
    out << "    li $a0, '\\n'\n";
    out << "    li $v0, 11\n";
    out << "    syscall\n\n";
}

void generateExpressionCode(const string& line, ofstream& out, const map<string, Symbol>& symbolTable) {
    stringstream ss(line);
    string resultVar, eq, operand1, op, operand2;
    ss >> resultVar >> eq >> operand1 >> op >> operand2;

    string baseResult = stripArrayAccess(resultVar);
    string type = symbolTable.at(baseResult).type;
    bool isFloat = (type == "FLOAT" || type == "ARRAY_FLOAT");

    auto loadOperand = [&](const string& operand, const string& regInt, const string& regFloat) {
        if (isArrayAccess(operand)) {
            string base = stripArrayAccess(operand);
            vector<string> indices = extractIndexStrings(operand);

            out << "    la $t4, " << base << "\n";
        
            const Symbol& sym = symbolTable.at(base);
            vector<int> strides = sym.sizes.empty() ? vector<int>(indices.size(), 4) : sym.sizes;

            emitOffsetComputation(out, indices, strides, symbolTable);

            out << "    add $t4, $t4, $t5\n";

            if (sym.type == "ARRAY_FLOAT") {
                out << "    lwc1 " << regFloat << ", ($t4)\n";
            } else {
                out << "    lw " << regInt << ", ($t4)\n";
            }

            out << "\n";
        } else if (isVariable(operand, symbolTable)) {
            string t = symbolTable.at(operand).type;

            if (t == "FLOAT") {
                out << "    l.s " << regFloat << ", " << operand << "\n";
            } else {
                out << "    lw " << regInt << ", " << operand << "\n";
            }

            out << "\n";
        } else {
            if (isFloat) {
                out << "    l.s " << regFloat << ", " << operand << "\n";
            } else {
                out << "    li " << regInt << ", " << operand << "\n";
            }

            out << "\n";
        }
    };

    if (isFloat) {
        loadOperand(operand1, "$t6", "$f0");
        loadOperand(operand2, "$t7", "$f1");

        if (op == "+")       out << "    add.s $f2, $f0, $f1\n";
        else if (op == "-")  out << "    sub.s $f2, $f0, $f1\n";
        else if (op == "*")  out << "    mul.s $f2, $f0, $f1\n";
        else if (op == "/")  out << "    div.s $f2, $f0, $f1\n";

        out << "\n";

        if (isArrayAccess(resultVar)) {
            vector<string> indices = extractIndexStrings(resultVar);

            out << "    la $t4, " << baseResult << "\n";

            const Symbol& sym = symbolTable.at(baseResult);
            emitOffsetComputation(out, indices, sym.sizes, symbolTable);

            out << "    add $t4, $t4, $t5\n";
            out << "    swc1 $f2, ($t4)\n";
        } else {
            out << "    s.s $f2, " << resultVar << "\n";
        }

    } else {
        loadOperand(operand1, "$t6", "$f0");
        loadOperand(operand2, "$t7", "$f1");

        if (op == "+")       out << "    add $t2, $t6, $t7\n";
        else if (op == "-")  out << "    sub $t2, $t6, $t7\n";
        else if (op == "*")  out << "    mul $t2, $t6, $t7\n";
        else if (op == "/") {
            out << "    div $t6, $t7\n";
            out << "    mflo $t2\n";
        } else if (op == "==")  out << "    seq $t2, $t6, $t7\n";
        else if (op == "!=")   out << "    sne $t2, $t6, $t7\n";
        else if (op == "<")    out << "    slt $t2, $t6, $t7\n";
        else if (op == "<=")   out << "    sle $t2, $t6, $t7\n";
        else if (op == ">")    out << "    sgt $t2, $t6, $t7\n";
        else if (op == ">=")   out << "    sge $t2, $t6, $t7\n";
        else if (op == "&&")   out << "    and $t2, $t6, $t7\n";
        else if (op == "||")   out << "    or $t2, $t6, $t7\n";

        out << "\n";

        if (isArrayAccess(resultVar)) {
            vector<string> indices = extractIndexStrings(resultVar);

            out << "    la $t4, " << baseResult << "\n";

            const Symbol& sym = symbolTable.at(baseResult);
            vector<int> strides = sym.sizes.empty() ? vector<int>(indices.size(), 4) : sym.sizes;

            emitOffsetComputation(out, indices, strides, symbolTable);

            out << "    add $t4, $t4, $t5\n";
            out << "    sw $t2, ($t4)\n";
        } else {
            out << "    sw $t2, " << resultVar << "\n";
        }
    }

    out << "\n";
}

void generateArrayAssignmentCode(const string& line, ofstream& out, const map<string, Symbol>& symbolTable) {
    stringstream ss(line);
    string varFull, eq, valueFull;
    ss >> varFull >> eq >> valueFull;

    string varBase = stripArrayAccess(varFull);
    string valueBase = stripArrayAccess(valueFull);

    const Symbol& varSymbol = symbolTable.at(varBase);
    string varType = varSymbol.type;

    string valueType;
    if (isVariable(valueBase, symbolTable)) {
        valueType = symbolTable.at(valueBase).type;
    } else {
        if (valueFull.find('.') != string::npos) {
            valueType = "FLOAT";
        } else {
            valueType = "INT";
        }
    }

    if (varType == "PTR_INT") varType = "ARRAY_INT";
    if (valueType == "PTR_INT") valueType = "ARRAY_INT";

    auto getStrides = [](const Symbol& symbol, const vector<string>& indices) -> vector<int> {
        if (!symbol.sizes.empty()) {
            return symbol.sizes;
        } else {
            return vector<int>(indices.size(), 4);
        }
    };

    if (varType == "ARRAY_INT" && valueType == "INT") {
        out << "    la $t4, " << varBase << "\n";

        vector<string> indexStrings = extractIndexStrings(varFull);
        vector<int> strides = getStrides(varSymbol, indexStrings);
        emitOffsetComputation(out, indexStrings, strides, symbolTable);

        out << "    add $t4, $t4, $t5\n";
        out << "    li $t0, " << valueFull << "\n";
        out << "    sw $t0, ($t4)\n\n";
    } else if (varType == "ARRAY_FLOAT" && valueType == "FLOAT") {
        out << "    la $t4, " << varBase << "\n";

        vector<string> indexStrings = extractIndexStrings(varFull);
        emitOffsetComputation(out, indexStrings, varSymbol.sizes, symbolTable);

        out << "    add $t4, $t4, $t5\n";
        out << "    l.s $f0, " << valueFull << "\n";
        out << "    swc1 $f0, ($t4)\n\n";
    } else if (varType == "INT" && valueType == "ARRAY_INT") {
        out << "    la $t4, " << valueBase << "\n";

        vector<string> indexStrings = extractIndexStrings(valueFull);
        const Symbol& valueSymbol = symbolTable.at(valueBase);
        vector<int> strides = getStrides(valueSymbol, indexStrings);

        emitOffsetComputation(out, indexStrings, strides, symbolTable);

        out << "    add $t4, $t4, $t5\n";
        out << "    lw $t0, ($t4)\n";
        out << "    sw $t0, " << varBase << "\n\n";
    } else if (varType == "FLOAT" && valueType == "ARRAY_FLOAT") {
        out << "    la $t4, " << valueBase << "\n";

        vector<string> indexStrings = extractIndexStrings(valueFull);
        const Symbol& valueSymbol = symbolTable.at(valueBase);
        emitOffsetComputation(out, indexStrings, valueSymbol.sizes, symbolTable);

        out << "    add $t4, $t4, $t5\n";
        out << "    lwc1 $f0, ($t4)\n";
        out << "    swc1 $f0, " << varBase << "\n\n";
    } else if (varType == "ARRAY_INT" && valueType == "ARRAY_INT") {
        out << "    la $t6, " << valueBase << "\n";
        {
            vector<string> indexStrings = extractIndexStrings(valueFull);
            const Symbol& valueSymbol = symbolTable.at(valueBase);
            vector<int> strides = getStrides(valueSymbol, indexStrings);

            emitOffsetComputation(out, indexStrings, strides, symbolTable);
            out << "    add $t6, $t6, $t5\n";
        }

        out << "    la $t4, " << varBase << "\n";
        {
            vector<string> indexStrings = extractIndexStrings(varFull);
            const Symbol& varSymbolLocal = symbolTable.at(varBase);
            vector<int> strides = getStrides(varSymbolLocal, indexStrings);

            emitOffsetComputation(out, indexStrings, strides, symbolTable);
            out << "    add $t4, $t4, $t5\n";
        }

        out << "    lw $t0, ($t6)\n";
        out << "    sw $t0, ($t4)\n\n";

    } else if (varType == "ARRAY_FLOAT" && valueType == "ARRAY_FLOAT") {
        out << "    la $t6, " << valueBase << "\n";
        {
            vector<string> indexStrings = extractIndexStrings(valueFull);
            const Symbol& valueSymbol = symbolTable.at(valueBase);
            emitOffsetComputation(out, indexStrings, valueSymbol.sizes, symbolTable);
            
            out << "    add $t6, $t6, $t5\n";
        }

        out << "    la $t4, " << varBase << "\n";
        {
            vector<string> indexStrings = extractIndexStrings(varFull);
            const Symbol& varSymbolLocal = symbolTable.at(varBase);
            emitOffsetComputation(out, indexStrings, varSymbolLocal.sizes, symbolTable);
            
            out << "    add $t4, $t4, $t5\n";
        }

        out << "    lwc1 $f0, ($t6)\n";
        out << "    swc1 $f0, ($t4)\n\n";
    }
}

void generateAssignmentCode(const string& line, ofstream& out, const map<string, Symbol>& symbolTable) {
    stringstream ss(line);
    string var, eq, value;
    ss >> var >> eq >> value;

    if (isArrayAccess(var) || isArrayAccess(value)) {
        generateArrayAssignmentCode(line, out, symbolTable);
        return;
    }

    string varType = symbolTable.at(var).type;
    string valueType;

    if (isVariable(value, symbolTable)) {
        valueType = symbolTable.at(value).type;
    } else {
        if (value.find('.') != string::npos) {
            valueType = "FLOAT";
        } else {
            valueType = "INT";
        }
    }

    if (varType == "FLOAT" && valueType == "INT") {
        if (isVariable(value, symbolTable)) {
            out << "    lw $t0, " << value << "\n";
        } else {
            out << "    li $t0, " << value << "\n";
        }
        out << "    mtc1 $t0, $f0\n";
        out << "    cvt.s.w $f1, $f0\n";
        out << "    s.s $f1, " << var << "\n";
    }
    else if (varType == "INT" && valueType == "FLOAT") {
        if (isVariable(value, symbolTable)) {
            out << "    l.s $f0, " << value << "\n";
        } else {
            out << "    li.s $f0, " << value << "\n";
        }
        out << "    cvt.w.s $f1, $f0\n";
        out << "    mfc1 $t0, $f1\n";
        out << "    sw $t0, " << var << "\n";
    }
    else if (varType == "FLOAT") {
        if (isVariable(value, symbolTable)) {
            out << "    l.s $f0, " << value << "\n";
        } else {
            out << "    li.s $f0, " << value << "\n";
        }
        out << "    s.s $f0, " << var << "\n";
    }
    else {
        if (isVariable(value, symbolTable)) {
            out << "    lw $t0, " << value << "\n";
        } else {
            out << "    li $t0, " << value << "\n";
        }
        out << "    sw $t0, " << var << "\n";
    }
}

void generateDeclarationCode(const string& line, ofstream& out, const map<string, Symbol>& symbolTable) {
    stringstream ss(line);
    string keyword, type, varName, eq, expr;

    ss >> keyword >> type >> varName >> eq;

    getline(ss, expr);
    expr.erase(0, expr.find_first_not_of(" \t"));

    if (type == "PTR_INT") {
        size_t leftBracket = expr.find('[');
        size_t rightBracket = expr.find(']');
        string sizeStr = (leftBracket != string::npos && rightBracket != string::npos && rightBracket > leftBracket)
                         ? expr.substr(leftBracket + 1, rightBracket - leftBracket - 1)
                         : "";

        out << "    li $v0, 9\n";

        if (!sizeStr.empty()) {
            try {
                int sizeNum = stoi(sizeStr);
                out << "    li $a0, " << sizeNum << "\n";
            } catch (const std::invalid_argument&) {
                out << "    lw $a0, " << sizeStr << "\n";
            }
        } else {
            out << "    li $a0, 0\n";
        }

        out << "    syscall\n";
        out << "    sw $v0, " << varName << "\n\n";

    } else {
        if (isVariable(expr, symbolTable)) {
            out << "    lw $t0, " << expr << "\n";
            out << "    sw $t0, " << varName << "\n\n";
        }
    }
}

void generateIfTrue(const string& line, ofstream& out) {
    stringstream ss(line);
    string ifTrue, var, gotoStr, label;
    ss >> ifTrue >> var >> gotoStr >> label;

    out << "    lw $t2, " << var << "\n";
    out << "    bnez $t2, " << label << "\n";
}

void generateIfFalse(const string& line, ofstream& out) {
    stringstream ss(line);
    string ifFalse, var, gotoStr, label;
    ss >> ifFalse >> var >> gotoStr >> label;

    out << "    lw $t2, " << var << "\n";
    out << "    beqz $t2, " << label << "\n";
}

void generateGoto(const string& line, ofstream& out) {
    stringstream ss(line);
    string gotoStr, label;
    ss >> gotoStr >> label;

    out << "    j " << label << "\n";
}

void generateLabel(const string& line, ofstream& out) {
    out << line << "\n";
}
