#ElastiCode Cordova BackView example

This is an example of implementing our Cordova plugin for BackView service  
The platform is Cordova (iOS only) and the language is JavaScript.

##Requirements:

- You need to integrate our SDK with premium integration
- Go to the dashboard and create 3 experiences for this example
- Add 2 appTriggers, their type should be “backView section”
- Name the sections “backViewSection_1” and “backViewSection_2”
- Attach two of the experiences you created to the sections, one for every section
- Attach the third experience to an appTrigger that called “BackView” - this is our main section
- Add an “apply to all” audience for all attached experiences

##How to use:

1) Put your API key  
2) Run the project  
3) click on the Home button once, the app goes to the background  
4) Double click on the Home button and you will see the Main back view section that you created  
5) Go back to the app, click “beginSection1” and repeat (3) and (4) - you will see the first back view section that you created  
6) Click “beginSection2” and repeat (3) and (4) to see the second back view section.  
7) Click “end all sections” to see the main back view section again.
