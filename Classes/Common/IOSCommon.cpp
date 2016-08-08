//
//  IOSCommon.cpp
//  xzmj2
//
//  Created by SaintKing on 8/8/16.
//
//

#include <stdio.h>
#include "IOSCommon.h"

IOSCommon::IOSCommon()
{
    
}
IOSCommon::~IOSCommon()
{
    
}

bool IOSCommon::IsIpad3()
{
    return false;
}

bool IOSCommon::IsIpad()
{
    return false;
}

void IOSCommon::OpenURL(char * url)
{
    printf(">>>>>[IOSCommon::OpenURL(char * url)]");
}