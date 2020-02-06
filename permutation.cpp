#include <iostream>
#include <vector>

using namespace std;

void permutation(vector<string> keywords, vector<string> &ov, int n=0, string str="") {

    if ( n == keywords.size() ) {
        ov.push_back(str);
        return;
    }

    for(int j=0;j<keywords[n].length();j++) {
        permutation(keywords, ov, n+1, str+keywords[n][j]);
    }

}

vector<string> read_file(FILE *file) {
    string str;
    vector<string> inputs;
    char ch = getc(file);
    while (ch != EOF) {
        if (ch == '\n') {
            inputs.push_back(str);
            str = "";
        }
        if ((ch >= 'a' && ch <= 'z') || (ch>='A' && ch<='Z')) {
            str += ch;
        }
        ch = getc(file);
    }
    if(str != "")
        inputs.push_back(str);
    return inputs;
}

int main(int argc, char** argv) {
    FILE *file = fopen(argv[1], "r");
    vector<string> inputvector = read_file(file), outputvector;
    // for(int i=0;i<inputvector.size();i++) {
    //     cout << inputvector[i] << endl;
    // }
    permutation(inputvector, outputvector);
    for(int i=0;i<outputvector.size();i++) {
        cout << outputvector[i];
        if(i < outputvector.size()-1) {
            cout << ", ";
        }
    }
    cout << endl;
}
