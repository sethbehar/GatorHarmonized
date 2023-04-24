#include <vector>
#include<set>
#include "Artist.h"
#include <limits>
#include <algorithm>

class AdjacencyMatrix {
private:
    vector<Artist> artists;
    vector<vector<double>> matrix;

public:
    AdjacencyMatrix(vector<Artist> artists) {
        this->artists = artists;
        int num_artists = artists.size();
        matrix.resize(num_artists, vector<double>(num_artists, 0.0));
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
        catch (const invalid_argument& e) {
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
    vector<string> Dijkstra(string artistName) {
        //Stores the number of artists in the matrix.
        int num_artists = artists.size();
        //Will store our final result.
        vector<string> result;
        //Scores will contain the final scores.
        vector<double> scores;
        //First, we need to find the starting index and the node to start at.
        int index = -1;
        for (int i = 0; i < artists.size(); i++) {
            if (artists[i].name == artistName) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            //We will return the empty set if the artist does not exist within the graph.
            return result;
        }

        //For the next step of Dijkstra's we must initialize the distance and visited vectors
        int size = matrix.size();
        //Use the limits class to set each distance to "infinity" as taught in lecture.
        vector<double> dist(size, numeric_limits<double>::max());
        //Default all visited to false, as no nodes have been visited yet,
        vector<bool> visited(size, false);

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
            //First step is to resize the vector
            //No artist has over 20 songs in the database.
            result.resize(20);
            //Now make sure there are no duplicates after cutting down the size using a set.
            set<string> seen;
            //Return vector will hold our final values.
            vector<string> returnVec;
            for (string name : result) {
                //If we have not seen the name, add it to the set and the vector.
                if (seen.count(name) == 0 && name != artistName) {
                    seen.insert(name);
                    returnVec.push_back(name);
                }
            }
            result = returnVec;
            result.resize(3);
        }
        return result;
    }

    //Our next algorithm will be Prim's Algorithm.
    vector<string> Prims(string artistName) {
        //Result will hold our return vector.
        vector<string> result;
        //Find the index of the node containing the artistName, just like in Dijkstra's
        int index = -1;
        for (int i = 0; i < artists.size(); i++) {
            if (artists[i].name == artistName) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            //We will return the empty set if the artist does not exist within the graph, just like in Dijkstra's
            return result;
        }

        //For the first step in Prims, we need to initialize the minimum spanning tree
        //Every parent will be initialized to -1 since we haven't run the algorithm yet.
        vector<int> parent(artists.size(), -1);
        vector<double> key(artists.size(), INT_MAX);
        //This will track which nodes have been pushed into the tree so far.
        vector<bool> contained(artists.size(), false);

        //First, the key of the starting node will be set to 0. The index variable holds the current position of our input.
        key[index] = 0;

        //Now begin building the tree using Prim's algorithm.
        for (int i = 0; i < artists.size() - 1; i++) {
            //Start by finding the node with the minimum key value that is not yet in the MST.
            int minKeyIndex = -1;
            double minKey = INT_MAX;
            for (int j = 0; j < artists.size(); j++) {
                //If the key is not yet in the MST and the key is less than the minimum key value...
                if (!contained[j] && key[j] < minKey) {
                    minKey = key[j];
                    minKeyIndex = j;
                }
            }
            //Make sure to change the nodes boolean value as well.
            contained[minKeyIndex] = true;

            //Now we can update adjacent node values.
            for (int j = 0; j < artists.size(); j++) {
                if (matrix[minKeyIndex][j] != 0 && !contained[j] && matrix[minKeyIndex][j] < key[j]) {
                    parent[j] = minKeyIndex;
                    key[j] = matrix[minKeyIndex][j];
                }
            }
        }

        //Fianlly, we can find the three closest nodes to the starting node in the MST.
        vector<pair<int, double>> distances;
        if (parent.empty() || parent.size() != artists.size()) {
            //If the parent vector is empty or if something went wrong in calculation, return the empty set.
            return result;
        }

        for (int i = 0; i < artists.size(); i++) {
            //Now we check if parent[i] is a valid index, and that it is not the same as the artist's index.
            if (i != index && parent[i] >= 0 && parent[i] < artists.size()) {
                //Store distance between nodes.
                double distance = 0;
                //Set j = i.
                int j = i;
                //Now we also need to check if parent[j] is a valid index, and that it is not the same as the artist's index.
                while (parent[j] != index && parent[j] >= 0 && parent[j] < artists.size()) {
                    distance += matrix[parent[j]][j];
                    j = parent[j];
                }
                if (parent[j] == index && j >= 0 && j < artists.size()) { // check if parent[j] is a valid index
                    distance += matrix[index][j];
                    distances.push_back(make_pair(i, distance));
                }
            }
        }
        //Now we can sort the elements of the distances vector based on the second value of each pair
        sort(distances.begin(), distances.end(), [](const pair<int, double>& a, const pair<int, double>& b) {
            // We are usign a simple lambda function that compares the second value of each pair a and b.
            return a.second < b.second;
            //This will return true if the distance in a is less than the distance in b
            });

        for (int i = 0; i < min((int)distances.size(), 3); i++) {
            //cout << artists[distances[i].first].name << " (distance: " << distances[i].second << ")" << endl;
            result.push_back(artists[distances[i].first].name);
        }
        return result;
    }
};
