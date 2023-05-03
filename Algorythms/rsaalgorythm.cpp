#include "rsaalgorythm.h"

RsaAlgorythm::RsaAlgorythm() {}
bool RsaAlgorythm::encrypt(std::string incomingDataFilePath,
                           std::string encryptedDataFilePath) {
  if (_alphabetType == Alphabet::UNDEFINED || incomingDataFilePath.empty() ||
      EncryptionAlgorythm::_keyString.empty()) {
    return false;
  }
  if (!parseKeyFromString(EncryptionAlgorythm::_keyString)) {
    return false;
  }
  if (!isPrimeNumber(_keyPair.first) || !isPrimeNumber(_keyPair.second)) {
    return false;
  }
  std::ifstream in;
  std::ofstream out;
  in.open(incomingDataFilePath.c_str(),
          std::ios_base::in | std::ios_base::binary);
  out.open(encryptedDataFilePath.c_str(),
           std::ios_base::out | std::ios_base::binary);

  int n = _keyPair.first * _keyPair.second;
  int eulerNumber = (_keyPair.first - 1) * (_keyPair.second - 1);
  const int e = findE(eulerNumber);
  const int m = std::log2(n);

  // ajusting n amd m values to byte size
  const int numberOfBytesForReading = m / 8;
  int numberOfBytesForWriting;
  if ((int)std::log2(n) % 8) {
    numberOfBytesForWriting = std::log2(n) / 8 + 1;
  } else {
    numberOfBytesForWriting = std::log2(n) / 8;
  }

  if (numberOfBytesForReading == 0) {
    return false;
  }
  char buffer;
  int currentByteForReading{};
  int currentByteForWriting = numberOfBytesForWriting - 1;
  uint64_t wholeNumber{};

  while (!in.eof()) {

    if (!in.get(buffer)) {
      // previous symbol was the last one, just add 0 if we did not read the
      // whole block
      for (int i = currentByteForReading; i < numberOfBytesForReading; i++) {
        wholeNumber += addByteToWholeNumber(
            0x00, numberOfBytesForReading - currentByteForReading - 1);
      }
      currentByteForReading = numberOfBytesForReading - 1;
    } else {
      // construct data with multiple bytes
      wholeNumber += addByteToWholeNumber(
          buffer, numberOfBytesForReading - currentByteForReading - 1);
    }

    // block encryption
    if (currentByteForReading ==
        numberOfBytesForReading - 1) { // last byte from data block
      uint64_t encryptedData = binPow(wholeNumber, e, n);

      for (int i = currentByteForWriting; i >= 0; i--) {
        uint8_t encryptedByte = getByteFromWholeNumber(encryptedData, i);
        out.put(encryptedByte);
      }
      currentByteForWriting = numberOfBytesForWriting - 1;
      currentByteForReading = 0;
      wholeNumber = 0;
      continue;
    }
    currentByteForReading++;
  }

  in.close();
  out.close();

  return true;
}

bool RsaAlgorythm::decrypt(std::string encryptedDataFilePath,
                           std::string decryptedDataFilePath) {
  if (_alphabetType == Alphabet::UNDEFINED || encryptedDataFilePath.empty() ||
      EncryptionAlgorythm::_keyString.empty()) {
    return false;
  }
  if (!parseKeyFromString(EncryptionAlgorythm::_keyString)) {
    return false;
  }
  if (!isPrimeNumber(_keyPair.first) || !isPrimeNumber(_keyPair.second)) {
    return false;
  }
  std::ifstream in;
  std::ofstream out;
  in.open(encryptedDataFilePath.c_str(),
          std::ios_base::in | std::ios_base::binary);
  out.open(decryptedDataFilePath.c_str(),
           std::ios_base::out | std::ios_base::binary);

  int n = _keyPair.first * _keyPair.second;
  int eulerNumber = (_keyPair.first - 1) * (_keyPair.second - 1);
  const int d = findD(eulerNumber);
  const int m = std::log2(n);

  // ajusting value to byte size
  int numberOfBytesForWriting = m / 8;
  int numberOfBytesForReading;
  if ((int)std::log2(n) % 8) {
    numberOfBytesForReading = std::log2(n) / 8 + 1;
  } else {
    numberOfBytesForReading = std::log2(n) / 8;
  }

  if (numberOfBytesForReading == 0) {
    return false;
  }
  char buffer;
  int currentByteForReading{};
  int currentByteForWriting = numberOfBytesForWriting - 1;
  uint64_t wholeNumber{};

  while (!in.eof()) {

    if (!in.get(buffer)) {
      // previous symbol was the last one, just add 0 if we did not read the
      // whole block
      for (int i = currentByteForReading; i < numberOfBytesForReading; i++) {
        wholeNumber += addByteToWholeNumber(
            0x00, numberOfBytesForReading - currentByteForReading - 1);
      }
      currentByteForReading = numberOfBytesForReading - 1;
    } else {
      // construct data with multiple bytes
      wholeNumber += addByteToWholeNumber(
          buffer, numberOfBytesForReading - currentByteForReading - 1);
    }

    // block decryption
    if (currentByteForReading ==
        numberOfBytesForReading - 1) { // last byte from data block
      uint64_t decryptedData = binPow(wholeNumber, d, n);

      for (int i = currentByteForWriting; i >= 0; i--) {
        uint8_t decryptedByte = getByteFromWholeNumber(decryptedData, i);
        out.put(decryptedByte);
      }
      currentByteForWriting = numberOfBytesForWriting - 1;
      currentByteForReading = 0;
      wholeNumber = 0;
      continue;
    }
    currentByteForReading++;
  }

  in.close();
  out.close();

  return true;
}

uint64_t RsaAlgorythm::addByteToWholeNumber(uint8_t byte,
                                            const uint64_t index) {
  uint64_t res = byte;
  res <<= (8 * index);
  return res;
}

uint8_t RsaAlgorythm::getByteFromWholeNumber(uint64_t number,
                                             const uint64_t shift) {
  return (number >> shift * 8) & 0xff;
}

int RsaAlgorythm::findE(int eulerNumber) {
  // choose e to be a prime number, relatively prime number with n
  // e < eulerNumber
  // use Fermat number
  int e{};
  for (int i = 4; i >= 0; i--) {
    int x{}, y{};
    e = fermaNumbers[i];
    if (e < eulerNumber && extendedGcd(e, eulerNumber, x, y) == 1) {
      break;
    }
  }
  return e;
}

int RsaAlgorythm::findD(int eulerNumber) {
  int e{}, d{};
  for (int i = 4; i >= 0; i--) {
    int y{};
    e = fermaNumbers[i];
    if (e < eulerNumber && extendedGcd(e, eulerNumber, d, y) == 1) {
      break;
    }
    d = 0;
  }
  return d;
}
