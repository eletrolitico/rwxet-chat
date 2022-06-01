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
    Cfg* Cfg::instance = nullptr;

    Cfg::Cfg() {}

    Cfg* Cfg::Get()
    {
        if(instance == nullptr)
            instance = new Cfg;
        return instance;
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
            fs::create_directory(m_cfg_dir);
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
        resp.Parse(apiJson.c_str());
        assert(resp.HasMember("status"));

        auto st = resp["status"].GetString();
        if(st == nullptr){
            return "Could not obtain response status";
        }

        if(strcmp(st, "error") == 0){
            char msg[500];
            strcpy(msg,"API Error: ");
            return strncat(msg, resp["message"].GetString(), 450);
        }

        if(strcmp(st, "success") != 0){
            char msg[500];
            strcpy(msg,"Unknown API reponse: ");
            return strncat(msg, st, 450);
        }

    }
} // namespace rwxet_net
