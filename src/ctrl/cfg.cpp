#include "ctrl/cfg.h"


#include <sstream>
#include <fstream>
#include <iostream>
#include <string.h>

#ifndef __WXMSW__
    #include <unistd.h>
    #include <sys/types.h>
    #include <pwd.h>
#endif


namespace rwxet_ctrl
{
    Cfg* Cfg::s_instance = nullptr;

    Cfg::Cfg() {}

    Cfg* Cfg::Get()
    {
        if(s_instance == nullptr)
            s_instance = new Cfg;
        return s_instance;
    }

    bool Cfg::Init()
    {
        const char * homedir;

        #ifdef __WXMSW__
            homedir = getenv("USERPROFILE");
        #else
            homedir = getenv("HOME");
            if(strnlen(homedir,100) < 3){
                struct passwd *pw = getpwuid(getuid());
                homedir = pw->pw_dir;
            }
        #endif

        m_cfg_dir = fs::path(homedir);
        m_cfg_dir.append(".rwxet");

        if(!fs::exists(m_cfg_dir))
        {
            if(!fs::create_directory(m_cfg_dir))
            {
                std::cerr << "Error creating " << m_cfg_dir << std::endl;
                return false;
            }

            std::cout << "Created cfg dir " << m_cfg_dir << std::endl;
        }

        auto p_cfg = m_cfg_dir/fs::path("config.json");
        if(fs::exists(p_cfg))
        {
            std::ifstream t(p_cfg);
            std::stringstream buffer;
            buffer << t.rdbuf();
            m_document.Parse(buffer.str().c_str());
        }

        return true;
    }

    std::string Cfg::ParseAuth(const std::string& apiJson)
    {
        js::Document resp;
        if (resp.Parse(apiJson.c_str()).HasParseError())
            return "Erro parse json api: cod " + std::to_string(resp.GetParseError());

        assert(resp.HasMember("status"));

        auto st = std::string(resp["status"].GetString());
        if(st.size() == 0)
            return "Could not obtain response status";

        if(st == "error")
            return "API Error: " + std::string(resp["message"].GetString());

        if(st != "success")
            return "Unknown API reponse: " + st;

        auto p_auth = m_cfg_dir/fs::path("auth.json");
        std::ofstream out(p_auth);
        out << apiJson;

        return "";
    }

    void Cfg::Save()
    {
    }
} // namespace rwxet_net
