#include "rabinalgorythm.h"
#include <iostream>

RabinAlgorythm::RabinAlgorythm() {}

bool RabinAlgorythm::encrypt(std::string incomingDataFilePath,
                             std::string encryptedDataFilePath) {
  if (!verifyInputData() || incomingDataFilePath.empty()) {
    return false;
  }
  std::ifstream in;
  std::ofstream out;
  in.open(incomingDataFilePath.c_str(),
          std::ios_base::in | std::ios_base::binary);
  out.open(encryptedDataFilePath.c_str(),
           std::ios_base::out | std::ios_base::binary);

  int n = _keyPair.first * _keyPair.second;
  const int m = std::log2(n);
  if (m < 16) { // at least 1 byte is carring the data and 1 for Heming code
    std::cout << "m should be >= 16" << '\n';
    return false;
  }

  // ajusting n amd m values to byte size
  int numberOfBytesForReading = m / 8 - 1; // 1 for Heming code
  int numberOfBytesForWriting = m / 4;

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
      uint8_t hemingCode = findHemingCode(wholeNumber);
      wholeNumber <<= 8;
      wholeNumber += addByteToWholeNumber(hemingCode, 0);
      uint64_t encryptedData = binPow(wholeNumber, 2, n);

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

bool RabinAlgorythm::decrypt(std::string encryptedDataFilePath,
                             std::string decryptedDataFilePath) {
  if (!verifyInputData() || encryptedDataFilePath.empty()) {
    return false;
  }
  std::ifstream in;
  std::ofstream out;
  in.open(encryptedDataFilePath.c_str(),
          std::ios_base::in | std::ios_base::binary);
  out.open(decryptedDataFilePath.c_str(),
           std::ios_base::out | std::ios_base::binary);

  int n = _keyPair.first * _keyPair.second;
  const int m = std::log2(n);
  if (m < 16) { // at least 1 byte is carring the data and 1 for Heming code
    std::cout << "m should be >= 16" << '\n';
    return false;
  }

  // ajusting value to byte size
  int numberOfBytesForReading = m / 4;
  int numberOfBytesForWriting = m / 8 - 1; // 1 for Heming code

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
    if (currentByteForReading == numberOfBytesForReading - 1) {
      // last byte from data block
      /*
       * m^2=c(modn)
       * m^2=c(modq)
       * x^2=c(modp)
       * r=c^((p+1)/4)modp
       * s=c^((q+1)/4)modq
       * x=(a*p*s+b*q*r)
       * y=(a*p*s-b*q*r)
       * m=x, n-x, y, n-y
       */

      int x{}, y{};
      extendedGcd(_keyPair.first, _keyPair.second, x, y);
      uint64_t r =
          binPow(wholeNumber, (_keyPair.first + 1) / 4, _keyPair.first);
      uint64_t s =
          binPow(wholeNumber, (_keyPair.second + 1) / 4, _keyPair.second);

      possibleData.push_back(
          ((x * _keyPair.first * s) + (y * _keyPair.second * r)));

      if (possibleData[0] < 0) {
        possibleData[0] = n - ((-possibleData[0]) % n);
      } else {
        possibleData[0] = possibleData[0] % n;
      }
      possibleData.push_back(n - possibleData[0]);
      possibleData.push_back(
          ((x * _keyPair.first * s) - (y * _keyPair.second * r)));
      if (possibleData[2] < 0) {
        possibleData[2] = n - ((-possibleData[2]) % n);
      } else {
        possibleData[2] = possibleData[2] % n;
      }
      possibleData.push_back(n - possibleData[2]);

      uint64_t decryptedData = findDecryptedData(possibleData);
      possibleData.clear();

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

uint64_t RabinAlgorythm::addByteToWholeNumber(uint8_t byte,
                                              const uint64_t index) {
  uint64_t res = byte;
  res <<= (8 * index);
  return res;
}

uint8_t RabinAlgorythm::getByteFromWholeNumber(uint64_t number,
                                               const uint64_t shift) {
  return (number >> shift * 8) & 0xff;
}

bool RabinAlgorythm::verifyInputData() {
  if (_alphabetType == Alphabet::UNDEFINED ||
      EncryptionAlgorythm::_keyString.empty()) {
    return false;
  }
  if (!parseKeyFromString(EncryptionAlgorythm::_keyString)) {
    return false;
  }
  if (_keyPair.first % 4 != 3 || _keyPair.second % 4 != 3) {
    return false;
  }
  if (!isPrimeNumber(_keyPair.first) || !isPrimeNumber(_keyPair.second)) {
    return false;
  }
}

uint8_t RabinAlgorythm::findHemingCode(uint64_t data) {
  //  const uint8_t hemingBytes[] = {0, 1, 3, 7, 15, 31};
  //  uint8_t hemingByte{};
  //  uint8_t hemingBit{};

  //  for (int i = 0; i < 6; i++) { // bits 6, 7 are never used for 64-bit data
  //    for (int j = 0; j < 64 / (2 * (hemingBytes[i] + 1)); j++) {
  //      data <<= (hemingBytes[i] + 1); // get MSB
  //      for (int k = 0; k < hemingBytes[i] + 1; k++) {
  //        hemingBit ^= data & 0x01;
  //        data <<= (hemingBytes[i] + 1);
  //      }
  //      data <<= (hemingBytes[i] + 1);
  //    }
  //  }
  return 0xff;
}

uint64_t RabinAlgorythm::findDecryptedData(std::vector<int> data) {
  for (int i = 0; i < data.size(); i++) {
    if (findHemingCode(data[i]) == (data[i] & 0xff)) {
      data[i] = data[i] & 0xffffffffffffff00;
      data[i] >>= 8;
      return data[i];
    }
  }
  return 0;
}
