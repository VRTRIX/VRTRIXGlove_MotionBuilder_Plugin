#if defined(_WIN32)
    #include <pyconfig-win32.h>
#elif defined(__linux__)
    #include <pyconfig-linux.h>
#elif defined(__MACH__)
    #include <pyconfig-osx.h>
#endif