#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Node {
    bool endofword;
    map<char, Node*> childrens;
};

void insert_word(Node *root, string word) {
    Node *ptr = root;
    for(int j=0;j<word.length();j++) {
        map<char, Node*>::iterator itr = ptr->childrens.find(word[j]);
        if(itr != ptr->childrens.end()) {
            ptr = itr->second;
        } else {
            Node *newchildren = new Node;
            if(j == word.length()-1) {
                newchildren->endofword = true;
            }
            ptr->childrens.insert(pair<char, Node*>(word[j], newchildren));
            ptr = newchildren;
        }
    }
}

void read_file(Node *root, FILE *file) {
    char word[100];
    while(fscanf(file, "%s", word) == 1) {
        insert_word(root, word);
    }
}

// void insert_words(Node *root, vector<string> words) {
//     for(int i=0;i<words.size();i++) {
//         insert_word(root, words[i]);
//     }
// }

int main(int argc, char** argv) {
    FILE *file = fopen(argv[1], "r");
    Node *root = new Node;
    read_file(root, )
}