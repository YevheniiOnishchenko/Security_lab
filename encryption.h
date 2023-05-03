#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "Algorythms/encryptionalgorythm.h"

class Encryption {
public:
  Encryption();
  bool encrypt(std::string, std::string);
  bool decrypt(std::string, std::string);
  void setAlgorythm(Algorythm); // used for configuration from main.cpp
  void setKey(std::string);
  void chooseAlphabet(Alphabet);
  bool isResultSuccessfull(std::string,
                           std::string); // compare incoming and decrypted files

private:
  Algorythm _algorythm = Algorythm::UNDEFINED;
  Algorythm _encriptionAlgorithm =
      Algorythm::UNDEFINED; // for internal algorithm tracking
  Alphabet _alphabet = Alphabet::UNDEFINED;
  std::string _keyString{};
  std::shared_ptr<EncryptionAlgorythm> alg;
};

#endif // ENCRYPTION_H
