let serialPort = require("serialport").SerialPort;

const express = require('express');
const fs = require('fs');
const path = require('path');
const app = express();
const port = 3000;
let htmlPath = path.join(__dirname, 'index.html');
fs.readFileSync(htmlPath);

app.get('/', (req, res) => {
	res.sendFile(htmlPath)
});

app.get('/start', (req, res) => {
	res.send('Game starting..');
});

app.listen(port, () => console.log(`Server started`));
