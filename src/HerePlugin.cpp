/* Template for Here Plugin */

#include "HerePlugin.h"

using namespace std;

int main(int argc, char *argv[]) {

    int counter = 0;
    while (counter < 10) {
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
        nlohmann::json landmarks_4 = get_landmarks_by_timestamp(1744153670000);
        cout << "landmarks_4 size: " << landmarks_4.size() << endl;

        cout << "5) get landmarks since timestamp until timestamp" << endl;
        nlohmann::json landmarks_5 = get_landmarks_by_timestamp(1744153670000, 1744153671000);
        cout << "landmarks_5 size: " << landmarks_5.size() << endl;

        cout << "6) get landmarks until timestamp" << endl;
        nlohmann::json landmarks_6 = get_landmarks_by_timestamp(-1, 1744153669000);
        cout << "landmarks_6 size: " << landmarks_6.size() << endl;


        // get_landmarks_after_id()
        cout << "7) get landmarks after id" << endl;
        nlohmann::json landmarks_7 = get_landmarks_after_id(597);
        cout << "landmarks_7 size: " << landmarks_7.size() << endl;


        // FILE API EXAMPLES
        cout << "==================== FILE API EXAMPLES ====================" << endl;
        cout << "8) post file" << endl;
        std::string content = "Hello, World.";
        // bool post_file_result = post_file("test.txt", content);
        // cout << "post_file_result: " << post_file_result << endl;

        cout << "9) post file with directory prefix" << endl;
        std::string content2 = R"({"message": "Hello, World!"})";
        // bool post_dir_file_result = post_file("/map1/map1.txt", content2);
        // cout << "post_dir_file_result: " << post_dir_file_result << endl;

        cout << "10) delete file" << endl;
        bool delete_file_result = delete_file("test.txt");
        cout << "delete_file_result: " << delete_file_result << endl;

        cout << "11) purge cache" << endl;
        bool purge_cache_result = purge_cache();
        cout << "purge_cache_result: " << purge_cache_result << endl;

        cout << "==============================================================" << endl;
        counter++;
        this_thread::sleep_for(chrono::seconds(5));
    }

	return 0;
}