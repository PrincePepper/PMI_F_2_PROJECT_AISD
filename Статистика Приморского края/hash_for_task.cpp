#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

bool comp(pair<string, int> a, pair<string, int> b){
    return a.second > b.second;
}

class Chain{
private:
    int key;
    pair<string, int> value;
    Chain *next;
public:
    Chain(int key, pair<basic_string<char>, long long int> value){
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }


    int getKey(){
        return key;
    }

    pair<string, int> getValue() {
        return value;
    }


    void setValue(pair<string, int> value) {
        this->value = value;
    }

    Chain *getNext() {
        return next;
    }

    void setNext(Chain *next) {
        this->next = next;
    }
};

class Hash{
    Chain *table[10]{};

    static int HashFunction(int num){//остаток от деления
        if (num > 1000)
            return 0;
        else if (num > 500)
            return 1;
        else if (num > 100)
            return 2;
        else if (num > 50)
            return 3;
        else if (num > 20)
            return 4;
        else if (num > 10)
            return 5;
        else if (num > 1)
            return 6;
        return 7;
    }

public:
    Hash(){
        for(auto & i : table){
            i = nullptr;
        }
    }

    void push(const string& region, int num){
        int hashNumber = HashFunction(num);
        auto *number = new Chain(hashNumber, make_pair(region, num));

        Chain *place = table[hashNumber];
        if (place == nullptr){
            table[hashNumber] = number;
            return;
        }
        while(place->getNext() != nullptr){
            place = place->getNext();
        }
        place->setNext(number);
    }

    pair<string ,int> find(const string& region, int num){
        int hashNumber = HashFunction(num);
        Chain *result = table[hashNumber];
        if (!result){
            return make_pair(nullptr, 0);
        }
        while(result->getValue().second != num){
            if (!result->getNext()){
                return make_pair(nullptr, 0);
            }
            result = result->getNext();
        }
        return result->getValue();
    }

    void pop(const string& region, int num){
        int hashNumber = HashFunction(num);
        Chain *result = table[hashNumber];
        if (!result){
            return;
        }
        if (result->getValue().second == num && result->getValue().first == region){
            table[hashNumber] = result->getNext();
            delete result;
            return;
        }
        while(result->getValue().second != num || result->getValue().first != region){
            if (!result->getNext()){
                return;
            }
            if (result->getNext()->getValue().second == num && result->getNext()->getValue().first == region)
                break;
            result = result->getNext();
        }
        result->setNext(result->getNext()->getNext());
    }

    vector<pair<string, int>> NumsOfHash(){
        vector<pair<string, int>> countries;
        for (auto & i : table){
            if (i != nullptr){
                Chain *num = i;
                while(num != nullptr){
                    countries.push_back(num->getValue());
                    num = num->getNext();
                }
            }
        }
        return countries;
    }

};


int main(){
    ifstream fin("input.txt");
    Hash hashTable;
    int a;
    fin >> a;
    for (int i = 0; i < a; i++){
        string tmp1;
        int tmp2;
        fin >> tmp1 >> tmp2;
        hashTable.push(tmp1, tmp2);
    }
    ofstream fout("output.txt");
    auto table = hashTable.NumsOfHash();
    cout << "sort [region] or [num]:";
    string choice;
    cin >> choice;
    if (choice == "region")
        sort(table.begin(), table.end());
    else
        sort(table.begin(), table.end(), comp);
    for (const auto& i : table){
        fout << i.first << " " << i.second << endl;
    }

    return 0;
}