#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <ostream>

using namespace std;

bool commonWordCheck(const string& word){
    unordered_set<string> commonWords = {"a", "i", "and", "the", "to", "for", "they", "as", "their"};
    return commonWords.find(word) != commonWords.end();
}
string cleanedWord(const string& word){ 
    string cleanword;
    for (char ch : word){
        if (isalnum(ch)){
            cleanword += tolower(ch);
        }
    }
    if (cleanword.empty() || commonWordCheck(cleanword)){
        return "";
    }

    return cleanword;
}

void invertedIndex(const string &filename, const string &outfilename){
    fstream inFile(filename);
    if (!inFile){
        cerr << "Cant open file.\n";
        return;
    }
    unordered_map<string, vector<int> > index;
    string word;
    int pos = 0; //start index at 0

    while (inFile >> word){ 
        string clean = cleanedWord(word); 
        if (!clean.empty()){ 
            index[clean].push_back(pos);
        }
        pos++;
    }
    inFile.close();

    ofstream outFile(outfilename);
    if (!outFile){
        cerr << " Cant open the file.\n";
        return;
    }
    outFile << "{" << endl;

    auto it = index.begin();
    while (it != index.end()){
        outFile << " \"" << it->first << "\": [";
        for (size_t i = 0; i < it->second.size(); ++i){
            outFile << it->second[i];
            if (i < it->second.size() - 1){
                outFile << ", ";
            }
        }
        outFile << "]";
        ++it;
        outFile << endl;
    }
    
    outFile << "}" << endl;
    outFile.close();
    
}

int main(){
    string inputfilename;
    string outputfilename;
    cout << "Enter filename you wanna read: ";
    cin >> inputfilename;
    cout <<"Enter filename you wanna output to: ";
    cin >> outputfilename;

    invertedIndex(inputfilename, outputfilename);
    cout << "Inverted index written to " << outputfilename << " from " << inputfilename << endl;
    return 0;
}