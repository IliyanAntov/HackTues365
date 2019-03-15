const serialPort = require("serialport");
const express = require('express');
const fs = require('fs');
const path = require('path');
const app = express();
const port = 3000;

const htmlPath = path.join(__dirname, 'index.html');
fs.readFileSync(htmlPath);

app.get('/', (req, res) => {
	res.sendFile(htmlPath)
});

app.get('/start', (req, res) => {
	res.send('Game starting..');
});

let arduinoPort = new serialPort('/dev/ttyACM1', {
    baudRate: 9600
});

arduinoPort.write('hello from node\n', err => {
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    console.log('message written');
});

app.listen(port, () => console.log(`Server started`));
