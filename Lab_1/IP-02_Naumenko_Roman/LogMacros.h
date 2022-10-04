#if DEBUG
    #define InfoLog(info) std::cout << info << std::endl
    #define DebugLog(info) std::cout <<  "DebugLog[" << __FILE__ << ":" << __LINE__ << "]: " << info << std::endl
#else
    #define InfoLog(info) 0
    #define DebugLog(info) 0 
#endif
