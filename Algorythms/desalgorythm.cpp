#include "desalgorythm.h"

#define LAST_BIT_MASK64 0x0000000000000001
#define LAST_BIT_MASK32 0x00000001
#define PART_SEPARATOR_MASK32 0x0000000fffffff
#define PART_SEPARATOR_MASK64 0x00000000ffffffff
DesAlgorythm::DesAlgorythm() {}

bool DesAlgorythm::encrypt(std::string incomingDataFilePath,
                           std::string encryptedDataFilePath) {
  bool success = false;

  // working with key
  memcpy(_keyData, &_key[0], 8);
  success = keyCompressionPermutation();
  success = subKeysGeneration() && success;

  // working with data
  std::ifstream in;
  std::ofstream out;

  in.open(incomingDataFilePath.c_str(),
          std::ios_base::in | std::ios_base::binary);
  out.open(encryptedDataFilePath.c_str(),
           std::ios_base::out | std::ios_base::binary);
  char dataChar[9]{};
  in.read(dataChar, 8);
  while (strlen(dataChar) > 0) {
    memcpy(_inputData, dataChar, 8);

    success = initialPermutation() && success;
    success = expantionPermutation(true) && success;
    success = finalPermutation() && success;

    out.write(reinterpret_cast<char *>(&_outputData), 8);

    memset(dataChar, 0x00, 8);
    in.read(dataChar, 8);
  }

  in.close();
  out.close();
  return success;
}

bool DesAlgorythm::decrypt(std::string encryptedDataFilePath,
                           std::string decryptedDataFilePath) {
  bool success = false;

  // working with key
  memcpy(_keyData, &_key[0], 8);

  success = keyCompressionPermutation();
  success = subKeysGeneration() && success;

  // working with data
  std::ifstream in;
  std::ofstream out;

  in.open(encryptedDataFilePath.c_str(),
          std::ios_base::in | std::ios_base::binary);
  out.open(decryptedDataFilePath.c_str(),
           std::ios_base::out | std::ios_base::binary);
  char dataChar[9]{};
  in.read(dataChar, 8);
  while (strlen(dataChar) > 0) {
    memcpy(_inputData, dataChar, 8);

    success = initialPermutation() && success;
    success = expantionPermutation(false) && success;
    success = finalPermutation() && success;

    out.write(reinterpret_cast<char *>(&_outputData), 8);

    memset(dataChar, 0x00, 8);
    in.read(dataChar, 8);
  }

  in.close();
  out.close();
  return success;
}

bool DesAlgorythm::initialPermutation() {
  int64_t dataInitialPermutationRes{0};

  uint64_t data64{};

  if (sizeof(_inputData) > 8) {
    return false;
  }

  if (sizeof(_inputData) < 8) {
    memset(&_inputData[sizeof(_inputData)], 0x00, 8 - sizeof(_inputData));
  }

  for (int i = 0; i < 8; i++) {
    data64 <<= 8;
    data64 += (_inputData[i]);
  }

  for (int i = 0; i < 64; i++) {
    dataInitialPermutationRes <<= 1;
    dataInitialPermutationRes |= (data64 >> (64 - IP[i])) & LAST_BIT_MASK64;
  }

  lDataPart =
      (uint32_t)(dataInitialPermutationRes >> 32) & PART_SEPARATOR_MASK64;
  rDataPart = (uint32_t)dataInitialPermutationRes & PART_SEPARATOR_MASK64;

  return true;
}

bool DesAlgorythm::finalPermutation() {
  uint64_t dataUnited{};
  uint64_t result{0};

  dataUnited = (uint64_t)rDataPart << 32 | (uint64_t)lDataPart; // reverse order

  /* PI permutation */
  for (int i = 0; i < 64; i++) {
    result <<= 1;
    result |= (dataUnited >> (64 - PI[i])) & LAST_BIT_MASK64;
  };

  for (int i = 0; i < 8; i++) {
    _outputData[7 - i] = (result)&0xff;
    result >>= 8;
  }
  return true;
}

bool DesAlgorythm::keyCompressionPermutation() {

  if (sizeof(_keyData) > 8) {
    return false;
  }

  if (sizeof(_keyData) < 8) {
    memset(&_keyData[sizeof(_keyData)], 0x00, 8 - sizeof(_keyData));
  }

  // We have 64 bit key
  uint64_t key64{};
  uint64_t key56{};

  for (int i = 0; i < 8; i++) {
    key64 <<= 8;
    key64 += (_keyData[i]);
  }

  for (int i = 0; i < 56; i++) {
    // Use PC-1 to compress the key to 56 bit size
    key56 <<= 1;
    key56 |= (key64 >> (64 - PC1[i])) & LAST_BIT_MASK64;
  }

  lKeyPart = (uint32_t)(key56 >> 28) & PART_SEPARATOR_MASK32;
  rKeyPart = (uint32_t)(key56)&PART_SEPARATOR_MASK32;

  return true;
}

bool DesAlgorythm::subKeysGeneration() {
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < iteration_shift[i]; j++) {
      lKeyPart =
          (0x0fffffff & (lKeyPart << 1)) | (0x00000001 & (lKeyPart >> 27));
      rKeyPart =
          (0x0fffffff & (rKeyPart << 1)) | (0x00000001 & (rKeyPart >> 27));
    }

    int64_t keyPartUnited{0};
    keyPartUnited = (((uint64_t)lKeyPart) << 28) | (uint64_t)rKeyPart;

    subKeys[i] = 0;

    for (int j = 0; j < 48; j++) {
      subKeys[i] <<= 1;
      subKeys[i] |= (keyPartUnited >> (56 - PC2[j])) & LAST_BIT_MASK64;
    }
  }
  return true;
}

bool DesAlgorythm::expantionPermutation(bool operation) {
  for (int i = 0; i < 16; i++) {
    // f(R,k) function
    uint64_t data48ExtendedInput{0};
    uint64_t data48ExtendedOutput{0};
    uint32_t fResult{0};

    for (int j = 0; j < 48; j++) {
      data48ExtendedInput <<= 1;
      data48ExtendedInput |=
          (uint64_t)((rDataPart >> (32 - E[j])) & LAST_BIT_MASK32);
    }

    // XORing E(Ri) with Ki
    if (operation == false) {
      // decryption
      data48ExtendedInput = data48ExtendedInput ^ subKeys[15 - i];
    } else {
      // encryption
      data48ExtendedInput = data48ExtendedInput ^ subKeys[i];
    }

    // S-Box Tables
    for (int j = 0; j < 8; j++) {
      uint8_t row =
          (uint8_t)((data48ExtendedInput & (0x0000840000000000 >> (6 * j))) >>
                    (42 - 6 * j)); // 100001 mask to get firt and last bit. It
                                   // is shifted for 6 bits to get B(n)
                                   // position. So we got B(n) byte. Then it is
                                   // shifted to the beginning and casted to 1
                                   // byte size.
      row = (row >> 4) |
            (row & 0x01); // set first raw bit to 1th position of byte and get
                          // second raw bit from 0th position of byte

      uint8_t column =
          (uint8_t)((data48ExtendedInput & (0x0000780000000000 >> (6 * j))) >>
                    (43 -
                     6 * j)); // 011110 mask to get column number. Shifted to 43
                              // because we dont care about 0 bit in set of 6

      data48ExtendedOutput <<= 4;
      data48ExtendedOutput |= (uint32_t)(S[j][16 * row + column] & 0x0f);
    }

    fResult = 0;

    // final permutation of f(R, k) function
    for (int j = 0; j < 32; j++) {
      fResult <<= 1;
      fResult |= (data48ExtendedOutput >> (32 - P[j])) & LAST_BIT_MASK32;
    }

    // satisfying the next conditions:
    // L(n) = R(n-1)
    // R(n) = L(n-1)^f(R(n-1), k(n))
    uint32_t lNewDataPart = rDataPart;
    rDataPart = lDataPart ^ fResult;
    lDataPart = lNewDataPart;
  }

  return true;
}
