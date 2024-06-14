int x = 2;
int y = -1;
int rot = 0;

int acc = 1;
int speed = 200;

int score = 0;
int level = 0;

unsigned long int tt = 0, tm = 0;

void drawBlock(byte arr[4][4], int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (arr[j][i] == 1) {
        gb.drawPoint(x + i, y + j);
      }
    }
  }
}

void makeMoveT() {
  if (millis() - tm >= 100) {
    if (gb.getKey() == 4) {
      if (!gb.checkBlockCollision(gb.block[rot], x - 1, y)) {
        x--;
      }
    }
    if (gb.getKey() == 5) {
      if (!gb.checkBlockCollision(gb.block[rot], x + 1, y)) {
        x++;
      }
    }
    if (gb.getKey() == 3) {
      if (!gb.checkBlockCollision(gb.block[rot], x + 1, y)) {
        if (rot == 3) {
          rot = 0;
        } else {
          rot++;
        }
      }
    }
    if (gb.getKey() == 6) {
      acc = 4;
    } else {
      acc = 1;
    }
    tm = millis();
  }
}

void createBlock(int num) {
  x = 2; y = -1; rot = random(0, 4);
  if (num == 0) gb.generateBlock(gb.block, I_block_1, I_block_2, I_block_3, I_block_4);
  if (num == 1) gb.generateBlock(gb.block, Z_block_1, Z_block_2, Z_block_3, Z_block_4);
  if (num == 2) gb.generateBlock(gb.block, S_block_1, S_block_2, S_block_3, S_block_4);
  if (num == 3) gb.generateBlock(gb.block, L_block_1, L_block_2, L_block_3, L_block_4);
  if (num == 4) gb.generateBlock(gb.block, J_block_1, J_block_2, J_block_3, J_block_4);
  if (num == 5) gb.generateBlock(gb.block, T_block_1, T_block_2, T_block_3, T_block_4);
  if (num == 6) gb.generateBlock(gb.block, O_block_1, O_block_2, O_block_3, O_block_4);
}

bool loss() {
  if (gb.checkBlockCollision(gb.block[rot], x, 0)) {
    return true;
  }
  return false;
}

bool win() {
  if (score >= 20) {
    return true;
  }
  return false;
}

void clearMemory() {
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 8; j++) {
      gb.wipePoint(j, i);
    }
  }
}

void tetris() {
  if (millis() - tt > speed / acc) {
    if (loss()) {
      Serial.println("You loss, your score: " + (String)score);
      clearMemory();
      gb.sound(COLLISION);
      //    gb.testMatrix(10);
      drawScore(gb, score);
      delay(1000);
      gb.clearDisplay();
      score = 0;
      level = 0;
    }
    if (win()) {
      clearMemory();
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 16; j++) {
          gb.setLed(i , j, WIN[j][i]);
        }
      }
      score = 0;
      level = 0;
      delay(2000);
      gb.clearDisplay();
    }

    if (gb.checkBlockCollision(gb.block[rot], x, y + 1)) {
      gb.memBlock(gb.block[rot], x, y);
      int lines = gb.fullLine();
      if (lines != 0) {
        score += lines;
        level += lines;
      }
      if (level >= 5) {
        acc += 1;
        level = 0;
      }
      createBlock(random(7));
    } else {
      y++;
    }
    gb.drawDisplay();
    drawBlock(gb.block[rot], x , y);
    tt = millis();
  }
  makeMoveT();
}
