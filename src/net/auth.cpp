#include "net/auth.h"

#include <iostream>

#include "simple_web/client_https.h"
#include "ctrl/cfg.h"

namespace rwxet_net
{
    typedef SimpleWeb::Client<SimpleWeb::HTTPS> HttpsClient;

    std::string login(const std::string &server,const std::string &user,const std::string &pass)
    {
        HttpsClient client(server + ":443", false);

        std::map<std::string,std::string> headers;
        headers["Content-type"] = "application/json";
        auto r1 = client.request("POST", "/api/v1/login","{\"user\": \""+user+"\", \"password\": \""+pass+"\"}",headers);

        std::stringstream buffer;
        buffer << r1->content.rdbuf();
        std::string str = buffer.str();

        auto cfg = rwxet_ctrl::Cfg::Get();
        return cfg->ParseAuth(std::move(str));
    }
} // namespace rwxet_net
