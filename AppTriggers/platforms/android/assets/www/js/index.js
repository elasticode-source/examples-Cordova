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
        document.getElementById("show1").addEventListener("click", showAppTrigger1);
        document.getElementById("show2").addEventListener("click", showAppTrigger2);
        document.getElementById("show3").addEventListener("click", showAppTrigger3);
        
        // Setting iOS and android api keys, which you can find in Dashboard -> acoount
        window.elasticode.setAndroidApiKey("your-api-key-here");
        window.elasticode.setIOSApiKey("your-api-key-here");
        
        // Creating session params object
        var params = window.elasticode.createSessionParamsObject();
        
        // Defining the app triggers, you need to add the app triggers from the dashboard first
        params.data.defineAppTrigger("appTrigger1", function(active){  });
        params.data.defineAppTrigger("appTrigger2", function(active){  });
        params.data.defineAppTrigger("appTrigger3", function(active){  });
        
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


function showAppTrigger1()
{   // Show app trigger
    window.elasticode.showAppTrigger("appTrigger1");
}

function showAppTrigger2()
{   // Show app trigger
    window.elasticode.showAppTrigger("appTrigger2");
}

function showAppTrigger3()
{   // Show app trigger
    window.elasticode.showAppTrigger("appTrigger3");
}
