
#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class HighscoreManager {
public:
    HighscoreManager(const string& filename);
    int getHighscore() const;
    void saveHighscore(int score);

private:
    string filename;
    int highscore;
    void loadHighscore();
};

#endif
