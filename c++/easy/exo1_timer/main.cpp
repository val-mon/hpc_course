#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;

int main(){
    auto start = high_resolution_clock::now();
    cout << "Hello World !" << endl;
    auto end = high_resolution_clock::now();

    cout << "Time: " << duration_cast<microseconds>(end-start).count() << " [µs]" << endl;
    return 0;
}
