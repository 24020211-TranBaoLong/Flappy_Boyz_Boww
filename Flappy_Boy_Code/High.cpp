
#include "High.h"
#include <limits>
using namespace std;
HighscoreManager::HighscoreManager(const string& filename) : filename(filename), highscore(0)
{
    loadHighscore();
}

int HighscoreManager::getHighscore() const {
    return highscore;
}

void HighscoreManager::saveHighscore(int score) {
    if (score > highscore)
        {
        highscore = score;
        ofstream file(filename);
        if (file.is_open())
        {
            file << highscore;
            file.close();
        }
        }
    }

void HighscoreManager::loadHighscore() {
    ifstream file(filename);
    if (file.is_open()) {
        file >> highscore;
        file.close();
    } else {
            highscore = 0;
         cerr << "Khong the mo file de doc, su dung diem so cao mac dinh la 0: " << filename << endl;
    }
}
