/* Template for Here Plugin */

#include "HerePlugin.h"

using namespace std;

int main(int argc, char *argv[]) {

    // parse debug flag
    bool debug = false;
    if (argc < 2){
        debug = false;
    }
    else {
        // convert string "true" to bool true
        // everything else if interpretted as false
        istringstream(argv[2]) >> boolalpha >> debug;
    }

    int counter = 0;
    while (counter < 10) {
        cout << "Loop iteration: " << counter << endl;

        // get position data
        getPosition();

        // upload something
        networkInteraction("https://example.com/upload", "data to upload");

        // download something
        // nlohmann::json json_data = get_json_from_url(LANDMARKS_GET_URL);

        // get info
        cout << "Getting info data..." << endl;
        nlohmann::json info_data = get_json_from_url(INFO_URL);
        cout << "Downloaded info data: " << info_data.at("ssid").get<std::string>() << endl;
        cout << "Downloaded info data: " << info_data.at("api_version").get<std::string>() << endl;

        // get map features

        // upload something

        counter++;
        this_thread::sleep_for(chrono::seconds(5));
    }

	return 0;
}