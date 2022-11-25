#include "ctrl/cfg.h"

#include <wx/wx.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>

#ifndef __WXMSW__
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

namespace JS = Poco::JSON;

namespace rwxet_ctrl
{
    Cfg *Cfg::s_instance = nullptr;

    Cfg::Cfg() = default;

    Cfg *Cfg::Get()
    {
        if (s_instance == nullptr)
            s_instance = new Cfg;
        return s_instance;
    }

    bool Cfg::Init()
    {
        const char *homedir;

#ifdef __WXMSW__
        homedir = getenv("USERPROFILE");
#else
        homedir = getenv("HOME");
        if (strnlen(homedir, 100) < 3)
        {
            struct passwd *pw = getpwuid(getuid());
            homedir = pw->pw_dir;
        }
#endif

        m_cfg_dir = fs::path(homedir);
        m_cfg_dir.append(".rwxet");

        if (!fs::exists(m_cfg_dir) && !fs::create_directory(m_cfg_dir))
        {
            std::cerr << "Error creating " << m_cfg_dir << std::endl;
            return false;
        }

        if (auto p_cfg = m_cfg_dir / fs::path("config.json"); fs::exists(p_cfg))
        {
            std::ifstream t(p_cfg);
            std::stringstream buffer;
            buffer << t.rdbuf();
            ParseAuth(buffer.str());
        }

        return true;
    }

    bool Cfg::ParseAuth(const std::string &apiJson, const std::string &base_url)
    {
        JS::Parser parser;
        auto result = parser.parse(apiJson);
        if (result.isEmpty())
            // yeet
            throw AuthException("this bitch empty");

        auto obj = result.extract<JS::Object::Ptr>();

        if (obj->get("status").extract<std::string>() != "success")
        {
            auto msg = obj->get("error").extract<std::string>();
            if (msg.find("totp") == std::string::npos)
                throw AuthException(msg);

            return false;
        }

        auto data = obj->get("data").extract<JS::Object::Ptr>();
        m_data.auth_token = data->get("authToken").extract<std::string>();
        m_data.user_id = data->get("userId").extract<std::string>();

        auto me = data->get("me").extract<JS::Object::Ptr>();
        m_data.name = me->get("name").extract<std::string>();
        m_data.pfp_link = me->get("avatarUrl").extract<std::string>();
        if (base_url.empty())
            m_data.base_url = obj->get("baseUrl").extract<std::string>();
        else
        {
            m_data.base_url = base_url;
            obj->set("baseUrl", base_url);
            auto p_cfg = m_cfg_dir / fs::path("config.json");
            std::ofstream f(p_cfg);
            obj->stringify(f, 1);
        }

        m_has_config = true;
        return true;
    }

    void Cfg::Save()
    {
    }
}
