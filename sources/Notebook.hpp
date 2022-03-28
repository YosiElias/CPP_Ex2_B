#pragma once
#include "Direction.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <unordered_map>

using namespace std;
using ariel::Direction;



namespace ariel {
	class Notebook
	{
	private:
        unordered_map<int, vector<string>> _nb;
        unordered_map<int, size_t> _numLine;
        const int MIN = 32; //min legality value char
        const int MAX = 126; //max legality value char
        const size_t sizeOfLine = 100;
        const size_t initSize = 10;
        void check_input_w(int page, int row, int column, const string &basicString, Direction direction) const;
        void pre_read_earse(int page, int row, int column, Direction d, int chars);


    public:
		void write( int page,  int row,  int column, Direction d, const string & str);
		string read( int page,  int row,  int column, Direction d,  int chars);
		void erase( int page,  int row,  int column, Direction d,  int chars);
		void show(int page);
		Notebook(){
            unordered_map<int, vector<string>> _nb;
            unordered_map<int, int> _numLine;
        };
//		~Notebook();
    };
};