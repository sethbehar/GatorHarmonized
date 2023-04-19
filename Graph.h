//
// Created by jakem on 4/19/2023.
//

#ifndef GATORHARMONIZED_GRAPH_H
#define GATORHARMONIZED_GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Artist.h"
using namespace std;

//We will be implementing the graph using an adjacency matrix, since every node is connected.
struct Graph{
    //Artists and Genre vectors.
    vector<Artist> artists;
    vector<string> genres;
    //Adjacency matrix to hold the edge weights / similarity scores.
    vector<vector<double>> scores;

    Graph(){

    }

    void add(Artist artist){

    }

    double CalculateSimilarity(Artist A1, Artist A2){

        /*Our algorithm for calculating similaty scores is simple:
         * There are three factors that contribute, familiarity score, hotness score, and genre.
         * The maximum score is one.
         * If the genres are the same, the Artists automatically gain 0.4 on their score.
         * We felt that genre is the most important aspect, so it will be worth the most points.
         * Next we will compare familiarity, which can maximum add 0.35 points to the score regarding how familiar each artist is.
         * Lastly we can compare artist hotness which will add a maximum of 0.25 points to the score.
         * */

        //First, we need to convert familiarity and hotness to double values.
        double famA1 = stod(A1.familiarity);
        double famA2 = stod(A2.familiarity);
        double hotA1 = stod(A1.hottness);
        double hotA2 = stod(A2.hottness);

        //Next we will calculate the genre score.
        double genreScore = 0;

        //Will hold each word in the genre of A1.
        vector<string> words;

        //Parse the gnere by spaces.
        string s = A1.genre;
        stringstream ss(s);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }

        //Now see if A2 has the genre of A1 within it.
        bool contains = false;
        string temp = A2.genre;
        for (int i = 0; i < words.size(); i++) {
            if(temp.find(words[i]) != 0){
                contains = true;
            }
        }
        //If the genre is contained in A2
        if(contains){
            genreScore += 0.4;
        }

        //Next we need to calculate the familiarity scores using our algorithm.
        //Our method will prevent famScore from rising over the 0.35 threshold.
        double famScore = 0;
        if (famA1 > famA2){
            famScore = 0.35 * (1 + ((famA2 / famA1) * 0.5));
        }
        else{
            famScore = 0.35 * (1 + ((famA1 / famA2) * 0.5));
        }

        //Lastly we need to calculate the hotness scores using our algorithm.

        //We will be using the same method
        double hotScore = 0;
        if (hotA1 > hotA2) {
            hotScore = 0.25 * (1 + ((hotA2 / hotA1) * 0.3));
        }
        else{
            hotScore = 0.25 * (1 + ((hotA1 / hotA2) * 0.3));
        }

        //Add all three score togethers.
        double score = genreScore + famScore + hotScore;

        //Finally return the score to be used when crafting the adjacency matrix.
        return score;
    }
};

#endif //GATORHARMONIZED_GRAPH_H
