/* Hivemapper Api */

#include "HivemapperApi.h"

using namespace std;

string LANDMARKS_GET_URL = "http://192.168.0.10:5000/api/1/landmarks/";
// string LANDMARKS_GET_URL = "http://192.168.197.55:5000/api/1/landmarks/";
string INFO_URL = "http://192.168.0.10:5000/api/1/info/";
// string INFO_URL = "http://192.168.197.55:5000/api/1/info/";
string LANDMARKS_POST_URL = "https://beemaps....";
string STORAGE_DIR = "/data/landmarks_plugin/";

void getPosition() {
    // Placeholder function to get position data
    cout << "Getting position data..." << endl;
}

void networkInteraction(string url, string data) {
    // Placeholder function to simulate network interaction
    cout << "Interacting with network at URL: " << url << endl;
    cout << "Data: " << data << endl;
}

// Helper for writing curl response into a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Main function to GET JSON from a URL
nlohmann::json get_json_from_url(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the write function and buffer
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Optional: follow redirects
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            throw std::runtime_error("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
        }
    } else {
        throw std::runtime_error("Failed to initialize CURL");
    }

    cout << "Downloaded JSON data: " << readBuffer << endl;

    return nlohmann::json::parse(readBuffer);
}