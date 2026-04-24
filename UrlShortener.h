#pragma once
#ifndef URL_SHORTENER_H
#define URL_SHORTENER_H

#include <string>
#include <unordered_map>
#include "StorageManager.h"

class UrlShortener {
private:
	// stores the mapping between long URLs and their corresponding short URLs
    std::unordered_map<std::string, std::string> longToShort;
    std::unordered_map<std::string, std::string> shortToLong;

    StorageManager storage;

	// allows us to generate unique short codes for new long URLs
    std::string generateHumanFriendlyCode(const std::string& longUrl);

public:
    
    UrlShortener();

    
    std::string shorten(const std::string& longUrl);
    std::string resolve(const std::string& shortUrl);
};

#endif