#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <ctime>
#pragma warning(disable : 4996)
using namespace std;

string GAME_FOLDER_NAME = "Save";

bool isTextFile(const std::string& fileName) {
    size_t dotIndex = fileName.rfind(".");
    if (dotIndex != std::string::npos) {
        std::string extension = fileName.substr(dotIndex);
        if (extension == ".txt") {
            return true;
        }
    }
    return false;
}

string removeSpaces(const std::string& str) {
    std::string tempStr = str;
    tempStr.erase(std::remove(tempStr.begin(), tempStr.end(), ' '), tempStr.end());
    return tempStr;
}

string replaceTo(std::string& str,char replace = '_', char to = ' ') {
    std::string tempStr = str;
    for (size_t i = 0; i < str.length(); i++) {
        if (tempStr[i] == replace) {
            tempStr[i] = to;
        }
    }
    return tempStr;
}

void writetoFile(const std::string& dosyaAdi, const std::string& metin) {
    std::ofstream dosya(GAME_FOLDER_NAME + "/" + dosyaAdi + ".txt", std::ios::app);
   
    if (dosya.is_open()) {
        dosya << metin  << '\n';
        dosya.close();
        std::cout << "Dosyaya yazma basarili." << std::endl;
    }
    else {
        std::cout << "Dosya acilamadi. Dosya olusturuluyor..." << std::endl;

        std::ofstream yeniDosya(GAME_FOLDER_NAME + "/" + dosyaAdi + ".txt" , std::ios::out);
        if (yeniDosya.is_open()) {
            yeniDosya <<  metin << '\n' ;
            yeniDosya.close();
            std::cout << "Dosya olusturma ve yazma basarili." << std::endl;
        }
        else {
            std::cout << "Dosya olusturulamadi." << std::endl;
        }
    }
}

std::string formatDate(const std::string& format) {
    std::time_t zaman;
    std::time(&zaman);
    std::tm* zamanBilesenleri = std::localtime(&zaman);

    char buffer[100];
    std::strftime(buffer, sizeof(buffer), format.c_str(), zamanBilesenleri);

    return buffer;

    return buffer;
}

void updateFile(const std::string& dosyaAdi, int index, const std::string& yeniVeri) {
    std::ifstream dosya(GAME_FOLDER_NAME + "/" + dosyaAdi + ".txt");
    if (!dosya.is_open()) {
        return;
    }

    std::vector<std::string> satirlar;
    std::string satir;
    while (std::getline(dosya, satir)) {
        satirlar.push_back(satir);
    }
    dosya.close();

    if (index < 0 || index >= satirlar.size()) {
        return;
    }

    satirlar[index] = yeniVeri;

    std::ofstream guncellenmisDosya(GAME_FOLDER_NAME + "/" + dosyaAdi + ".txt");
    if (!guncellenmisDosya.is_open()) {
        return;
    }

    for (const auto& satir : satirlar) {
        guncellenmisDosya << satir << std::endl;
    }
    guncellenmisDosya.close();

}

vector<string> readFileContent(const std::string& fileName) {
    std::vector<std::string> satirDizisi;
    std::ifstream dosya(GAME_FOLDER_NAME + "/" + fileName);

    if (!dosya.is_open()) {
        return satirDizisi;
    }

    std::string satir;
    while (std::getline(dosya, satir)) {
        satirDizisi.push_back(satir);
    }

    dosya.close();
    return satirDizisi;
}

vector<string> listTextFilesInFolder() {
    vector<string> fileNames;

    std::string searchPath = GAME_FOLDER_NAME + "\\*";
    WIN32_FIND_DATAA findData;
    HANDLE findHandle = FindFirstFileA(searchPath.c_str(), &findData);

    if (findHandle != INVALID_HANDLE_VALUE) {
        int index = 0;
        do {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                continue;
            }
            std::string fileName = findData.cFileName;
            if (isTextFile(fileName)) {
                fileNames.push_back(fileName);
            }
            index++;
        } while (FindNextFileA(findHandle, &findData) != 0);

        FindClose(findHandle);
    }
    else {
        std::cout << "Klasör açýlamadý!" << std::endl;
    }
    return fileNames;
}
