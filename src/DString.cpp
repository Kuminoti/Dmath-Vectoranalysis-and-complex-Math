#include"../include/Types/Dstring.hpp"


bool Dmath::StringHelper::exsitsIn(const std::string& mainString, const std::string& find){
    bool exsits = false;

    size_t foundAt = mainString.find(find);
    if(foundAt != std::string::npos){
        exsits = true;
    }

    return exsits;
}

bool Dmath::StringHelper::exsitsInC(const std::string& mainString, const char& find){
    bool exsits = false;

    size_t foundAt = mainString.find(find);
    if(foundAt != std::string::npos){
        exsits = true;
    }

    return exsits;
}


bool Dmath::StringHelper::isNumeric(const std::string& str) {
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

std::string Dmath::StringHelper::extractFirstWord(const std::string& str) {
    std::string result;

    for (char c : str) {
        if (c == ' ' || c == '.') break; // Stoppe bei Leerzeichen oder Punkt
        result += c;
    }

    return result;
}

std::string Dmath::StringHelper::extractFromTo(const std::string& mainString, char start, char end) {
    std::string stringExtract = "";
    if(!this->exsitsInC(mainString, start) || !this->exsitsInC(mainString, end)){
        return "";
    }
    size_t startPos = mainString.find(start); // Position des Startzeichens
    size_t endPos = mainString.find(end, startPos + 1); // Position des Endzeichens nach Start

    stringExtract = mainString.substr(startPos + 1, endPos - startPos - 1);
    return stringExtract;
}


Dmath::Text Dmath::StringHelper::extractSentences(const std::string& mainString) {
    Dmath::Text sentences;
    std::string sentence;

    for (size_t i = 0; i < mainString.size(); ++i) {
        char c = mainString[i];
        sentence += c; 

        if (c == '.' || c == '?' || c == '!') {
            size_t start = sentence.find_first_not_of(" \t\n");
            size_t end = sentence.find_last_not_of(" \t\n");

            if (start != std::string::npos) {
                sentences.push_back(sentence.substr(start, end - start + 1));
            }

        sentence.clear(); 
        }
    }

    if (!sentence.empty()) {
        size_t start = sentence.find_first_not_of(" \t\n");
        size_t end = sentence.find_last_not_of(" \t\n");

        if (start != std::string::npos) {
            sentences.push_back(sentence.substr(start, end - start + 1));
        }
    }

    return sentences;
}


std::string Dmath::StringHelper::replaceWordExact(const std::string& input, const std::string& target, const std::string& replacement) {
    std::string output;
    std::string currentWord;
    std::string delimiters = " +-/*!^%()$=[]";
    
    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];

        // Trennzeichen beenden ein Wort
        if (delimiters.find(c) != std::string::npos) {
            if (!currentWord.empty()) {
                // Prüfe, ob das Wort ersetzt werden muss
                if (currentWord == target) {
                    output += replacement;
                } else {
                    output += currentWord;
                }
                currentWord.clear();
            }

            // Sonderzeichen zählen als eigenes Wort (werden direkt angehängt)
            output += c;
        } else {
            // Buchstaben/Ziffern/etc. -> Teil eines Wortes
            currentWord += c;
        }
    }

    // Letztes Wort verarbeiten
    if (!currentWord.empty()) {
        if (currentWord == target) {
            output += replacement;
        } else {
            output += currentWord;
        }
    }

    return output;
}

std::string Dmath::StringHelper::toUpper(const std::string& mainString) {

    std::string result = mainString;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return std::toupper(c);
    });
    return result;
}

std::string Dmath::StringHelper::toLower(const std::string& mainString) {
    std::string result = mainString;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return result;
}

size_t Dmath::StringHelper::howOften(const std::string& mainString, const std::string& find) {
    size_t count = 0;
    size_t pos = mainString.find(find); // Erste Position von "find" suchen

    // Wiederhole, solange "find" im String gefunden wird
    while (pos != std::string::npos) {
        ++count; // Zähler erhöhen
        pos = mainString.find(find, pos + find.length()); // Suche ab der nächsten Position
    }

    return count;
}

Dmath::Duo<std::string, std::string> Dmath::StringHelper::splitString(std::string mainString, size_t position){
    Dmath::Duo<std::string, std::string> mainDuo("-1","-1"); //String of -1 reperesents an  empty value or an errorvalue
    
    if(position < mainString.size()){
        std::string firstPart = mainString.substr(0,position);
        std::string otherPart = mainString.substr(position);
        
        mainDuo.one = firstPart;
        mainDuo.two = otherPart;
    }


    return mainDuo;
}


std::string  Dmath::StringHelper::getFileExtension(const std::string& filename) {
    size_t pos = filename.rfind('.');
    if (pos == std::string::npos || pos == filename.length() - 1) {
        // Kein Punkt gefunden oder Punkt am Ende → keine Extension
        return " ";  // wie gewünscht: " " für kein Format
    }
    return filename.substr(pos);  // inkl. Punkt, z.B. ".exe"
}