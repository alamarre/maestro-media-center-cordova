if(!window.cast) {

var cast= {};

class CastContext {
    constructor() {
        this.receiverApplicationId = null;
        this.session = null;
        this.options = {};
    }

    getCurrentSession() {
        return this.session;
    }

    setSession(session) {
        this.session = session;
    }

    setOptions(options) {
        this.options = options;
    }
}

class CastSession {
    sendMessage(channel, customData, successCallback, failureCallback) {
        cordova.plugins.chromecastios.sendMessage(JSON.stringify(customData));
    }

    getCastDevice() {
        return {friendlyName: this.friendlyName};
    }

    setFriendlyName(friendlyName) {
        this.friendlyName = friendlyName;
    }
}

class RemotePlayer {

}

class RemotePlayerController {
    constructor(remotePlayer) {
        this.listener = null;
    }

    addEventListener(type,callback) {
        this.listener = callback;
        document.addEventListener("chromecast-connected", () => {
            this.listener();
        })

        const buttons = document.getElementsByClassName("cast-button");
        for(let i=0; i< buttons.length; i++) {
            const button = buttons[i];
            //button.onclick = listDevices;
            let image = document.createElement("img");
            image.className = "cast-image";
            image.onclick = listDevices;
            image.setAttribute("src", "chromecast.png");
            image.setAttribute("width", "30px");
            image.setAttribute("height", "30px");
            button.parentNode.replaceChild(image, button);
            image.style.display = "none";
            //button.appendChild(image);
        }

        cordova.plugins.chromecastios.scanForDevices(cast.framework.CastContext.getInstance().options.receiverApplicationId).then(function(response){
            console.log(JSON.stringify(response));
            
            //successfully started scanning for devices
            //response is simply a string value "started";
        }).catch(function(error){
            //failed to start scanning for devices
            //see error for details
        });
    }

}

function listDevices() {
    if(cordova.plugins.chromecastios.connected) {
        cordova.plugins.chromecastios.disconnect();
    }
    let devices = cordova.plugins.chromecastios.devices;
    let div = document.createElement("div");
    let childDiv = document.createElement("div");
    div.appendChild(childDiv);
    let ul = document.createElement("ul");
    div.className= "device-selector";
    for(let device of devices) {
        let li = document.createElement("li");
        li.innerHTML = device.friendlyName;
        li.onclick = () => {
            document.body.removeChild(div);
            launchToDevice(device);
        }
        ul.appendChild(li);
    }
    childDiv.appendChild(ul);

    let button = document.createElement("button");
    button.innerHTML = "Cancel";
    button.onclick = () => {
        document.body.removeChild(div);
    }
    childDiv.appendChild(button);

    document.body.appendChild(div);


}

let instance = new CastContext();
instance.setSession(new CastSession());

function launchToDevice(device) {
    cordova.plugins.chromecastios.selectDevice(device).then((response) => {
        cast.framework.CastContext.getInstance().getCurrentSession().setFriendlyName(device.friendlyName);
        //successfully selected device
        //returns an object with the selected device details
        cordova.plugins.chromecastios.launchApplication(cast.framework.CastContext.getInstance().options.receiverApplicationId).then((launchResponse) => {
            let event = new CustomEvent("chromecast-connected", {});
            document.dispatchEvent(event);
        }, (error) => {
            console.log(error);
        });
    }).catch(function(error){
        console.log(error);
        //an error occurred selecting the device
        //returns an error code
    });
}

cast.framework = { 
    CastContext : { getInstance: () => { return instance; }},
    RemotePlayer: RemotePlayer,
    RemotePlayerController: RemotePlayerController
};

document.addEventListener("chromecast-ios-device", function(event) {
    let devices = cordova.plugins.chromecastios.devices;
    let showButton = devices.length > 0;

    const buttons = document.getElementsByClassName("cast-image");
    for(let i=0; i< buttons.length; i++) {
        const button = buttons[i];
        button.style.display = (showButton) ? "inline": "none";
    }
});

cast.framework.RemotePlayerEventType = {
    "ANY_CHANGE":"anyChanged",
    "IS_CONNECTED_CHANGED":"isConnectedChanged",
    "IS_MEDIA_LOADED_CHANGED":"isMediaLoadedChanged",
    "DURATION_CHANGED":"durationChanged",
    "CURRENT_TIME_CHANGED":"currentTimeChanged",
    "IS_PAUSED_CHANGED":"isPausedChanged",
    "VOLUME_LEVEL_CHANGED":"volumeLevelChanged",
    "CAN_CONTROL_VOLUME_CHANGED":"canControlVolumeChanged",
    "IS_MUTED_CHANGED":"isMutedChanged",
    "CAN_PAUSE_CHANGED":"canPauseChanged",
    "CAN_SEEK_CHANGED":"canSeekChanged",
    "DISPLAY_NAME_CHANGED":"displayNameChanged",
    "STATUS_TEXT_CHANGED":"statusTextChanged",
    "TITLE_CHANGED":"titleChanged",
    "DISPLAY_STATUS_CHANGED":"displayStatusChanged",
    "MEDIA_INFO_CHANGED":"mediaInfoChanged",
    "IMAGE_URL_CHANGED":"imageUrlChanged",
    "PLAYER_STATE_CHANGED":"playerStateChanged"};

//cast.framework.CastContext.getInstance().setOptions

let chrome = {};

chrome.cast ={};
chrome.cast.AutoJoinPolicy = {
    CUSTOM_CONTROLLER_SCOPED: "custom_controller_scoped",
    TAB_AND_ORIGIN_SCOPED: "tab_and_origin_scoped",
    ORIGIN_SCOPED: "origin_scoped",
    PAGE_SCOPED: "page_scoped"}

window.cast = cast;
window.chrome = chrome;
}
