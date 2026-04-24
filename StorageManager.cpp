#include "StorageManager.h"
#include <fstream>
#include <iostream>

// constructor to initialize the filename for storage
StorageManager::StorageManager(const std::string& file) {
    filename = file;
}

void StorageManager::loadMappings(std::unordered_map<std::string, std::string>& longToShort,
    std::unordered_map<std::string, std::string>& shortToLong) {
    //  (Input File Stream)
    std::ifstream inFile(filename);

	//if the file doesn't exist, we simply return without doing anything, which means the program will start with an empty memory (no mappings)
    if (!inFile.is_open()) {
        return; 
    }

    std::string shortUrl, longUrl;


    while (inFile >> shortUrl >> longUrl) {
        longToShort[longUrl] = shortUrl;
        shortToLong[shortUrl] = longUrl;
    }

    inFile.close(); 
}

void StorageManager::appendMapping(const std::string& shortUrl, const std::string& longUrl) {
    
    std::ofstream outFile(filename, std::ios::app);

    if (outFile.is_open()) {

        outFile << shortUrl << " " << longUrl << "\n";
        outFile.close();
    }
    else {
        std::cerr << "Error: Could not open file for writing.\n";
    }
}