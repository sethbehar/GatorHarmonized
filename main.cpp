#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Artist.h"
#include "Graph.h"
#include "CSV.h"

using namespace std;

int main() {
    CsvParser parser("music.csv");
    vector<vector<string>> csv = parser.getData();
    vector<Artist*> artists;

    for (int i = 0; i < csv.size(); i++) {
        // Create new artist object, only passing in the values -> id, name, familiarity, hottness, longitude
        Artist* artist = new Artist(csv[i][2], csv[i][6], csv[i][0], csv[i][1], csv[i][5], csv[i][8]);
        artist->id = csv[i][2];
        artist->name = csv[i][6];
        artist->familiarity = csv[i][0];
        artist->hottness = csv[i][1];
        artist->longitude = csv[i][5];
        artist->genre = csv[i][8];


        artists.push_back(artist);
        //artist.printArtist();
    }
    MinimumSpanningTree mst(artists);
    //vector<Edge> minimumSpanningTree = mst.getMinimumSpanningTree();
    float totalWeight = 0;

    /*for (int i = 0; i < minimumSpanningTree.size(); i++) {
        Edge e = minimumSpanningTree[i];
        cout << e.a->getName() << " -- " << e.b->getName() << " : " << e.weight << endl;
        totalWeight += e.weight;
    }
    cout << "Total weight: " << totalWeight << endl;*/
    

    return 0;
}
