// <----- Generate random values for all games ----->


function random(max) {  												// generate a random number between 0 and max-1
	return Math.floor(Math.random() * max);
}

function randomizeButtonGame() { 										// generate random values to pass to the arduino Button_game
	let timeValues = [random(10), random(10), random(10), random(10)];  // set of possible release values
	let index = random(4); 												// index for color

	let ret = {
		"timeValues": timeValues,
		"index": index
	}

	return ret;
}

module.exports.randomizeButtonGame = randomizeButtonGame;

