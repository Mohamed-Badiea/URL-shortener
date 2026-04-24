#ifndef STORAGE_MANAGER_H
#define STORAGE_MANAGER_H

#include <string>
#include <unordered_map>

class StorageManager {
private:
    std::string filename;

public:
	// Constructor file name to manage the storage of URL mappings
    StorageManager(const std::string& file);

	// function to load all existing mappings from the file into memory (into the provided maps)
    void loadMappings(std::unordered_map<std::string, std::string>& longToShort,
        std::unordered_map<std::string, std::string>& shortToLong);

	// to add a new mapping to the file (append mode) when a new URL is shortened
    void appendMapping(const std::string& shortUrl, const std::string& longUrl);
};

#endif