#include "Notebook.hpp"
#include <string>
#include <iostream>
#include "Direction.hpp"
#include <map>

using namespace std;
using namespace ariel;
#define maxNum 100
#define minNum 0

Notebook::Notebook(){

}

Notebook::~Notebook(){

}

void Notebook::write(int page, int row, int col, Direction direction, string str){
    if(page < minNum || row < minNum){
        throw invalid_argument("Error, please enter positive number");
    }

    if(col > maxNum || col < minNum){
        throw invalid_argument("Error, please enter number between 0 to 100");
    }

    if(str.length() > maxNum && direction == Direction::Horizontal){
        throw invalid_argument("Error, string length is out of range");
    }

    for(int i=0; i<str.length(); i++){
        if (str[i] == '~'){
            throw invalid_argument("The char '~' is invalid");
        }
    }

    int len = str.length();
    if (direction == Direction::Horizontal){
        for(int i=0; i<len; i++){
            if(noteMap[page][row][col+i] != '_'){
                throw invalid_argument("Error, the current col is taken");
            }
        }

        for(int i=0; i<len; i++){
            noteMap[page][row][col+i] = str[i];
        }


    }
    else{
        for(int i=0; i<len; i++){
            if(noteMap[page][row+i][col] == '_'){
                throw invalid_argument("Error, the current col is taken");
            }
        }

        for(int i=0; i<len; i++){
            noteMap[page][row+i][col] = str[i];
        }

    }



}


string Notebook::read(int page,  int row, int col, Direction direction, int num){
    if(page < minNum || row < minNum){
        throw invalid_argument("Error, please enter positive number");
    }

    if(col > maxNum || col < minNum){
        throw invalid_argument("Error, please enter number between 0 to 100");
    }

    if(num < minNum){
        throw invalid_argument("Error, please enter positive number");
    }

    if(col + num > maxNum && direction == Direction::Horizontal){
        throw invalid_argument("Error, out of bounds");
    }

    string ans;
    if (direction == Direction::Horizontal){
        for(int i=col; i<col+num; i++){
            ans += noteMap[page][row][i];
        }
    }
    else{
        for(int i=0; i<num; i++){
            ans += noteMap[page][row+i][col];
        }
    }
    return ans;
}


void Notebook::erase(int page, int row, int col, Direction direction, int num){
    if(page < minNum || row < minNum){
        throw invalid_argument("Error, please enter positive number");
    }

    if(col > maxNum || col < minNum){
        throw invalid_argument("Error, please enter number between 0 to 100");
    }

    if(num < minNum){
        throw invalid_argument("Error, please enter positive number");
    }

    if(col + num > maxNum && direction == Direction::Horizontal){
        throw invalid_argument("Error, out of bounds");
    }

    if (direction == Direction::Horizontal){
        for(int i=col; i<col+num; i++){
            noteMap[page][row][i] = '~';
        }
    }
    else{
        for(int i=0; i<num; i++){
            noteMap[page][row+i][col] = '~';
        }
    }


}


void Notebook::show(int page){
    if(page < minNum){
        throw invalid_argument("Error, please enter positive number");
    }
}

