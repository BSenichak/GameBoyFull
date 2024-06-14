bool state = true; 

int snakeX[30]; 
int snakeY[30];

int up = 0; 
int right = 1;
int bottom = 2;
int left = 3;

int direction = right; 

int lenSnake = 3; 

int foodX = 0, foodY = 0; 





void makeMove() {
  if (gb.getKey() == 3 && direction != bottom) {
    direction = up;
  }
  if (gb.getKey() == 4 && direction != right) {
    direction = left;
  }
  if (gb.getKey() == 5 && direction != left) {
    direction = right;
  }
  if (gb.getKey() == 6 && direction != up) {
    direction = bottom;
  }
}

void drawFood(){
  state = !state;
  if(state){
    gb.drawPoint(foodX, foodY);
  }else{
    gb.wipePoint(foodX, foodY);
  }
}
bool isPartOfSnake(int x, int y){
  for(int i = lenSnake - 1; i > 0; i--){
    if(x == snakeX[i] && y == snakeY[i]) return true;
  }
  return false;
}

void makeFood() {
  foodX = random(8);
  foodY = random(16);
  while(isPartOfSnake(foodX, foodY)){
    foodX = random(8);
    foodY = random(16);
  }
}

void move() {
  for (int i = lenSnake - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }
  if (direction == up) {
    if (snakeY[0] == 0) {
      snakeY[0] = 15;
    } else {
      snakeY[0]--;
    }
  }
  if (direction == bottom) {
    if (snakeY[0] == 15) {
      snakeY[0] = 0;
    } else {
      snakeY[0]++;
    }
  }
  if (direction == left) {
    if (snakeX[0] == 0) {
      snakeX[0] = 7;
    } else {
      snakeX[0]--;
    }
  }
  if (direction == right) {
    if (snakeX[0] == 7) {
      snakeX[0] = 0;
    } else {
      snakeX[0]++;
    }
  }
}

void drawSnake() {
  for (int i = 0; i < lenSnake; i++) {
    gb.drawPoint(snakeX[i], snakeY[i]);
  }
}

void lose(){
  for(int i = lenSnake - 1; i > 0; i--){
    if(snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]){
      delay(2000);
      gb.clearDisplay();
      gb.testMatrix(10);
      drawScore(gb, lenSnake - 3);
      delay(2000);
      gb.clearDisplay();
      for(int j = 0; j < lenSnake; j++){
        snakeX[j] = 0;
        snakeY[j] = 0;
      }
      direction = right;
      snakeX[0] = 4;
      snakeY[0] = 7;
      foodX = 3;
      foodY = 3;
      lenSnake = 3;
      return;
    }
  }
}

void snakeGame() {
  makeMove();
  move();
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    lenSnake++;
    makeFood();
  }
  gb.clearDisplay();
  drawFood();
  drawSnake();
  lose();
  delay(250);
}
