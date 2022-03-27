#include "Notebook.hpp"
#include <string>
#include <iostream>
#include "../Direction.hpp"
#include <map>

using namespace std;
using namespace ariel;
#define maxNum 100
#define minNum 0

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

    for(int i=0; i<str.length(); i++){
        if (str[(size_t)(i)] == '~'){
            throw invalid_argument("The char '~' is invalid");
        }
        if (!isprint(str[(size_t)(i)]) ){
            throw invalid_argument("The char is invalid");
        }
    }

    if (direction == Direction::Horizontal){
        if(noteMap[page].find(row) == noteMap[page].end()){
            noteMap[page][row] = "____________________________________________________________________________________________________";
        }

        for(int i=0; i<len; i++){
            if(noteMap[page][row][(size_t)(col+i)] != '_'){
                throw invalid_argument("Error, the current col is taken");
            }
        }

        for(int i=0; i<len; i++){
            noteMap[page][row][(size_t)(col+i)] = str[(size_t)(i)];
        }


    }
    else{
        for(int i=0; i<len; i++){
            if(noteMap[page].find((size_t)(row+i)) == noteMap[page].end()){
                noteMap[page][(size_t)(row+i)] = "____________________________________________________________________________________________________";
            }
        }


        for(int i=0; i<len; i++){
            if(noteMap[page][(size_t)(row+i)][(size_t)col] != '_'){
                throw invalid_argument("Error, the current col is taken");
            }
        }

        for(int i=0; i<len; i++){
            noteMap[page][(size_t)(row+i)][(size_t)col] = str[(size_t)(i)];
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

    if(direction == Direction::Horizontal) {
        if (noteMap.find(page) == noteMap.end() || noteMap[page].find(row) == noteMap[page].end()) {
            string a;
            for (int i = 0; i < num; i++) {
                a += '_';
            }
            return a;
        }
    }
    else if(direction == Direction::Vertical){
        string a ;
        for(int i=0; i<num; i++){
            if(noteMap.find(page) != noteMap.end() && noteMap[page].count(row+i)!=0){
                a+=noteMap[page][(size_t)(row+i)][(size_t)(col)];
            }
            else{
                a+='_';
            }

        }
        return a;
    }

    string ans;
    if (direction == Direction::Horizontal){
        for(int i=col; i<col+num; i++){
            ans += noteMap[page][row][(size_t)(i)];
        }
    }
    else{
        for(int i=0; i<num; i++){
            ans += noteMap[page][(size_t)(row+i)][(size_t)col];
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

    if (direction == Direction::Horizontal){
        if(noteMap.find(page) == noteMap.end() || noteMap[page].find(row) == noteMap[page].end()){
            noteMap[page][(size_t)(row)] = "____________________________________________________________________________________________________";
        }

        for(int i=col; i<col+num; i++){
            noteMap[page][row][(size_t)(i)] = '~';
        }
    }
    else{
        for(int i=0; i<num; i++){
            if(noteMap[page].find((size_t)(row+i)) == noteMap[page].end()){
                noteMap[page][(size_t)(row+i)] = "____________________________________________________________________________________________________";
            }
        }

        for(int i=0; i<num; i++){
            noteMap[page][(size_t)(row+i)][(size_t)col] = '~';
        }
    }


}


void Notebook::show(int page){
    if(page < minNum){
        throw invalid_argument("Error, please enter positive number");
    }
}

