#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Node {
    map<char, Node*> childrens;
    bool endofword = false;
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

void deserilize(Node *root, FILE *file) {
    char word[100];
    while(fscanf(file, "%s", word) == 1) {
        insert_word(root, word);
    }
}

void create_tree(Node *root) {
    int n;
    cin >> n;
    for(int i=0;i<n;i++) {
        string word;
        Node *ptr = root;
        cin >> word;
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
}

void print_tree(Node *root, string str="") {
    if(root->endofword) {
        cout << str << endl;
    }
    for(auto itr = root->childrens.begin(); itr != root->childrens.end(); itr++) {
        print_tree(itr->second, str+itr->first);
    }
}

void serilize(Node *root, FILE *file, string str="") {
    if(root->endofword) {
        fprintf(file, "%s\n", str.c_str());
    }
    for(auto itr = root->childrens.begin(); itr != root->childrens.end(); itr++) {
        serilize(itr->second, file, str+itr->first);
    }
}

int main(int argc, char** argv) {
    Node *root = new Node;
    string argument = argv[1];
    if(argument == "load") {

        FILE *file = fopen(argv[2], "r");
        deserilize(root, file);
        print_tree(root);

    } else if (argument == "create") {

        FILE *write = fopen(argv[3], "a");
        FILE *read = fopen(argv[2], "r");
        deserilize(root, read);
        serilize(root, write);

    }
}



















// Node *createNode(char data) {
//     Node *root = new Node;
//     root->data = data;
//     return root;
// }

// Node *insert(Node *root, char data) {
//     if(!root) return createNode(data);
//     if(root->data < data) root->left = insert(root->left, data);
//     else root->right = insert(root->right, data);
//     return root;
// }

// void create_tree(Node **rootptr) {
//     Node *root = *rootptr;
//     int n;
//     cin >> n;
//     for(int i=0; i<n; i++) {
//         string str;
//         cin >> str;
//         for(int j=0;j<str.length();j++) {
//             *rootptr = insert(*rootptr, str[j]);
//         }
//     }
// }

// void serialize_tree(Node *root) {
//     FILE *file = fopen("tree.txt", "w");


// }

// int main() {

// }