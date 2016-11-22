package com.elasticode.cordova;


import android.app.Activity;
import android.content.Intent;
import android.util.Log;
import android.view.View;

import com.elasticode.model.ElasticodeAction;
import com.elasticode.model.ElasticodeDObjType;
import com.elasticode.model.ElasticodeSessionParams;
import com.elasticode.provider.Elasticode;
import com.elasticode.provider.ElasticodeBlock;
import com.elasticode.provider.callback.DismissBlock;
import com.elasticode.provider.callback.ElasticodeResponse;
import com.elasticode.view.ElasticodeOnClickListener;
import com.google.gson.Gson;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.PluginResult;
import org.json.JSONObject;
import org.json.JSONArray;
import org.json.JSONException;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Observable;
import java.util.Observer;


public class ElasticodeCordovaPlugin extends CordovaPlugin {

    public static final String TAG = "elasticode";
    private Elasticode elasticode;

    @Override
    public void onNewIntent(Intent intent) {
        if(elasticode != null){
            elasticode.setNewIntent(intent);
        }
    }
    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        if(action.equals("initJSFunctionCallback")){
            scc_jsFunction = callbackContext;
            return true;
        }
        if(action.equals("initJSEventCallback")){
            scc_jsEvent = callbackContext;
            return true;
        }
        if (action.equals("setAndroidApiKey")) {
            String apiKey = args.getString(0);
            this.setAPIKey(callbackContext, apiKey);
            return true;
        }
        if (action.equals("setIOSApiKey")) {
            return true;
        }
        if(!_sanityCheck()){
            callbackContext.error("Please use setAndroidApiKey first");
            return false;
        }

        if (action.equals("ready")) {
            JSONObject actions = args.getJSONObject(0);
            this.ready(actions);
            return true;
        }
        if (action.equals("enableHTTPS")) {
            this.enableHTTPS();
            return true;
        }
        if (action.equals("setSessionParams")) {
            boolean inProduction = args.getBoolean(0);
            JSONObject sessionParams = args.getJSONObject(1);
            this.setSessionParams(inProduction, sessionParams);
            return true;
        }
        if (action.equals("restartSession")) {
            this.restartSession();
            return true;
        }
        if (action.equals("showAppTrigger")) {
            String appTriggerName = args.getString(0);
            this.showAppTrigger(appTriggerName);
            return true;
        }
        if (action.equals("showAppTriggerWithContext")) {
            String appTriggerName = args.getString(0);
            JSONObject context = args.getJSONObject(1);
            this.showAppTriggerWithContext(appTriggerName, context);
            return true;
        }
        if (action.equals("endAppTrigger")) {
            boolean goalReched = args.getBoolean(0);
            this.endAppTrigger(goalReched);
            return true;
        }
        if (action.equals("goalReachedForAppTrigger")) {
            String appTriggerName = args.getString(0);
            this.goalReachedForAppTrigger(appTriggerName);
            return true;
        }
        if (action.equals("showFAQ")) {
            return true;
        }
        if (action.equals("shareUserInfo")) {
            JSONObject userInfo = args.getJSONObject(0);
            this.shareUserInfo(userInfo);
            return true;
        }
        if (action.equals("setUserEmail")) {
            String userEmail = args.getString(0);
            this.setUserEmail(userEmail);
            return true;
        }
        if (action.equals("stateIndexForCase")) {
            String caseName = args.getString(0);
            this.stateIndexForCase(callbackContext, caseName);
            return true;
        }
        if (action.equals("stateIndexWithoutVisitForCase")) {
            String caseName = args.getString(0);
            this.stateIndexWithoutVisitForCase(callbackContext, caseName);
            return true;
        }
        if (action.equals("valueForDynamicObject")) {
            String caseName = args.getString(0);
            this.valueForDynamicObject(callbackContext, caseName);
            return true;
        }
        if (action.equals("valueWithoutVisitForDynamicObject")) {
            String caseName = args.getString(0);
            this.valueWithoutVisitForDynamicObject(callbackContext, caseName);
            return true;
        }
        if (action.equals("visitCase")) {
            String caseName = args.getString(0);
            this.visitCase(caseName);
            return true;
        }
        if (action.equals("visitDynamicObject")) {
            String caseName = args.getString(0);
            this.visitDynamicObject(caseName);
            return true;
        }
        if (action.equals("goalReached")) {
            String caseName = args.getString(0);
            this.goalReached(caseName);
            return true;
        }
        if (action.equals("dynamicObjectGoalReached")) {
            String caseName = args.getString(0);
            this.dynamicObjectGoalReached(caseName);
            return true;
        }
        if (action.equals("event") || action.equals("eventWithAttributes")) {
            String eventName = args.getString(0);
            JSONObject eventAttributes = null;
            if(args.length() == 2){
                eventAttributes = args.getJSONObject(1);
            }
            this.event(eventName, eventAttributes);
            return true;
        }
        return false;
    }

    // Initialize
    private void setAPIKey(CallbackContext callbackContext, String apiKey) {
        if (apiKey == null || apiKey.length() == 0) {
            callbackContext.error("Failed to setAndroidApiKey, Invalid API key");
        }else{
            Activity activity = this.cordova.getActivity();
            elasticode = Elasticode.getInstance(activity, apiKey, elasticodeObserver);
        }
    }
    private void ready(JSONObject actions) {
        try {
            JSONArray tpa = actions.getJSONArray("tpa");
            for (int i = 0; i < tpa.length(); i++){
                final String currTPA = tpa.getString(i);
                elasticode.setThirdPartyAnalytics(currTPA, new ElasticodeBlock() {
                    @Override
                    public void perform(String s) {
                        fireJSFunction(currTPA, "tpa", s);
                    }
                });
            }
            JSONArray global = actions.getJSONArray("global");
            for (int i = 0; i < global.length(); i++){
                final String currActionName = global.getString(i);
                ElasticodeAction currAction = new ElasticodeAction(currActionName, new ElasticodeOnClickListener(){
                    @Override
                    public void onClick(View v) {
                        super.onClick(v);
                        fireJSFunction(currActionName, "global", null);
                    }
                });
                elasticode.addActions(currAction);
            }
        } catch (JSONException ignored) {}
        elasticode.ready();
    }
    private void enableHTTPS() {
        elasticode.enableHTTPS();
    }

    // Session
    private void setSessionParams(boolean inProduction, JSONObject sessionParams){

        JSONObject settings = null;
        JSONObject data = null;
        try {
            settings = sessionParams.getJSONObject("settings");
            data = sessionParams.getJSONObject("data");
        } catch (JSONException ignored) {}
        if(settings == null || data == null){
            return;
        }
        Activity activity = this.cordova.getActivity();
        ElasticodeSessionParams params = new ElasticodeSessionParams(inProduction, activity);
        String[] settingsKeys = {
                "onLaunchVersion",
                "connectionTimeout",
                "imageDownloadTimeout",
                "disableOnLaunch",
                "onTimeoutDisableOnLaunch",
                "offlineMode"
        };
        for( int sKeyIndex = 0; sKeyIndex < settingsKeys.length; sKeyIndex++) {
            try {
                if(settings.has(settingsKeys[sKeyIndex])){
                    String sKey = settingsKeys[sKeyIndex];
                    switch (sKeyIndex) {
                        case 0:
                            String onLaunchVersion = settings.getString(sKey);
                            if (onLaunchVersion == null) {
                                continue;
                            }
                            params.settings.setOnLaunchVersion(onLaunchVersion);
                            break;
                        case 1:
                            int timeoutParam = settings.getInt(sKey);
                            params.settings.setConnectionTimeout(timeoutParam);
                            break;
                        case 2:
                            int imageDownloadTimeout = settings.getInt(sKey);
                            params.settings.setImageDownloadTimeout(imageDownloadTimeout);
                            break;
                        case 3:
                            boolean disabledOnLaunch = settings.getBoolean(sKey);
                            params.settings.setDisabledOnLaunch(disabledOnLaunch);
                            break;
                        case 4:
                            boolean onTimeoutDisableOnLaunch = settings.getBoolean(sKey);
                            params.settings.setOnTimeoutDisableOnLaunch(onTimeoutDisableOnLaunch);
                            break;
                        case 5:
                            boolean offlineMode = settings.getBoolean(sKey);
                            params.settings.setOfflineMode(offlineMode);
                            break;
                        default:
                            break;
                    }
                }
            }catch (JSONException ignored){}
        }

        if(data.has("attributes")) {
            JSONObject attributes = null;
            try {
                attributes = data.getJSONObject("attributes");
            } catch (JSONException ignored) {}
            if (attributes != null) {
                if (attributes.has("global")) {
                    JSONArray values = null;
                    try {
                        values = attributes.getJSONArray("global");
                    } catch (JSONException ignored) {}
                    if(values != null) {
                        for (int i = 0; i < values.length(); i++) {
                            try {
                                JSONObject value = values.getJSONObject(i);
                                Map<String, Object> valueMap = _jsonToMap(value);
                                params.data.addSessionAttributes(valueMap);
                            } catch (JSONException ignored) {}
                        }
                    }
                }
                if (attributes.has("adjust")) {
                    JSONArray values = null;
                    try {
                        values = attributes.getJSONArray("adjust");
                    } catch (JSONException ignored) {}
                    if(values != null) {
                        for (int i = 0; i < values.length(); i++) {
                            try {
                                JSONObject value = values.getJSONObject(i);
                                Map<String, Object> valueMap = _jsonToMap(value);
                                params.data.addSessionAdjustAttributes(valueMap);
                            } catch (JSONException ignored) {}
                        }
                    }
                }
                if (attributes.has("appsFlyer")) {
                    JSONArray values = null;
                    try {
                        values = attributes.getJSONArray("appsFlyer");
                    } catch (JSONException ignored) {}
                    if(values != null) {
                        for (int i = 0; i < values.length(); i++) {
                            try {
                                JSONObject value = values.getJSONObject(i);
                                Map<String, Object> valueMap = _jsonToMap(value);
                                params.data.addSessionAppsFlyerAttributes(valueMap);
                            } catch (JSONException ignored) {}
                        }
                    }
                }
                if (attributes.has("branchio")) {
                    JSONArray values = null;
                    try {
                        values = attributes.getJSONArray("branchio");
                    } catch (JSONException ignored) {}
                    if(values != null) {
                        for (int i = 0; i < values.length(); i++) {
                            try {
                                JSONObject value = values.getJSONObject(i);
                                Map<String, Object> valueMap = _jsonToMap(value);
                                params.data.addSessionBranchIOAttributes(valueMap);
                            } catch (JSONException ignored) {}
                        }
                    }
                }
                if (attributes.has("button")) {
                    JSONArray values = null;
                    try {
                        values = attributes.getJSONArray("button");
                    } catch (JSONException ignored) {}
                    if(values != null) {
                        for (int i = 0; i < values.length(); i++) {
                            try {
                                JSONObject value = values.getJSONObject(i);
                                Map<String, Object> valueMap = _jsonToMap(value);
                                params.data.addSessionButtonAttributes(valueMap);
                            } catch (JSONException ignored) {}
                        }
                    }
                }
                if (attributes.has("kochava")) {
                    JSONArray values = null;
                    try {
                        values = attributes.getJSONArray("kochava");
                    } catch (JSONException ignored) {}
                    if(values != null) {
                        for (int i = 0; i < values.length(); i++) {
                            try {
                                JSONObject value = values.getJSONObject(i);
                                Map<String, Object> valueMap = _jsonToMap(value);
                                params.data.addSessionKochavaAttributes(valueMap);
                            } catch (JSONException ignored) {}
                        }
                    }
                }
            }
        }

        if(data.has("moments")){
            JSONArray moments = null;
            try {
                moments = data.getJSONArray("moments");
            } catch (JSONException ignored) {}
            if(moments != null){
                for (int i = 0; i < moments.length(); i++) {
                    try {
                        String appTriggerName = moments.getString(i);
                        params.data.defineAppTrigger(appTriggerName);
                    } catch (JSONException ignored) {}
                }
            }
        }
        if(data.has("advanced")){
            JSONObject advanced = null;
            try {
                advanced = data.getJSONObject("advanced");
            } catch (JSONException ignored) {}
            if(advanced != null){
                if(advanced.has("cases")){
                    JSONArray cases = null;
                    try {
                        cases = advanced.getJSONArray("cases");
                    } catch (JSONException ignored) {}
                    if(cases != null){
                        for (int i = 0; i < cases.length(); i++) {
                            try {
                                JSONArray caseData = cases.getJSONArray(i);
                                if(caseData != null && caseData.length() == 2){
                                    String caseName = caseData.getString(0);
                                    int numOfStates = caseData.getInt(1);
                                    params.data.defineCase(caseName, numOfStates);
                                }
                            } catch (JSONException ignored) {}
                        }
                    }
                }
                if(advanced.has("dynamicObjects")){
                    JSONArray dynamicObjects = null;
                    try {
                        dynamicObjects = advanced.getJSONArray("dynamicObjects");
                    } catch (JSONException ignored) {}
                    if(dynamicObjects != null){
                        for (int i = 0; i < dynamicObjects.length(); i++) {
                            try {
                                JSONArray doData = dynamicObjects.getJSONArray(i);
                                if(doData != null && doData.length() == 3){
                                    String doName = doData.getString(0);
                                    int doType = doData.getInt(1);
                                    Object defaultValue = doData.get(2);
                                    defaultValue = _convertJSONArrayToObject(doType, defaultValue);
                                    params.data.defineDynamicObject(doName, ElasticodeDObjType.fromInteger(doType), defaultValue);
                                }
                            } catch (JSONException ignored) {}
                        }
                    }
                }
            }
        }
        elasticode.setSessionParams(params);
    }
    private void restartSession(){
        elasticode.restartSession();
    }

    // App triggers
    private void showAppTrigger(String appTriggerName){
        elasticode.showAppTrigger(appTriggerName);
    }
    private void showAppTriggerWithContext(String appTriggerName, JSONObject context){
        Map<String, Object> contextMap = null;
        try {
            contextMap = _jsonToMap(context);
        } catch (JSONException ignored) {}
        elasticode.showAppTriggerWithContext(appTriggerName, contextMap);
    }
    private void endAppTrigger(boolean goalReached){
        elasticode.endAppTriggerWithCompletionAfterDismissBlock(goalReached, new DismissBlock() {
            @Override
            public void perform() {
                fireJSFunction("endMoment_afterDismiss", "ec", null);
            }
        });
    }
    private void goalReachedForAppTrigger(String appTriggerName){
        elasticode.goalReachedForAppTrigger(appTriggerName);
    }

    // User information
    private void shareUserInfo(JSONObject userInfo){
        Map<String, Object> userInfoMap = null;
        try {
            userInfoMap = _jsonToMap(userInfo);
        } catch (JSONException ignored) {}
        elasticode.shareUserInfo(userInfoMap);
    }
    private void setUserEmail(String userEmail){
        elasticode.setUserEmail(userEmail);
    }

    // Cases & Dynamic objects
    private void stateIndexForCase(CallbackContext callbackContext, String caseName){
        int stateIndex = elasticode.stateIndexForCaseWithVisit(caseName);
        callbackContext.success(stateIndex);
    }
    private void stateIndexWithoutVisitForCase(CallbackContext callbackContext, String caseName){
        int stateIndex = elasticode.stateIndexForCaseWithoutVisit(caseName);
        callbackContext.success(stateIndex);
    }
    private void valueForDynamicObject(CallbackContext callbackContext, String caseName){
        Object value = elasticode.valueForDynamicObject(caseName);
        _convertToResult(callbackContext, value);
    }
    private void valueWithoutVisitForDynamicObject(CallbackContext callbackContext, String caseName){
        Object value = elasticode.valueForDynamicObjectWithoutVisit(caseName);
        _convertToResult(callbackContext, value);
    }
    private void visitCase(String caseName){
        elasticode.visitCase(caseName);
    }
    private void visitDynamicObject(String caseName){
        elasticode.visitDynamicObject(caseName);
    }
    private void goalReached(String caseName){
        elasticode.goalReached(caseName);
    }
    private void dynamicObjectGoalReached(String caseName){
        elasticode.goalReached(caseName);
    }

    // Events
    private void event(String eventName, JSONObject eventAttributes){
        Map<String, Object> eventAttributesMap = null;
        if(eventAttributes != null){
            try {
                eventAttributesMap = _jsonToMap(eventAttributes);
            } catch (JSONException ignored) {}
        }
        elasticode.eventWithAttributes(eventName, eventAttributesMap);
    }



    private Observer elasticodeObserver = new Observer() {
        @Override
        public void update(Observable observable, Object data) {
            if (data instanceof ElasticodeResponse) {
                ElasticodeResponse response = (ElasticodeResponse) data;
                if (response.getError() != null) {
                    Log.d(TAG, "Error"+response.getError());
                }
                switch (response.getType()) {
                    case SESSION_STARTED:
                        String detailStarted = "\"detail\": { \"success\": " + (response.getError() == null? "true" : "false") + "}";
                        fireJSEvent("EC_SessionStarted", detailStarted);
                        break;

                    case SESSION_RESTARTED:
                        String detailRestarted = "\"detail\": { \"success\": " + (response.getError() == null? "true" : "false") + "}";
                        fireJSEvent("EC_SessionRestarted", detailRestarted);
                        break;
                    case APP_TRIGGERS_DEFINED:
                        Map<String, Boolean> appTriggers = (HashMap<String, Boolean>) response.getAdditionalData();
                        for (String appTriggerName : appTriggers.keySet()) {
                            fireJSFunction(appTriggerName, "atu", appTriggers.get(appTriggerName).toString());
                        }
                        break;
                    case APP_TRIGGER_DISPLAYED:
                        String detail = "\"detail\": \""+response.getDescription()+"\"";
                        fireJSEvent("EC_AppTriggerDisplayed", detail);
                        break;
                    case RETURN_CONTEXT:
                        Map<String, Object> context = (Map<String, Object>) response.getAdditionalData();
                        break;
                    case ON_LAUNCH_DISPLAYED:
                        fireJSFunction("onLaunchComplete", "ec", response.getAdditionalData());
                        break;
                    case CASE_DEFINE:
                    case DYNAMIC_OBJECT_DEFINE:
                    case CASE_VISIT:
                    case DYNAMIC_OBJECT_VISIT:
                    case TAKE_SNAPHOT:
                    case GOAL_REACH:
                    case EVENT:
                    case SHARE_USER_INFO:
                        break;
                }
            }
        }

    };

    // Helpers
    private boolean _sanityCheck()
    {
        return elasticode != null;
    }

    public static Map<String, Object> _jsonToMap(JSONObject json) throws JSONException {
        Map<String, Object> retMap = new HashMap<String, Object>();

        if(json != JSONObject.NULL) {
            retMap = _toMap(json);
        }
        return retMap;
    }

    public static Map<String, Object> _toMap(JSONObject object) throws JSONException {
        Map<String, Object> map = new HashMap<String, Object>();

        Iterator<String> keysItr = object.keys();
        while(keysItr.hasNext()) {
            String key = keysItr.next();
            Object value = object.get(key);

            if(value instanceof JSONArray) {
                value = _toList((JSONArray) value);
            }

            else if(value instanceof JSONObject) {
                value = _toMap((JSONObject) value);
            }
            map.put(key, value);
        }
        return map;
    }

    public static List<Object> _toList(JSONArray array) throws JSONException {
        List<Object> list = new ArrayList<Object>();
        for(int i = 0; i < array.length(); i++) {
            Object value = array.get(i);
            if(value instanceof JSONArray) {
                value = _toList((JSONArray) value);
            }

            else if(value instanceof JSONObject) {
                value = _toMap((JSONObject) value);
            }
            list.add(value);
        }
        return list;
    }
    private Object _convertJSONArrayToObject(int type, Object value)
    {
        Object tempValue = value;
        int index = 0;
        if(value instanceof JSONArray){
            JSONArray valueJSONArray = (JSONArray) value;
            try {
                switch (ElasticodeDObjType.fromInteger(type)) {
                    case ARRAY_OF_BOOLEAN:
                        Boolean[] boolArray = new Boolean[valueJSONArray.length()];
                        for (;index < valueJSONArray.length(); index++){
                            boolean oneValue = valueJSONArray.getBoolean(index);
                            boolArray[index] = oneValue;
                        }
                        tempValue = boolArray;
                        break;
                    case ARRAY_OF_INTEGER:
                        Integer[] intArray = new Integer[valueJSONArray.length()];
                        for (;index < valueJSONArray.length(); index++){
                            int oneValue = valueJSONArray.getInt(index);
                            intArray[index] = oneValue;
                        }
                        tempValue = intArray;
                        break;
                    case ARRAY_OF_DOUBLE:
                        Double[] doubleArray = new Double[valueJSONArray.length()];
                        for (;index < valueJSONArray.length(); index++){
                            double oneValue = valueJSONArray.getDouble(index);
                            doubleArray[index] = oneValue;
                        }
                        tempValue = doubleArray;
                        break;
                    case ARRAY_OF_STRING:
                        String[] stringArray = new String[valueJSONArray.length()];
                        for (;index < valueJSONArray.length(); index++){
                            String oneValue = valueJSONArray.getString(index);
                            stringArray[index] = oneValue;
                        }
                        tempValue = stringArray;
                        break;
                    default:
                        break;
                }
            } catch (JSONException ignored) {}
        }
        return tempValue;
    }
    private void _convertToResult(CallbackContext callbackContext, Object value)
    {
        PluginResult dataResult = null;
        if(value != null) {
            if (value instanceof Boolean) {
                dataResult = new PluginResult(PluginResult.Status.OK, (Boolean) value);
            } else if (value instanceof Integer) {
                dataResult = new PluginResult(PluginResult.Status.OK, (Integer) value);
            } else if (value instanceof Double) {
                String temp = value.toString();
                Float fValue = Float.parseFloat(temp);
                dataResult = new PluginResult(PluginResult.Status.OK, fValue);
            } else if (value instanceof String) {
                dataResult = new PluginResult(PluginResult.Status.OK, (String) value);
            } else if (value instanceof Boolean[]
                    || value instanceof Integer[]
                    || value instanceof Double[]
                    || value instanceof String[]) {
                Gson gson = new Gson();
                try {
                    String json = gson.toJson(value);
                    dataResult = new PluginResult(PluginResult.Status.OK, new JSONArray(json));
                } catch (JSONException ignored) {
                    Log.e(TAG, ignored.getMessage());
                } catch (Exception e){
                    Log.e(TAG, e.getMessage());
                }
            }
        }
        if(dataResult != null){
            callbackContext.sendPluginResult(dataResult);
        }else{

            callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK));
        }
    }

    private CallbackContext scc_jsFunction;
    private CallbackContext scc_jsEvent;

    private void fireJSFunction(String functionName, String family, Object params)
    {
        String paramsStr = null;
        String values = "{" +
                "\"functionName\": \""+functionName+"\"," +
                "\"family\": \""+family+"\"";
        if(params != null){
            if(params instanceof String){
                paramsStr = '"'+(String)params+'"';
            }else{
                paramsStr = params.toString();
            }
            values += ", \"params\": "+paramsStr;
        }
        values += "}";
        PluginResult dataResult = new PluginResult(PluginResult.Status.OK, values);
        dataResult.setKeepCallback(true);
        scc_jsFunction.sendPluginResult(dataResult);
    }


    private void fireJSEvent(String eventName, String detail)
    {
        String values = "{" +
                "\"eventName\": \""+eventName+"\"," +
                detail +
                "}";
        PluginResult dataResult = new PluginResult(PluginResult.Status.OK, values);
        dataResult.setKeepCallback(true);
        scc_jsEvent.sendPluginResult(dataResult);
    }
}
