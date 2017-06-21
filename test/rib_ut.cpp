

#include "rib.h"


 int main ()
 {
    Rib test;
    test.add_route("eth1", "10.1.1.1", "11.1.1.1", 255);
    return 0;
 }
