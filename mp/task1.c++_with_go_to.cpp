#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;
int main() {
    string s = "";
    int count2;
    string ignore[] = {"for", "to", "the", "a", "an"};
    const int IGNORED = 5;
    string line;
    ifstream myfile ("expample.txt");
    if (myfile.is_open()){
        read:
        s += line;
        s += " ";
        if(getline (myfile,line)) {
            goto read;
        }
        myfile.close();
    }
    int currSymb = -1;
    int wordCount = 0;
    countW:
    currSymb++;
    if(s[currSymb] == ' ') {
        wordCount++;
    }
    if(currSymb < s.length()) {
        goto countW;
    }

    int curr = 0;
    currSymb = -1;
    string words[wordCount];
    string currWord = "";

    extract:

    currSymb++;
    if(s[currSymb] == ' ' && currWord != "") {
        count2 = 0;
        check:
        if(ignore[count2] == currWord) {
            currWord = "";
            goto extract;
        }
        count2++;
        if(count2 < IGNORED) {
            goto check;
        }
        words[curr] = currWord;
        currWord = "";
        curr++;
        goto extract;
    }
    if(65 <= s[currSymb] + 0 && 90 >= s[currSymb] + 0) {
        currWord += s[currSymb] + 32;
    } else if (97 <= s[currSymb] + 0 && 122 >= s[currSymb] + 0) {
        currWord += s[currSymb];
    }

    if(currSymb < s.length()) {
        goto extract;
    }

    int count1 = 0;
    string newWords[curr];
    int counters[curr];
    bool exist;
    int size = 0;
    int index = 0;

    count:
    count2 = -1;
    exist = false;

    find:
    count2++;
    if(count2 < size){
        if(words[count1].length() != newWords[count2].length()){
            goto find;
        }
        compare:
        char a = words[count1][index] + 0;
        char b = newWords[count2][index] + 0;
        if(words[count1][index] != newWords[count2][index]) {
            index = 0;
            goto find;
        }
        index++;
        if(index < words[count1].length()) {
            goto compare;
        }
        index = 0;
        exist = true;
    } else if (count2 < size) {
        goto find;
    }
    
    if(exist) {
        counters[count2]++;
    } else {
        newWords[size++] = words[count1];
        counters[size - 1] = 1;
    }
    count1++;
    if(count1 < curr) {
        goto count;
    }
    const int N = size <= 25 ? size : 25;
    string topWords[N];
    int topCount[N];
    int currPos = 0;
    count1 = 0;
    count2 = 0;
    curr=-1;
    
    findpos:
    count1 = 0;
    count2 = 0;
    curr = -1;

    maximizer:
    if(count2 < counters[count1]){
        count2 = counters[count1];
        curr = count1;
    }

    count1++;

    if(count1 < size) {
        goto maximizer;
    }
    topWords[currPos] = newWords[curr];
    topCount[currPos] = counters[curr];
    newWords[curr] = "";
    counters[curr] = 0;
    currPos++;
    if(currPos < N) {
        goto findpos;
    }
    currPos = 0;
    print:
    printf("%s - %d",topWords[currPos].c_str(), topCount[currPos]);
    printf("\n");
    currPos++;
    if(currPos < N) {
        goto print;
    }

    getch();
    return 0;
}

