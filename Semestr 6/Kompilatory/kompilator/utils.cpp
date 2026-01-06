#include "utils.h"

#include <sstream>
#include <cctype>

using namespace std;

bool isVariable(const string& operand, const map<string, Symbol>& symbolTable) {
    return symbolTable.find(operand) != symbolTable.end();
}

bool isLabel(const string& line) {
    string trimmed = line;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    return !trimmed.empty() && trimmed.back() == ':';
}

bool isGoto(const string& line) {
    string trimmed = line;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    return trimmed.substr(0, 4) == "GOTO";
}

bool isIfFalse(const string& line) {
    string trimmed = line;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    return trimmed.substr(0, 8) == "IF_FALSE";
}

bool isIfTrue(const string& line) {
    string trimmed = line;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));
    return trimmed.substr(0, 7) == "IF_TRUE";
}

string getLineType(const string& line) {
    string trimmed = line;
    trimmed.erase(0, trimmed.find_first_not_of(" \t"));

    if (isLabel(trimmed)) return "label";
    if (isGoto(trimmed)) return "goto";
    if (isIfTrue(trimmed)) return "if_true";
    if (isIfFalse(trimmed)) return "if_false";
    if (trimmed.substr(0, 4) == "DECL") return "declaration";
    if (trimmed.substr(0, 5) == "PRINT") return "print";
    if (trimmed.substr(0, 5) == "INPUT") return "input";

    size_t equalsPos = trimmed.find('=');
    if (equalsPos == string::npos) return "invalid";

    string rightSide = trimmed.substr(equalsPos + 1);
    rightSide.erase(0, rightSide.find_first_not_of(" \t"));
    rightSide.erase(rightSide.find_last_not_of(" \t") + 1);

    if (!rightSide.empty() && rightSide.front() == '"' && rightSide.back() == '"')
        return "assignment";

    stringstream ss(rightSide);
    string token;
    int tokenCount = 0;
    while (ss >> token) tokenCount++;

    return tokenCount > 1 ? "expression" : (tokenCount == 1 ? "assignment" : "invalid");
}

string toFloatLiteral(const string& val) {
    return (val.find('.') == string::npos && isdigit(val[0])) ? val + ".0" : val;
}

string stripArrayAccess(const string& s) {
    size_t lb = s.find('[');
    return (lb != string::npos) ? s.substr(0, lb) : s;
}

vector<string> extractIndexStrings(const string& arrayAccess) {
    vector<string> indices;
    size_t start = arrayAccess.find('[');
    while (start != string::npos) {
        size_t end = arrayAccess.find(']', start);
        indices.push_back(arrayAccess.substr(start + 1, end - start - 1));
        start = arrayAccess.find('[', end);
    }
    return indices;
}

bool isArrayAccess(const string& s) {
    return s.find('[') != string::npos;
}

void emitOffsetComputation(ofstream& out,
                           const vector<string>& indexStrings,
                           const vector<int>& strides,
                           const map<string, Symbol>& symbolTable) {
    out << "    li $t5, 0\n";

    for (size_t i = 0; i < indexStrings.size(); ++i) {
        const string& idx = indexStrings[i];

        if (!isVariable(idx, symbolTable)) {
            out << "    li $t0, " << idx << "\n";
        } else {
            out << "    lw $t0, " << idx << "\n";
        }

        out << "    li $t1, " << strides[i] << "\n";
        out << "    mul $t0, $t0, $t1\n";
        out << "    add $t5, $t5, $t0\n";
    }
}
