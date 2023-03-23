#ifndef DESALGORYTHM_H
#define DESALGORYTHM_H

#include "../Utils/DesTables.h"
#include "encryptionalgorythm.h"

class DesAlgorythm : public EncryptionAlgorythm {
public:
  DesAlgorythm();
  bool encrypt(std::string, std::string) override;
  bool decrypt(std::string, std::string) override;

private:
  bool initialPermutation();
  bool finalPermutation();
  bool keyCompressionPermutation();
  bool subKeysGeneration();
  bool expantionPermutation(bool);

private:
  uint8_t _keyData[8]{};
  uint64_t subKeys[16]{};
  uint32_t lKeyPart{}, rKeyPart{};
  uint32_t lDataPart{}, rDataPart{};
  uint8_t _inputData[8]{};
  int8_t _outputData[8]{};
};

#endif // DESALGORYTHM_H
