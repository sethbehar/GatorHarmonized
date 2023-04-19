#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Artist.h"
#include "CSV.h"

using namespace std;

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

