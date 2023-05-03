#ifndef RSAALGORYTHM_H
#define RSAALGORYTHM_H

#include "encryptionalgorythm.h"
#include <cmath>

class RsaAlgorythm : public EncryptionAlgorythm {
public:
  RsaAlgorythm();
  bool encrypt(std::string, std::string) override;
  bool decrypt(std::string, std::string) override;

protected:
  uint64_t addByteToWholeNumber(uint8_t, const uint64_t);
  uint8_t getByteFromWholeNumber(uint64_t, const uint64_t);
  int findE(int);
  int findD(int);

private:
};

#endif // RSAALGORYTHM_H
