//
// Created by jakem on 4/19/2023.
//

#ifndef GATORHARMONIZED_CSV_H
#define GATORHARMONIZED_CSV_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class CsvParser {
private:
    vector<vector<string>> data;
public:
    CsvParser(string filename) {
        ifstream file(filename);

        if (!file) {
            cerr << "Failed to open file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> row;
            string field;

            while (getline(ss, field, ',')) {
                row.push_back(field);
            }

            data.push_back(row);
        }

        file.close();
    }

    void printData() {
        for (vector<string> row : data) {
            for (string field : row) {
                cout << field << "\t";
            }
            cout << endl;
        }
    }

    vector<vector<string>> getData() {
        return data;
    }


};

#endif //GATORHARMONIZED_CSV_H
