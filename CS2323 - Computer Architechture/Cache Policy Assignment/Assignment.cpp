#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include <limits>
#include <map>

using namespace std;

/*
    Written by - SHRAIYSH VAISHAY on 21/09/2018 at 21:31
    This program is supposed to be compiled using g++-7.
    This has been tested to work properly on g++-7.3.0
*/

void traverse_deque(deque<string> my_vector) {
    // cout << "Traversing" << endl;
    for(deque<string>::iterator i = my_vector.begin(); i != my_vector.end(); i++) {
        cout << "\t|" << *i;
    }
    cout << "\t|" << endl;
    // cout << "Travresal ends"<<endl;
}
void traverse_vector(vector<string> my_vector) {
    // cout << "Traversing" << endl;
    for(vector<string>::iterator i = my_vector.begin(); i != my_vector.end(); i++) {
        cout << "\t|" << *i;
    }
    cout << "\t|" << endl;
    // cout << "Travresal ends"<<endl;
}

string LRU(vector<string> address_accesses, string output_file_name, int cache_size) {
    int capacity_misses = 0, compulsory_misses = 0;
    set<string> addresses_already_fetched;
    deque<string> cache;
    string output_string = "";
    for(vector<string>::iterator i = address_accesses.begin(); i!=address_accesses.end(); ++i) {
        int indexOfI = find(cache.begin(), cache.end(), *i) - cache.begin();
        if(indexOfI < cache.size()) {
            output_string += "HIT\n";
            rotate(cache.begin(), cache.begin() + indexOfI, cache.begin() + indexOfI + 1);
        }
        else {
            output_string += "MISS\n";
            if(cache.size() >= cache_size) {
                cache.pop_back();
            }
            cache.push_front(*i);
            if(addresses_already_fetched.find(*i) != addresses_already_fetched.end()) {
                capacity_misses++;
            }
            else {
                compulsory_misses++;
                addresses_already_fetched.insert(*i);
            }
        }
    }
    string output_string_HEAD = "TOTAL_ACCESSES = " + to_string(address_accesses.size()) + "\n"
                        + "TOTAL_MISSES = " + to_string(compulsory_misses + capacity_misses) + "\n"
                        + "COMPULSORY_MISSES = " + to_string(compulsory_misses) + "\n"
                        + "CAPACITY_MISSES = " + to_string(capacity_misses) + "\n";
    output_string = output_string_HEAD + output_string;
    return output_string;
}

string FIFO(vector<string> address_accesses, string output_file_name, int cache_size) {
    string output_string = "";
    int capacity_misses = 0, compulsory_misses = 0;
    set<string> addresses_already_fetched;
    deque<string> cache;
    for(vector<string>::iterator i = address_accesses.begin(); i != address_accesses.end(); ++i) {
        if(find(cache.begin(), cache.end(), *i) != cache.end()) {
            // HIT
            output_string += "HIT\n";
        }
        else {
            // MISS
            output_string += "MISS\n";
            if(cache.size() >= cache_size) {
                cache.pop_back();
            }
            cache.push_front(*i);
            if(addresses_already_fetched.find(*i) != addresses_already_fetched.end()) {
                capacity_misses++;
            }
            else {
                compulsory_misses++;
                addresses_already_fetched.insert(*i);
            }
        }
    }
    string output_string_HEAD = "TOTAL_ACCESSES = " + to_string(address_accesses.size()) + "\n"
                        + "TOTAL_MISSES = " + to_string(compulsory_misses + capacity_misses) + "\n"
                        + "COMPULSORY_MISSES = " + to_string(compulsory_misses) + "\n"
                        + "CAPACITY_MISSES = " + to_string(capacity_misses) + "\n";
    output_string = output_string_HEAD + output_string;
    return output_string;
}

void traverse_map(map<string, int> cache) {
    map <string, int> :: iterator itr; 
    cout << "Size = " << cache.size() << endl;
    cout << "\tKEY\tELEMENT\n"; 
    for (itr = cache.begin(); itr != cache.end(); ++itr) 
    { 
        if(itr->second != numeric_limits<int>::max()) {
            cout << '\t' << itr->first << '\t' << itr->second << '\n'; 
        }
    } 
    cout << endl;
}

string OPTIMAL(vector<string> address_accesses, string output_file_name, int cache_size) {
    int compulsory_misses = 0, capacity_misses = 0;
    map<string, int> cache;
    map<string, int>::iterator it;
    string output_string = "";
    set<string> addresses_already_fetched;
    for(vector<string>::iterator i = address_accesses.begin(); i != address_accesses.end(); i++) {
        // Updating current distance to the next occurence
        for(map<string, int>::iterator cache_itr = cache.begin(); cache_itr != cache.end(); cache_itr++) {
            cache[cache_itr->first] = cache_itr->second - 1;
        }
        it = cache.find(*i);
        if(it != cache.end()) {
            // HIT
            // In this case, since it->first = *i is accessed and is found in the map, it's distance
            // should be zero i.e. it->second = 0
            output_string += "HIT\n";
            // Now the distance of *i has to be updated. First set it to infinite.
            cache[*i] = numeric_limits<int>::max();
            vector<string>::iterator j = i + 1;
            // j will store ptr to next occurence of i if there is any.
            while(j != address_accesses.end() && (*i).compare(*j) != 0) {
                j++;
            }
            if(j!=address_accesses.end()) {
                // Update distance
                cache[*i] = j-i;
            }
        }
        else {
            // MISS
            output_string += "MISS\n";
            if(cache.size() == cache_size) {
                // If cache.size() == cache_size, it means that cache is full. Replace the farthest occuring element
                int max_distance = 0;
                map<string, int>::iterator found_at;
                bool found = false;
                for(it = cache.begin(); it != cache.end(); it++) {
                    if(it->second > max_distance || !found) {
                        // If there is no element that is farthest, it will take first element that does not
                        // occur in the list anymore as it's distance will be infinity.
                        max_distance = it->second;
                        found_at = it;
                        found = true;
                    }
                }
                if(found) {
                    cache.erase(found_at);
                }
            }
            // Adding new entry to cache
            vector<string>::iterator j = i + 1;
            cache[*i] = std::numeric_limits<int>::max();
            while(j != address_accesses.end() && (*i).compare(*j) != 0) {
                j++;
            }
            if(j!=address_accesses.end()) {
                cache[*i] = j-i;
            }
            // MISS Count handling
            if(addresses_already_fetched.find(*i) != addresses_already_fetched.end()) {
                capacity_misses++;
            }
            else {
                compulsory_misses++;
                addresses_already_fetched.insert(*i);
            }
        }
    }
    string output_string_HEAD = "TOTAL_ACCESSES = " + to_string(address_accesses.size()) + "\n"
                        + "TOTAL_MISSES = " + to_string(compulsory_misses + capacity_misses) + "\n"
                        + "COMPULSORY_MISSES = " + to_string(compulsory_misses) + "\n"
                        + "CAPACITY_MISSES = " + to_string(capacity_misses) + "\n";
    output_string = output_string_HEAD + output_string;
    return output_string;
}

int main(int argc, char *argv[]) {
    if(argc < 4 || atoi(argv[3])<=0) return 1;          // 1. Invalid length of args
    string in_file_name = argv[2];
    string address, output_file_name;
    vector<string> address_accesses;
    vector<int> left_distance;
    vector<int> right_distance;
    int left = 0, right = 1;
    ifstream input_file;
    input_file.open(argv[2]);
    if(!input_file) return 1;       // Input File could not open
    // Reading from file
    while(input_file >> address) {
        address_accesses.push_back(address);

    }
    input_file.close();
    string output_string;
    if(strcmp(argv[1], "LRU") == 0) {
        // Follow LRU replacement
        output_file_name = "CS17BTECH11050_LRU_" + in_file_name.substr(0, in_file_name.length() - 4) + "_" + argv[3] + ".out";
        output_string = LRU(address_accesses, output_file_name, atoi(argv[3]));
    }
    else if(strcmp(argv[1], "FIFO") == 0) {
        output_file_name = "CS17BTECH11050_FIFO_" + in_file_name.substr(0, in_file_name.length() - 4) + "_" + argv[3] + ".out";
        output_string = FIFO(address_accesses, output_file_name, atoi(argv[3]));
        // Follow FIFO replacement
    }
    else if(strcmp(argv[1], "OPTIMAL") == 0) {
        output_file_name = "CS17BTECH11050_OPTIMAL_" + in_file_name.substr(0, in_file_name.length() - 4) + "_" + argv[3] + ".out";
        output_string = OPTIMAL(address_accesses, output_file_name, atoi(argv[3]));
        // Follow OPTIMAL replacement
    }
    else return 1;                  // 2. Invalid replacement Policy
    // For g++-5 converting string to char array
    char output_file_name_char_array[output_file_name.size() + 1];
    output_file_name.copy(output_file_name_char_array, output_file_name.size() + 1);
    output_file_name_char_array[output_file_name.size()] = '\0';

    // Open output file

    ofstream output_file;
    output_file.open(output_file_name_char_array);
    if(!output_file) return 1;       // Could not open output file.
    output_file << output_string;
    output_file.close();
    return 0;
}