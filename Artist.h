//
// Created by jakem on 4/19/2023.
//
#ifndef GATORHARMONIZED_ARTIST_H
#define GATORHARMONIZED_ARTIST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Artist {
public:
    string id;
    string name;
    string familiarity;
    string hottness;
    string longitude;
    string genre;

    Artist(string id, string name, string familiarity, string hottness, string longitude, string genre) {
        this->id = id;
        this->name = name;
        this->familiarity = familiarity;
        this->hottness = hottness;
        this->longitude = longitude;
        this->genre = genre;
    }

    void printArtist() {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Familiarity: " << familiarity << endl;
        cout << "Hottness: " << hottness << endl;
        cout << "Longitude: " << longitude << endl;
        cout << "Genre: " << genre << endl;
    }

    string getId() { return id; }
    string getName() { return name; }
    string getFamiliarity() { return familiarity; }
    string getHottness() { return hottness; }
    string getLongitude() { return longitude; }

};

#endif //GATORHARMONIZED_ARTIST_H
