#include "Direction.hpp"
using ariel::Direction;

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include "Notebook.hpp"
using namespace std;


void ariel::Notebook::write(int  page, int  row, int  column, Direction d, const string & str){
    check_input_w(page, row, column, str, d);
    if (this->_nb.count(page) == 0) { //init page
        this->_nb[page].resize(initSize,  string(sizeOfLine, '_'));
        this->_numLine[page] = initSize;
    }
    //set lines in page:
    if (d == Direction::Horizontal){
        while (row >= this->_numLine[page]){
            this->_nb[page].resize(size_t(this->_numLine[page]*2), string(sizeOfLine, '_'));
            this->_numLine[page] = this->_numLine[page]*2;
        }
    }
    else{
        while ((size_t(row)+str.size()) >= this->_numLine[page]) {
            this->_nb[page].resize(size_t(this->_numLine[page]*2),  string(sizeOfLine, '_'));
            this->_numLine[page] = this->_numLine[page] * 2;
        }
    }
    //check clean line if Horizontal:
    if (d == Direction::Horizontal) {
        string s(str.size(), '_');  //clean line
        if (s != this->_nb[page].at(size_t(row)).substr(size_t(column), str.size())){
            throw invalid_argument("Cant override");
        }
    }

    if (d == Direction::Horizontal){
        this->_nb[page].at(size_t(row)).replace(size_t(column), str.size(), str);
    }
    else{
        for (int line=row, i=0; line < (size_t(row) + str.size()); line++, i++){
            if (this->_nb[page].at(size_t(line)).at(size_t(column)) != '_'){
                throw invalid_argument("Cant override");
            }
            this->_nb[page].at(size_t(line)).replace(size_t(column), 1, string(1,str.at(size_t(i))));
        }
    }
}

string ariel::Notebook::read(int page,  int row, int column, Direction d, int chars){
    pre_read_earse(page, row, column, d, chars);
    //read:
    if (d == Direction::Horizontal){
        return this->_nb[page].at(size_t(row)).substr(size_t(column), size_t(chars));
    }
    string ans; // = ""
    for (int line=row, i=0; i < chars; line++, i++){
        ans += this->_nb[page].at(size_t(line)).at(size_t(column));
    }
    return ans;
}

void ariel::Notebook::erase(int page, int row, int column, Direction d, int chars){
    pre_read_earse(page, row, column, d, chars);
    string  str2earse(size_t(chars), '~');

    if (d == Direction::Horizontal){
         this->_nb[page].at(size_t(row)).replace(size_t(column), size_t(chars), str2earse);
    }
    else{
        for (int line=row, i=0; i < chars; line++, i++){
            this->_nb[page].at(size_t(line)).replace(size_t(column), 1, str2earse);
        }
    }
}

void ariel::Notebook::show(int page){
    if (page<0){
        throw invalid_argument("Value cant be minus");
    }
    //if the page not exist:
    if (this->_nb.count(page) == 0) { //init page
        this->_nb[page].resize(initSize,  string(sizeOfLine, '_'));
        this->_numLine[page] = initSize;
    }
    string ans = "\t\t\t\t\tPage Number: "+to_string(page)+"\t\t\t\t\t\n\n";
    for (size_t i=0; i<this->_numLine[page]; i++){
        ans += to_string(i)+":  ";
        ans += this->_nb[page].at(i);
        ans+= '\n';
    }
    cout<<ans<<endl;
}

void ariel::Notebook::check_input_w(int page, int row, int column, const string &basicString, Direction d) const {
    for (size_t i=0; i < basicString.size(); i++) {
        if (basicString[i] < MIN || basicString[i] > MAX || basicString[i] == '~') {
            throw invalid_argument("Chars are not legal");
        }
    }
    if (page < 0 || row<0 || column < 0) {
        throw invalid_argument("Value cant be minus");
    }
    if (d == Direction::Horizontal && (size_t(column) + basicString.size()) > sizeOfLine) {
        throw invalid_argument("Value out of line");
    }
    if (column >= sizeOfLine) {
        throw invalid_argument("Value out of line");
    }
}

void ariel::Notebook::pre_read_earse(int page, int row, int column, Direction d, int chars) {
    //check_input:
    if (page < 0 || row<0 || column < 0 || chars < 0) {
        throw invalid_argument("Value cant be minus");
    }
    if (d == Direction::Horizontal && (column + chars) > sizeOfLine) {
        throw invalid_argument("Value out of line");
    }
    if (column >= sizeOfLine) {
        throw invalid_argument("Value out of line");
    }

    //if the page not exist:
    if (this->_nb.count(page) == 0) { //init page
        this->_nb[page].resize(initSize,  string(sizeOfLine, '_'));
        this->_numLine[page] = initSize;
    }
    //if the line not exist:
    if (d == Direction::Horizontal){
        while (row >= this->_numLine[page]){
            this->_nb[page].resize(size_t(this->_numLine[page]*2),  string(sizeOfLine, '_'));
            this->_numLine[page] = this->_numLine[page]*2;
        }
    }
    else{
        while ((row+chars) >= this->_numLine[page]) {
            this->_nb[page].resize(size_t(this->_numLine[page]*2),  string(sizeOfLine, '_'));
            this->_numLine[page] = this->_numLine[page] * 2;
        }
    }
}