#include "net/auth.h"
#include "simple_web/client_https.h"

namespace rwxet_net
{
    typedef SimpleWeb::Client<SimpleWeb::HTTPS> HttpsClient;

    std::string login(const std::string &server,const std::string &user,const std::string &pass)
    {
        HttpsClient client(server + ":443", false);

        std::map<std::string,std::string> headers;
        headers["Content-type"] = "application/json";
        auto r1 = client.request("POST", "/api/v1/login","{\"user\": \""+user+"\", \"password\": \""+pass+"\"}",headers);

        std::stringstream resp;
        resp << r1->content.rdbuf();
        return resp.str();
    }
} // namespace rwxet_net
