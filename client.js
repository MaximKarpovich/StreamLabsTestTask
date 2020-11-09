console.log('Client-side code running');

//const button = document.getElementById('start_stream_button');
//button.addEventListener('click', function(e) {
//  console.log('Start button was clicked');
//});

const InitEventsFunc = () => {
    const button = document.getElementById('start_stream_button');
    button.addEventListener('click', () => console.log(' start_stream_buttonClick'))
}

module.exports.InitEvents = InitEventsFunc;