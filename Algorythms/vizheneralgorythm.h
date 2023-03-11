#ifndef VIZHENERALGORYTHM_H
#define VIZHENERALGORYTHM_H

#include "encryptionalgorythm.h"

class VizhenerAlgorythm : public EncryptionAlgorythm {
public:
  VizhenerAlgorythm();
  bool encrypt(std::string, std::string) override;
  bool decrypt(std::string, std::string) override;

private:
  std::map<char, int> _alphabetIndices;
  std::map<char, int> _alphabetIndicesReverse;
  std::map<char, int> _keyIndices;

private:
  void determineIndicesForAlphabet();
  void determineIndicesForKey();
};

#endif // VIZHENERALGORYTHM_H
