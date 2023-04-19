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

class Artist {
public:
    string id;
    string name;
    string familiarity;
    string hottness;
    string longitude;
    string genre;

    Artist(string id, string name, string familiarity, string hottness, string longitude, string genre) {
        this->id = id;
        this->name = name;
        this->familiarity = familiarity;
        this->hottness = hottness;
        this->longitude = longitude;
        this->genre = genre;
    }

    void printArtist() {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Familiarity: " << familiarity << endl;
        cout << "Hottness: " << hottness << endl;
        cout << "Longitude: " << longitude << endl;
        cout << "Genre: " << genre << endl;
    }

    string getId() { return id; }
    string getName() { return name; }
    string getFamiliarity() { return familiarity; }
    string getHottness() { return hottness; }
    string getLongitude() { return longitude; }

};

int main() {
    CsvParser parser("music.csv");
    vector<vector<string>> csv = parser.getData();
    vector<Artist> artists;

    for (int i = 0; i < csv.size(); i++) {
        // Create new artist object, only passing in the values -> id, name, familiarity, hottness, longitude
        Artist artist(csv[i][2], csv[i][6], csv[i][0], csv[i][1], csv[i][5], csv[i][8]);
        artists.push_back(artist);
    }

    for (int i = 0; i < artists.size(); i++) {
        artists[i].printArtist();
        cout << endl;
    }

    return 0;
}
