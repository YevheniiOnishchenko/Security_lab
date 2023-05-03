#include "vizheneralgorythm.h"

VizhenerAlgorythm::VizhenerAlgorythm() {}

bool VizhenerAlgorythm::encrypt(std::string incomingDataFilePath,
                                std::string encryptedDataFilePath) {
  if (_alphabetType == Alphabet::UNDEFINED || incomingDataFilePath.empty() ||
      _keyString.empty()) {
    return false;
  }
  fillInAlphabet();
  determineIndicesForAlphabet();
  determineIndicesForKey();

  std::ifstream in;
  std::ofstream out;
  in.open(incomingDataFilePath.c_str(), std::ios_base::in);
  out.open(encryptedDataFilePath.c_str(), std::ios_base::out);

  char buffer{};
  int keyUseTracker = 0;

  while (in.get(buffer)) {

    if (buffer == '\0') {
      return true;
    }

    if (keyUseTracker == _keyString.length()) {
      keyUseTracker = 0;
    }

    int incomingLetterPosition = _alphabetIndices.at(buffer);
    int encryptedLetterPosition =
        (incomingLetterPosition +
         _alphabetIndices.at(_keyString.at(keyUseTracker))) %
        getAlphabetSize();
    char encryptedLetter =
        static_cast<char>(_alphabetIndicesReverse.at(encryptedLetterPosition));

    out.put(encryptedLetter);
  }

  in.close();
  out.close();

  return true;
}

bool VizhenerAlgorythm::decrypt(std::string encryptedDataFilePath,
                                std::string decryptedDataFilePath) {
  if (_alphabetType == Alphabet::UNDEFINED || encryptedDataFilePath.empty() ||
      _keyString.empty()) {
    return false;
  }
  fillInAlphabet();
  determineIndicesForAlphabet();
  determineIndicesForKey();

  std::ifstream in;
  std::ofstream out;
  in.open(encryptedDataFilePath.c_str(), std::ios_base::in);
  out.open(decryptedDataFilePath.c_str(), std::ios_base::out);

  char buffer{};
  int keyUseTracker = 0;

  while (in.get(buffer)) {

    if (buffer == '\0') {
      return true;
    }

    if (keyUseTracker == _keyString.length()) {
      keyUseTracker = 0;
    }

    int encryptedLetterPosition = _alphabetIndices.at(buffer);
    int decryptedLetterPosition =
        (encryptedLetterPosition -
         _alphabetIndices.at(_keyString.at(keyUseTracker)));
    if (decryptedLetterPosition > getAlphabetSize()) {
      decryptedLetterPosition = decryptedLetterPosition % getAlphabetSize();
    } else {
      decryptedLetterPosition =
          (decryptedLetterPosition + getAlphabetSize()) % getAlphabetSize();
    }

    char decryptedLetter =
        static_cast<char>(_alphabetIndicesReverse.at(decryptedLetterPosition));

    out.put(decryptedLetter);
  }

  in.close();
  out.close();

  return true;
}
