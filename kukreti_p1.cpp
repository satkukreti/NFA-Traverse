#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <regex>
#include <set>
#include <map>

using namespace std;

set<int> astates;
map<int, vector<vector<char>>> nfa;
vector<vector<int>> combinations;

void helper(string istring, int start, vector<int> path);

int main(int argc, char** argv) {
    if(argc != 3) {
        cerr << "Please provide proper arguments formatted 'input_file.txt' 'input_string" << endl;
        return 1;
    }
    
    //start state
    int start;
    
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Failed to open the file" << endl;
        return 1;
    }
    string line;
    while(getline(inputFile, line)){
	    //delimits the words
        vector<string> tokens;
        stringstream storage(line);
	string cmds;
        while(storage >> cmds){		
            tokens.push_back(cmds);
        }

        if(tokens[0] == "state"){
            string combine;
            for(int i = 2; i < (int)tokens.size(); i++){
                combine += tokens[i];
            }
            regex a ("(accept)");
            regex s ("(start)");
            smatch m;

            if(regex_search(combine, m, a)){
                astates.insert(tokens[1][0]-'0');
            }
            if(regex_search(combine, m, s)){
                start = stoi(tokens[1]);
            }
        } else if(tokens[0] == "transition"){
            vector<char> t2;
            int key = stoi(tokens[1]);
            t2.push_back(tokens[2][0]);
            t2.push_back(tokens[3][0]);
	    nfa[key].push_back(t2);
        } else {
	  cerr << "Invalid commands" << endl;
	  return 1;
	}
    }

    string istring = argv[2];

    if(nfa.find(start) == nfa.end()){
        cerr << "Start state is not specified" << endl;
        return 1;
    }

    vector<int> temp;
    helper(istring, start, temp);

    set<int> rejected;
    set<int> accepted;
    for(int i = 0; i < (int)combinations.size(); i++){
      int size = combinations[i].size()-1;
      if(astates.find(combinations[i][size]) != astates.end()){
	accepted.insert(combinations[i][size]);
      } else {
	rejected.insert(combinations[i][size]);
      }
    }

    if(accepted.size() > 0){
      cout << "accept";
      for(int i:accepted){
	cout << " " << i;
      }
      cout << endl;
    } else {
      cout << "reject";
      for(int i:rejected){
	cout << " " << i;
      }
      cout << endl;
    }

    inputFile.close();
};

void helper(string istring, int start, vector<int> path){
  path.push_back(start);
  
  if(istring.size() == 0){
    combinations.push_back(path);
    return;
  }
  
  
  char c = istring[0];

  vector<vector<char>> temp = nfa.at(start);

  bool b = false;
  for(int i = 0; i < (int)temp.size(); i++){
    if(c == temp[i][0]){
      b = true;
      start = temp[i][1] - '0';
      helper(istring.substr(1), start, path);
    }
  }
  if(b == false){
    combinations.push_back(path);
  }
  return;
};
