#include "net/util.h"
#include "ctrl/cfg.h"

#include <iostream>

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>

#include <Poco/Exception.h>
namespace rwxet_net
{
    std::tuple<int, std::string> request(const std::string &method, const std::string &path, const std::string &body, const std::string &host)
    {
        auto cfg = rwxet_ctrl::Cfg::Get();
        Poco::URI uri(host);

        if (host.empty())
            uri = Poco::URI(cfg->GetConfig().base_url);

        Poco::Net::HTTPRequest request(method, path);
        Poco::Net::HTTPResponse response;

        if (!body.empty())
        {
            request.add("Content-Type", "application/json");
            request.setContentLength(body.length());
        }

        auto tfa = cfg->get2FAToken();
        if (cfg->HasConfig())
        {
            rwxet_ctrl::cfg_data const &data = cfg->GetConfig();
            request.add("X-User-Id", data.user_id);
            request.add("X-Auth-Token", data.auth_token);
        }
        if (!tfa.empty())
        {
            request.add("X-2fa-Method", "totp");
            request.add("X-2fa-Code", tfa);
            cfg->set2FAToken("");
        }

        std::string out;
        if (uri.getScheme().compare("https") == 0)
        {
            Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort());
            session.sendRequest(request) << body;
            std::istream &rs = session.receiveResponse(response);
            Poco::StreamCopier::copyToString(rs, out);
        }
        else
        {
            Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
            session.sendRequest(request) << body;
            std::istream &rs = session.receiveResponse(response);
            Poco::StreamCopier::copyToString(rs, out);
        }

        std::cout << out << std::endl;

        return std::make_tuple(response.getStatus(), out);
    }
}