#include "evaluator.h"
#include <iostream>
#include <sstream>
#include <stdexcept>    // excecoes padrao
#include <algorithm>
#include <stack>
#include <cmath>

#include <iostream>

using namespace std;

/// Todos os nomes validos de funcoes, associados aos respectivos identificadores
map<string,Evaluator::TokenFunction> Evaluator::functions =
    {
        {"sin", TokenFunction::FUNCTION_SIN},
        {"cos", TokenFunction::FUNCTION_COS},
        {"tan", TokenFunction::FUNCTION_TAN},
        {"exp", TokenFunction::FUNCTION_EXP},
        {"log", TokenFunction::FUNCTION_LOG},
        {"sqrt", TokenFunction::FUNCTION_SQRT}
};

/// Todos os operadores validos, associados aos respectivos identificadores
map<char,Evaluator::TokenOperator> Evaluator::operators =
    {
        {'+', TokenOperator::OPERATOR_ADDITION},
        {'-', TokenOperator::OPERATOR_SUBTRACTION},
        {'*', TokenOperator::OPERATOR_MULTIPLICATION},
        {'/', TokenOperator::OPERATOR_DIVISION},
        {'^', TokenOperator::OPERATOR_EXPONENTIATION},
        {'~', TokenOperator::OPERATOR_NEGATIVE}
};

/// Precedencia de um operador
int Evaluator::Token::precedence() const
{
    if (type != TypeOfToken::TOKEN_OPERATOR)
    {
        // Nunca deve entrar aqui...
        throw invalid_argument("precedence is only defined for operator tokens");
    }
    switch(op)
    {
    case TokenOperator::OPERATOR_EXPONENTIATION:
        return 4;
    case TokenOperator::OPERATOR_MULTIPLICATION:
    case TokenOperator::OPERATOR_DIVISION:
        return 3;
    case TokenOperator::OPERATOR_ADDITION:
    case TokenOperator::OPERATOR_SUBTRACTION:
    case TokenOperator::OPERATOR_NEGATIVE:
        return 2;
    default:
        // Nunca deve entrar aqui...
        throw invalid_argument("unknown operator to calculate precedence");
    }
}

/// Liberar
void Evaluator::clear()
{
    txt.clear();
    expr.clear();
}

/// Consulta aa expressao a ser evaluada
string Evaluator::getExpression() const
{
    stringstream SS;
    auto itF=functions.begin();
    auto itOP=operators.begin();
    for (auto E : expr)
    {
        switch(E.type)
        {
        case TypeOfToken::TOKEN_NUMBER:
            SS << E.x;
            break;
        case TypeOfToken::TOKEN_VARIABLE:
            SS << 'x';
            break;
        case TypeOfToken::TOKEN_FUNCTION:
            itF = find_if(functions.begin(), functions.end(), [&E](auto X)
                          {
                              return (X.second == E.f);
                          });
            SS << (itF!=functions.end() ? itF->first : "???");
            break;
        case TypeOfToken::TOKEN_OPERATOR:
            itOP = find_if(operators.begin(), operators.end(), [&E](auto X)
                           {
                               return (X.second == E.op);
                           });
            SS << (itOP!=operators.end() ? itOP->first : '?');
            break;
        default:
            SS << "ERROR!";
            break;
        }
        SS << ' ';
    }
    return SS.str();
}

/// Fixa a expressao a ser evaluada.
/// Faz a análise de sintaxe e armazena o novo texto e a expressao codificada
/// nos dados internos "txt" e "expr".
/// Em caso de expressao invalida, gera excecao.
void Evaluator::set(const string& S)
{
    // Copia o parametro para o texto a ser evaluado
    txt=S;
    // Limpa a expressao anterior
    expr.clear();

    // Converte o texto a ser evaluado para minusculas
    transform(txt.begin(), txt.end(), txt.begin(), ::tolower);

    // Remove os espacos do texto a ser evaluado
    txt.erase( remove(txt.begin(), txt.end(), ' '), txt.end() );

    // A pilha de tokens que estao aguardando para serem inseridos
    // na expressao a ser evaluada
    std::stack<Token> stack_token;
    // O texto a ser evaluado deve ser: VALOR OPERADOR VALOR OPERADOR ... VALOR
    // Portanto, em determinados momentos soh eh valido um valor,
    // em outros soh eh valido um operador.
    TypeOfToken valid_next_token = TypeOfToken::TOKEN_VALUE;
    // O token lido
    Token T;
    // O indice do proximo caractere a ser analisado
    int cursor = 0;
    // O proximo caractere
    char C;

    while (cursor < static_cast<int>(txt.size()))
    {
        C = txt[cursor];
        switch(valid_next_token)
        {
        // Eh esperado um valor: um numero, uma variavel, uma funcao ou um abre parentese
        case TypeOfToken::TOKEN_VALUE:
            // Testa se proximo caractere eh o sinal do valor (+ ou -)
            if (C=='+' || C=='-')
            {
                // Se for '+', nao faz nada
                // Se for '-', insere o operador na pilha de esper
                if (C=='-')
                {
                    // Gera o token correspondente ao negativo
                    T.type = TypeOfToken::TOKEN_OPERATOR;
                    T.op = TokenOperator::OPERATOR_NEGATIVE;
                    // Insere o token na pilha de espera
                    stack_token.push(T);
                }
                // Avanca o cursor em qualquer caso (+ ou -)
                ++cursor;
                C = txt[cursor];
            }

            // Testa se proximo caractere eh um abre parentese
            if (C=='(')
            {
                // Nao avanca o cursor
                // Vai entrar novamente, com o mesmo caractere, no estado no qual espera um abre parentese.
                valid_next_token = TypeOfToken::TOKEN_LEFT_PARENTHESES;

                // Encerra o switch case TypeOfToken::TOKEN_VALUE
                break;
            }

            // Testa se proximo caractere eh valido como primeiro caractere de um numero real.
            // Se havia + ou - antes, jah foi processado como soma/subtracao ou como negativo.
            if (isdigit(C)/*De 0 a 9*/ || C=='.')
            {
                double num(0.0); // Valor do numero a ser lido
                size_t len;      // Numero de caracteres lidos

                // Calcula o double correspondente aos caracteres validos a partir de cursor.
                try
                {
                    num = stod(txt.substr(cursor), &len);
                }
                catch(exception &e)
                {
                    string msg_err(txt+": invalid number at position ");
                    msg_err += to_string(cursor);
                    clear();
                    throw invalid_argument(msg_err);
                }

                // Gera o token correspondente ao numero
                T.type = TypeOfToken::TOKEN_NUMBER;
                T.x = num;
                // Insere o token na expressao
                expr.push_back(T);

                // Avanca o cursor na quantidade de digitos do numero
                cursor += len;
                // Muda o tipo do proximo token a ser lido
                valid_next_token = TypeOfToken::TOKEN_OPERATOR;
            }
            // Testa se proximo caractere eh letra, que pode ser a variavel 'x' ou uma funcao
            else if (isalpha(C)/*De a a z*/)
            {
                string S;
                while (cursor < static_cast<int>(txt.size()) &&
                       isalnum(txt[cursor])/*De a a z ou de 0 a 9*/)
                {
                    S.push_back(txt[cursor]);
                    // Avanca o cursor
                    ++cursor;
                }
                // Testa se eh uma variavel
                if (S=="x")
                {
                    // Gera o token correspondente aa variavel
                    T.type = TypeOfToken::TOKEN_VARIABLE;
                    // Insere o token na expressao
                    expr.push_back(T);

                    // Muda o tipo do proximo token a ser lido
                    valid_next_token = TypeOfToken::TOKEN_OPERATOR;
                }
                // Se nao, deve ser uma funcao
                else
                {
                    auto func = functions.find(S);
                    if (func == functions.end())
                    {
                        string msg_err(txt+": invalid name '");
                        msg_err += S+"' before position " + to_string(cursor);
                        clear();
                        throw invalid_argument(msg_err);
                    }
                    // Gera o token correspondente aa funcao
                    T.type = TypeOfToken::TOKEN_FUNCTION;
                    T.f = func->second;
                    // Insere o token na pilha de espera
                    stack_token.push(T);

                    // Muda o tipo do proximo token a ser lido
                    valid_next_token = TypeOfToken::TOKEN_LEFT_PARENTHESES;
                }
            }
            // Deveria ler um valor mas o proximo caractere nao corresponde a nenhuma
            // das possibilidades: um numero ou uma variavel ou uma funcao ou um abre parentese
            else
            {
                string msg_err(txt+": unexpected character '");
                msg_err.push_back(C);
                msg_err += "' at position " + to_string(cursor) + " while expecting a value";
                clear();
                throw invalid_argument(msg_err);
            }

            // Encerra o switch case TypeOfToken::TOKEN_VALUE
            break;
        // Eh esperado ler um abre parentese
        case TypeOfToken::TOKEN_LEFT_PARENTHESES:
            if (C=='(')
            {
                // Gera o token correspondente ao (
                T.type = TypeOfToken::TOKEN_LEFT_PARENTHESES;
                // Insere o token na pilha de espera
                stack_token.push(T);
            }
            else
            {
                string msg_err(txt+": unexpected character '");
                msg_err.push_back(C);
                msg_err += "' at position " + to_string(cursor) + " while expecting a '('";
                clear();
                throw invalid_argument(msg_err);
            }

            // Avanca o cursor
            ++cursor;
            // Muda o tipo do proximo token a ser lido
            valid_next_token = TypeOfToken::TOKEN_VALUE;

            // Encerra o switch case TypeOfToken::TOKEN_PARENTHESIS
            break;
        // Eh esperado ler um operador: + - * / ^ ou fecha parentese
        case TypeOfToken::TOKEN_OPERATOR:
            if (C=='+' || C=='-' || C=='*' || C=='/' || C=='^' || C==')')
            {
                if (C==')')
                {
                    // Insere os operadores anteriores na expressao ateh encontrar um '('
                    bool insert_previous = true;
                    Token O2;
                    while(!stack_token.empty() && insert_previous)
                    {
                        O2 = stack_token.top();
                        if (O2.type == TypeOfToken::TOKEN_OPERATOR)
                        {
                            // Insere o token anterior na expressao
                            expr.push_back(O2);
                            // Exclui o token anterior da pilha de espera
                            stack_token.pop();
                        }
                        else insert_previous=false;
                    }

                    // Erro se nao encontrou '('
                    if (stack_token.empty() || O2.type!=TypeOfToken::TOKEN_LEFT_PARENTHESES)
                    {
                        string msg_err(txt+": unbalaced ')' at position ");
                        msg_err += to_string(cursor);
                        clear();
                        throw invalid_argument(msg_err);
                    }

                    // Extrai o '(' da pilha de espera
                    stack_token.pop();

                    // Verifica se proximo tolen da pilha de espera eh uma funcao.
                    // Se for, extrai e insere na expressao
                    if (!stack_token.empty())
                    {
                        O2 = stack_token.top();
                        if (O2.type == TypeOfToken::TOKEN_FUNCTION)
                        {
                            expr.push_back(O2);
                            stack_token.pop();
                        }
                    }

                    // Muda o tipo do proximo token a ser lido
                    valid_next_token = TypeOfToken::TOKEN_OPERATOR;
                }
                else
                {
                    auto oper = operators.find(C);
                    if (oper == operators.end())
                    {
                        // Nunca deve entrar aqui...
                        string msg_err(txt+": invalid operator '");
                        msg_err.push_back(C);
                        msg_err += "' at position " + to_string(cursor);
                        clear();
                        throw invalid_argument(msg_err);
                    }

                    // Gera o token correspondente ao operador
                    T.type = TypeOfToken::TOKEN_OPERATOR;
                    T.op = oper->second;

                    // Insere os operadores anteriores de maior precedencia na expressao
                    bool insert_previous = true;
                    Token O2;
                    while(!stack_token.empty() && insert_previous)
                    {
                        O2 = stack_token.top();
                        if (O2.type == TypeOfToken::TOKEN_OPERATOR &&
                            (O2.precedence() > T.precedence() ||
                             (O2.precedence() == T.precedence() &&
                              T.op != TokenOperator::OPERATOR_EXPONENTIATION)))
                        {
                            // Insere o token anterior na expressao
                            expr.push_back(O2);
                            // Exclui o token anterior da pilha de espera
                            stack_token.pop();
                        }
                        else insert_previous=false;
                    }

                    // Insere o token na pilha de espera
                    stack_token.push(T);

                    // Muda o tipo do proximo token a ser lido
                    valid_next_token = TypeOfToken::TOKEN_VALUE;
                }
            }
            else
            {
                string msg_err(txt+": unexpected character '");
                msg_err.push_back(C);
                msg_err += "' at position " + to_string(cursor) + " while expecting an operator";
                clear();
                throw invalid_argument(msg_err);
            }

            // Avanca o cursor
            ++cursor;

            // Encerra o switch case TypeOfToken::TOKEN_OPERATOR
            break;
        default:
            // Nunca deve entrar aqui: erro de programacao
            clear();
            throw logic_error("should never enter here...");
        }
    }

    // Expressao acabou sem valor apos um operador
    if (valid_next_token == TypeOfToken::TOKEN_VALUE)
    {
        string msg_err(txt+": value required before end of expression");
        clear();
        throw invalid_argument(msg_err);
    }

    // Expressao acabou sem parentese apos uma funcao
    if (valid_next_token == TypeOfToken::TOKEN_LEFT_PARENTHESES)
    {
        string msg_err(txt+": '(' required before end of expression");
        clear();
        throw invalid_argument(msg_err);
    }

    // Extrai todos os tokens restantes da pilha de espera para a expressao
    while (!stack_token.empty())
    {
        T = stack_token.top();
        if (T.type == TypeOfToken::TOKEN_LEFT_PARENTHESES)
        {
            string msg_err(txt+": unbalanced '(' at the end of expression");
            clear();
            throw invalid_argument(msg_err);
        }
        stack_token.pop();
        expr.push_back(T);
    }
}

/// Evaluacao da expressao para um dado valor da variavel X.
/// Retorna 0.0 se expressao estiver vazia.
/// Gera excecao em caso de erro na expressao.
double Evaluator::operator()(double X) const
{
    if (empty()) return 0.0;

    stack<double> values;
    double v1,v2;

    for (auto T : expr)
    {
        switch(T.type)
        {
        case TypeOfToken::TOKEN_NUMBER:
            values.push(T.x);
            break;
        case TypeOfToken::TOKEN_VARIABLE:
            values.push(X);
            break;
        case TypeOfToken::TOKEN_FUNCTION:
            if (values.size() < 1)
            {
                // Nunca deve entrar aqui...
                throw invalid_argument("no value on stack to calculate function value");
            }
            // Extrai ultimo valor da pilha
            v1 = values.top();
            values.pop();
            switch(T.f)
            {
            case TokenFunction::FUNCTION_SIN:
                values.push(sin(v1));
                break;
            case TokenFunction::FUNCTION_COS:
                values.push(cos(v1));
                break;
            case TokenFunction::FUNCTION_TAN:
                values.push(tan(v1));
                break;
            case TokenFunction::FUNCTION_EXP:
                values.push(exp(v1));
                break;
            case TokenFunction::FUNCTION_LOG:
                values.push(log(v1));
                break;
            case TokenFunction::FUNCTION_SQRT:
                values.push(sqrt(v1));
                break;
            default:
                // Nunca deve entrar aqui...
                throw invalid_argument("unknown function while evaluating expression");
            }
            break;
        case TypeOfToken::TOKEN_OPERATOR:
            // Extrai ultimo valor da pilha (argumento aa direita do operador)
            if (values.size() < 1)
            {
                // Nunca deve entrar aqui...
                throw invalid_argument("no first value on stack to calculate operator value");
            }
            v2 = values.top();
            values.pop();
            if (T.op == TokenOperator::OPERATOR_NEGATIVE)
            {
                // Unico operador que tem um unico argumento
                values.push(-v2);
                break;
            }
            // Extrai ultimo valor da pilha (argumento aa esquerda do operador)
            if (values.size() < 1)
            {
                // Nunca deve entrar aqui...
                throw invalid_argument("no second value on stack to calculate operator value");
            }
            v1 = values.top();
            values.pop();
            switch(T.op)
            {
            case TokenOperator::OPERATOR_ADDITION:
                values.push(v1+v2);
                break;
            case TokenOperator::OPERATOR_SUBTRACTION:
                values.push(v1-v2);
                break;
            case TokenOperator::OPERATOR_MULTIPLICATION:
                values.push(v1*v2);
                break;
            case TokenOperator::OPERATOR_DIVISION:
                values.push(v1/v2);
                break;
            case TokenOperator::OPERATOR_EXPONENTIATION:
                values.push(pow(v1,v2));
                break;
            default:
                // Nunca deve entrar aqui...
                throw invalid_argument("unknown operator while evaluating expression");
            }
            break;
        default:
            // Nunca deve entrar aqui...
            throw invalid_argument("unknown type of token while evaluating expression");
            break;
        }
    }
    if (values.size() != 1)
    {
        // Nunca deve entrar aqui...
        throw invalid_argument("there is no single final value on the stack to calculate the value of the expression");
    }
    return values.top();
}
