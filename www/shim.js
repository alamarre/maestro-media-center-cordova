var chrome = {};

chrome.cast = {};

chrome.cast.isAvailable = true;

chrome.cast.SessionRequest = class {
    constructor(appId) {
        this.appId = appId;
    }

    getAppId() {
        return this.appId;
    }
}

chrome.cast.AutoJoinPolicy = {ORIGIN_SCOPED: "origin"}

chrome.cast.ApiConfig = class {
    constructor(sessionRequest,
        sessionListenter,
        receiverListener,
        autoJoinPolicy
    ) {
        this.sessionRequest = sessionRequest;
        this.sessionListenter = sessionListenter;
        this.receiverListener = receiverListener;
        this.autoJoinPolicy = autoJoinPolicy;
    }
}

chrome.cast.initialize = function(apiConfig, onCastInitSuccess, onCastInitError) {
    document.addEventListener('chromecast-ios-device', function(e) {
        console.log(e);
    });
    cordova.plugins.chromecastios.scanForDevices(apiConig.sessionRequest.appId).then(function(response){
        alert(JSON.stringify(response));
        
        //successfully started scanning for devices
        //response is simply a string value "started";
    }).catch(function(error){
        //failed to start scanning for devices
        //see error for details
    });
}

window.chrome = chrome;