/* Hivemapper Api */

#pragma once

#include <iostream>
#include <string>

#include <Eigen/Dense>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;

extern string LANDMARKS_GET_URL;
extern string INFO_URL;
extern string LANDMARKS_POST_URL;
extern string STORAGE_DIR;

// Helper for writing curl response into a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);

// Get JSON from URL
nlohmann::json get_json_from_url(const std::string& url);

void getPosition();

void networkInteraction(string url, string data);
