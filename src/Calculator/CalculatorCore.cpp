#include "pch.h"
#include "CalculatorCore.h"
#include <stack>
#include <sstream>
#include <string>
#include <unordered_map>
#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace std;
using namespace boost::multiprecision;

auto op_dict = unordered_map<char, int>{
    {'\n', 0},
    {')',  0},
    {'&',  1},
    {'|',  1},
    {'+',  2},
    {'-',  2},
    {'*',  3},
    {'/',  3},
    {'!',  4},
    {'(',  5}
};

auto __calculator(stringstream& in, bool isInitial) -> cpp_dec_float_100 {
    auto ops = stack<char>();
    auto nums = stack<cpp_dec_float_100>();
    auto calculate = [&] {
        if (nums.empty())
            throw runtime_error("Invalid expression");
        auto op = ops.top();
        ops.pop();
        auto res = (cpp_dec_float_100)0;
        if (op == '!') {
            auto x = nums.top();
            nums.pop();
            res = !x;
            nums.push(res);
            return;
        }
        if (nums.size() < 2)
            throw runtime_error("Invalid expression");
        auto y = nums.top();
        nums.pop();
        auto x = nums.top();
        nums.pop();
        if (op == '+')
            res = x + y;
        else if (op == '-')
            res = x - y;
        else if (op == '*')
            res = x * y;
        else if (op == '&')
            res = x && y;
        else if (op == '|')
            res = x || y;
        else {
            if (y == 0)
                throw runtime_error("Math error");
            res = x / y;
        }
        nums.push(res);
    };
    while (!in.eof()) {
        if (isdigit(in.peek())) {
            auto temp = string();
            while (isdigit(in.peek()))
                temp += (char)in.get();
            nums.push(cpp_dec_float_100(temp));
            continue;
        }
        auto temp = (char)in.get();
        auto priority = op_dict[temp];
        if (priority == 2) {
            while (op_dict[in.peek()] == 2)
                temp = temp == in.get() ? '+' : '-';
            if (nums.empty())
                nums.push(0);
        }
        else if (priority == 3) {
            auto ch = '+';
            while (op_dict[in.peek()] == 2)
                ch = ch == in.get() ? '+' : '-';
            if (!nums.empty() && ch == '-') {
                auto temp_num = nums.top();
                nums.pop();
                nums.push(-temp_num);
            }
        }
        if (temp == '(') {
            nums.push(__calculator(in, false));
            continue;
        }
        while (!ops.empty() && priority <= op_dict[ops.top()])
            calculate();
        if (temp == ')') {
            if (isInitial)
                throw runtime_error("Invalid expression");
            break;
        }
        if (temp == '\n')
            break;
        ops.push(temp);
    }
    if (!ops.empty() || nums.size() != 1)
        throw runtime_error("Invalid expression");
    return nums.top();
}

auto calculator(stringstream& in) -> cpp_dec_float_100 {
    return __calculator(in, true);
}
