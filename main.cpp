#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

const int SIMULATIONS = 15;

// function prototypes
vector<long long> reading_race(vector<string>& vec, list<string>& lst, set<string>& st);
vector<long long> sorting_race(vector<string>& vec, list<string>& lst);
vector<long long> inserting_race(vector<string>& vec, list<string>& lst, set<string>& st);
vector<long long> deleting_race(vector<string>& vec, list<string>& lst, set<string>& st);
void display_results(const long long results[SIMULATIONS][4][3], const vector<string>& operations);


int main() {

    vector<string> vec;
    list<string> lst;
    set<string> st;

    long long results[SIMULATIONS][4][3] = {};
    vector<string> operations = {
        "Reading", "Sorting", "Inserting", "Deleting"
    };

    // run races and store results
    for (int sim = 0; sim < SIMULATIONS; sim++) {

        vec.clear();
        lst.clear();
        st.clear();

        vector<long long> reading = reading_race(vec, lst, st);
        vector<long long> sorting = sorting_race(vec, lst);
        vector<long long> inserting = inserting_race(vec, lst, st);
        vector<long long> deleting = deleting_race(vec, lst, st);

        for (int i = 0; i < 3; i++) {
            results[sim][0][i] = reading[i];
            results[sim][1][i] = sorting[i];
            results[sim][2][i] = inserting[i];
            results[sim][3][i] = deleting[i];

        }
    }

    // display results
    display_results(results, operations);
    

    return 0;
}

// read codes into each container
vector<long long> reading_race(vector<string>& vec, list<string>& lst, set<string>& st) {
    ifstream fin("codes.txt");
    if (!fin) {
        cout << "Error opeing codes.txt" << endl;
        exit(1);
    }

    string code;
    long long vecTime, listTime, setTime;

    // start timing
    auto start = high_resolution_clock::now();

    // read code into vector
    while (fin >> code) {
        vec.push_back(code);
    }

    // end timing
    auto end = high_resolution_clock::now();

    // calculate duration
    auto duration = duration_cast<nanoseconds>(end - start);
    vecTime = duration.count();

    fin.close();

    // reopen file
    fin.open("codes.txt");

    // start timing
    start = high_resolution_clock::now();

    // read into list
    while (fin >> code) {
        lst.push_back(code);
    }

    // end timing
    end = high_resolution_clock::now();

    // calculate duration
    duration = duration_cast<nanoseconds>(end - start);
    listTime = duration.count();

    fin.close();

    // reopen file
    fin.open("codes.txt");

    // start timing
    start = high_resolution_clock::now();

    // read code into set
    while (fin >> code) {
        st.insert(code);
    }

    // end timing
    end = high_resolution_clock::now();

    // calulate duration
    duration = duration_cast<nanoseconds>(end - start);
    setTime = duration.count();

    fin.close();

    return {vecTime, listTime, setTime};
}

// sort vector and list
vector<long long> sorting_race(vector<string>& vec, list<string>& lst) {

    // start timing
    auto start = high_resolution_clock::now();

    // sort vector
    sort(vec.begin(), vec.end());

    // end timing
    auto end = high_resolution_clock::now();

    // calculate duration
    auto duration = duration_cast<nanoseconds>(end - start);
    long long vecTime = duration.count();

    // start timing
    start = high_resolution_clock::now();

    // sort list
    lst.sort();

    // end timing
    end = high_resolution_clock::now();

    // calculate duration
    duration = duration_cast<nanoseconds>(end - start);
    long long listTime = duration.count();

    // set is already sorted
    return {vecTime, listTime, -1};
}

// inserting TESTCODE into each container
vector<long long> inserting_race(vector<string>& vec, list<string>& lst, set<string>& st) {

    // find the middle vector
    int middle = vec.size() / 2;

    // start timing
    auto start = high_resolution_clock::now();

    // instert code into middle
    vec.insert(vec.begin() + middle, "TESTCODE");

    // end timing
    auto end = high_resolution_clock::now();

    // calculate duration
    auto duration = duration_cast<nanoseconds>(end - start);
    long long vecTime = duration.count();

    // find middle of list
    auto it = lst.begin();
    advance(it, lst.size() / 2);

    // start timing
    start = high_resolution_clock::now();

    // insert code into middle
    lst.insert(it, "TESTCODE");

    // end timing
    end = high_resolution_clock::now();

    // calculate duration
    duration = duration_cast<nanoseconds>(end - start);
    long long listTime = duration.count();

    //start timing
    start = high_resolution_clock::now();

    // insert code into set
    st.insert("TESTCODE");

    // end timing
    end = high_resolution_clock::now();

    // calculate duration
    duration = duration_cast<nanoseconds>(end - start);
    long long setTime = duration.count();

    return {vecTime, listTime, setTime};
}

// delete from middle element from each container
vector<long long> deleting_race(vector<string>& vec, list<string>& lst, set<string>& st) {

    // find middle of vector
    int middle = vec.size() / 2;

    // start timing
    auto start = high_resolution_clock::now();

    // remove the element
    vec.erase(vec.begin() + middle);

    // end timing
    auto end = high_resolution_clock::now();

    // calculate duration
    auto duration = duration_cast<nanoseconds>(end - start);
    long long vecTime = duration.count();

    // find the middle of list
    auto it = lst.begin();
    advance(it, lst.size() / 2);

    // start timing
    start = high_resolution_clock::now();

    // remove the element
    lst.erase(it);

    // end timing
    end = high_resolution_clock::now();

    // calculate duration
    duration = duration_cast<nanoseconds>(end - start);
    long long listTime = duration.count();

    // find middle of set
    auto setIt = st.begin();
    advance(setIt, st.size() / 2);

    // start timing
    start = high_resolution_clock::now();

    // remove the element
    st.erase(setIt);

    // end timing
    end = high_resolution_clock::now();

    // calculate duration
    duration = duration_cast<nanoseconds>(end - start);
    long long setTime = duration.count();

    return {vecTime, listTime, setTime};
}

// display results in a formatted table
void display_results(const long long results[SIMULATIONS][4][3], const vector<string>& operations) {

    cout << "\nRace Results (nanoseconds)\n";

    cout << left << setw(15) << "Operation"
         << setw(15) << "Vector"
         << setw(15) << "List"
         << setw(15) << "Set" << endl;

     for (int i = 0; i < 4; i++) {
        cout << right << setw(12) << operations[i];

        for (int j = 0; j < 3; j++) {
            long long total = 0;

            for (int k = 0; k < SIMULATIONS; k++) {
                total += results[k][i][j];
            }
                
            cout << setw(12) << total / SIMULATIONS;

        }
        cout << endl;
    }
}