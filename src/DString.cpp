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