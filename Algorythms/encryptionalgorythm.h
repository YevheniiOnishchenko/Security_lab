#ifndef ENCRYPTIONALGORYTHM_H
#define ENCRYPTIONALGORYTHM_H

#include <fstream>
#include <map>
#include <numeric>
#include <vector>

enum class Algorythm {
  UNDEFINED = 0,
  VIZHENER,
  ONE_TIME_PAD,
  DES,
  AFFINE,
  RSA
};
enum class Alphabet { UNDEFINED = 0, ALL_SYMBOLS, LATIN, CYRILLIC };

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
  std::string _keyString;
  std::pair<int, int> _keyPair;
  std::map<char, int> _alphabetIndices;
  std::map<char, int> _alphabetIndicesReverse;
  std::map<char, int> _keyIndices;
  int fermaNumbers[5] = {3, 5, 17, 257, 65537};

protected:
  int getAlphabetSize();
  int getKeySize();
  void fillInAlphabet();
  bool parseKeyFromString(std::string);
  int extendedGcd(const int &a, const int &b, int &x, int &y);
  int powerByModule(int c, int e, int n, int r);
  uint64_t binPow(uint64_t a, uint64_t b, uint64_t mod);
  bool isPrimeNumber(int n);
  void determineIndicesForAlphabet();
  void determineIndicesForKey();
};

#endif // ENCRYPTIONALGORYTHM_H
