#include "encryption.h"
#include <iostream>

int main() {
  std::string incomingDataFilePath{
      "D:\\Studing\\Master\\2sem\\Security\\IncomingDataFile.txt"};

  std::string encryptedDataFilePath{
      "D:\\Studing\\Master\\2sem\\Security\\EncryptedDataFile.txt"};

  std::string decryptedDataFilePath{
      "D:\\Studing\\Master\\2sem\\Security\\DecryptedDataFile.txt"};

  std::string keyVizhener{"Onishchenko"};

  Encryption encryptor;

  //  encryptor.setAlgorythm(Algorythm::VIZHENER);
  //  encryptor.setKey(keyVizhener);

  //  encryptor.chooseAlphabet(Alphabet::LATIN);
  //  encryptor.encrypt(incomingDataFilePath, encryptedDataFilePath);
  //  encryptor.decrypt(encryptedDataFilePath, decryptedDataFilePath);

  //  bool successVIZHENER = encryptor.isResultSuccessfull(incomingDataFilePath,
  //                                                       decryptedDataFilePath);
  //  std::cout << (successVIZHENER ? "SUCCESS" : "FAILED") << '\n';

  //  encryptor.setAlgorythm(Algorythm::ONE_TIME_PAD);
  //  // key is generated automaticaly
  //  encryptor.encrypt(incomingDataFilePath, encryptedDataFilePath);
  //  encryptor.decrypt(encryptedDataFilePath, decryptedDataFilePath);

  //  bool successONE_TIME_PAD = encryptor.isResultSuccessfull(
  //      incomingDataFilePath, decryptedDataFilePath);
  //  std::cout << (successONE_TIME_PAD ? "SUCCESS" : "FAILED") << '\n';

  encryptor.setAlgorythm(Algorythm::DES);
  encryptor.setKey("Onishe");
  encryptor.chooseAlphabet(Alphabet::LATIN);
  encryptor.encrypt(incomingDataFilePath, encryptedDataFilePath);
  encryptor.decrypt(encryptedDataFilePath, decryptedDataFilePath);

  bool successDES = encryptor.isResultSuccessfull(incomingDataFilePath,
                                                  decryptedDataFilePath);
  std::cout << (successDES ? "SUCCESS" : "FAILED") << '\n';

  return 0;
}
