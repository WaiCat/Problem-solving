#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Prediction {
    int bulb1;
    char color1;
    int bulb2;
    char color2;
    int bulb3;
    char color3;
};

bool isValid(const vector<char>& bulbs, const vector<Prediction>& predictions) {
    for (const auto& pred : predictions) {
        int match_count = 0;
        if (bulbs[pred.bulb1 - 1] == pred.color1) match_count++;
        if (bulbs[pred.bulb2 - 1] == pred.color2) match_count++;
        if (bulbs[pred.bulb3 - 1] == pred.color3) match_count++;
        if (match_count < 2) return false;
    }
    return true;
}

bool backtrack(vector<char>& bulbs, const vector<Prediction>& predictions, int index) {
    if (index == bulbs.size()) {
        return isValid(bulbs, predictions);
    }
    bulbs[index] = 'R';
    if (backtrack(bulbs, predictions, index + 1)) return true;
    bulbs[index] = 'B';
    if (backtrack(bulbs, predictions, index + 1)) return true;
    return false;
}

int main() {
    ifstream infile("show.inp");
    ofstream outfile("show.out");
    int test_cases;
    infile >> test_cases;

    while (test_cases--) {
        int n, m;
        infile >> n >> m;
        vector<Prediction> predictions(m);

        for (int i = 0; i < m; i++) {
            infile >> predictions[i].bulb1 >> predictions[i].color1 
                   >> predictions[i].bulb2 >> predictions[i].color2 
                   >> predictions[i].bulb3 >> predictions[i].color3;
        }

        vector<char> bulbs(n, 'B');  // Initializing all bulbs to 'B'
        if (backtrack(bulbs, predictions, 0)) {
            outfile << 1 << endl;
        } else {
            outfile << -1 << endl;
        }
    }

    infile.close();
    outfile.close();
    return 0;
}
