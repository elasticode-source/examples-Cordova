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
        document.getElementById("state1").addEventListener("click", state1);
        document.getElementById("state2").addEventListener("click", state2);
        document.getElementById("visit1").addEventListener("click", visit1);
        document.getElementById("visit2").addEventListener("click", visit2);
        document.getElementById("goal1").addEventListener("click", goal1);
        document.getElementById("goal2").addEventListener("click", goal2);
        document.getElementById("share").addEventListener("click", share);

        // Setting iOS and android api keys, which you can find in Dashboard -> acoount
        window.elasticode.setAndroidApiKey("your-api-key-here");
        window.elasticode.setIOSApiKey("your-api-key-here");
        
        // Creating session params object
        var params = window.elasticode.createSessionParamsObject();
        
        // Define the two cases, the first index is the default
        params.data.defineCase("case1",4);
        params.data.defineCase("case2",7);
        
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

function state1()
{
        // State index for case 1
        window.elasticode.stateIndexForCase("case1", function(value){
    
         console.log(String(value));
    
         });
}

function state2()
{       // State index for case 1
        window.elasticode.stateIndexForCase("case2", function(value){
    
         console.log(String(value));
    
         });
}

function visit1()
{   // Visit case 1, you can call this only after 'state index'
    window.elasticode.visitCase("case1");
}

function visit2()
{   // Visit case 2, you can call this only after 'state index'
    window.elasticode.visitCase("case2");
}

function goal1()
{   // Goal reached for case 1, you can call this only after case visited
    window.elasticode.goalReached("case1");
}

function goal2()
{   // Goal reached for case 2, you can call this only after case visited
    window.elasticode.goalReached("case2");
}

function share()
{
    var attributes = {"name":"david"};
    // Share user info, you can share your own parameters
    window.elasticode.shareUserInfo(attributes);
    
}
