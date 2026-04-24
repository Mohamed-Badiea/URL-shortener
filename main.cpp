#include <iostream>
#include <string>
#include "UrlShortener.h" 

bool isValidUrl(const std::string& url) {
    if (url.find("http://") != 0 && url.find("https://") != 0) {
        return false;
    }
    if (url.find(' ') != std::string::npos) {
        return false;
    }
    return true;
}

int main() {
    UrlShortener service; 
    int choice;
    std::string inputUrl;

    std::cout << "--- URL Shortener Service (MVP) ---" << std::endl;

    while (true) {
        std::cout << "\n1. Shorten URL\n2. Resolve URL\n3. Exit\nChoose: ";
        std::cin >> choice;

        if (choice == 3) {
            std::cout << "Exiting system..." << std::endl;
            break;
        }

        std::cout << "Enter URL: ";
        std::cin >> inputUrl;

        if (choice == 1) {
            if (!isValidUrl(inputUrl)) {
                std::cout << "Error: Invalid URL! Must start with http:// or https:// and contain no spaces.\n";
                continue; 
            }
            std::string result = service.shorten(inputUrl);
            std::cout << "Generated Short URL: " << result << std::endl;
        }
        else if (choice == 2) {
            std::string result = service.resolve(inputUrl);
            std::cout << "Original URL: " << result << std::endl;
        }
        else {
            std::cout << "Invalid Input. Please try again." << std::endl;
        }
    }

    return 0;
}