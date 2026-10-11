#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

// Simple key-value store using std::map for demonstration
// In a real implementation, this would be replaced with a B+ Tree on file storage

class FileStorageBPT {
private:
    map<string, set<int>> data;

public:
    void insert(const string& index, int value) {
        data[index].insert(value);
    }

    void remove(const string& index, int value) {
        auto it = data.find(index);
        if (it != data.end()) {
            it->second.erase(value);
            if (it->second.empty()) {
                data.erase(it);
            }
        }
    }

    vector<int> find(const string& index) {
        auto it = data.find(index);
        if (it != data.end()) {
            return vector<int>(it->second.begin(), it->second.end());
        }
        return vector<int>();
    }
};

int main() {
    FileStorageBPT db;
    int n;
    cin >> n;
    cin.ignore(); // ignore newline after n
    
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        
        stringstream ss(line);
        string command;
        ss >> command;
        
        if (command == "insert") {
            string index;
            int value;
            ss >> index >> value;
            db.insert(index, value);
        } else if (command == "delete") {
            string index;
            int value;
            ss >> index >> value;
            db.remove(index, value);
        } else if (command == "find") {
            string index;
            ss >> index;
            vector<int> results = db.find(index);
            
            if (results.empty()) {
                cout << "null" << endl;
            } else {
                for (int j = 0; j < results.size(); j++) {
                    if (j > 0) cout << " ";
                    cout << results[j];
                }
                cout << endl;
            }
        }
    }
    
    return 0;
}