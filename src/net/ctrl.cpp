#include "net/ctrl.h"

#include <string>
#include <iostream>
#include <string.h>

#ifndef WIN32
    #include <unistd.h>
    #include <sys/types.h>
    #include <pwd.h>
#endif

namespace rwxet_net
{
    bool check_user_cfg(){
        const char * homedir;

        #ifdef WIN32
            homedir = getenv("USERPROFILE");
        #else
            homedir = getenv("HOME");
            if(strnlen(homedir,100) < 3){
                struct passwd *pw = getpwuid(getuid());
                homedir = pw->pw_dir;
            }
        #endif

        std::cout << homedir << std::endl;

        return true;
    }
} // namespace rwxet_net
