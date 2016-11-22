/*global cordova, module*/
var channel = require('cordova/channel');

channel.onCordovaReady.subscribe(function() {
    //Call your plugin and do whatever you need to do with the results of it
    //exec(successCallback, errorCallback, "Device", "getDeviceInfo", []);
    cordova.exec(
        function(dataStr) {
            var data = JSON.parse(dataStr);
            if(data && data.hasOwnProperty("functionName")
                && data.hasOwnProperty("family")
                && (window.elasticode._actionsByName.hasOwnProperty(data["family"])
                && window.elasticode._actionsByName[data["family"]].hasOwnProperty(data["functionName"]))){
                var callback = window.elasticode._actionsByName[data["family"]][data["functionName"]];
                if(data.hasOwnProperty("params")){
                    callback(data["params"]);
                }else{
                    callback();
                }
            }
        },
        function() {}, "ElastiCode", "initJSFunctionCallback", []);
    cordova.exec(
        function(dataStr) {
            var data = JSON.parse(dataStr);
            if(data && data.hasOwnProperty("eventName")
                && data.hasOwnProperty("detail")){
                var params = { detail: data["detail"]};
                document.dispatchEvent(new CustomEvent(data["eventName"], params));
            }
        },
        function() {}, "ElastiCode", "initJSEventCallback", []);
});
module.exports = {
    _checkFunction : function(callback){
        if(typeof callback == 'function'){
            return callback;
        }
        return function (){};
    },
    _actionsByName : {
        ec : {
            "onLaunchComplete" : function(){}
        },
        tpa : {},
        global : {},
        atu: {}
    },
    _sessionParamsData : {},
    createSessionParamsObject : function(){
        var sessionParamsObject = {
            ECType : {
                bool : 1,
                int : 2,
                double : 3,
                string : 4,
                arrayOfBool : 11,
                arrayOfInt : 12,
                arrayOfDouble : 13,
                arrayOfString : 14
            },
            ECLogLevel: {
                none : 0,
                errors : 1,
                detailed : 2
            }
        };
        var _momentsData = [];
        var _backViewData = [];
        var _casesData = {
            cases : [],
            dynamicObjects : []
        };
        var _actionsByName = this._actionsByName;
        var _sessionAttributes = {
            global : [],
            appsFlyer : [],
            branchio : [],
            button : [],
            adjust : [],
            kochava : []
        };
        sessionParamsObject.settings = {
            onLaunchVersion :          "1.0",
            connectionTimeout :         false,
            imageDownloadTimeout :      false,
            offlineMode :               false,
            disableOnLaunch :          false,
            onTimeoutDisableOnLaunch : false,
            disableBackView :           false,
            logLevel :                  false
        };
        sessionParamsObject.data = {
            /**
             *
             * @param appTriggerName
             * @param callback
             */
            defineAppTrigger: function(appTriggerName, callback) {
                _momentsData.push(appTriggerName);
                _actionsByName.atu[appTriggerName] = window.elasticode._checkFunction(callback);
            },
            /**
             *
             * @param sectionName
             */
            defineBackViewSection: function(sectionName) {
                _backViewData.push(sectionName);
            },
            // Session attributes
            /**
             *
             * @param attributes
             */
            addSessionAttributes: function(attributes) {
                _sessionAttributes.global.push(attributes);
            },
            /**
             *
             * @param attributes
             */
            addSessionAppsFlyerAttributes: function(attributes) {
                _sessionAttributes.appsFlyer.push(attributes);
            },
            /**
             *
             * @param attributes
             */
            addSessionBranchIOAttributes: function(attributes) {
                _sessionAttributes.branchio.push(attributes);
            },
            /**
             *
             * @param attributes
             */
            addSessionButtonAttributes: function(attributes) {
                _sessionAttributes.button.push(attributes);
            },
            /**
             *
             * @param attributes
             */
            addSessionAdjustAttributes: function(attributes) {
                _sessionAttributes.adjust.push(attributes);
            },
            /**
             *
             * @param attributes
             */
            addSessionKochavaAttributes: function(attributes) {
                _sessionAttributes.kochava.push(attributes);
            },
            /**
             *
             * @param caseName
             * @param numOfStates
             */
            defineCase: function(caseName, numOfStates) {
                _casesData.cases.push([caseName, numOfStates]);
            },
            /**
             *
             * @param doName
             * @param doType
             * @param defaultValue
             */
            defineDynamicObject: function(doName, doType, defaultValue) {
                _casesData.dynamicObjects.push([doName, doType, defaultValue]);
            },
            // Third party analytics
            /**
             *
             * @param name
             * @param callBack
             */
            setThirdPartyAnalytics: function(name, callBack) {
                console.log('params.data.setThirdPartyAnalytics is Deprecated, Please use elasticode.setThirdPartyAnalytics');
                _actionsByName.tpa[name] = window.elasticode._checkFunction(callBack);
            },
            /**
             *
             * @param actionsObject
             */
            addActions : function(actionsObject){
                console.log('params.data.addActions is Deprecated, Please use elasticode.setActions');
                for (var actionName in actionsObject) {
                    if (actionsObject.hasOwnProperty(actionName)) {
                        _actionsByName.global[actionName] = window.elasticode._checkFunction(actionsObject[actionName]);
                    }
                }
            }
        };
        this._sessionParamsData._momentsData = _momentsData;
        this._sessionParamsData._backViewData = _backViewData;
        this._sessionParamsData._casesData = _casesData;
        this._sessionParamsData._sessionAttributes = _sessionAttributes;
        this._sessionParamsData._actionsByName = _actionsByName;

        return sessionParamsObject;
    },
    ecError: function(error){
        console.log("[ElastiCode] error in method: "+error);
    },
    // Initialize
    setIOSApiKey: function(apiKey) {
        cordova.exec(null, this.ecError, "ElastiCode", "setIOSApiKey", [apiKey]);
    },
    setAndroidApiKey: function(apiKey) {
        cordova.exec(null, this.ecError, "ElastiCode", "setAndroidApiKey", [apiKey]);
    },

    ready: function(){
        var actions = {};
        if(this._actionsByName.hasOwnProperty("tpa")){
            actions["tpa"] = Object.keys(this._actionsByName.tpa);
        }
        if(this._actionsByName.hasOwnProperty("global")){
            actions["global"] = Object.keys(this._actionsByName.global);
        }
        cordova.exec(null, this.ecError, "ElastiCode", "ready", [actions]);
    },
    enableHTTPS: function(){
        cordova.exec(null, this.ecError, "ElastiCode", "enableHTTPS", []);
    },
    // Third party analytics
    /**
     *
     * @param name
     * @param callBack
     */
    setThirdPartyAnalytics: function(name, callBack) {
        this._actionsByName.tpa[name] = window.elasticode._checkFunction(callBack);
    },
    // Actions
    /**
     *
     * @param actionsObject
     */
    setActions : function(actionsObject){
        for (var actionName in actionsObject) {
            if (actionsObject.hasOwnProperty(actionName)) {
                this._actionsByName.global[actionName] = window.elasticode._checkFunction(actionsObject[actionName]);
            }
        }
    },
    setOnLaunchCallback : function(callback) {
        this._actionsByName.ec["onLaunchComplete"] = window.elasticode._checkFunction(callback);
    },
    //-------- Session
    /**
     *
     * @param inProduction
     * @param sessionParams
     */
    setSessionParams: function(inProduction, sessionParams) {
        var actions = {
            "tpa" : Object.keys(this._sessionParamsData._actionsByName.tpa),
            "global" : Object.keys(this._sessionParamsData._actionsByName.global)
        };

        sessionParams.data = {
            "moments" : this._sessionParamsData._momentsData,
            "backViewSections" : this._sessionParamsData._backViewData,
            "advanced" : this._sessionParamsData._casesData,
            "attributes" : this._sessionParamsData._sessionAttributes,
            "actions" : actions
        };
        cordova.exec(null, this.ecError, "ElastiCode", "setSessionParams", [inProduction, sessionParams]);
    },
    /**
     *
     */
    restartSession: function() {
        cordova.exec(null, this.ecError, "ElastiCode", "restartSession", []);
    },

    //-------- App triggers
    /**
     *
     * @param appTriggerName
     */
    showAppTrigger: function(appTriggerName) {
        cordova.exec(null, this.ecError, "ElastiCode", "showAppTrigger", [appTriggerName]);
    },
    /**
     *
     * @param appTriggerName
     * @param context
     */
    showAppTriggerWithContext: function(appTriggerName, context) {
        cordova.exec(null, this.ecError, "ElastiCode", "showAppTriggerWithContext", [appTriggerName, context]);
    },
    /**
     *
     * @param hadGoalConversion
     * @param callBack
     */
    endAppTrigger: function(hadGoalConversion, callback) {
        this._actionsByName.ec["endMoment_afterDismiss"] = window.elasticode._checkFunction(callback);
        cordova.exec(null, this.ecError, "ElastiCode", "endAppTrigger", [hadGoalConversion]);
    },
    /**
     *
     * @param appTriggerName
     */
    goalReachedForAppTrigger: function(appTriggerName) {
        cordova.exec(null, this.ecError, "ElastiCode", "goalReachedForAppTrigger", [appTriggerName]);
    },
    /**
     *
     * @param sectionName
     */
    beginBackViewSection: function(sectionName) {
        cordova.exec(null, this.ecError, "ElastiCode", "beginBackViewSection", [sectionName]);
    },
    /**
     *
     */
    endBackViewSection: function() {
        cordova.exec(null, this.ecError, "ElastiCode", "endBackViewSection", []);
    },
    // FAQ
    /**
     *
     * @param faqCode
     */
    showFAQ: function(faqCode, callback) {
        this._actionsByName.ec["faqCompleted"] = window.elasticode._checkFunction(callback);
        cordova.exec(null, this.ecError, "ElastiCode", "showFAQ", [faqCode]);
    },
    // User information
    /**
     *
     * @param attributes
     */
    shareUserInfo: function(attributes) {
        cordova.exec(null, this.ecError, "ElastiCode", "shareUserInfo", [attributes]);
    },

    //-------- Cases & Dynamic objects

    /**
     *
     * @param caseName
     * @param callback
     */
    stateIndexForCase: function(caseName, callback) {
        cordova.exec(window.elasticode._checkFunction(callback), this.ecError, "ElastiCode", "stateIndexForCase", [caseName]);
    },
    /**
     *
     * @param caseName
     * @param callback
     */
    stateIndexWithoutVisitForCase: function(caseName, callback) {
        cordova.exec(window.elasticode._checkFunction(callback), this.ecError, "ElastiCode", "stateIndexWithoutVisitForCase", [caseName]);
    },
    /**
     *
     * @param doName
     * @param callback
     */
    valueForDynamicObject: function(doName, callback) {
        cordova.exec(window.elasticode._checkFunction(callback), this.ecError, "ElastiCode", "valueForDynamicObject", [doName]);
    },
    /**
     *
     * @param doName
     */
    valueWithoutVisitForDynamicObject: function(doName, callback) {
        cordova.exec(window.elasticode._checkFunction(callback), this.ecError, "ElastiCode", "valueWithoutVisitForDynamicObject", [doName]);
    },
    /**
     *
     * @param caseName
     */
    visitCase: function(caseName) {
        cordova.exec(null, this.ecError, "ElastiCode", "visitCase", [caseName]);
    },
    /**
     *
     * @param doName
     */
    visitDynamicObject: function(doName) {
        cordova.exec(null, this.ecError, "ElastiCode", "visitDynamicObject", [doName]);
    },
    /**
     *
     * @param caseName
     */
    goalReached: function(caseName) {
        cordova.exec(null, this.ecError, "ElastiCode", "goalReached", [caseName]);
    },
    /**
     *
     * @param doName
     */
    dynamicObjectGoalReached: function(doName) {
        cordova.exec(null, this.ecError, "ElastiCode", "dynamicObjectGoalReached", [doName]);
    },

    //-------- Events
    /**
     *
     * @param eventName
     */
    event: function(eventName) {
        cordova.exec(null, this.ecError, "ElastiCode", "event", [eventName]);
    },
    /**
     *
     * @param eventName
     * @param attributes
     */
    eventWithAttributes: function(eventName, attributes) {
        cordova.exec(null, this.ecError, "ElastiCode", "eventWithAttributes", [eventName, attributes]);
    }
};
