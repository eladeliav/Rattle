//
// Created by elad on 06/11/2019.
//

#ifndef RATTLE_LEXER_HPP
#define RATTLE_LEXER_HPP
#include "Token.hpp"
#include "Classifier.hpp"
#include <string>
#include <vector>
#include <array>
#include <unordered_set>
#include <regex>
#include <iostream>
#include <fstream>

using LineNumber = unsigned int;
namespace Lexer
{
    Token getToken(std::string buffer, LineNumber line);
    std::vector<Token> tokenize(std::string filename);
};


#endif //RATTLE_LEXER_HPP
