#include "onetimepadalgorythm.h"

OneTimePadAlgorythm::OneTimePadAlgorythm() {}

bool OneTimePadAlgorythm::encrypt(std::string incomingDataFilePath,
                                  std::string encryptedDataFilePath) {
  if (_alphabetType == Alphabet::UNDEFINED || incomingDataFilePath.empty()) {
    return false;
  }

  std::ifstream in;
  std::ofstream out;
  in.open(incomingDataFilePath.c_str(),
          std::ios_base::in | std::ios_base::binary);
  out.open(encryptedDataFilePath.c_str(),
           std::ios_base::out | std::ios_base::binary);

  in.seekg(0, in.end);
  int keySize = in.tellg();
  in.seekg(0, in.beg);

  std::size_t filePathDelimiterPosition =
      incomingDataFilePath.find_last_of("\\");
  _keyFilePath = incomingDataFilePath.substr(0, filePathDelimiterPosition) +
                 "\\KeyFile.txt";
  generateKey(keySize);

  std::ifstream key;
  key.open(_keyFilePath.c_str(), std::ios_base::in | std::ios_base::binary);

  if (!key.is_open()) {
    return false;
  }

  char inBuffer{}, keyBuffer;
  while (in.get(inBuffer), key.get(keyBuffer)) {

    char encryptedLetter = inBuffer ^ keyBuffer;
    out.put(encryptedLetter);
  }

  in.close();
  key.close();
  out.close();

  return true;
}

bool OneTimePadAlgorythm::decrypt(std::string encryptedDataFilePath,
                                  std::string decryptedDataFilePath) {
  if (_alphabetType == Alphabet::UNDEFINED || encryptedDataFilePath.empty()) {
    return false;
  }

  std::size_t filePathDelimiterPosition =
      encryptedDataFilePath.find_last_of("\\");
  _keyFilePath = encryptedDataFilePath.substr(0, filePathDelimiterPosition) +
                 "\\KeyFile.txt";
  std::ifstream in;
  std::ofstream out;
  in.open(encryptedDataFilePath.c_str(),
          std::ios_base::in | std::ios_base::binary);
  out.open(decryptedDataFilePath.c_str(),
           std::ios_base::out | std::ios_base::binary);

  std::ifstream key;
  key.open(_keyFilePath.c_str(), std::ios_base::in | std::ios_base::binary);
  if (!key.is_open()) {
    return false;
  }

  key.seekg(0, key.end);
  int keySize = key.tellg();
  key.seekg(0, key.beg);

  if (keySize == 0) {
    return false;
  }

  char encryptedBuffer{}, keyBuffer;
  while (in.get(encryptedBuffer), key.get(keyBuffer)) {

    char decryptedLetter = encryptedBuffer ^ keyBuffer;
    out.put(decryptedLetter);
  }

  in.close();
  key.close();
  out.close();

  return true;
}

bool OneTimePadAlgorythm::generateKey(int size) {
  if (size == 0) {
    return false;
  }

  std::ofstream out;
  if (_keyFilePath.empty()) {
    return false;
  }

  out.open(_keyFilePath.c_str(), std::ios_base::out | std::ios_base::binary);
  if (!out.is_open()) {
    return false;
  }

  for (int i = 0; i < size; i++) {
    char keyChar = static_cast<char>(std::rand() % 255);
    out.put(keyChar);
  }

  out.close();
  return true;
}

void OneTimePadAlgorythm::toBinaryForm() {}

void OneTimePadAlgorythm::toTextForm() {}
