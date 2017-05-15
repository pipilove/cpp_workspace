#include <iostream>
#include <vector>
 
class A {
public:
    A() {
        static int ref = 0;
        std::cout << "ref:" << ref++ << std::endl;
    }
 
    static A* GetInstance() {
        static A* pa = new A;
        return pa;
    }
};

int __main() {
    std::vector<A *> as;
    for (int i = 0; i < 3; ++i) {
        as.push_back(A::GetInstance());
    }

    A **pa = &(as[0]);
    for (int i = 0; i < 3; ++i) {
        delete *pa;
    }
}