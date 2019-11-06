//
// Created by elad on 06/11/2019.
//

#include "Lexer.hpp"

using namespace Lexer;

std::vector<Token> Lexer::tokenize(std::string filename)
{
    std::ifstream file(filename, std::ios::in);

    if(file.fail())
    {
        std::cout << "Can't open file " << filename << std::endl;
        std::cin.get();
        exit(-2);
    }

    LineNumber lineNumber = 1;
    std::string buffer = "";
    char ch;
    std::vector<Token> tokens;

    while(file >> std::noskipws >> ch)
    {
        Token currentToken = getToken(std::to_string(ch), lineNumber);
        if(currentToken.getTokenType() == Token::Type::NEWLINE)
        {
            lineNumber++;
            buffer = "";
            continue;
        }

        if(currentToken.getTokenType() == Token::Type::DELIMINATOR)
        {
            if(buffer != "")
            {
                tokens.push_back(getToken(buffer, lineNumber));
                buffer = "";
            }
            tokens.push_back(currentToken);
            continue;
        }

        if(currentToken.getTokenType() == Token::Type::WHITESPACE)
        {
            if(buffer != "")
            {
                tokens.push_back(getToken(buffer, lineNumber));
                buffer = "";
            }
            continue;
        }

        buffer += ch;

    }

    return tokens;

}

Token Lexer::getToken(std::string buffer, LineNumber line)
{
    for(const auto& obj : string_classifiers)
    {
        if(obj.among(buffer))
        {
            return Token(buffer, obj.getType(), obj.getTypeName());
        }
    }

    for(const auto& obj : char_classifiers)
    {
        char asciiVal = 0;
        try
        {
            asciiVal = (char)std::stoi(buffer);
        }catch(std::invalid_argument& e)
        {
            continue;
        }

        if(obj.among(asciiVal))
        {
            return Token(std::string(1, asciiVal), obj.getType(), obj.getTypeName());
        }
    }

    std::regex identifier_pattern("[a-zA-Z][a-zA-Z0-9_]*");
    std::regex string_pattern("\".*\"");
    std::regex literal_pattern("^[0-9]+$");

    std::array<std::regex, 3> patterns {identifier_pattern, string_pattern, literal_pattern};
    std::array<Token::Type, 3> types {Token::Type::IDENTIFIER, Token::Type::STRING, Token::Type::LITERAL};
    std::array<std::string, 3> typeNames {"Identifier", "String", "Literal"};

    for(unsigned int i = 0;  i < patterns.size();i++)
        if(std::regex_match(buffer, patterns.at(i)))
            return Token(buffer, types.at(i), typeNames.at(i));

    std::cout << "Don't support comments yet at " << line << std::endl;
    std::cin.get();
    exit(-1);
}
