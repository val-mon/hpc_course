#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
    // arguments check
    if (argc != 3){
        cerr << "Error: incorrect argements" << endl;
        cerr << "\tUsage: ./run {file_path} {nbr_of_lines}" << endl;
        exit(1);
    }

    int nbr_of_lines;
    try {
        nbr_of_lines = stoi(argv[2]);
        if (nbr_of_lines < 0){
           throw invalid_argument("negative number");
        }
    } catch (const exception &e) {
        cerr << "Error: '" << argv[2] << "' is not a valid number" << endl;
        exit(1);
    }

    // open a file in read mode
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file!" << endl;
        exit(1);
    }

    // read lines from the file
    string line;
    for (int i = 0; i < nbr_of_lines && getline(file, line); i++) {
        cout << line + "\n";
    }
    file.close();

    return 0;
}
