#include "affinealgorythm.h"

AffineAlgorythm::AffineAlgorythm() {}

bool AffineAlgorythm::encrypt(std::string incomingDataFilePath,
                              std::string encryptedDataFilePath) {
  if (_alphabetType == Alphabet::UNDEFINED || incomingDataFilePath.empty() ||
      EncryptionAlgorythm::_key.empty()) {
    return false;
  }
  if (!parseKeyFromString(EncryptionAlgorythm::_key)) {
    return false;
  }
  fillInAlphabet();
  determineIndicesForAlphabet();

  std::ifstream in;
  std::ofstream out;
  in.open(incomingDataFilePath.c_str(), std::ios_base::in);
  out.open(encryptedDataFilePath.c_str(), std::ios_base::out);

  int x, y;
  int gcd = extendedGcd(_key.first, _alphabet.size(), x, y);
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
        (incomingLetterPosition * _key.first + _key.second) % getAlphabetSize();
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
      EncryptionAlgorythm::_key.empty()) {
    return false;
  }
  _key = {0, 0};
  if (!parseKeyFromString(EncryptionAlgorythm::_key)) {
    return false;
  }
  fillInAlphabet();
  determineIndicesForAlphabet();

  std::ifstream in;
  std::ofstream out;
  in.open(encryptedDataFilePath.c_str(), std::ios_base::in);
  out.open(decryptedDataFilePath.c_str(), std::ios_base::out);

  int x, y; // x is converse a value
  int gcd = extendedGcd(_key.first, _alphabet.size(), x, y);
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
        ((encryptedLetterPosition - _key.second) * x) % getAlphabetSize();

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

void AffineAlgorythm::determineIndicesForAlphabet() {
  if (!_alphabetIndices.empty()) {
    _alphabetIndices.clear();
  }
  for (int i = 0; i < getAlphabetSize(); i++) {
    _alphabetIndices.insert(std::pair<char, int>(_alphabet.at(i), i));
    _alphabetIndicesReverse.insert(std::pair<int, char>(i, _alphabet.at(i)));
  }
}

bool AffineAlgorythm::parseKeyFromString(std::string s) {
  int comaPosition = s.find(',');
  if (comaPosition == -1) {
    return false;
  }
  std::string s1 = s.substr(0, comaPosition);
  std::string s2 = s.substr(comaPosition + 1, s.length() - s1.length() - 1);

  _key.first = std::stoi(s1);
  _key.second = std::stoi(s2);
  return true;
}

int AffineAlgorythm::extendedGcd(const int &a, const int &b, int &x, int &y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }

  int x1, y1;
  int gcd = extendedGcd(b % a, a, x1, y1);

  x = y1 - (b / a) * x1;
  y = x1;

  return gcd;
}
