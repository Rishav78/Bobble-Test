#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Node {
    bool endofword;
    map<char, Node*> childrens;
    int wt;
};

void insert_word(Node *root, string word, int wt) {
    Node *ptr = root;
    for(int j=0;j<word.length();j++) {
        map<char, Node*>::iterator itr = ptr->childrens.find(word[j]);
        if(itr != ptr->childrens.end()) {
            ptr = itr->second;
        } else {
            Node *newchildren = new Node;
            if(j == word.length()-1) {
                newchildren->endofword = true;
                newchildren->wt = wt;
            }
            ptr->childrens.insert(pair<char, Node*>(word[j], newchildren));
            ptr = newchildren;
        }
    }
}

void read_file(Node *root, FILE *file) {
    char word[100];
    int wt;
    while(fscanf(file, "%s %d", word, &wt) != EOF) {
        string s = "";
        int i=0;
        while(word[i] != '\0') {
            if((word[i] >= 'a' && word[i] <= 'z') || (word[i]>='A' && word[i]<='Z')) {
                s += word[i];
            }
            i++;
        }
        insert_word(root, s, wt);
    }
}

void get_suggestions(Node *root, map<int, string> &s, string str="") {
    if(root->endofword) {
        s.insert({ root->wt, str });
    }
    for(auto itr = root->childrens.begin(); itr != root->childrens.end(); itr++) {
        get_suggestions(itr->second, s, str+itr->first);
    }
}

void complete_word(Node *root, string word, map<int, string> &s, int i=0, int match=0, string str="") {
    if(i == word.length()) {
        get_suggestions(root, s, str);
        return;
    }

    auto itr = root->childrens.find(word[i]);

    if(itr == root->childrens.end()) {
        complete_word(root, word, s, i+1, match, str+itr->first);
    } else {
        complete_word(itr->second, word, s, i+1, match+1, str+itr->first);
    }
}

int main(int argc, char** argv) {
    FILE *file = fopen(argv[1], "r");
    Node *root = new Node;
    map<int, string> suggestions;
    read_file(root, file);
    complete_word(root, argv[2], suggestions);
    auto itr = suggestions.begin();
    int i=0;
    for(i=0; itr!=suggestions.end() && i<5; i++, itr++) {
        cout << itr->second << " ";
    }
    for(;i<5;i++) {
        cout << "word" << i+1 << " ";
    }
    cout << endl;
    return 0;
}