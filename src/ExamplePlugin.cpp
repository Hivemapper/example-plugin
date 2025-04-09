/* Template for Example Plugin */

#include "ExamplePlugin.h"

int main(int argc, char *argv[]) {

    int counter = 0;
    while (counter < 10) {
        std::cout << "Loop iteration: " << counter << std::endl;

        // POSITION API EXAMPLES
        std::cout << "==================== POSITION API EXAMPLES ====================" << std::endl;

        // get_latest_position
        std::cout << "1) get latest position" << std::endl;
        nlohmann::json postion_1 = get_latest_position();
        std::cout << "position_1: " << postion_1 << std::endl;


        // LANDMARKS API EXAMPLES
        std::cout << "==================== LANDMARKS API EXAMPLES ====================" << std::endl;

        // get_latest_landmark
        std::cout << "1) get latest landmark" << std::endl;
        nlohmann::json landmarks_1 = get_latest_landmark();
        std::cout << "landmarks_1: " << landmarks_1 << std::endl;


        // get_last_n_landmarks()
        std::cout << "2) get last n (5) landmarks" << std::endl;
        nlohmann::json landmarks_2 = get_last_n_landmarks(5);
        std::cout << "landmarks_2: " << landmarks_2 << std::endl;


        // get_landmarks_by_timestamp()
        std::cout << "3) get all landmarks (limited to latest 5000)" << std::endl;
        nlohmann::json landmarks_3 = get_landmarks_by_timestamp();
        std::cout << "landmarks_3 size: " << landmarks_3.size() << std::endl;

        std::cout << "4) get landmarks since timestamp" << std::endl;
        nlohmann::json landmarks_4 = get_landmarks_by_timestamp(1744153670000);
        std::cout << "landmarks_4 size: " << landmarks_4.size() << std::endl;

        std::cout << "5) get landmarks since timestamp until timestamp" << std::endl;
        nlohmann::json landmarks_5 = get_landmarks_by_timestamp(1744153670000, 1744153671000);
        std::cout << "landmarks_5 size: " << landmarks_5.size() << std::endl;

        std::cout << "6) get landmarks until timestamp" << std::endl;
        nlohmann::json landmarks_6 = get_landmarks_by_timestamp(-1, 1744153669000);
        std::cout << "landmarks_6 size: " << landmarks_6.size() << std::endl;


        // get_landmarks_after_id()
        std::cout << "7) get landmarks after id" << std::endl;
        nlohmann::json landmarks_7 = get_landmarks_after_id(597);
        std::cout << "landmarks_7 size: " << landmarks_7.size() << std::endl;


        // FILE API EXAMPLES
        std::cout << "==================== FILE API EXAMPLES ====================" << std::endl;
        std::cout << "8) post file" << std::endl;
        std::string content = "Hello, World.";
        // bool post_file_result = post_file("test.txt", content);
        // std::cout << "post_file_result: " << post_file_result << std::endl;

        std::cout << "9) post file with directory prefix" << std::endl;
        std::string content2 = R"({"message": "Hello, World!"})";
        // bool post_dir_file_result = post_file("/map1/map1.txt", content2);
        // std::cout << "post_dir_file_result: " << post_dir_file_result << std::endl;

        std::cout << "10) delete file" << std::endl;
        bool delete_file_result = delete_file("test.txt");
        std::cout << "delete_file_result: " << delete_file_result << std::endl;

        std::cout << "11) purge cache" << std::endl;
        bool purge_cache_result = purge_cache();
        std::cout << "purge_cache_result: " << purge_cache_result << std::endl;

        std::cout << "==============================================================" << std::endl;
        counter++;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

	return 0;
}