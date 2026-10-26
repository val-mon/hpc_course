#include <iostream>
#include <chrono>
#include <vector>
#include <cassert>

using namespace std;
using namespace chrono;

vector<float> generate_vector(double size){
    vector<float> resultVector;
    // srand(time(0));
    for (int i = 0; i < size; i++){
        float rdm = rand() % 10;
        float sign = ((rand() % 10) > 5) ? -1 : 1;
        resultVector.push_back(rdm * sign);
    }
    return resultVector;
}

void printVector(vector<float> v){
    cout << "\nVECTOR" << endl;
    for (float e : v){
        cout << "\t";
        cout << e << endl;
    }
}

/// complexity: O(n) | n = lenght
double dotProduct(vector<float> v1, vector<float> v2){
    double tot = 0;
    int lenght = size(v1);

    assert(size(v2) == lenght);

    for (int i = 0; i < lenght; i++){
        tot += v1[i]*v2[i];
    }

    return tot;
}

int main(){
    double sizes[4] = {
        1e6,
        1e7,
        5e7,
        1e8,
    };

    vector<float> v1_ref = generate_vector(sizes[0]);
    vector<float> v2_ref = generate_vector(sizes[0]);

    auto ref_start = high_resolution_clock::now();
    dotProduct(v1_ref, v2_ref);
    auto ref_end = high_resolution_clock::now();
    double ref_time = duration_cast<microseconds>(ref_end-ref_start).count();

    int i = 0;
    for (double s : sizes){
        vector<float> v1 = generate_vector(s);
        vector<float> v2 = generate_vector(s);

        auto start = high_resolution_clock::now();
        dotProduct(v1, v2);
        auto end = high_resolution_clock::now();

        double t = duration_cast<microseconds>(end-start).count();
        i++;
        double ratio = t/ref_time*100;


        cout << "\tsize: " << s;
        cout << "\ttime [µs]: ";
        cout << t;
        cout << "\tratio: ";
        cout << ratio << "%" << endl;
    }
    return 0;
}
