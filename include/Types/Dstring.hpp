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


    bool isNumeric(const std::string& str) {
        std::string cleaned;
        
        // Entferne Leerzeichen
        for (char c : str) {
            if (!std::isspace(c)) {
                cleaned += c;
            }
        }
    
        if (cleaned.empty()) return false;
    
        bool hasDecimal = false;
        bool hasDigit = false;
        size_t start = 0;
    
        // Prüft negatives Vorzeichen am Anfang
        if (cleaned[0] == '-') {
            if (cleaned.length() == 1) return false; // Nur "-" ist ungültig
            start = 1;
        }
    
        for (size_t i = start; i < cleaned.length(); ++i) {
            if (std::isdigit(cleaned[i])) {
                hasDigit = true;
            } else if (cleaned[i] == '.') {
                if (hasDecimal) return false; // Mehr als ein Punkt ist ungültig
                hasDecimal = true;
            } else {
                return false; // Ungültiges Zeichen gefunden
            }
        }
    
        return hasDigit; // Mindestens eine Ziffer muss enthalten sein
    }
    std::string extractFirstWord(const std::string& str) {
        std::string result;
    
        for (char c : str) {
            if (c == ' ' || c == '.') break; // Stoppe bei Leerzeichen oder Punkt
            result += c;
        }
    
        return result;
    }
    
};

NAMESPACEEND
#endif 