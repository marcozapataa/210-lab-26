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

// function prototypes
vector<long long> reading_race(vector<string>& vec, list<string>& lst, set<string>& st);
vector<long long> sorting_race(vector<string>& vec, list<string>& lst);
vector<long long> inserting_race(vector<string>& vec, list<string>& lst, set<string>& st);
vector<long long> deleting_race(vector<string>& vec, list<string>& lst, set<string>& st);
void display_results(const vector<vector<long long>>& results, const vector<string>& operations);


int main() {

    vector<string> vec;
    list<string> lst;
    set<string> st;

    vector<vector<long long>> results;
    vector<string> operations = {
        "Reading", "Sorting", "Inserting", "Deleting"
    };

    // run races and store results
    results.push_back(reading_race(vec, lst, st));
    results.push_back(sorting_race(vec, lst));
    results.push_back(inserting_race(vec, lst, st));
    results.push_back(deleting_race(vec, lst, st));

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
void display_results(const vector<vector<long long>>& results, const vector<string>& operations) {

    cout << "\nRace Results (nanoseconds)\n";

    cout << left << setw(15) << "Operation"
         << setw(15) << "Vector"
         << setw(15) << "List"
         << setw(15) << "Set" << endl;

     for (size_t i = 0; i < results.size(); i++) {
        cout << left << setw(15) << operations[i];

        for (size_t j = 0; j < results[i].size(); j++) {
            cout << setw(15) << results[i][j];
        }

        cout << endl;
    }
}