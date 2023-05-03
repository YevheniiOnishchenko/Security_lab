#include "affinealgorythm.h"

AffineAlgorythm::AffineAlgorythm() {}

bool AffineAlgorythm::encrypt(std::string incomingDataFilePath,
                              std::string encryptedDataFilePath) {
  if (_alphabetType == Alphabet::UNDEFINED || incomingDataFilePath.empty() ||
      EncryptionAlgorythm::_keyString.empty()) {
    return false;
  }
  if (!parseKeyFromString(EncryptionAlgorythm::_keyString)) {
    return false;
  }
  fillInAlphabet();
  determineIndicesForAlphabet();

  std::ifstream in;
  std::ofstream out;
  in.open(incomingDataFilePath.c_str(), std::ios_base::in);
  out.open(encryptedDataFilePath.c_str(), std::ios_base::out);

  int x, y;
  int gcd = extendedGcd(_keyPair.first, _alphabet.size(), x, y);
  if (gcd != 1) {
    return false;
  }

  char buffer{};
  while (in.get(buffer)) {

    if (buffer == '\0') {
      return true;
    }

    int incomingLetterPosition{};
    if (_alphabetIndices.count(std::toupper(buffer)) ==
        0) { // symbol does not exist
      out.put(buffer);
      continue;
    }

    bool isUpper = buffer ? ((int)buffer < 97) : ((int)buffer >= 97);

    buffer = std::toupper(buffer); // alphabet is only for upper case letters

    incomingLetterPosition = _alphabetIndices.at(buffer);
    int encryptedLetterPosition =
        (incomingLetterPosition * _keyPair.first + _keyPair.second) %
        getAlphabetSize();
    char encryptedLetter =
        static_cast<char>(_alphabetIndicesReverse.at(encryptedLetterPosition));

    if (!isUpper) {
      encryptedLetter = std::tolower(encryptedLetter);
    }
    out.put(encryptedLetter);
  }

  in.close();
  out.close();

  return true;
}

bool AffineAlgorythm::decrypt(std::string encryptedDataFilePath,
                              std::string decryptedDataFilePath) {
  if (_alphabetType == Alphabet::UNDEFINED || encryptedDataFilePath.empty() ||
      EncryptionAlgorythm::_keyString.empty()) {
    return false;
  }
  _keyString = {0, 0};
  if (!parseKeyFromString(EncryptionAlgorythm::_keyString)) {
    return false;
  }
  fillInAlphabet();
  determineIndicesForAlphabet();

  std::ifstream in;
  std::ofstream out;
  in.open(encryptedDataFilePath.c_str(), std::ios_base::in);
  out.open(decryptedDataFilePath.c_str(), std::ios_base::out);

  int x, y; // x is converse a value
  int gcd = extendedGcd(_keyPair.first, _alphabet.size(), x, y);
  if (gcd != 1) {
    return false;
  }

  char buffer{};
  while (in.get(buffer)) {

    if (buffer == '\0') {
      return true;
    }

    int encryptedLetterPosition{};
    if (_alphabetIndices.count(std::toupper(buffer)) ==
        0) { // symbol does not exist
      out.put(buffer);
      continue;
    }

    bool isUpper = buffer ? ((int)buffer < 97) : ((int)buffer >= 97);

    buffer = std::toupper(buffer); // alphabet is only for upper case letters

    encryptedLetterPosition = _alphabetIndices.at(buffer);
    int decryptedLetterPosition =
        ((encryptedLetterPosition - _keyPair.second) * x) % getAlphabetSize();

    if (decryptedLetterPosition > getAlphabetSize()) {
      decryptedLetterPosition = decryptedLetterPosition % getAlphabetSize();
    } else {
      decryptedLetterPosition =
          (decryptedLetterPosition + getAlphabetSize()) % getAlphabetSize();
    }
    char decryptedLetter =
        static_cast<char>(_alphabetIndicesReverse.at(decryptedLetterPosition));

    if (!isUpper) {
      decryptedLetter = std::tolower(decryptedLetter);
    }
    out.put(decryptedLetter);
  }

  in.close();
  out.close();

  return true;
}
