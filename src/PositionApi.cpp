/* Position API */

#include "PositionApi.h"

using namespace std;

/* @brief Get the latest position
*
*   Will return empty JSON object if no position is available yet
*   meaning that the GNSS has not yet obtained a fix after boot
*
*   @return A JSON object containing the latest position data.
*/
nlohmann::json get_latest_position(){
    string postion_url = "http://" + dashcam::DASHCAM_HOST + ":" + dashcam::DASHCAM_PORT + "/api/1/gnssConcise";
    string request = postion_url + "/latestValid";
    return get_json_from_url(request);
}