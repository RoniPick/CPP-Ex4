#include <string>
#include <iostream>
#include "Direction.hpp"
#include <map>
#include <vector>

using namespace std;

namespace ariel {
    class Notebook {
    private:
        map<int, map<int, string>> noteMap;

    public:
        Notebook();
        ~Notebook();

        void write(int page, int row, int col, Direction direction, string str);
        string read(int page, int row, int col, Direction direction, int num);
        void erase(int page, int row, int col, Direction direction, int num);
        void show(int page);

    };
};

