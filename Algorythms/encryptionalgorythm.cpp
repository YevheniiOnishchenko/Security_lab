#include "encryptionalgorythm.h"
#include "affinealgorythm.h"
#include "desalgorythm.h"
#include "onetimepadalgorythm.h"
#include "vizheneralgorythm.h"

EncryptionAlgorythm::EncryptionAlgorythm() {}

EncryptionAlgorythm::~EncryptionAlgorythm() {}

EncryptionAlgorythm *
EncryptionAlgorythm::constructEncryptorByAlgorythm(Algorythm alg) {
  switch (alg) {
  case Algorythm::VIZHENER:
    return new VizhenerAlgorythm();
    break;
  case Algorythm::ONE_TIME_PAD:
    return new OneTimePadAlgorythm();
    break;
  case Algorythm::DES:
    return new DesAlgorythm();
    break;
  case Algorythm::AFFINE:
    return new AffineAlgorythm();
    break;
  default:
    return new VizhenerAlgorythm(); // to be changed
    break;
  }
}

void EncryptionAlgorythm::setKey(std::string &key) { _key = key; }

void EncryptionAlgorythm::chooseAlphabet(Alphabet type) {
  _alphabetType = type;
}

int EncryptionAlgorythm::getAlphabetSize() { return _alphabet.size(); }

int EncryptionAlgorythm::getKeySize() { return _key.length(); }

void EncryptionAlgorythm::fillInAlphabet() {
  switch (_alphabetType) {
  case Alphabet::LATIN_FULL:
    _alphabet.resize(128);
    std::iota(_alphabet.begin(), _alphabet.end(), static_cast<char>(0));
    break;
  case Alphabet::LATIN:
    _alphabet.resize(26);
    std::iota(_alphabet.begin(), _alphabet.end(), static_cast<char>(65));
    break;
  case Alphabet::CYRILLIC:

    break;
  default:
    break;
  }
}
