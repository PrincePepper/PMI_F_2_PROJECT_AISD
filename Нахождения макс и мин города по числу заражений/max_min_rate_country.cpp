#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

vector<pair<float, string>> mass;

int main() {
    ifstream fin("../country_infection_rate.txt");
    ofstream fout("../output_min_or_max.txt");
    int N;
    fin >> N;

    for (int i = 0; i < N; i++) {
        string name_country;
        float rate;
        fin >> name_country >> rate;
        if (name_country.find('_') != -1) {
            name_country[name_country.find('_')] = ' ';
        }
        mass.emplace_back(rate, name_country);
    }
    cout << "min or max?";
    string choice;
    cin >> choice;
    if (choice == "max") {
        make_heap(mass.begin(), mass.end());
    } else make_heap(mass.begin(), mass.end(), greater<>{});
    auto top = mass[0];
    for (int i = 0; i < N; i++) {
        if (mass[i].first == top.first) {
            fout << mass[i].second << " " << mass[i].first << endl;
        }
    }
}