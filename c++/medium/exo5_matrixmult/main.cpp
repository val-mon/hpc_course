#include <iostream>
#include <chrono>
#include <cassert>

using namespace std;
using namespace chrono;

class Matrix {
    public:
        int* data;
        int size;

        // constructor
        Matrix(int* _data, int _size){
            data = _data;
            size = _size;
        }

        // destructor
        ~Matrix(){
            delete[] data;
        }

        // helper
        void print(){
            cout << "\nMATRIX:" << endl;

            int len = size*size;
            for (int i = 0; i < len; i++){
                int n = data[i];
                if (n >= 0){
                    cout << "+" << n << " ";
                }
                else{
                    cout << n << " ";
                }
                if ((i+1) % size == 0){cout << "\n";}
            }
        }
};

Matrix generate_squared_matrix(int size){
    int len = size*size;
    int* data = new int[len]{0}; // new for heap allocation

    for (int i = 0; i < len; i++){
        int rdm = rand() % 3;
        int sign = ((rand() % 10) > 5) ? -1 : 1;
        data[i] = rdm * sign;
    }

    return Matrix(data, size);
}

Matrix matrix_product(const Matrix& m1, const Matrix& m2){
    assert(m1.size == m2.size);

    int size = m1.size;
    Matrix res = Matrix(new int[size*size]{0}, size);

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            double tot = 0;
            for (int e = 0; e < size; e++){
                tot += m1.data[i*size + e] * m2.data[e*size + j];
            }
            res.data[i*size + j] = tot;
        }
    }
    return res;
}


int main(){
    double test_sizes[3] = {
        5e2,
        1e3,
        2e3,
    };
    Matrix m1_ref = generate_squared_matrix(test_sizes[0]);
    Matrix m2_ref = generate_squared_matrix(test_sizes[0]);

    auto ref_start = high_resolution_clock::now();
    matrix_product(m1_ref, m2_ref);
    auto ref_end = high_resolution_clock::now();
    double ref_time = duration_cast<milliseconds>(ref_end-ref_start).count();

    int i = 0;
    for (double s : test_sizes){
        Matrix m1 = generate_squared_matrix(s);
        Matrix m2 = generate_squared_matrix(s);

        auto start = high_resolution_clock::now();
        matrix_product(m1, m2);
        auto end = high_resolution_clock::now();

        double t = duration_cast<milliseconds>(end-start).count();
        i++;
        double ratio = t/ref_time;

        cout << "\tsize: " << s;
        cout << "\t\ttime [ms]: ";
        cout << t;
        cout << "\t\tratio: ";
        cout << ratio << endl;
    }
    
    return 0;
}
