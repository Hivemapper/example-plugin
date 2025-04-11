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
        std::cout << "1) post file" << std::endl;
        std::string content = R"({"message": "Hello, World."})";
        bool post_file_result = post_json_file("test.txt", content);
        std::cout << "post file success: " << std::boolalpha << post_file_result << std::endl;

        std::cout << "2) post file with directory prefix" << std::endl;
        std::string content2 = landmarks_2.dump();
        bool post_dir_file_result = post_json_file("/map1/map1.txt", content2);
        std::cout << "post file with directory prefix succcess: " << std::boolalpha << post_dir_file_result << std::endl;

        std::cout << "3) list cached files" << std::endl;
        nlohmann::json list_files_result = list_cached_files();
        std::cout << list_files_result << std::endl;

        std::cout << "4) check if test.txt file exists" << std::endl;
        bool check_file_result = check_file_exists("test.txt");
        std::cout << "test.txt file exists: " << std::boolalpha << check_file_result << std::endl;

        std::cout << "5) check if imaginary.txt file exists" << std::endl;
        bool check_file_result2 = check_file_exists("imaginary.txt");
        std::cout << "imaginary.txt file exists: " << std::boolalpha << check_file_result2 << std::endl;

        std::cout << "6) delete file" << std::endl;
        bool delete_file_result = delete_file("test.txt");
        std::cout << "delete file success: " << delete_file_result << std::endl;

        std::cout << "7) purge cache" << std::endl;
        bool purge_cache_result = purge_cache();
        std::cout << "purge_cache_result: " << purge_cache_result << std::endl;

        // NETWORK REQUEST EXAMPLES
        std::cout << "==================== NETWORK INTERFACE EXAMPLES ====================" << std::endl;

        // Convert 5 last landmarks JSON to a string for posting.
        std::string postBody = landmarks_2.dump();

        nlohmann::json targetHeaders;
        targetHeaders["Content-Type"] = "application/json";

        std::string postUrl = "http://httpbin.org/post";

        std::cout << "1) Posting landmarks to " << postUrl << std::endl;
        std::string response = fetch(postUrl, "POST", postBody, targetHeaders);

        try {
            auto respJson = nlohmann::json::parse(response);
            if (respJson.contains("json") && respJson["json"] == landmarks_2) {
                std::cout << "Landmarks posted successfully (verified by echoed response)." << std::endl;
            } else {
                std::cout << "POST response received, but it did not match the sent landmarks." << std::endl;
            }
        }
        catch (std::exception &ex) {
            std::cerr << "Error parsing response JSON: " << ex.what() << std::endl;
        }

        std::cout << "==============================================================" << std::endl;
        counter++;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

	return 0;
}