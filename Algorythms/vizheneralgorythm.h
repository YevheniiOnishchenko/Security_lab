#ifndef VIZHENERALGORYTHM_H
#define VIZHENERALGORYTHM_H

#include "encryptionalgorythm.h"
#include <map>
#include <numeric>
#include <vector>

class VizhenerAlgorythm : public EncryptionAlgorythm {
public:
  VizhenerAlgorythm();
  bool encrypt(std::string, std::string) override;
  bool decrypt(std::string, std::string) override;
  void chooseAlphabet(Alphabet) override;
  void setKey(std::string &key) override;

private:
  std::vector<char> _alphabet;
  Alphabet _alphabetType = Alphabet::UNDEFINED;
  std::map<char, int> _alphabetIndices;
  std::map<char, int> _alphabetIndicesReverse;
  std::vector<char> _key;
  std::map<char, int> _keyIndices;

private:
  int getAlphabetSize();
  int getKeySize();
  void fillInAlphabet();
  void determineIndicesForAlphabet();
  void determineIndicesForKey();
};

#endif // VIZHENERALGORYTHM_H
