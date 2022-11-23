#include "net/auth.h"

#include <iostream>
#include <tuple>

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>

#include "ctrl/cfg.h"

namespace rwxet_net
{
    std::tuple<int,std::string> request(const std::string &method,const std::string &host, const std::string& path, const std::string &body)
    {
        Poco::URI uri(host);

        Poco::Net::HTTPRequest request(method, path);
        Poco::Net::HTTPResponse response;

        request.add("Content-Type","application/json");
        request.setContentLength(body.length());

        std::string out;
        if(uri.getScheme().compare("https") == 0){
            Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort());
            session.sendRequest(request) << body;
            std::istream &rs = session.receiveResponse(response);
            Poco::StreamCopier::copyToString(rs,out);
        }else{
            Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
            session.sendRequest(request) << body;
            std::istream &rs = session.receiveResponse(response);
            Poco::StreamCopier::copyToString(rs,out);
        }

        return std::make_tuple(response.getStatus(),out);
    }

    std::string login(const std::string &server,const std::string &user,const std::string &pass)
    {
        auto res = request("POST",server,"/api/v1/login", "{\"user\": \""+user+"\", \"password\": \""+pass+"\"}");

        std::string bd = std::get<1>(res);

        std::cout << bd << std::endl;

        auto cfg = rwxet_ctrl::Cfg::Get();
        return cfg->ParseAuth(bd);
    }
} // namespace rwxet_net
