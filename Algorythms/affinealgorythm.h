#ifndef AFFINEALGORYTHM_H
#define AFFINEALGORYTHM_H

#include "encryptionalgorythm.h"
#include <string>

class AffineAlgorythm : public EncryptionAlgorythm {
public:
  AffineAlgorythm();
  bool encrypt(std::string, std::string) override;
  bool decrypt(std::string, std::string) override;

private:
  int extendedGcd(const int &a, const int &b, int &x, int &y);
  void determineIndicesForAlphabet();
  void determineIndicesForKey();
  bool parseKeyFromString(std::string);

private:
  std::map<char, int> _alphabetIndices;
  std::map<char, int> _alphabetIndicesReverse;
  std::pair<int, int> _key;
};

#endif // AFFINEALGORYTHM_H
