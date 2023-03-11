#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>

class FileHandler {
public:
  FileHandler(std::string iFileName);
  FileHandler(std::string iFileName, std::string eFileName);
  FileHandler(std::string iFileName, std::string eFileName,
              std::string dFileName);

  //  std::ifstream readFromIncomingDataFile();
  //  std::ofstream writeToEncryptedDataFile();
  //  std::ofstream writeToDecryptedDataFile();

  void constructOutcomingDataFilePath();

private:
  std::string _iFileName = nullptr;
  std::string _eFileName = nullptr;
  std::string _dFileName = nullptr;
};

#endif // FILEHANDLER_H
