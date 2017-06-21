#include "rib_common.h"
#include "rib.h"



void Rib:: _insert(const RtableEntry& route)
{

	std::cout << route <<std::endl;
}


void Rib::_lookup(const ipaddr prefix)
{

}

void Rib::add_route(const std::string if_name, const std::string dst,
                    const std::string gw, const byte metric)
{
	ipaddr gw_ip = 0;
	ipaddr dst_ip = 0;
	convStrToIp(gw_ip, gw);
	convStrToIp(dst_ip, dst);

    const RtableEntry route_to_insert(metric, dst_ip, gw_ip, if_name);

	_insert(route_to_insert);


}


void Rib::get_routes(const std::string prefix, std::list<RtableEntry> &routes)
{



}
