#include <iostream>
#include <string>
#include <stack>
#include <cctype>

enum OpType : char {
    NONE = 0,
    PLUS = '+',
    MINUS = '-',
    MULTIPLY = '*',
    DIVIDE = '/',
    LPAREN = '(',
    RPAREN = ')'
};

OpType charToOp(const char c) {
    switch (c) {
        case '+': return PLUS;
        case '-': return MINUS;
        case '*': return MULTIPLY;
        case '/': return DIVIDE;
        case '(': return LPAREN;
        case ')': return RPAREN;
        default:  return NONE;
    }
}
std::string opToString(const OpType op)
{
    switch (op)
    {
        case PLUS: return "+";
        case MINUS: return "-";
        case MULTIPLY: return "*";
        case DIVIDE: return "/";
        case LPAREN: return "(";
        case RPAREN: return ")";
        default:  return "";
    }
}
int getPriority(const OpType op) {
    switch (op) {
        case PLUS:
        case MINUS:
            return 1;
        case MULTIPLY:
        case DIVIDE:
            return 2;
        default:
            return 0;
    }
}

std::string infixToPostfix(const std::string& infix) {
    std::stack<OpType> opStack;
    std::string postfix;

    size_t i = 0;
    while (i < infix.length()) {
        const char ch = infix[i];

        if (std::isdigit(ch)) {
            while (i < infix.length() && std::isdigit(infix[i])) {
                postfix += infix[i];
                i++;
            }
            postfix += ' ';
            continue;
        }

        OpType currentOp = charToOp(ch);
        if (currentOp == NONE) {
            i++;
            continue;
        }

        if (currentOp == LPAREN) {
            opStack.push(currentOp);
        }
        else if (currentOp == RPAREN) {
            while (!opStack.empty() && opStack.top() != LPAREN) {
                postfix += opToString(opStack.top());
                postfix += ' ';
                opStack.pop();
            }
            if (!opStack.empty()) opStack.pop();
        }
        else {
            while (!opStack.empty() && opStack.top() != LPAREN &&
                   getPriority(opStack.top()) >= getPriority(currentOp)) {
                postfix += opToString(opStack.top());
                postfix += ' ';
                opStack.pop();
            }
            opStack.push(currentOp);
        }
        i++;
    }

    while (!opStack.empty()) {
        postfix += opToString(opStack.top());
        postfix += ' ';
        opStack.pop();
    }
    return postfix;
}
