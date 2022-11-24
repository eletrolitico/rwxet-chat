#ifndef CTRL_CFG_H
#define CTRL_CFG_H

#include <filesystem>

namespace fs = std::filesystem;

namespace rwxet_ctrl
{
    typedef struct
    {
        std::string name;
        std::string user_id;
        std::string auth_token;
        std::string pfp_link;
        std::string base_url;
    } cfg_data;
    class Cfg
    {
    public:
        static Cfg *Get();
        bool Init();
        bool ParseAuth(const std::string &, const std::string & = "");
        void Save();

        inline bool HasConfig()
        {
            return has_config;
        }
        inline const cfg_data &GetConfig()
        {
            return data;
        }

    private:
        static Cfg *s_instance;
        Cfg();

        fs::path m_cfg_dir;
        bool has_config{false};
        cfg_data data;
    };
} // namespace rwxet_ctrl

#endif