#include <vector>
#include<set>
#include "Artist.h"
#include <limits>
#include <algorithm>

class AdjacencyMatrix {
private:
    std::vector<Artist> artists;
    std::vector<std::vector<double>> matrix;

public:
    AdjacencyMatrix(std::vector<Artist> artists) {
        this->artists = artists;
        int num_artists = artists.size();
        matrix.resize(num_artists, std::vector<double>(num_artists, 0.0));
    }

    //This function populates our matrix with initial scores.
    void populateMatrixWithScores(AdjacencyMatrix& matrix) {
        int num_artists = matrix.artists.size();
        for (int i = 0; i < num_artists; i++) {
            for (int j = i + 1; j < num_artists; j++) {
                float score = computeSimilarityScore(matrix.artists[i], matrix.artists[j]);
                matrix.setScore(i, j, score);
            }
        }
    }

    void setScore(int i, int j, double score) {
        matrix[i][j] = score;
        matrix[j][i] = score;
    }

    float getScore(int i, int j) {
        return matrix[i][j];
    }

    float computeSimilarityScore(Artist A1, Artist A2) {

        //First, we must convert familiarity and hotness to floats.
        //These will store familiarity and hot scores of each artist.
        float famA1 = 0.0;
        float famA2 = 0.0;
        float hotA1 = 0.0;
        float hotA2 = 0.0;

        //Try catch block to make sure no exceptions are thrown.
        try {
            famA1 = stof(A1.familiarity);
            famA2 = stof(A2.familiarity);
            hotA1 = stof(A1.hottness);
            hotA2 = stof(A2.hottness);
        }
        catch (const std::invalid_argument& e) {
            //Handle the exceptions
            return 0;
        }

        // Compute genre similarity score
        string genre1 = A1.genre;
        string genre2 = A2.genre;
        float genreScore = 0;
        if (A1.genre == A2.genre) {
            genreScore = 0.4;
        }

        // Compute familiarity score
        float famScore = 0.0;
        if (famA1 > famA2) {
            famScore = 0.35 * (1 + ((famA2 / famA1) * 0.5));
        }
        else {
            famScore = 0.35 * (1 + ((famA1 / famA2) * 0.5));
        }

        // Compute hotness score
        float hotScore = 0.0;
        if (hotA1 > hotA2) {
            hotScore = 0.25 * (1 + ((hotA2 / hotA1) * 0.3));
        }
        else {
            hotScore = 0.25 * (1 + ((hotA1 / hotA2) * 0.3));
        }

        // Compute final similarity score as a weighted sum of the three scores
        float score = genreScore + famScore + hotScore;
        return score;
    }

    //This is the Dijkstra's Algorithm function. It will return the 3 most similar artists to the artist input.
    vector<string> Dijkstra(string artistName){
        //Stores the number of artists in the matrix.
        int num_artists = artists.size();
        //Will store our final result.
        vector<string> result;

        //First, we need to find the starting index and the node to start at.
        int index = -1;
        for (int i = 0; i < artists.size(); i++) {
            if (artists[i].name == artistName) {
                index = i;
                break;
            }
        }
        if(index == -1) {
            //We will return the empty set if the artist does not exist within the graph.
            return result;
        }

        //For the next step of Dijkstra's we must initialize the distance and visited vectors
        int size = matrix.size();
        //Use the limits class to set each distance to "infinity" as taught in lecture.
        std::vector<double> dist(size, numeric_limits<double>::max());
        //Default all visited to false, as no nodes have been visited yet,
        std::vector<bool> visited(size, false);

        //Set distance of starting node to 0
        dist[index] = 0.0;

        //Now we iterate through all of the nodes to find shortest paths
        for (int i = 0; i < size - 1; i++) {
            //Now find the node with the minimum distance
            int min_index = -1;
            double min_dist = numeric_limits<double>::max();
            for (int j = 0; j < size; j++) {
                if (!visited[j] && dist[j] < min_dist) {
                    min_index = j;
                    min_dist = dist[j];
                }
            }
            //Set the minimum distance node to visited
            visited[min_index] = true;

            // Update the distances of the neighboring nodes
            for (int i = 0; i < size; i++) {
                if (!visited[i] && matrix[min_index][i] > 0.0 && dist[min_index] != numeric_limits<double>::max()) {
                    double new_dist = dist[min_index] + matrix[min_index][i];
                    if (new_dist < dist[i]) {
                        dist[i] = new_dist;
                    }
                }
            }
        }

        //Now we will find the three artists with the shortest distances
        for (int i = 0; i < size; i++) {
            if (i != index && dist[i] != numeric_limits<double>::max()) {
                result.push_back(artists[i].name);
            }
        }
        // Build the result vector with the top 3 most similar artists
        for (int i = 0; i < num_artists; i++) {
            if (i != index) {
                result.push_back(artists[i].name);
            }
        }

        //Finally, we must sort the result vector based on artist's score
        sort(result.begin(), result.end(), [&](const string& a, const string& b) {
            int index_a = find_if(artists.begin(), artists.end(), [&](const Artist& artist) { return artist.name == a; }) - artists.begin();
            int index_b = find_if(artists.begin(), artists.end(), [&](const Artist& artist) { return artist.name == b; }) - artists.begin();
            return dist[index_a] < dist[index_b];
        });

        //And remember to keep only the top three artists
        if (result.size() > 3) {
            for(int i = 0; i < result.size(); i++){
                if(result[i] == artistName){
                    result[i] = artistName;
                }
            }
            //First step is to resize the
            result.resize(100);
            //Now make sure there are no duplicates after cutting down the size.
            //We will use a set to track duplicate values.
            set<string> seen;
            //Return vector will hold our final values.
            vector<string> returnVec;
            for(string name : result){
                //If we have not seen the name, add it to the set and the vector.
                if(seen.count(name) == 0 && name != artistName){
                    seen.insert(name);
                    returnVec.push_back(name);
                }
            }
            result = returnVec;
            result.resize(3);
        }
        return result;
    }
};
