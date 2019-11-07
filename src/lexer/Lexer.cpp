//
// Created by elade on 11/6/2019.
//

#include "Lexer.hpp"

Lexer::Token Lexer::Lex::getNextToken()
{
    if ((size_t) pos >= this->text.size())
        return Token("", Token::Type::END_OF_LINE);

    char ch = text.at(pos);

    std::regex integer_pattern(INTEGER_REGEX);

    if (std::regex_match(std::string(1, ch), integer_pattern))
    {
        currentToken = Token(std::string(1, ch), Token::Type::INTEGER);
        pos++;
        return currentToken;
    }

    if (ch == '+')
    {
        currentToken = Token(std::string(1, ch), Token::Type::ADD);
        pos++;
        return currentToken;
    }
    return Token("", Token::Type::END_OF_LINE);
}

void Lexer::Lex::eat(Token::Type type)
{
    if (currentToken.getType() == type)
    {
        currentToken = getNextToken();
    }
    //error
}

std::string Lexer::Lex::runExpression()
{
    currentToken = getNextToken();

    Token leftToken = currentToken;
    eat(Token::Type::INTEGER);

    Token op = currentToken;
    eat(Token::Type::ADD);

    Token right = currentToken;
    eat(Token::Type::INTEGER);

    int leftNum = std::stoi(leftToken.getValue());
    int rightNum = std::stoi(right.getValue());
    int resultNum = leftNum + rightNum;
    std::string result = std::to_string(resultNum);

    return result;

}
