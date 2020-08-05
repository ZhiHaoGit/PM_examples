//
// Created by zhihao on 2020/8/5.
//

#ifndef PM_EXAMPLES_PM_EXAMPLES_HPP
#define PM_EXAMPLES_PM_EXAMPLES_HPP

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
namespace pe {
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

}

#endif //PM_EXAMPLES_PM_EXAMPLES_HPP
