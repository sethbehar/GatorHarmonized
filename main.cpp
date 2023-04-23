#include "Artist.h"
#include "Graph.h"
#include "CSV.h"

int main() {

    CsvParser parser("C:/Users/jakem/Desktop/music.csv");
    vector<vector<string>> csv = parser.getData();
    vector<Artist> artists;


    for (int i = 0; i < csv.size(); i++) {
        Artist artist(csv[i][2], csv[i][6], csv[i][0], csv[i][1], csv[i][5], csv[i][8]);
        artists.push_back(artist);
    }

    AdjacencyMatrix matrix(artists);
    matrix.populateMatrixWithScores(matrix);

    /*DEBUG THE MATRIX
     * for (int i = 0; i < artists.size(); i++) {
        for (int j = 0; j < artists.size(); j++) {
            std::cout << matrix.getScore(i, j) << " ";
        }
        std::cout << "\n";
    }*/
    vector<string> result = matrix.Dijkstra("Faiz Ali Faiz");

    for(string s : result){
        std::cout << s << " ";
    }
    return 0;
}
