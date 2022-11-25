#include "net/chat.h"

#include "net/util.h"

#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>

namespace JS = Poco::JSON;

namespace rwxet_net
{
    std::vector<std::string> get_friends()
    {
        auto res = request("GET", "/api/v1/users.list");
        JS::Parser parser;
        auto users = parser.parse(std::get<1>(res)).extract<JS::Object::Ptr>()->get("users").extract<JS::Array::Ptr>();

        std::vector<std::string> ret;
        for (auto it = users->begin(); it != users->end(); ++it)
            ret.push_back(it->extract<JS::Object::Ptr>()->get("name").extract<std::string>());
        return ret;
    }
} // namespace rwxet_net
