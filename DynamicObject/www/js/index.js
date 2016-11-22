/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
var app = {
    // Application Constructor
    initialize: function() {
        document.addEventListener('deviceready', this.onDeviceReady.bind(this), false);
    },

    // deviceready Event Handler
    //
    // Bind any cordova events here. Common events are:
    // 'pause', 'resume', etc.
    onDeviceReady: function() {
        this.receivedEvent('deviceready');

        // Adding listeners for the buttons
        document.getElementById("value1").addEventListener("click", value1);
        document.getElementById("value2").addEventListener("click", value2);
        document.getElementById("visit1").addEventListener("click", visit1);
        document.getElementById("visit2").addEventListener("click", visit2);
        document.getElementById("goal1").addEventListener("click", goal1);
        document.getElementById("goal2").addEventListener("click", goal2);
        document.getElementById("share").addEventListener("click", share);
        
        // Setting iOS and android api keys, which you can find in Dashboard -> acoount
        window.elasticode.setAndroidApiKey("your-api-key-here");
        window.elasticode.setIOSApiKey("your-api-key-here");
        
        // Creating session params object
        var params = window.elasticode.createSessionParamsObject();
        
        // Define the two dynamic objects
        params.data.defineDynamicObject("DynamicObject1",params.ECType.string,"value1");
        params.data.defineDynamicObject("DynamicObject2",params.ECType.arrayOfString,["value1","value2","value3"]);
        
        // Set the session params, 'bool' parameter is for development/production mode
        window.elasticode.setSessionParams(false, params);
        
        // Ready is mandatory
        window.elasticode.ready();
    },

    // Update DOM on a Received Event
    receivedEvent: function(id) {
        var parentElement = document.getElementById(id);
        var listeningElement = parentElement.querySelector('.listening');
        var receivedElement = parentElement.querySelector('.received');

        listeningElement.setAttribute('style', 'display:none;');
        receivedElement.setAttribute('style', 'display:block;');

        console.log('Received Event: ' + id);
    }
};

app.initialize();

function value1()
{   // Value for dynamic object 1
    window.elasticode.valueForDynamicObject("DynamicObject1", function(value){console.log(value);});
    
}

function value2()
{   // Value for dynamic object 1
    window.elasticode.valueForDynamicObject("DynamicObject2", function(value){console.log(value);});
    
}

function visit1()
{   // Visit dynamic object 1, you can call this only after 'value for'
    window.elasticode.visitDynamicObject("DynamicObject1");
    
}

function visit2()
{   // Visit dynamic object 2, you can call this only after 'value for'
    window.elasticode.visitDynamicObject("DynamicObject2");
}

function goal1()
{   // Goal reached for dynamic object 1, you can call this only after dynamic object 1 visited
    window.elasticode.dynamicObjectGoalReached("DynamicObject1");
}

function goal2()
{   // Goal reached for dynamic object 2, you can call this only after dynamic object 2 visited
    window.elasticode.dynamicObjectGoalReached("DynamicObject2");
}

function share()
{
    var attributes = {"name":"david"};
    // Share user info, you can share your own parameters
    window.elasticode.shareUserInfo(attributes);
    
}


