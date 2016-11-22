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
        document.getElementById("show1").addEventListener("click", showFAQ1);
        document.getElementById("show2").addEventListener("click", showFAQ2);
        document.getElementById("show3").addEventListener("click", showFAQ3);

        // Setting iOS api key, which you can find in Dashboard -> acoount
        window.elasticode.setIOSApiKey("your-api-key-here");
        
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

// Show FAQ with FAQTrigger key
function showFAQ1(){
    window.elasticode.showFAQ(
                              "FAQTrigger-code-here",
                              function(didAppear){
                              if(didAppear){
                              // FAQ did appear
                              }
                              }
                              );
    
}

// Show FAQ with FAQTrigger key
function showFAQ2(){
    window.elasticode.showFAQ(
                              "FAQTrigger-code-here",
                              function(didAppear){
                              if(didAppear){
                              // FAQ did appear
                              }
                              }
                              );
    
}

// Show FAQ with FAQTrigger key
function showFAQ3(){
    window.elasticode.showFAQ(
                              "FAQTrigger-code-here",
                              function(didAppear){
                              if(didAppear){
                              // FAQ did appear
                              }
                              }
                              );
    
}
