cordova.define('cordova/plugin_list', function(require, exports, module) {
module.exports = [
    {
        "id": "com.elasticode.cordova.Elasticode",
        "file": "plugins/com.elasticode.cordova/www/elasticode.js",
        "pluginId": "com.elasticode.cordova",
        "clobbers": [
            "elasticode"
        ]
    }
];
module.exports.metadata = 
// TOP OF METADATA
{
    "cordova-plugin-whitelist": "1.3.0",
    "com.elasticode.cordova": "2.0.4"
};
// BOTTOM OF METADATA
});