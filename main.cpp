#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <pthread.h>
#include <libpmemobj++/p.hpp>
#include <libpmemobj++/pool.hpp>
#include <libpmemobj++/detail/common.hpp>
#include <libpmemobj++/detail/template_helpers.hpp>
#include <libpmemobj++/experimental/v.hpp>
#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/make_persistent_atomic.hpp>
#include <libpmemobj++/mutex.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/transaction.hpp>

#define LAY_OUT "COUNTER_INC"
using namespace std;
namespace pobj = pmem::obj;

struct root {
    pobj::mutex mt;
    pobj::p<int> counter;
};

using pop_type = pobj::pool<root>;

void increase(pop_type& pop) {
    auto proot = pop.root();
    pobj::transaction::run(pop, [&] {
        for(int i = 0; i< 1000; i++) {
            //std::unique_lock<pobj::mutex> lock(proot->mt);
            proot->counter.get_rw() += 1;
        }
    }, proot->mt);
}


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
