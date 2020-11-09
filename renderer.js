// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// No Node.js APIs are available in this process because
// `nodeIntegration` is turned off. Use `preload.js` to
// selectively enable features needed in the rendering
// process.
const obs = require('./bin/Release/obs_client.node');

function startUp() {
	obs.IPC.connect("mysock")
	obs.SetWorkingDirectory(".")
	obs.OBS_API_initAPI("en-US", "." ,"1.0.0")
}

function startStreaming() {
    console.log("Start Button click")
    obs.OBS_service_startStreaming()
}

function stopStreaming() {
    console.log("Stop Button click")
    obs.OBS_service_stopStreaming()
}


document.querySelector('#start_stream_button').addEventListener('click', () => {
    startStreaming()
})

document.querySelector('#stop_stream_button').addEventListener('click', () => {
    stopStreaming()
})

document.addEventListener("DOMContentLoaded", function(event) {
    startUp()
});