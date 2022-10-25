#include<iostream>

struct S {
    int i;
    double d;

};

S func1(int i, double d);


int main() {
    
    S s = func1(99,88.8);
    std::cout << s.d << " " << s.i << std::endl;
}

S func1(int i, double d) {
    return {i,d};
}