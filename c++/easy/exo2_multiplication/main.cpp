#include <chrono>
#include <iostream>
#include <fstream>

using namespace std;
using namespace chrono;

const int MAX_MULTIPLE = 1e5;

string test_file(int number, bool use_endl = false){
    // define file name
    string filename;
    if (use_endl){
        filename = "multiple_of_" + to_string(number) + "_endl.txt";
    } else {
        filename = "multiple_of_" + to_string(number) + ".txt";
    }

    // compute benchmark
    auto start = high_resolution_clock::now();
    ofstream file(filename);

    for (int i = 0; i <= MAX_MULTIPLE; i++) {
        file << i * number;
        if (use_endl) {
            file << endl;
        } else {
            file << '\n';
        }
    }

    file.close();
    auto end = high_resolution_clock::now();

    // return timing
    return to_string(duration_cast<microseconds>(end-start).count()) + " [µs]";
}

int main(){
    // get a valid number from the user
    printf("\nPlease enter a number: ");
    int number;
    while(!(cin >> number)){
        printf("Please enter a valid number: ");
        cin.clear(); // reopen cin, the queue
        cin.ignore(1000, '\n'); // throw away current queue
    }

    // compute multiple benchmarks
    cout << "\t endl    : " << test_file(number, true) << endl;
    cout << "\t no endl : " << test_file(number) << endl << endl;
    return 0;

    /*
        Explanations:
        - endl force the writing of the buffer
        - its like writing : file << '\n' << flush;
        - flush simply trigger a costly systemcall
    */
}
