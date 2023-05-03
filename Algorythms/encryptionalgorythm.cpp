#include "encryptionalgorythm.h"
#include "affinealgorythm.h"
#include "desalgorythm.h"
#include "onetimepadalgorythm.h"
#include "rsaalgorythm.h"
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
  case Algorythm::RSA:
    return new RsaAlgorythm();
  default:
    return new VizhenerAlgorythm(); // to be changed
    break;
  }
}

void EncryptionAlgorythm::setKey(std::string &key) { _keyString = key; }

void EncryptionAlgorythm::chooseAlphabet(Alphabet type) {
  _alphabetType = type;
}

int EncryptionAlgorythm::getAlphabetSize() { return _alphabet.size(); }

int EncryptionAlgorythm::getKeySize() { return _keyString.length(); }

void EncryptionAlgorythm::fillInAlphabet() {
  switch (_alphabetType) {
  case Alphabet::ALL_SYMBOLS:
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

bool EncryptionAlgorythm::parseKeyFromString(std::string s) {
  int comaPosition = s.find(',');
  if (comaPosition == -1) {
    return false;
  }
  std::string s1 = s.substr(0, comaPosition);
  std::string s2 = s.substr(comaPosition + 1, s.length() - s1.length() - 1);

  _keyPair.first = std::stoi(s1);
  _keyPair.second = std::stoi(s2);
  return true;
}

int EncryptionAlgorythm::extendedGcd(const int &a, const int &b, int &x,
                                     int &y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }

  int x1, y1;
  int gcd = extendedGcd(b % a, a, x1, y1);

  x = y1 - (b / a) * x1;
  y = x1;

  return gcd;
}

int EncryptionAlgorythm::powerByModule(int c, int e, int n, int r) {
  if (e == 0) {
    return r;
  }

  int ret = (c * r) % n;
  return powerByModule(c, e - 1, n, ret);
}

uint64_t EncryptionAlgorythm::binPow(uint64_t a, uint64_t b, uint64_t mod) {
  int result = 1;
  a %= mod;

  while (b > 0) {
    if (b & 1) {
      result = (result * a) % mod;
    }
    a = (a * a) % mod;
    b >>= 1;
  }

  return result;
}

bool EncryptionAlgorythm::isPrimeNumber(int n) {
  // 0 and 1 are not prime numbers
  if (n == 0 || n == 1) {
    return false;
  }

  // loop to check if n is prime
  for (int i = 2; i <= n / 2; ++i) {
    if (n % i == 0) {
      return false;
      break;
    }
  }
}

void EncryptionAlgorythm::determineIndicesForAlphabet() {
  if (!_alphabetIndices.empty()) {
    _alphabetIndices.clear();
  }
  for (int i = 0; i < getAlphabetSize(); i++) {
    _alphabetIndices.insert(std::pair<char, int>(_alphabet.at(i), i));
    _alphabetIndicesReverse.insert(std::pair<int, char>(i, _alphabet.at(i)));
  }
}

void EncryptionAlgorythm::determineIndicesForKey() {
  if (!_keyIndices.empty()) {
    _keyIndices.clear();
  }
  for (int i = 0; i < getKeySize(); i++) {
    _keyIndices.insert(std::pair<char, int>(_keyString.at(i), i));
  }
}
