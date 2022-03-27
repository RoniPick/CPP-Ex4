#include "Notebook.hpp"
#include <string>
#include <iostream>
#include "../Direction.hpp"
#include <map>

using namespace std;
using namespace ariel;
constexpr int maxNum = 100;
constexpr int minNum = 0;

Notebook::Notebook(){

}

//Notebook::~Notebook(){
//
//}

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

    int len = str.length();
    if((col+len) > maxNum && direction == Direction::Horizontal){
        throw invalid_argument("Error, out of bounds");
    }

    //checking the string input
    for(int i=0; i<str.length(); i++){
        if (str[(size_t)(i)] == '~'){
            throw invalid_argument("The char '~' is invalid");
        }
        if (isprint(str[(size_t)(i)]) == 0){
            throw invalid_argument("The char is invalid");
        }
    }

    //if the row does not exist we're creating a new empty row
    if (direction == Direction::Horizontal){
        if(noteMap[page].find(row) == noteMap[page].end()){
            noteMap[page][row] = "____________________________________________________________________________________________________";
        }

        //checking if the cols in the row are available to write on
        for(int i=0; i<len; i++){
            if(noteMap[page][row][(unsigned int)(col+i)] != '_'){
                throw invalid_argument("Error, the current col is taken");
            }
        }

        //writing the string into the notebook
        for(int i=0; i<len; i++){
            noteMap[page][row][(unsigned int)(col+i)] = str[(unsigned int)(i)];
        }


    }
    //if the direction is vertical
    else{
        for(int i=0; i<len; i++){
            //if the row does not exist we're creating a new one
            if(noteMap[page].find((size_t)(row+i)) == noteMap[page].end()){
                noteMap[page][(row+i)] = "____________________________________________________________________________________________________";
            }
        }

        //checking if the col in each row is available to write on
        for(int i=0; i<len; i++){
            if(noteMap[page][(row+i)][(unsigned int)col] != '_'){
                throw invalid_argument("Error, the current col is taken");
            }
        }

        //writing the string into the notebook
        for(int i=0; i<len; i++){
            noteMap[page][(row+i)][(unsigned int)col] = str[(unsigned int)(i)];
        }

    }

}


string Notebook::read(int page,  int row, int col, Direction direction, int num){
    if(page < minNum || row < minNum){
        throw invalid_argument("Error, please enter positive number");
    }

    if(col >= maxNum || col < minNum){
        throw invalid_argument("Error, please enter number between 0 to 100");
    }

    if(num < minNum){
        throw invalid_argument("Error, please enter positive number");
    }

    if(col + num > maxNum && direction == Direction::Horizontal){
        throw invalid_argument("Error, out of bounds");
    }

    //if the row is not exist we want to return only empty row - "____"
    if(direction == Direction::Horizontal) {
        if (noteMap.find(page) == noteMap.end() || noteMap[page].find(row) == noteMap[page].end()) {
            string a;
            for (int i = 0; i < num; i++) {
                a += '_';
            }
            return a;
        }
    }

    //if the col in each row in the num range is not exist we want to return only empty row - "____"
    else if(direction == Direction::Vertical){
        string a ;
        for(int i=0; i<num; i++){
            //if the row is not empty
            if(noteMap.find(page) != noteMap.end() && noteMap[page].count(row+i)!=0){
                a+=noteMap[page][(row+i)][(unsigned int)(col)];
            }
            else{
                a+='_';
            }

        }
        return a;
    }

    //writing the requested string
    string ans;
    if (direction == Direction::Horizontal){
        for(int i=col; i<col+num; i++){
            ans += noteMap[page][row][(unsigned int)(i)];
        }
    }
    else{
        for(int i=0; i<num; i++){
            ans += noteMap[page][(row+i)][(unsigned int)col];
        }
    }
    return ans;
}


void Notebook::erase(int page, int row, int col, Direction direction, int num){
    if(page < minNum || row < minNum){
        throw invalid_argument("Error, please enter positive number");
    }

    if(col >= maxNum || col < minNum){
        throw invalid_argument("Error, please enter number between 0 to 100");
    }

    if(num < minNum){
        throw invalid_argument("Error, please enter positive number");
    }

    if(col + num >= maxNum && direction == Direction::Horizontal){
        throw invalid_argument("Error, out of bounds");
    }

    //if the row does not exist we're creating a new empty row
    if (direction == Direction::Horizontal){
        if(noteMap.find(page) == noteMap.end() || noteMap[page].find(row) == noteMap[page].end()){
            noteMap[page][(size_t)(row)] = "____________________________________________________________________________________________________";
        }

        //deleting the row by putting '~' instead of the current char
        for(int i=col; i<col+num; i++){
            noteMap[page][row][(size_t)(i)] = '~';
        }
    }
    //if the direction is vertical
    else{
        for(int i=0; i<num; i++){
            //if the row does not exist we're creating a new one
            if(noteMap[page].find((row+i)) == noteMap[page].end()){
                noteMap[page][(row+i)] = "____________________________________________________________________________________________________";
            }
        }

        //deleting the row by putting '~' instead of the current char
        for(int i=0; i<num; i++){
            noteMap[page][(size_t)(row+i)][(size_t)col] = '~';
        }
    }
}


void Notebook::show(int page){
    if(page < minNum){
        throw invalid_argument("Error, please enter positive number");
    }
//    string ans;
    int len = noteMap[page].size();
    for(int i=0; i<len; i++){
        if(noteMap[page].find(i) == noteMap[page].end()){
            cout << i << ".         ...      \n";
        }
        else{
            cout << i << "." << noteMap[page][i];
//            for(int j=0; j<100; j++){
//                cout << i << "." << noteMap[page][i];
//            }
        }
    }
}

