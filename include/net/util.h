#ifndef NET_UTIL_H
#define NET_UTIL_H

#include <string>
#include <tuple>

namespace rwxet_net
{
   std::tuple<int, std::string> request(const std::string &method, const std::string &path, const std::string &body = "", const std::string &host = "");
} // namespace rwxet_net


#endif