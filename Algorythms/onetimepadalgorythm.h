#ifndef ONETIMEPADALGORYTHM_H
#define ONETIMEPADALGORYTHM_H

#include "encryptionalgorythm.h"
#include <random>

class OneTimePadAlgorythm : public EncryptionAlgorythm {
public:
  OneTimePadAlgorythm();
  bool encrypt(std::string, std::string) override;
  bool decrypt(std::string, std::string) override;
  bool generateKey(int);

private:
  void toBinaryForm();
  void toTextForm();

private:
  std::string _keyFilePath; // lets store the key in file
};

#endif // ONETIMEPADALGORYTHM_H
