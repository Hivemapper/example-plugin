/* Template for Here Plugin */

#include "HerePlugin.h"

using namespace std;

int main(int argc, char *argv[]) {

    cout << "first step" << endl;

    int counter = 0;
    while (counter < 1) {
        cout << "Loop iteration: " << counter << endl;

        // POSITION API EXAMPLES
        cout << "==================== POSITION API EXAMPLES ====================" << endl;
        // get_latest_position
        cout << "1) get latest position" << endl;
        nlohmann::json postion_1 = get_latest_position();
        cout << "position_1: " << postion_1 << endl;

        // LANDMARKS API EXAMPLES
        cout << "==================== LANDMARKS API EXAMPLES ====================" << endl;
        // get_latest_landmark
        cout << "1) get latest landmark" << endl;
        nlohmann::json landmarks_1 = get_latest_landmark();
        cout << "landmarks_1: " << landmarks_1 << endl;

        // get_last_n_landmarks()
        cout << "2) get last n (5) landmarks" << endl;
        nlohmann::json landmarks_2 = get_last_n_landmarks(5);
        cout << "landmarks_2: " << landmarks_2 << endl;

        // get_landmarks_by_timestamp()
        cout << "3) get all landmarks (limited to latest 5000)" << endl;
        nlohmann::json landmarks_3 = get_landmarks_by_timestamp();
        cout << "landmarks_3 size: " << landmarks_3.size() << endl;

        cout << "4) get landmarks since timestamp" << endl;
        nlohmann::json landmarks_4 = get_landmarks_by_timestamp(1672531199);
        cout << "landmarks_4 size: " << landmarks_4.size() << endl;

        cout << "5) get landmarks since timestamp until timestamp" << endl;
        nlohmann::json landmarks_5 = get_landmarks_by_timestamp(1672531199, 1672531200);
        cout << "landmarks_5 size: " << landmarks_5.size() << endl;

        cout << "6) get landmarks until timestamp" << endl;
        nlohmann::json landmarks_6 = get_landmarks_by_timestamp(-1, 1672531200);
        cout << "landmarks_6 size: " << landmarks_6.size() << endl;

        // get_landmarks_after_id()
        cout << "7) get landmarks after id" << endl;
        nlohmann::json landmarks_7 = get_landmarks_after_id(597);
        cout << "landmarks_7 size: " << landmarks_7.size() << endl;

        // // get info
        // cout << "Getting info data..." << endl;
        // nlohmann::json info_data = get_json_from_url(INFO_URL);
        // cout << "info data " << endl << info_data << endl;
        // cout << "Downloaded info data: " << info_data.at("ssid").get<std::string>() << endl;
        // cout << "Downloaded info data: " << info_data.at("api_version").get<std::string>() << endl;

        counter++;
        this_thread::sleep_for(chrono::seconds(5));
    }

	return 0;
}