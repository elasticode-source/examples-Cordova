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
        document.getElementById("section1").addEventListener("click", beginSection1);
        document.getElementById("section2").addEventListener("click", beginSection2);
        document.getElementById("end").addEventListener("click", endSection);
        
        // Setting iOS api key, which you can find in Dashboard -> acoount
        window.elasticode.setIOSApiKey("your-api-key-here");
        
        // Creating session params object
        var params = window.elasticode.createSessionParamsObject();
        
        // Define backView sections, you need to add the section from the dashboard first
        params.data.defineBackViewSection("backViewSection_1");
        params.data.defineBackViewSection("backViewSection_2");
        
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


function beginSection1()
{   // Begin backView section
    window.elasticode.beginBackViewSection("backViewSection_1");
}


function beginSection2()
{   // Begin backView section
    window.elasticode.beginBackViewSection("backViewSection_2");
}


function endSection()
{   // End any backView section thats on now
    window.elasticode.endBackViewSection();
}
