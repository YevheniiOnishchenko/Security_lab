#ifndef AFFINEALGORYTHM_H
#define AFFINEALGORYTHM_H

#include "encryptionalgorythm.h"
#include <string>

class AffineAlgorythm : public EncryptionAlgorythm {
public:
  AffineAlgorythm();
  bool encrypt(std::string, std::string) override;
  bool decrypt(std::string, std::string) override;
};

#endif // AFFINEALGORYTHM_H
