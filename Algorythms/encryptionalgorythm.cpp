#include "encryptionalgorythm.h"
#include "vizheneralgorythm.h"

EncryptionAlgorythm::EncryptionAlgorythm() {}

EncryptionAlgorythm::~EncryptionAlgorythm()
{

}

EncryptionAlgorythm *
EncryptionAlgorythm::constructEncryptorByAlgorythm(Algorythm alg) {
  switch (alg) {
  case Algorythm::VIZHENER:
    return new VizhenerAlgorythm();
    break;
  default:
    return new VizhenerAlgorythm(); // to be changed
    break;
  }
}
