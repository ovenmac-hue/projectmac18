#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string f,
                        vector<string>& n,
                        vector<int>& s,
                        vector<char>& g){
    ifstream filetext(f);
    string textline;
    while(getline(filetext,textline)){
        size_t pos = textline.find(':');

        string name = textline.substr(0, pos);
        string scorePart = textline.substr(pos + 1);

        int s1, s2, s3;
        sscanf(scorePart.c_str(), "%d %d %d", &s1, &s2, &s3);

        int total = s1 + s2 + s3;

        n.push_back(name);
        s.push_back(total);
        g.push_back(score2grade(total));
    }

    filetext.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n";

    string line;
    getline(cin, line);

    // แยกคำสั่งกับ key
    size_t pos = line.find(' ');

    if(pos == string::npos){
        command = line;
        key = "";
    }else{
        command = line.substr(0, pos);
        key = line.substr(pos + 1);
    }
}


void searchName(vector<string>&n,
                vector<int>& s,
                vector<char>& g,
                string k){
    cout << "---------------------------------\n";
    bool found = false;
    for (unsigned i = 0 ; i < n.size();i++){
        if(toUpperStr(n[i]) == toUpperStr(k) ){
            cout << n[i] << "'s score = " << s[i] << endl ;
            cout << n[i] << "'s grade = " << g[i] << endl ;
            found = true;
            break;
        }
    }
    if (!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
    
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    cout << "---------------------------------\n";
    bool found = false;
    char target = key[0];
    for (unsigned i = 0 ; i < grades.size();i++){
        if(grades[i] == target){
            cout << names[i] << " " << "(" << scores[i] << ")" << endl ;
            found = true;
        }
    }
    if (!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";

}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
