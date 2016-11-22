//
//  ElastiCode+PEnums.h
//  ElastiCode
//
//  Created by Tomer Shkolnik on 1.2.2016.
//  Copyright © 2016 Elasticode. All rights reserved.
//

#ifndef ElastiCode_PEnums_h
#define ElastiCode_PEnums_h
typedef enum momentType{
    ECMomentType_none = -1, // Not a moment
    ECMomentType_appLaunch = 0,     // OnBoarding
    ECMomentType_inSession = 1,     // Moment
    ECMomentType_appSwitcher = 2    // app switcher
}ECMomentType;

typedef enum elastiCodeLogLevel
{
    elastiCodeLogLevelNone,
    elastiCodeLogLevelErrors,
    elastiCodeLogLevelDetailed
} ECLogLevel;

typedef enum dObjType
{
    ElastiCodeDObjType_none = 0,
    ElastiCodeDObjType_bool = 1,
    ElastiCodeDObjType_int = 2,
    ElastiCodeDObjType_double = 3,
    ElastiCodeDObjType_string = 4,
    ElastiCodeDObjType_color = 7,
    ElastiCodeDObjType_frame = 8,
    ElastiCodeDObjType_arrayOfBool = 11,
    ElastiCodeDObjType_arrayOfInt = 12,
    ElastiCodeDObjType_arrayOfDouble = 13,
    ElastiCodeDObjType_arrayOfString = 14,
    ElastiCodeDObjType_arrayOfColor = 17,
    ElastiCodeDObjType_arrayOfFrame = 18,
} ElastiCodeDObjType;

typedef enum listOfOptionsType
{
    ElastiCodeListOfOptionsType_none = 0,
    ElastiCodeListOfOptionsType_string = 4,
    ElastiCodeListOfOptionsType_image = 5,
    ElastiCodeListOfOptionsType_action = 6,
    ElastiCodeListOfOptionsType_arrayOfInt = 12,
    ElastiCodeListOfOptionsType_arrayOfString = 14,
    ElastiCodeListOfOptionsType_arrayOfImage = 15,
    ElastiCodeListOfOptionsType_arrayOfAction = 16
} ElastiCodeListOfOptionsType;


typedef enum ECDeviceSupport
{
    ECDeviceSupport_all = 0, // iPad - Popup, iPhone - Full screen
    ECDeviceSupport_iPhoneOnly = 1, // iPad - Will not display, iPhone - Full screen
    ECDeviceSupport_iPadOnly = 2 // iPad - Full screen, iPhone - will not display
} ECDeviceSupport;

typedef enum ECExperienceType
{
    ECExperienceType_appTrigger = 0,
    ECExperienceType_dynamicOB = 1,
    ECExperienceType_interactiveFAQ = 2,
    ECExperienceType_supportLinks = 3,
    ECExperienceType_releaseNotes = 4
} ECExperienceType;
#endif /* ElastiCode_PEnums_h */


