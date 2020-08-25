const WebSocket = require('ws');

// use arp-scan to find the ESP, will add in mobile interface
const ws = new WebSocket('ws://192.168.1.###:80');

ws.on('open', function open() {
    console.log('connected');

    const motions = ['F', 'L', 'F', 'L', 'F', 'L', 'F'];
    const maxMoveCounter = 6;
    let curCounter = 0;
    let curMotionIndex = 0;

    setInterval(() => {
        if (curCounter < maxMoveCounter) {
            console.log('sending', motions[curMotionIndex]);
            ws.send(motions[curMotionIndex]);
        } else {
            curMotionIndex += 1;
            curCounter = 0;
        }
        if (curMotionIndex === 6) {
            curMotionIndex = 0;
        }
        if (curCounter === maxMoveCounter) {
            curCounter = 0;
        }
        curCounter +=1;
    }, 500);
});

ws.on('message', function incoming(data) {
    const date_obj = new Date();
    console.log('received', data, date_obj.getSeconds());
});

ws.on('close', function close() {
    console.log('client closed');
});