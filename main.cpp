#include "Artist.h"
#include "Graph.h"
#include "CSV.h"


int main() {

    CsvParser parser("music.csv");
    vector<vector<string>> csv = parser.getData();
    vector<Artist> artists;


    for (int i = 0; i < csv.size(); i++) {
        Artist artist(csv[i][2], csv[i][6], csv[i][0], csv[i][1], csv[i][5], csv[i][8]);
        artists.push_back(artist);
        //cout << artist.familiarity << endl;
    }

    AdjacencyMatrix matrix(artists);
    matrix.populateMatrixWithScores(matrix);
    
    for (int i = 0; i < artists.size(); i++) {
        for (int j = 0; j < artists.size(); j++) {
            std::cout << matrix.getScore(i, j) << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
