/* File API */

#include "FileApi.h"

bool delete_file(const std::string& fileName) {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    char* escapedName = curl_easy_escape(curl, fileName.c_str(), 0);
    if (!escapedName) {
        curl_easy_cleanup(curl);
        return false;
    }

    std::string url = "http://" + dashcam::DASHCAM_HOST + ":" + dashcam::DASHCAM_PORT + "/api/1/file/?name=" + std::string(escapedName);
    curl_free(escapedName);

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    cout << endl;

    return (res == CURLE_OK);
}

bool purge_cache() {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    std::string url = "http://" + dashcam::DASHCAM_HOST + ":" + dashcam::DASHCAM_PORT + "/api/1/file/purge";
    // cout << "purge url:" << url << endl;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    cout << endl;


    return (res == CURLE_OK);
}