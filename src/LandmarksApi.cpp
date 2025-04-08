/* Landmarks Api */

#include "LandmarksApi.h"

using namespace std;

// string LANDMARKS_GET_URL = "http://192.168.0.10:5000/api/1/landmarks/";
string LANDMARKS_GET_URL = "http://192.168.197.55:5000/api/1/landmarks";
// string INFO_URL = "http://192.168.0.10:5000/api/1/info/";
string INFO_URL = "http://192.168.197.55:5000/api/1/info/";
string LANDMARKS_POST_URL = "https://beemaps....";
string STORAGE_DIR = "/data/landmarks_plugin/";

/* @brief Get the latest landmark
*
*   Retrieves the latest (last inserted) observations and landmarks by their rowid.
*
*   @return A JSON object containing the latest landmark data.
*/
nlohmann::json get_latest_landmark(){
    string request = LANDMARKS_GET_URL + "/latest";
    return get_json_from_url(request);
}

/* @brief Get the last n landmarks
*
*   Retrieves the last n landmarks (in descending order based on their internal id)
*   along with the most recent associated observation timestamp.
*
*   @param n The number of landmarks to retrieve.
*   @return A JSON object containing the last n landmarks.
*/
nlohmann::json get_last_n_landmarks(int n){
    string request = LANDMARKS_GET_URL + "/last/" + to_string(n);
    return get_json_from_url(request);
}

/* @brief Get landmarks with timestamps in a range
*
*   Retrieves landmarks with timestamps in the specified range.
*   If no landmarks are found, the endpoint falls back to returning the last 5000 landmarks.
*
*   @param since_timestamp The lower bound (inclusive) for the unix timestamp of the landmarks.
*   @param until_timestamp The upper bound (inclusive) for the unix timestamp of the landmarks.
*   @return A JSON object containing the landmark data.
*/
nlohmann::json get_landmarks_by_timestamp(long since_timestamp, long until_timestamp){
    string request = LANDMARKS_GET_URL;
    if (since_timestamp != -1){
        request += "?since=" + to_string(since_timestamp);
    }
    if (since_timestamp != -1 && until_timestamp != -1){
        request += "&until=" + to_string(until_timestamp);
    }
    else if (until_timestamp != -1){
        request += "?until=" + to_string(until_timestamp);
    }
    return get_json_from_url(request);
}

/* @brief Get landmark starting with id (inclusive)
*
*   Retrieves the landmark with the specified id and its associated observation timestamp.
*   If no landmark is found with the given id, the endpoint falls back to returning the last
*   5000 landmarks.
*
*   @param id The id of the landmark to retrieve.
*   @return A JSON object containing the landmark data.
*/
nlohmann::json get_landmarks_after_id(long id){
    string request = LANDMARKS_GET_URL + "/" + to_string(id);
    return get_json_from_url(request);
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

    // cout << "Downloaded JSON data: " << readBuffer << endl;

    return nlohmann::json::parse(readBuffer);
}

