#ifndef ENCRYPTIONALGORYTHM_H
#define ENCRYPTIONALGORYTHM_H

#include <fstream>

enum class Algorythm { UNDEFINED = 0, VIZHENER };
enum class Alphabet { UNDEFINED = 0, LATIN, CYRILLIC };

class EncryptionAlgorythm {
public:
  EncryptionAlgorythm();
  virtual ~EncryptionAlgorythm();
  static EncryptionAlgorythm *constructEncryptorByAlgorythm(Algorythm);
  virtual bool encrypt(std::string, std::string) = 0;
  virtual bool decrypt(std::string, std::string) = 0;
  virtual void setKey(std::string &key) = 0;
  virtual void chooseAlphabet(Alphabet) = 0;
};

#endif // ENCRYPTIONALGORYTHM_H
