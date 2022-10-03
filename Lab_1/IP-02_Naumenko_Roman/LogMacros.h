#if DEBUG
    #define DebugLog(info) std::cout << \
    "DebugLog["<< __FILE__ << ":" << __LINE__ << "]: "<< std::endl << \
    info << std::endl
#else
    #define DebugLog(info) 0 
#endif