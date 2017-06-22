#include "rib_common.h"



RtableEntry::RtableEntry(byte metric,
                          ipaddr gw,
                          ipaddr dst_ip,
                          std::string if_name):_metric(metric),
                                              _gw_ip(gw),
                                              _dst_ip(dst_ip),
                                              _if_name(if_name)
{
    _is_valid = true;

}


bool RtableEntry::check(RtableEntry& route, rib_err_t& err_code) const
{

	return true;
}

std::ostream& operator <<( std::ostream& out, const RtableEntry& route)
{

	out << std::endl    <<" DST: " << std::hex<< route._dst_ip
                        <<" GW: "  << std::hex << route._gw_ip
						<<" IF: "  << route._if_name
						<<" MET: " << std::dec << route._metric
					    << std::endl;

	return out;
}

void convStrToIp(ipaddr& ip, std::string s)
{
    std::string delimiter = ".";
	size_t pos = 0;
	std::string token;
    int i = 0;

	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		ip = ip | (stoul(token, nullptr, 0) << (24 - 8*i));
		i++;

		/*Need to erase a part of the string till the delimiter
		 * Other wise find will always return the first
		 * occurence of the delimiter
		 */

		s.erase(0, pos + delimiter.length());

	}
		ip = ip | (stoul(token, nullptr, 0));
}
