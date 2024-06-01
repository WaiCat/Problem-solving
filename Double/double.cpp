#include <iostream>
#include <fstream>
#include <string>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::multiprecision;

cpp_dec_float_100 calculate(string expr) {
    vector<string> tokens;
    boost::split(tokens, expr, boost::is_any_of(" "));
    
    cpp_dec_float_100 operand1 = cpp_dec_float_100(tokens[0]);
    string op = tokens[1];
    cpp_dec_float_100 operand2 = cpp_dec_float_100(tokens[2]);

    if (op == "+")
        return operand1 + operand2;
    else if (op == "-")
        return operand1 - operand2;
    else if (op == "*")
        return operand1 * operand2;
    else if (op == "/")
        return operand1 / operand2;
    else
        throw invalid_argument("Invalid operator");
}

int main() {
    ifstream infile("double.inp");
    ofstream outfile("double.out");

    if (!infile.is_open()) {
        cerr << "Unable to open input file." << endl;
        return 1;
    }

    if (!outfile.is_open()) {
        cerr << "Unable to open output file." << endl;
        return 1;
    }

    int n;
    infile >> n;
    infile.ignore(); // ignore newline

    for (int i = 0; i < n; ++i) {
        string expr;
        getline(infile, expr);
        cpp_dec_float_100 result = calculate(expr);
        outfile << result.convert_to<int>() << endl;
    }

    infile.close();
    outfile.close();

    return 0;
}
