#ifndef NET_AUTH_H
#define NET_AUTH_H

#include <string>

namespace rwxet_net
{
    std::string login(const std::string &server,const std::string &user,const std::string &pass);
} // namespace rwxet_net


#endif