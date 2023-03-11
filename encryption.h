#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "Algorythms/encryptionalgorythm.h"

class Encryption {
public:
  Encryption();
  bool encrypt(std::string, std::string);
  bool decrypt(std::string, std::string);
  void setAlgorythm(Algorythm);
  void setKey(std::string);
  void chooseAlphabet(Alphabet);
  bool isResultSuccessfull(std::string,
                           std::string); // compare incoming and decrypted files

private:
  Algorythm _algorythm = Algorythm::UNDEFINED;
  Alphabet _alphabet = Alphabet::UNDEFINED;
  std::string _key{};
};

#endif // ENCRYPTION_H
