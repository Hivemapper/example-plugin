/* File API */

#ifndef FILE_API_H
#define FILE_API_H

#include <iostream>
#include <string>
#include <fstream>

#include <curl/curl.h>
#include <nlohmann/json.hpp>

#include "hivecpp/Utils.h"

bool delete_file(const std::string& fileName);

bool purge_cache();

#endif // FILE_API_H

