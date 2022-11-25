#ifndef CTRL_CFG_H
#define CTRL_CFG_H

#include <filesystem>

namespace fs = std::filesystem;

namespace rwxet_ctrl
{
    class AuthException : public std::exception
    {
    public:
        AuthException(const std::string &why) : reason(why)
        {
        }
        const char *what() const throw() override
        {
            return reason.c_str();
        }

    private:
        std::string reason;
    };
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
            return m_has_config;
        }
        inline const cfg_data &GetConfig()
        {
            return m_data;
        }
        inline void set2FAToken(const std::string &token)
        {
            m_2fa_token = token;
        }
        inline std::string get2FAToken()
        {
            return m_2fa_token;
        }

    private:
        static Cfg *s_instance;
        Cfg();

        fs::path m_cfg_dir;
        bool m_has_config{false};
        cfg_data m_data;
        std::string m_2fa_token;
    };
} // namespace rwxet_ctrl

#endif