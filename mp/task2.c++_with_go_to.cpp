#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;

int main()
{
    string f = "";
    string ignore[] = {"for", "to", "the", "a", "an"};
    const int IGNORED = 5;
    int count2;
    string line;
    ifstream myfile ("expample.txt");
    if (myfile.is_open()){
        read:
        f+= line;
        f+='\n';
        if(getline(myfile,line)) {
            goto read;
        }
        myfile.close();
    }
    int pagesCount = 0;
    int words = 0;
    const int MAX = 100;
    const int SEPARATOR = 45;
    int currSymb = -1;
    int wordCount = 0;
    countW:
    currSymb++;
    if(f[currSymb] == ' ') {
        words++;
    }
    if(f[currSymb] == '\n') {
        pagesCount++;
        words++;
    }
    if(currSymb < f.length()) {
        goto countW;
    }
    pagesCount = pagesCount / SEPARATOR;
    string pages[pagesCount + 1][words + 1];
    string uniqueWords[words + 1];
    int size = 0;
    int count = 0;
    bool exist = false;
    int currLine = 0;
    int currPage = 0;
    int currWords = 0;
    int currSymbol = -1;
    string word = "";
    extract:
    currSymbol++;
    if(currLine == SEPARATOR) {
        currPage++;
        currLine = 0;
        currWords = 0;
    }
    
    if(f[currSymbol] == '\n') {
        count2 = 0;
        currLine++;
        check:
        if(ignore[count2] == word) {
            word = "";
            goto extract;
        }
        count2++;
        if(count2 < IGNORED) {
            goto check;
        }
        pages[currPage][currWords] = word;
        count = -1;
        exist = false;
        find:
        count++;
        if(uniqueWords[count]== word && count < size) {
            exist = true;
        }
        if(count < size) {
            goto find;
        }
        if(!exist && word != "") {
            uniqueWords[size++] = word;
        }
        word = "";
        currWords++;
    } else if(f[currSymbol] == ' ') {
        count2 = 0;
        check2:
        if(ignore[count2] == word) {
            word = "";
            goto extract;
        }
        count2++;
        if(count2 < IGNORED) {
            goto check2;
        }
        pages[currPage][currWords] = word;
        count = -1;
        exist = false;
        find2:
        count++;
        if(uniqueWords[count]== word && count < size) {
            exist = true;
            count = size;
        }
        if(count < size) {
            goto find2;
        }
        if(!exist && word != "") {
            uniqueWords[size++] = word;
        }
       word = "";
       currWords++;
    } else if(65 <= f[currSymbol] + 0 && 90 >= f[currSymbol] + 0) {
        word += f[currSymbol] + 32;
    } else if (97 <= f[currSymbol] + 0 && 122 >= f[currSymbol] + 0) {
        word += f[currSymbol];
    }

    
    if(currSymbol < f.length()) {
        goto extract;
    }
    
    count = 0;
    count2 = size;
    string temp = uniqueWords[size-1];
    
    sort:
    
    temp = uniqueWords[size-1];
    count2 = size-2;
    
    inner:
    
    if(count2 >= 0 && uniqueWords[count2] > temp) {
        uniqueWords[count2+1] = uniqueWords[count2];
    } else if(count2 >= 0) {
        uniqueWords[count2+1] = temp;
        temp = uniqueWords[count2];
    }
    
    count2--;
    
    if(count2 >= count) {
        goto inner;
    }
    
    if(count2 >= -1) {
       uniqueWords[count2+1] = temp; 
    }
    
    count++;
    
    if(count < size){
        goto sort;
    }
    count2 = 0;
    int finders[words + 1][MAX];
    int count3 = 0;
    
    loop:
    
    count = 0;
    currWords = 0;
    loop2:
    
    count3 = 0;
    loop3:
    
    if(pages[count][count3] == uniqueWords[count2]) {
        finders[count2][currWords] = count + 1;
        currWords++;
        count3 = words + 1;
    }

    count3++;
    if(count3 < words + 1) {
        goto loop3;
    }
    
    count++;
    if(count < pagesCount + 1 && currWords < MAX) {
        goto loop2;
    }
    finders[count2][currWords] = 0;
    count2++;
    if(count2 < size) {
        goto loop;
    }
    count = 0;
    print:
    count2 = 0;
    word = "[";
    print2:
    word += to_string(finders[count][count2]);
    count2++;
    if(finders[count][count2] > 0 && count2 < MAX) {
        word +=", ";
        goto print2;
    }
    word += "]";
    printf("%s - %s",uniqueWords[count].c_str(), word.c_str());
    printf("\n");
    count++;
    if(count < size) {
        goto print;
    }
    getch();

    return 0;
}