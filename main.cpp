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

  //  encryptor.chooseAlphabet(Alphabet::ALL_SYMBOLS);
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

  //  encryptor.setAlgorythm(Algorythm::DES);
  //  encryptor.setKey("Onishe");
  //  encryptor.chooseAlphabet(Alphabet::ALL_SYMBOLS);
  //  encryptor.encrypt(incomingDataFilePath, encryptedDataFilePath);
  //  encryptor.decrypt(encryptedDataFilePath, decryptedDataFilePath);

  //  encryptor.setAlgorythm(Algorythm::AFFINE);
  //  encryptor.setKey("3, 5");
  //  encryptor.chooseAlphabet(Alphabet::LATIN);
  //  encryptor.encrypt(incomingDataFilePath, encryptedDataFilePath);
  //  encryptor.decrypt(encryptedDataFilePath, decryptedDataFilePath);
  //  bool successAffine = encryptor.isResultSuccessfull(incomingDataFilePath,
  //                                                     decryptedDataFilePath);
  //  std::cout << (successAffine ? "SUCCESS" : "FAILED") << '\n';

  //  encryptor.setAlgorythm(Algorythm::RSA);
  //  encryptor.setKey("827, 829"); // prime numbers
  //  encryptor.chooseAlphabet(Alphabet::LATIN);
  //  encryptor.encrypt(incomingDataFilePath, encryptedDataFilePath);
  //  encryptor.decrypt(encryptedDataFilePath, decryptedDataFilePath);
  //  bool successRsa = encryptor.isResultSuccessfull(incomingDataFilePath,
  //                                                     decryptedDataFilePath);
  //  std::cout << (successRsa ? "SUCCESS" : "FAILED") << '\n';

  encryptor.setAlgorythm(Algorythm::RABIN);
  encryptor.setKey("167, 719"); // prime numbers
  encryptor.chooseAlphabet(Alphabet::LATIN);
  encryptor.encrypt(incomingDataFilePath, encryptedDataFilePath);
  encryptor.decrypt(encryptedDataFilePath, decryptedDataFilePath);
  bool successRabin = encryptor.isResultSuccessfull(incomingDataFilePath,
                                                    decryptedDataFilePath);
  std::cout << (successRabin ? "SUCCESS" : "FAILED") << '\n';
  return 0;
}
