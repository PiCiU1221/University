#include "utils.h"
#include "generation_utils.h"
#include "asmgen.h"

using namespace std;

void processLine(const string& line, ifstream& in, ofstream& out, const map<string, Symbol>& symbolTable) {
    string lineType = getLineType(line);

    if (lineType == "print") {
        generatePrintCode(line, out, symbolTable);
    } else if (lineType == "input") {
        generateInputCode(line, out, symbolTable);
    } else if (lineType == "expression") {
        generateExpressionCode(line, out, symbolTable);
    } else if (lineType == "assignment") {
        generateAssignmentCode(line, out, symbolTable);
    } else if (lineType == "declaration") {
        generateDeclarationCode(line, out, symbolTable);
    } else if (lineType == "if_true") {
        generateIfTrue(line, out);
    } else if (lineType == "if_false") {
        generateIfFalse(line, out);
    } else if (lineType == "goto") {
        generateGoto(line, out);
    } else if (lineType == "label") {
        generateLabel(line, out);
    }
}

void generateMIPS(const string& inputFile, const string& outputFile, const map<string, Symbol>& symbolTable) {
    ifstream in(inputFile);
    ofstream out(outputFile);

    out << ".data\n\n";

    for (auto it = symbolTable.begin(); it != symbolTable.end(); ++it) {
        const string& name = it->first;
        const Symbol& symbol = it->second;
        const string& type = symbol.type;

        out << "    ";
    
        if (type == "INT" || type == "BOOL") {
            out << name << ": .word " << symbol.integerValue << "\n";
        } else if (type == "FLOAT") {
            out << name << ": .float " << symbol.floatValue << "\n";
        } else if (type == "CHAR") {
            out << name << ": .byte '" << symbol.stringValue << "'\n";
        } else if (type == "STRING") {
            out << name << ": .asciiz " << symbol.stringValue << "\n";
        } else if (type == "ARRAY_INT" || type == "ARRAY_FLOAT") {
            int totalElements = 1;
            for (int dim : symbol.dims) {
                totalElements *= dim;
            }

            if (type == "ARRAY_INT") {
                out << name << ": .word 0:" << totalElements << "\n";
            } else if (type == "ARRAY_FLOAT") {
                out << name << ": .float 0.0:" << totalElements << "\n";
            }
        } else if (type == "PTR_INT") {
            out << name << ": .word 0\n";
        }
    }

    out << "\n.text\n\n";

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;

        processLine(line, in, out, symbolTable);
    }

    out << "    li $v0, 10\n    syscall\n";
}
