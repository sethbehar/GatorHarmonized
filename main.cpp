#include "Artist.h"
#include "Graph.h"
#include "CSV.h"

int main() {
    //COP3530 Final Prject: "Gator Harmonized!"
    //By: Jacob Moss, Seth Behar, Daniel Wajsbrot.

   /* SOURCES CITED AND HELPFUL RESOURCES!
    * Lambda Expressions in C++ - https://www.youtube.com/watch?v=MH8mLFqj-n8&ab_channel=CodeBeauty
    * Learning GUI's in C++ - https://www.youtube.com/watch?v=LF1cI7zeFm4&ab_channel=Simplilearn
    * Help Understanding Prim's - https://www.youtube.com/watch?v=rqlVROP5ua8&ab_channel=Simplilearn
    * Creating Pairs in C++ - https://www.youtube.com/watch?v=Puaw04YmtrI&ab_channel=CppNuts
    * Professor Kapoor's Lecture Slides and Supplementary Study Guides on Graphs (Module 8)
    * */

    CsvParser parser("C:/Users/jakem/Desktop/music.csv");
    vector<vector<string>> csv = parser.getData();
    vector<Artist> artists;

    for (int i = 0; i < csv.size(); i++) {
        Artist artist(csv[i][2], csv[i][6], csv[i][0], csv[i][1], csv[i][5], csv[i][8]);
        artists.push_back(artist);
    }

    AdjacencyMatrix matrix(artists);
    matrix.populateMatrixWithScores(matrix);

    cout << "Dijkstra's" << endl;

    vector<string> result = matrix.Dijkstra("U2");

    for(string s : result){
        std::cout << s << " ";
    }

    cout << "\nPRIMS" << endl;

    vector<string> temp = matrix.Prims("U2");

    for(string s : temp){
        std::cout << s << " ";
    }
    return 0;
}
