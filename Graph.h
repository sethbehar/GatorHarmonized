#include <vector>
#include "Artist.h"

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

        // Convert familiarity and hotness to floats
        float famA1 = 0.0;
        float famA2 = 0.0;
        float hotA1 = 0.0;
        float hotA2 = 0.0;
        try {
            famA1 = stof(A1.familiarity);
            famA2 = stof(A2.familiarity);
            hotA1 = stof(A1.hottness);
            hotA2 = stof(A2.hottness);
        }
        catch (const std::invalid_argument& e) {
            // Handle the exception
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

};
