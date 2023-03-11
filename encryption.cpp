#include "encryption.h"

Encryption::Encryption() {}

bool Encryption::encrypt(std::string incomingDataFilePath,
                         std::string encryptedDataFilePath) {
  if (incomingDataFilePath.empty() || _algorythm == Algorythm::UNDEFINED ||
      _key.empty()) {
    return false;
  }

  EncryptionAlgorythm *alg =
      EncryptionAlgorythm::constructEncryptorByAlgorythm(_algorythm);

  alg->setKey(_key);
  alg->chooseAlphabet(_alphabet);

  return alg->encrypt(incomingDataFilePath, encryptedDataFilePath);
  delete alg;
}

bool Encryption::decrypt(std::string encryptedDataFilePath,
                         std::string decryptedDataFilePath) {
  if (encryptedDataFilePath.empty() || _algorythm == Algorythm::UNDEFINED ||
      _key.empty()) {
    return false;
  }

  EncryptionAlgorythm *alg =
      EncryptionAlgorythm::constructEncryptorByAlgorythm(_algorythm);

  alg->setKey(_key);
  alg->chooseAlphabet(_alphabet);

  return alg->decrypt(encryptedDataFilePath, decryptedDataFilePath);
  delete alg;
}

void Encryption::setAlgorythm(Algorythm alg) { _algorythm = alg; }

void Encryption::setKey(std::string key) { _key = key; }

void Encryption::chooseAlphabet(Alphabet alph) { _alphabet = alph; }

bool Encryption::isResultSuccessfull(std::string incomingDataFilePath,
                                     std::string decryptedDataFilePath) {
  if (decryptedDataFilePath.empty() || incomingDataFilePath.empty()) {
    return false;
  }

  std::ifstream f1;
  std::ifstream f2;
  f1.open(incomingDataFilePath.c_str(), std::ios_base::in);
  f2.open(decryptedDataFilePath.c_str(), std::ios_base::in);

  if (f1.fail() || f2.fail()) {
    return false; // file problem
  }

  if (f1.tellg() != f2.tellg()) {
    return false; // size mismatch
  }

  // seek back to beginning and use std::equal to compare contents
  f1.seekg(0, std::ifstream::beg);
  f2.seekg(0, std::ifstream::beg);
  return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                    std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(f2.rdbuf()));
}
