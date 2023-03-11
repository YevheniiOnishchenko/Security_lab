#include "encryption.h"
#include <iostream>

int main() {
  std::string incomingDataFilePath{
      "D:\\Studing\\Master\\2sem\\Security\\IncomingDataFile.txt"};

  std::string encryptedDataFilePath{
      "D:\\Studing\\Master\\2sem\\Security\\EncryptedDataFile.txt"};

  std::string decryptedDataFilePath{
      "D:\\Studing\\Master\\2sem\\Security\\DecryptedDataFile.txt"};

  std::string key{};
  key = "Onishchenko";

  Encryption vizhenerEncryption;

  vizhenerEncryption.setAlgorythm(Algorythm::VIZHENER);
  vizhenerEncryption.setKey(key);
  vizhenerEncryption.chooseAlphabet(Alphabet::LATIN);
  vizhenerEncryption.encrypt(incomingDataFilePath, encryptedDataFilePath);
  vizhenerEncryption.decrypt(encryptedDataFilePath, decryptedDataFilePath);

  bool success = vizhenerEncryption.isResultSuccessfull(incomingDataFilePath,
                                                        decryptedDataFilePath);

  std::cout << (success ? "SUCCESS" : "FAILED") << '\n';

  return 0;
}
