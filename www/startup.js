if(cordova) {
    window.chromecastPromise = new Promise((s) => {
                                           function checkForPlugin() {
                                           if(cordova.plugins && cordova.plugins.chromecastios) {
                                           s();
                                           } else {
                                           setTimeout(checkForPlugin, 100);
                                           }
                                           }
                                           checkForPlugin();
                                           })
} else {
    window.chromecastPromise = new Promise(() => {});
}

async function loadFromCache() {
    const js = await localStorage.getItem("maestroJs");
    attachJs(js);
}

function attachJs(js) {
    let script = document.createElement("script");
    script.innerHTML = js;
    document.body.appendChild(script);
}
const jsUrl ="https://videos.omny.ca/app.js";
fetch(jsUrl).then(response => {
                  return response.text();
                  }, loadFromCache)
.then((js) => {
      try {
      localStorage.setItem("maestroJs", js);
      } catch(e) {
      console.error(e);
      }
      //attachJs(js);
      const script = document.createElement("script");
      script.src = jsUrl;
      document.body.appendChild(script);
      }, loadFromCache);

window.maestroSettings = {
    "HOST": "gladiator.omny.ca",
    "PORT": 443,
    "PROTOCOL": "https",
    "NEVER_HIDE_SETTINGS": true
};
