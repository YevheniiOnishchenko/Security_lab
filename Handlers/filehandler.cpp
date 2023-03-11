#include "filehandler.h"

FileHandler::FileHandler(std::string iFileName) : _iFileName(iFileName) {}

FileHandler::FileHandler(std::string iFileName, std::string eFileName)
    : _iFileName(iFileName), _eFileName(eFileName) {}

FileHandler::FileHandler(std::string iFileName, std::string eFileName,
                         std::string dFileName)
    : _iFileName(iFileName), _eFileName(eFileName), _dFileName(dFileName) {}

// std::ifstream FileHandler::readFromIncomingDataFile() {
//   std::ifstream in;

//  in.open(_iFileName, std::ios::in);

//  char buffer;
//  while (in.get(buffer)) {
//  }

//  in.close();
//}

// std::ofstream FileHandler::writeToEncryptedDataFile() {}

// std::ofstream FileHandler::writeToDecryptedDataFile() {}

void FileHandler::constructOutcomingDataFilePath() {
  if (_iFileName.empty()) {
    return;
  }
}
