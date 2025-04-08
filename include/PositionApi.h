/* Position API */

#ifndef POSITION_API_H
#define POSITION_API_H


#include <iostream>
#include <string>

#include <nlohmann/json.hpp>

#include "Utils.h"

using namespace std;

/* @brief Get the latest position
*
*   Will return empty JSON object if no position is available yet
*   meaning that the GNSS has not yet obtained a fix after boot
*
*   @return A JSON object containing the latest position data.
*/
nlohmann::json get_latest_position();

#endif // POSITION_API_H