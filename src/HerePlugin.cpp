/* Template for Here Plugin */

#include "HerePlugin.h"

using namespace std;

int main(int argc, char *argv[]) {

    int counter = 0;
    while (counter < 1) {
        cout << "Loop iteration: " << counter << endl;

        // LANDMARKS API EXAMPLES
        // get_latest_landmark
        cout << "1) get latest landmark" << endl;
        nlohmann::json result_1 = get_latest_landmark();
        cout << "result_1: " << result_1 << endl;

        // get_last_n_landmarks()
        cout << "2) get last n (5) landmarks" << endl;
        nlohmann::json result_2 = get_last_n_landmarks(5);
        cout << "result_2: " << result_2 << endl;

        // get_landmarks_by_timestamp()
        cout << "3) get all landmarks (limited to latest 5000)" << endl;
        nlohmann::json result_3 = get_landmarks_by_timestamp();
        cout << "result_3 size: " << result_3.size() << endl;

        cout << "4) get landmarks since timestamp" << endl;
        nlohmann::json result_4 = get_landmarks_by_timestamp(1672531199);
        cout << "result_4 size: " << result_4.size() << endl;

        cout << "5) get landmarks since timestamp until timestamp" << endl;
        nlohmann::json result_5 = get_landmarks_by_timestamp(1672531199, 1672531200);
        cout << "result_5 size: " << result_5.size() << endl;

        cout << "6) get landmarks until timestamp" << endl;
        nlohmann::json result_6 = get_landmarks_by_timestamp(-1, 1672531200);
        cout << "result_6 size: " << result_6.size() << endl;

        // get_landmarks_after_id()
        cout << "7) get landmarks after id" << endl;
        nlohmann::json result_7 = get_landmarks_after_id(597);
        cout << "result_7 size: " << result_7.size() << endl;

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