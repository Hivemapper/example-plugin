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

        // get map features

        // upload something

        counter++;
        this_thread::sleep_for(chrono::seconds(5));
    }

	return 0;
}