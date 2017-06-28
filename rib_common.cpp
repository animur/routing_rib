#include "rib_common.h"

RtableEntry::RtableEntry(byte metric,
						 ipaddr dst_ip,
						 ipaddr gw_ip,
						 std::string if_name) : _metric(metric),
												_gw_ip(gw_ip),
												_dst_ip(dst_ip),
												_if_name(if_name)
{
	_is_valid = true;
}

bool RtableEntry::check(RtableEntry &route, rib_err_t &err_code) const
{

	return true;
}

std::ostream &operator<<(std::ostream &out, const RtableEntry &route)
{

	out << std::endl
		<< " DST: " << std::hex << route._dst_ip
		<< " GW: " << std::hex << route._gw_ip
		<< " IF: " << route._if_name
		<< " MET: " << std::dec << route._metric;

	return out;
}

bool operator<(const RtableEntry &lhs, const RtableEntry &rhs)
{
	return (lhs._metric < rhs._metric);
}

bool operator == (const RtableEntry &lhs, const RtableEntry &rhs)
{

    return ((lhs._metric  ==  rhs._metric)&&
            (lhs._dst_ip  ==  rhs._dst_ip)&&
            (lhs._gw_ip   ==  rhs._gw_ip)&&
            (lhs._if_name ==  rhs._if_name)
           );
}

void convStrToIp(ipaddr &ip, std::string s)
{
	std::string delimiter = ".";
	size_t pos = 0;
	std::string token;
	int i = 0;

	while ((pos = s.find(delimiter)) != std::string::npos)
	{
		token = s.substr(0, pos);
		ip = ip | (stoul(token, nullptr, 0) << (24 - 8 * i));
		i++;

		/*Need to erase a part of the string till the delimiter
		 * Other wise find will always return the first
		 * occurence of the delimiter
		 */

		s.erase(0, pos + delimiter.length());
	}
	ip = ip | (stoul(token, nullptr, 0));
}
