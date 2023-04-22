#ifndef ENCRYPTIONALGORYTHM_H
#define ENCRYPTIONALGORYTHM_H

#include <fstream>
#include <map>
#include <numeric>
#include <vector>

enum class Algorythm { UNDEFINED = 0, VIZHENER, ONE_TIME_PAD, DES, AFFINE };
enum class Alphabet { UNDEFINED = 0, LATIN_FULL, LATIN, CYRILLIC };

class EncryptionAlgorythm {
public:
  EncryptionAlgorythm();
  virtual ~EncryptionAlgorythm();
  static EncryptionAlgorythm *constructEncryptorByAlgorythm(Algorythm);
  virtual bool encrypt(std::string, std::string) = 0;
  virtual bool decrypt(std::string, std::string) = 0;
  void setKey(std::string &key);
  void chooseAlphabet(Alphabet);

protected:
  std::vector<char> _alphabet;
  Alphabet _alphabetType = Alphabet::UNDEFINED;
  std::string _key;

  int getAlphabetSize();
  int getKeySize();
  void fillInAlphabet();
};

#endif // ENCRYPTIONALGORYTHM_H
