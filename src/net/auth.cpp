#include "net/auth.h"
#include "net/util.h"

#include <iostream>
#include <tuple>

#include "ctrl/cfg.h"

namespace rwxet_net
{
    bool login(const std::string &server, const std::string &user, const std::string &pass)
    {
        auto res = request("POST", "/api/v1/login", "{\"user\": \"" + user + "\", \"password\": \"" + pass + "\"}", server);

        std::string bd = std::get<1>(res);

        std::cout << bd << std::endl;

        auto cfg = rwxet_ctrl::Cfg::Get();
        if (!cfg->ParseAuth(bd, server))
            return false;

        return true;
    }
} // namespace rwxet_net
