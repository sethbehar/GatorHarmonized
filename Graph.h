#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include "Artist.h"

using namespace std;

struct Edge {
    Artist* a;
    Artist* b;
    float weight;
};

class EdgeComparator {
public:
    bool operator()(const Edge& a, const Edge& b) {
        return a.weight > b.weight;
    }
};

class MinimumSpanningTree {
public:
    MinimumSpanningTree(vector<Artist*>& artists) {
        int n = artists.size();
        vector<vector<float>> similarityMatrix(n, vector<float>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    //float similarityScore = CalculateSimilarity(artists[i], artists[j]);
                    //similarityMatrix[i][j] = similarityScore;
                    cout << artists[i]->familiarity << endl;
                }
            }
        }

        set<int> visitedNodes;
        priority_queue<Edge, vector<Edge>, EdgeComparator> pq;

        visitedNodes.insert(0);

        for (int i = 0; i < n; i++) {
            if (i != 0) {
                Edge e;
                e.a = artists[0];
                e.b = artists[i];
                e.weight = similarityMatrix[0][i];
                pq.push(e);
            }
        }

        while (visitedNodes.size() < n) {
            Edge e = pq.top();
            pq.pop();

            if (visitedNodes.find(getIndex(artists, e.a)) == visitedNodes.end() || visitedNodes.find(getIndex(artists, e.b)) == visitedNodes.end()) {
                visitedNodes.insert(getIndex(artists, e.a));
                visitedNodes.insert(getIndex(artists, e.b));
                minimumSpanningTree.push_back(e);
                int nodeToCheck;

                if (visitedNodes.find(getIndex(artists, e.a)) == visitedNodes.end()) {
                    nodeToCheck = getIndex(artists, e.a);
                }
                else {
                    nodeToCheck = getIndex(artists, e.b);
                }

                for (int i = 0; i < n; i++) {
                    if (visitedNodes.find(i) == visitedNodes.end()) {
                        Edge newEdge;
                        newEdge.a = artists[nodeToCheck];
                        newEdge.b = artists[i];
                        newEdge.weight = similarityMatrix[nodeToCheck][i];
                        pq.push(newEdge);
                    }
                }
            }
        }
    }

    vector<Edge> getMinimumSpanningTree() {
        return minimumSpanningTree;
    }

private:
    vector<Edge> minimumSpanningTree;

    double CalculateSimilarity(Artist* A1, Artist* A2) {

        /*Our algorithm for calculating similaty scores is simple:
         * There are three factors that contribute, familiarity score, hotness score, and genre.
         * The maximum score is one.
         * If the genres are the same, the Artists automatically gain 0.4 on their score.
         * We felt that genre is the most important aspect, so it will be worth the most points.
         * Next we will compare familiarity, which can maximum add 0.35 points to the score regarding how familiar each artist is.
         * Lastly we can compare artist hotness which will add a maximum of 0.25 points to the score.
         * */

         //First, we need to convert familiarity and hotness to double values.
        double famA1 = stod(A1->familiarity);
        double famA2 = stod(A2->familiarity);
        double hotA1 = stod(A1->hottness);
        double hotA2 = stod(A2->hottness);

        //Next we will calculate the genre score.
        double genreScore = 0;

        //Will hold each word in the genre of A1.
        vector<string> words;

        //Parse the gnere by spaces.
        string s = A1->genre;
        stringstream ss(s);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }

        //Now see if A2 has the genre of A1 within it.
        bool contains = false;
        string temp = A2->genre;
        for (int i = 0; i < words.size(); i++) {
            if (temp.find(words[i]) != 0) {
                contains = true;
            }
        }
        //If the genre is contained in A2
        if (contains) {
            genreScore += 0.4;
        }

        //Next we need to calculate the familiarity scores using our algorithm.
        //Our method will prevent famScore from rising over the 0.35 threshold.
        double famScore = 0;
        if (famA1 > famA2) {
            famScore = 0.35 * (1 + ((famA2 / famA1) * 0.5));
        }
        else {
            famScore = 0.35 * (1 + ((famA1 / famA2) * 0.5));
        }

        //Lastly we need to calculate the hotness scores using our algorithm.

        //We will be using the same method
        double hotScore = 0;
        if (hotA1 > hotA2) {
            hotScore = 0.25 * (1 + ((hotA2 / hotA1) * 0.3));
        }
        else {
            hotScore = 0.25 * (1 + ((hotA1 / hotA2) * 0.3));
        }

        //Add all three score togethers.
        double score = genreScore + famScore + hotScore;

        //Finally return the score to be used when crafting the adjacency matrix.
        return score;
    }

    int getIndex(vector<Artist*>& artists, Artist* a) {
        for (int i = 0; i < artists.size(); i++) {
            if (artists[i] == a) {
                return i;
            }
        }

        return -1;
    }
};
