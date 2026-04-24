#include "UrlShortener.h"


UrlShortener::UrlShortener() : storage("urls.txt") {

    storage.loadMappings(longToShort, shortToLong);
}

std::string UrlShortener::shorten(const std::string& longUrl) {
	// check if the long URL has already been shortened
	//find return iterator to the element if found, or end() if not found
    if (longToShort.find(longUrl) != longToShort.end()) {
        return longToShort[longUrl];
    }

	//call the helper function to generate a human-friendly short code based on the long URL
    std::string shortCode = generateHumanFriendlyCode(longUrl);

	// store the mapping between the long URL and the generated short code in both directions
    longToShort[longUrl] = shortCode;
    shortToLong[shortCode] = longUrl;

    storage.appendMapping(shortCode, longUrl);

    return shortCode;
}

std::string UrlShortener::resolve(const std::string& shortUrl) {
	// 1. search for the short URL in the mapping
    if (shortToLong.find(shortUrl) != shortToLong.end()) {
        return shortToLong[shortUrl];
    }

    // 2. (Edge Case)
    return "Error: Short URL not found!";
}

// helper function to generate a human-friendly short code based on the long URL
std::string UrlShortener::generateHumanFriendlyCode(const std::string& longUrl) {
    std::string url = longUrl;

    // --- step 1: (Sanitization) ---
    // remove ://http or ://https
    size_t protocolPos = url.find("://");
    if (protocolPos != std::string::npos) {
        url.erase(0, protocolPos + 3); // remove from the beginning up to the end of ://
    }
    // remove www. if present
    if (url.find("www.") == 0) {
        url.erase(0, 4);
    }

    // --- step 2: separate (Domain vs Path) ---
    size_t firstSlash = url.find('/');
	std::string domain = url.substr(0, firstSlash); //extract the domain part (e.g., github.com)

    size_t lastDot = domain.find_last_of('.');
    if (lastDot != std::string::npos) {
		domain = domain.substr(0, lastDot); // cut off the TLD (e.g., .com) to focus on the main domain (e.g., github)
    }

    std::string identifier = "";
    // if there is a path, take the last part of it as the identifier
    if (firstSlash != std::string::npos) {
        size_t lastSlash = url.find_last_of('/');
        if (lastSlash != std::string::npos && lastSlash + 1 < url.length()) {
            identifier = url.substr(lastSlash + 1); // take the part after the last slash (e.g., 154)
        }
    }

    // --- step 3: split the domain and extract letters ---
    std::string shortCode = "";
    size_t start = 0;
    // find the first dot or hyphen
    size_t end = domain.find_first_of(".-");

    while (end != std::string::npos) {
        // extract the word (e.g., github)
        std::string word = domain.substr(start, end - start);

        // take the first two letters, or the whole word if it's only one letter
        shortCode += (word.length() >= 2) ? word.substr(0, 2) : word;

        shortCode += "-";
        // move to the next word
        start = end + 1;
        end = domain.find_first_of(".-", start);
    }

    // process the last word in the domain
    std::string lastWord = domain.substr(start);
    shortCode += (lastWord.length() >= 2) ? lastWord.substr(0, 2) : lastWord;

    // --- step 4: final assembly ---
    if (!identifier.empty()) {
        shortCode += "/" + identifier; // add the identifier at the end
    }

    return shortCode;
}