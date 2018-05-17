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

  window.maestroSettings = {
      "HOST": "gladiator.omny.ca",
      "PORT": 443,
      "PROTOCOL": "https",
      "NEVER_HIDE_SETTINGS": true
  };
