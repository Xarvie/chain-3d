//
// Created by xarvie on 2020/10/6.
//

#ifndef INC_3D4_DEVICERESOURCE_H
#define INC_3D4_DEVICERESOURCE_H

#include <cstdio>
#if defined(IOS)
#include <CoreFoundation/CFBundle.h>
#include <CoreFoundation/CFURL.h>
#endif

#include <cassert>
#include "ResourceMgr.h"
#include "Config.h"
class DeviceResource {

public:
    static FILE* load(){
#if defined(IOS)

        printf("GameBundle start");
        CFBundleRef gameBundle = CFBundleGetMainBundle();
        if(gameBundle == NULL)
            printf("GameBundle NULL");
       

        CFStringRef filename = CFSTR("data");
        CFStringRef fileExtension = CFSTR("0");
        CFStringRef subdirectory = CFSTR("");
        CFURLRef fileLocation ;

        fileLocation = CFBundleCopyResourceURL(gameBundle, filename, fileExtension, subdirectory);
        if(fileLocation == NULL)
            return NULL;
        printf("GameBundle start2");
        char manifest_path[1024];
        CFURLGetFileSystemRepresentation(fileLocation, true,
                                         reinterpret_cast<UInt8 *>(manifest_path), sizeof(manifest_path));
        CFRelease(fileLocation);

        FILE* f = fopen(manifest_path, "r"); // etc.
        if(f)
        {
            printf("load ok%s", manifest_path);
            fclose(f);
            res.loadFromPath(manifest_path);
        }
        else
        {

            printf("load failed");
        }
#else
        if(res.loadFromPath("./data.0")){
            res.loadFromPath("../data.0");
        }
        return 0;
#endif

    }

};


#endif //INC_3D4_DEVICERESOURCE_H
