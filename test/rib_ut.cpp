

#include "rib.h"
#include "rib_common.h"


void thread_fn(int tid)
{
    Rib* rib_inst = Rib::get_instance();
    std::list<RtableEntry> routes;


    rib_inst->add_route("eth1", "10.1.2.1", "111.1.1.1", 251, "Apple");
    rib_inst->add_route("eth1", "10.1.2.1", "111.1.1.1", 250, "Apple");
    rib_inst->add_route("eth1", "10.1.2.1", "111.2.1.1", 150, "Apple");
    rib_inst->del_route("eth1", "10.1.2.1", "111.2.1.1", 150, "Apple");
    rib_inst->get_routes("10.1.2.1", "Apple", routes);

    for (auto &i : routes)
    {

        std::cout << i;
    }

    std::cout << std::endl;


}

int main()
{
#ifdef SINGLE_THREAD
    Rib* rib_inst = Rib::get_instance();
    std::list<RtableEntry> routes;
    rib_inst->add_route("eth1", "10.1.2.1", "111.1.1.1", 251, "Apple");
    rib_inst->add_route("eth1", "10.1.2.1", "111.1.1.1", 250, "Apple");
    rib_inst->add_route("eth1", "10.1.2.1", "111.2.1.1", 150, "Apple");
    rib_inst->del_route("eth1", "10.1.2.1", "111.2.1.1", 150, "Apple");
    rib_inst->get_routes("10.1.2.1", "Apple", routes);

    for (auto &i : routes)
    {

        std::cout << i;
    }

    std::cout << std::endl;
#else

    std::thread thread_array [100];
    for (int i = 0; i < 100; i++) {
        thread_array[i] = std::thread(thread_fn, i);

    }

    for (int i = 0; i < 100; i++) {

        thread_array[i].join();
    }
#endif
    return 0;
}
