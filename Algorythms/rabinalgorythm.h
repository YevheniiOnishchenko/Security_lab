#ifndef RABINALGORYTHM_H
#define RABINALGORYTHM_H

#include "encryptionalgorythm.h"

class RabinAlgorythm : public EncryptionAlgorythm {
public:
  RabinAlgorythm();
  bool encrypt(std::string, std::string) override;
  bool decrypt(std::string, std::string) override;

protected:
  uint64_t addByteToWholeNumber(uint8_t, const uint64_t);
  uint8_t getByteFromWholeNumber(uint64_t, const uint64_t);
  std::vector<int> possibleData;
  bool verifyInputData();

  uint8_t findHemingCode(uint64_t);
  uint64_t findDecryptedData(std::vector<int>);
};

#endif // RABINALGORYTHM_H
