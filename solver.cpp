#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

struct CharInfo {
  bool terminates = false;
  std::map<char, CharInfo> nextCharMap;
};

void nextChar(std::map<char, CharInfo>* currMap, char* charList, int charCount,
              char* currentWord, int wordLength) {
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
      char newWord[wordLength + 2] = {0};
      std::memcpy(newWord, currentWord, wordLength);
      newWord[wordLength] = charList[i];

      //If a word ends here, emit it
      if (charInfo->terminates) {
        std::cout << newWord << std::endl;
      }

      nextChar(&charInfo->nextCharMap, charList, charCount, newWord, wordLength + 1);
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "ERROR: Requires 2 arguments, exiting" << std::endl;
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

  nextChar(&wordMap, argv[2], std::strlen(argv[2]), nullptr, 0);

  return EXIT_SUCCESS;
}
