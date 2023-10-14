/**
 * 给定一个语言，定义它的文法的一种表示
 * 并定义一个解释器，这个解释器使用该表示来解释语言中的句子
 * 解决的问题：
 *     如果一种特定类型的问题发生的频率足够高，那么可能就值得将该问题的各个实例表示成一个简单语言中的句子
 *      这样就可以构建一个解释器，该解释器可以解释这些句子来解决这些问题
*/

#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

class Expression
{
public:
    virtual ~Expression(){}
    virtual double interpreter(unordered_map<string,int> var) = 0;
private:

};

class VarExpression : public Expression
{
public:
    VarExpression(string key) : m_key(key){}

    double interpreter(unordered_map<string,int> var) override{
        return var[m_key];
    }
private:
    string m_key;
};

class SymbolExpression : public Expression
{
public:
    SymbolExpression(Expression* left, Expression* right) : m_left(left), m_right(right){}

    virtual double interpreter(unordered_map<string,int>) = 0;
protected:
    Expression* m_left;
    Expression* m_right;
private:

};

class AddExpression : public SymbolExpression
{
public:
    AddExpression(Expression* left, Expression* right) : SymbolExpression(left,right){}
    double interpreter(unordered_map<string,int> var) override {
        return m_left->interpreter(var) + m_right->interpreter(var);
    }
private:

};

class SubExpression : public SymbolExpression
{
public:
    SubExpression(Expression* left, Expression* right) : SymbolExpression(left,right){}
    double interpreter(unordered_map<string,int> var) override {
        return m_left->interpreter(var) + m_right->interpreter(var);
    }
private:

};

class Calculator
{
public:
    Calculator(vector<string> expStr){
        stack<Expression*> stack;
        Expression* left;
        Expression* right;

        for (int i = 0; i < expStr.size(); ++i) {
            if(expStr[i] == "+"){
                left = stack.top();
                stack.pop();
                right = new VarExpression(expStr[i++]);
                stack.push(new AddExpression(left,right));
            }
            else if (expStr[i] == "-"){
                left = stack.top();
                stack.pop();
                right = new VarExpression(expStr[i++]);
                stack.push(new SubExpression(left,right));
            }
            else{
                stack.push(new VarExpression(expStr[i]));
            }
        }
        m_expression = stack.top();
    }

    double run(unordered_map<string,int> var){
        return m_expression->interpreter(var);
    }
private:
    Expression* m_expression;
};

string vector_to_string(vector<string>& expStr) {
    string str;
    for (const auto& expstr : expStr) {
        str.append(expstr);
        str.append(" ");
    }
    str.pop_back();
    return str;
}

int main(int argc, const char** argv) {
    vector<string> exptr{"a1","+","a2","+","a3","-","a5"};
    unordered_map<string,int> var{{"a1",10},{"a2",5},{"a3",7},{"a5",20}};

    for(auto exp : exptr) {

    }

    Calculator calcu(exptr);

    cout << "Result: " << vector_to_string(exptr) << " = " << calcu.run(var) << endl;
    
    return 0;
}