#pragma once 

#ifndef DSTRING_HPP
#define DSTRING_HPP

#include"../dataTypes.hpp"



NAMESPACESTART



class SHARED_LIB StringHelper{

public:
    bool exsitsIn(const std::string& mainString, const std::string& find);
    bool exsitsInC(const std::string& mainString, const char& find);
    size_t howOften(const std::string& mainString, const std::string& find);
    Dmath::Duo<std::string, std::string> splitString(std::string mainString, size_t position);

    std::string extractFromTo(const std::string& mainString, char start, char end);
    Dmath::Text extractSentences(const std::string& mainString);

    std::string toUpper(const std::string& mainString) {

        std::string result = mainString;
        std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
            return std::toupper(c);
        });
        return result;
    }

// Konvertiert den gesamten String in nur Kleinbuchstaben
    std::string toLower(const std::string& mainString) {
        std::string result = mainString;
        std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
            return std::tolower(c);
        });
        return result;
    }
    
};

NAMESPACEEND
#endif 