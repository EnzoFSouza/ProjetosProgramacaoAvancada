#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <string>
#include <map>
#include <vector>

class Evaluator
{
    // Funcoes publicas
public:
    // Construtores
    Evaluator(): txt(),expr() {}
    Evaluator(const std::string& S): Evaluator()
    {
        set(S);
    }

    // Liberar
    void clear();

    // Testa se estah vazio
    bool empty() const {return expr.empty();}

    // Consulta ao texto a ser evaluado
    const std::string& getText() const {return txt;}
    // Consulta aa expressao a ser evaluada
    std::string getExpression() const;

    // Fixa a expressao a ser evaluada.
    // Gera excecao em caso de erro de sintaxe.
    void set(const std::string& S);

    // Evaluacao da expressao para um dado valor da variavel X.
    // Retorna 0.0 se expressao estiver vazia.
    // Gera excecao em caso de erro na expressao.
    double operator()(double X) const;

    // Tipos privados
private:
    enum class TypeOfToken
    {
        TOKEN_VALUE,            // Todos os tipos de valores:
        TOKEN_NUMBER,           // - um numero (descrito por um double)
        TOKEN_VARIABLE,         // - uma variavel (nao tem descricao adicional)
        TOKEN_FUNCTION,         // - uma funcao (descrita por um TokenFunction)
        TOKEN_OPERATOR,         // Um operador (descrito por um TokenOperator)
        TOKEN_LEFT_PARENTHESES  // Um abre parentese (nao tem descricao adicional)
    };
    enum class TokenFunction
    {
        FUNCTION_SIN,
        FUNCTION_COS,
        FUNCTION_TAN,
        FUNCTION_EXP,
        FUNCTION_LOG,
        FUNCTION_SQRT
    };
    enum class TokenOperator
    {
        OPERATOR_ADDITION,
        OPERATOR_SUBTRACTION,
        OPERATOR_MULTIPLICATION,
        OPERATOR_DIVISION,
        OPERATOR_EXPONENTIATION,
        OPERATOR_NEGATIVE
    };
    struct Token
    {
        TypeOfToken type;
        union
        {
            double x;
            TokenFunction f;
            TokenOperator op;
        };
        int precedence() const;
    };

    // Dados estaticos privados
private:
    // Todos os nomes validos de funcoes, associados aos respectivos identificadores
    static std::map<std::string,TokenFunction> functions;
    // Todos os operadores validos, associados aos respectivos identificadores
    static std::map<char,TokenOperator> operators;

    // Dados privados
private:
    std::string txt;
    std::vector<Token> expr;
};


#endif
