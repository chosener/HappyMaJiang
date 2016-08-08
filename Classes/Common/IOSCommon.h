//
//  IOSCommon.h
//  xzmj2
//
//  Created by SaintKing on 8/8/16.
//
//

#ifndef IOSCommon_h
#define IOSCommon_h

class IOSCommon {
public:
    IOSCommon();
    ~IOSCommon();
    
    static bool IsIpad3();
    static bool IsIpad();

    static void OpenURL(char * url);
};

#endif /* IOSCommon_h */
