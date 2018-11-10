var valueX = 360 // posição inicial do player
var sizeCanvasX = 720
var sizeCanvasY = 600
var fr = 30; //starting FPS

//randomSeed(99);

var enemyPosX = 25
var enemyPosY = 25
var pass = 1, count = 0

function setup() {
  createCanvas(sizeCanvasX, sizeCanvasY);
  background('rgba(0%,0%,50%, 0.5)')
  frameRate(fr)
}

function draw() {
	background('rgba(0%,0%,50%, 0.5)')

  moveEnemy()
  movePlayer() // movendo o personagem

  noStroke();

  rect(enemyPosX, enemyPosY, 50, 50); // enemy
	ellipse(valueX,550,80,80) // player
}

function moveEnemy() {
	if (enemyPosY < (sizeCanvasY) + 25) {
		enemyPosY += pass
	}else{
		pass += parseInt(count/5)
		if( count == 5) count = 0
		console.log(pass + ' - ' + count + '\n')
		count ++
		enemyPosY = 25
	}
}

function movePlayer() {
	if (keyIsDown(LEFT_ARROW) && valueX > 40) {
    valueX -= 5;
  }
  if(keyIsDown(RIGHT_ARROW) && valueX < (sizeCanvasX - 40)) {
    valueX += 5;
  }
}