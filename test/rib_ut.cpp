

#include "rib.h"

int main()
{
    Rib test;
    std::list<RtableEntry> routes;
    test.add_route("eth1", "10.1.2.1", "111.1.1.1", 251, "Apple");
    test.add_route("eth1", "10.1.2.1", "111.1.1.1", 250, "Apple");
    test.add_route("eth1", "10.1.2.1", "111.2.1.1", 150, "Apple");
    test.get_routes("10.1.2.1", "Apple", routes);

    for (auto &i : routes)
    {

        std::cout << i;
    }

    return 0;
}
