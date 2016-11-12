
// define one container for the unrepeat pairs. 
#include <vector>

#ifndef ASET_H
#define ASET_H

class Point;

class Aset
{
public:
    ~Aset();
    static getinstance();
    void push_back();
    void pop_back();
    void clear();
private:
    Aset();
    static Aset * myAset;
    std::vector<Point> points;
}

#endif //EOF
