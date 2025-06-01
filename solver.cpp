#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

namespace {
  struct CharInfo {
    bool terminates = false;
    std::map<char, CharInfo> nextCharMap;
  };

  void nextChar(std::map<char, CharInfo>* currMap, char* charList, int charCount,
                char* currentWord, int wordLength, bool repeat) {
    //Iterate over unique characters, recurse if progress is made on any words
    for (int i = 0; i < charCount; i++) {
      //If a word contains the current pattern, prepare and recurse
      if (currMap->contains(charList[i])) {
        //If the character already appeared in this loop, skip
        bool duplicate = false;
        for (int j = 0; j < i; j++) {
          if (charList[i] == charList[j]) {
            duplicate = true;
            break;
          }
        }
        if (duplicate) {
          continue;
        }

        CharInfo* charInfo = &(*currMap)[charList[i]];

        //Add character to current word, as new word
        char* newWord = new char[wordLength + 2]{0};
        if (currentWord != nullptr) {
          std::memcpy(newWord, currentWord, wordLength);
        }
        newWord[wordLength] = charList[i];

        //If a word ends here, emit it
        if (charInfo->terminates) {
          std::cout << newWord << std::endl;
        }

        if (repeat) {
          nextChar(&charInfo->nextCharMap, charList, charCount, newWord, wordLength + 1, repeat);
        } else {
          //Filter out current character
          char* newCharList = new char[charCount]{0};
          int nextIndex = 0;
          bool hasFound = false;
          for (int x = 0; x < charCount; x++) {
            if (hasFound || (charList[i] != charList[x])) {
              newCharList[nextIndex++] = charList[x];
            } else {
              hasFound = true;
            }
          }

          nextChar(&charInfo->nextCharMap, newCharList, nextIndex, newWord, wordLength + 1, repeat);
          delete [] newCharList;
        }

        delete [] newWord;
      }
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc == 2) {
    if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") {
      std::cout << "Usage: solver [WORD FILE] [CHARACTERS] [--allow-repeat]" << std::endl;
      std::cout << " - [--allow-repeat] is optional" << std::endl;
      return EXIT_SUCCESS;
    }
  }

  if (argc != 3 && argc != 4) {
    std::cerr << "ERROR: Requires 2 or 3 arguments, exiting" << std::endl;
    std::cerr << " - Call program with '--help' for help" << std::endl;
    return EXIT_FAILURE;
  }

  //Decide whether to allow repeating characters
  bool allowRepeat = false;
  if (argc == 4 && !std::strcmp(argv[3], "--allow-repeat")) {
    allowRepeat = true;
  } else if (argc == 4) {
    std::cerr << "ERROR: Unrecognised option '" << argv[3] << "', exiting" << std::endl;
    return EXIT_FAILURE;
  }

  std::map<char, CharInfo> wordMap;

  //Read word file in
  std::string lineData;
  std::ifstream input(argv[1]);
  if (input.is_open()) {
    while (std::getline(input, lineData)) {
      //Fill word map with data
      std::map<char, CharInfo>* currMapPtr = &wordMap;
      for (unsigned int i = 0; i < lineData.size(); i++) {
        //Add entry for character
        if (!currMapPtr->contains(lineData[i])) {
          currMapPtr->emplace();
        }

        //If the word ends here, set terminates to true
        if (i == lineData.size() - 1) {
          (*currMapPtr)[lineData[i]].terminates = true;
        }

        //Set the next map
        currMapPtr = &(*currMapPtr)[lineData[i]].nextCharMap;
      }
    }
    input.close();
  } else {
    std::cerr << "ERROR: Word file doesn't exist" << std::endl;
    return EXIT_FAILURE;
  }

  if (wordMap.size() == 0) {
    std::cerr << "ERROR: Word file specified is empty" << std::endl;
    return EXIT_FAILURE;
  }

  nextChar(&wordMap, argv[2], std::strlen(argv[2]), nullptr, 0, allowRepeat);

  return EXIT_SUCCESS;
}
