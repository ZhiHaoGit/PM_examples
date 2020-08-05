#include <iostream>

#include "pm_examples.hpp"

using namespace std;
namespace pobj = pmem::obj;
using namespace pe;

int main(int argc, char *argv[]) {
    pop_type pop = pop_type::open("./file.1", LAY_OUT);
    auto proot = pop.root();
    cout << "Counter = " << proot->counter << endl;

    std::vector<std::thread> workers;
    int n = 20;
    workers.reserve(10);
    for(int i=0; i<10; i++)
        workers.emplace_back(increase, std::ref(pop));

    for(int i=0; i<10; i++)
        workers[i].join();

    cout << "Counter = " << proot->counter << endl;

    pop.close();
    return 0;
}
