#ifndef CTRL_CFG_H
#define CTRL_CFG_H

#include <filesystem>
#include <rapidjson/document.h>

namespace fs = std::filesystem;
namespace js = rapidjson;

namespace rwxet_ctrl
{
    class Cfg{
        public:
            static Cfg* Get();
            bool Init();
            std::string ParseAuth(const std::string&);

        private:
            static Cfg* instance;
            Cfg();

            fs::path m_cfg_dir;
            js::Document m_document;
    };

    constexpr std::string_view AUTH_TOKEN = "authToken";
    constexpr std::string_view PFP_LINK   = "pfpLink";
} // namespace rwxet_ctrl

#endif