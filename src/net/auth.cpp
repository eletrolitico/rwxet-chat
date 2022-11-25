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
        auto cfg = rwxet_ctrl::Cfg::Get();
        return cfg->ParseAuth(std::get<1>(res), server);
    }
} // namespace rwxet_net
