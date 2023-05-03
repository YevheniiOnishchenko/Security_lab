#ifndef VIZHENERALGORYTHM_H
#define VIZHENERALGORYTHM_H

#include "encryptionalgorythm.h"

class VizhenerAlgorythm : public EncryptionAlgorythm {
public:
  VizhenerAlgorythm();
  bool encrypt(std::string, std::string) override;
  bool decrypt(std::string, std::string) override;
};

#endif // VIZHENERALGORYTHM_H
