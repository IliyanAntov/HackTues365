const gen = require('./generator.js').randomize();

const serialPort = require("serialport");
const express = require('express');
const fs = require('fs');
const path = require('path');
const readline = require('readline');
const app = express();
const port = 3000;

let usb;

// let gen = exports.ButtonGameRandomizer();

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

const htmlPath = path.join(__dirname, 'index.html');
fs.readFileSync(htmlPath);

const arduinoPort = new serialPort('/dev/ttyACM0', {
    baudRate: 9600
});

app.get('/', (req, res) => {
	res.sendFile(htmlPath)
});

app.get('/start', (req, res) => {
	res.send('Game starting..');
	res.send(`If red light lights release when ${}`)
	arduinoPort.write('hello from node\n', err => {
	    if (err) {
			return console.log('Error on write: ', err.message);
	    }
	    console.log('message written');
	});

	print();
});

app.listen(port, () => {
	console.log(`Server started`)
	rl.question('usb: ', answer => {
		usb = answer;
		rl.close();
	});
});
