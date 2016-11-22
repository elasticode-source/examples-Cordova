# Elasticode Cordova Plugin 

Cordova Plugin for the Elasticode SDKs:
- iOS
- Android


## Usage

### 1. Install into project

cd into root of your cordova/phonegap project
```
cordova plugin add <PATH TO PLUGIN>
```

#### For iOS platform 
For iOS add variable IOS_URL_SCHEME for elasticode url scheme like so:
```
--variable IOS_URL_SCHEME=ecXXXXXXXX
```
(While ecXXXXXXXX is your iOS url scheme)

#### For Android platform
For Android add variable ANDROID_URL_SCHEME for elasticode url scheme like so:
```
--variable ANDROID_URL_SCHEME=ecXXXXXXXX
```
(While ecXXXXXXXX is your android url scheme)


#### Full example
```
cordova plugin add /Users/superman/elasticode-cordova-plugin --variable IOS_URL_SCHEME=ecXXXXXXXX --variable ANDROID_URL_SCHEME=ecXXXXXXXX
```

### 2. Build your app
```
cordova build
```
