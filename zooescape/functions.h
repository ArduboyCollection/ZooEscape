
void updatePlayer() {
  if (p1.jumping) {
    if (p1.jump >= 0) {
      // jumping-UP
      p1.ypos -= 3;
      p1.jump--;
    } else {
      // jumping-DOWN
      p1.ypos += 3;

      // cocrodile-jump
      if (croco.kicked == false && p1.ypos >= 26 && p1.xpos > croco.xpos && p1.xpos <= croco.xpos + 50) {
        croco.kicked = true;
        croco.attack = 0;

        p1.jump = 3;

        score+=25;
        sound.tone(1000, 100);
      }

      // touch SUELO
      if (p1.ypos >= p1.SUELO) {
        p1.jump = 0;
        p1.ypos = p1.SUELO;
        p1.jumping = false;
      }
    }
  } else if (!p1.killed && !p1.bite && p1.hit <= 0 && arduboy.justPressed(B_BUTTON)) {
    p1.jumping = true;
    p1.jump = 6;
  }

  if (!p1.bite) {
    p1.frameChange = 3;
    if (p1.hit <= 0) {
      if (arduboy.pressed(RIGHT_BUTTON)) {
        p1.frameChange = 2;
        distance = min(distance + 1, 46);
      } else if (arduboy.pressed(LEFT_BUTTON)) {
        p1.frameChange = 4;
        distance -= 1;
      } else {
        if (!p1.jumping) {
          if (distance < 0) distance++;
          if (distance > 0) distance--;
        }
      }
    } else {
      distance -= 2;
      p1.hit--;
    }
  }

  if(p1.killed){
    distance++;
    if(p1.ypos<=64){
      p1.ypos+=p1.vx; 
      p1.vx+=1;
    }
    distance++;
  }
  p1.xpos = distance + 48;

  if (!p1.jumping && !p1.killed) {
    if (p1.bite) {
      sprites.drawErase( p1.xpos, p1.ypos, playerhit_mask, 0);
      sprites.drawSelfMasked( p1.xpos, p1.ypos, playerhit, 0);
    } else if (p1.hit > 0) {
      sprites.drawErase( p1.xpos, p1.ypos, playerhit_mask, 1);
      sprites.drawSelfMasked( p1.xpos, p1.ypos, playerhit, 1);
    } else {
      if (arduboy.everyXFrames(p1.frameChange)) p1.frame = (p1.frame + 1) % 2;
      sprites.drawErase( p1.xpos, p1.ypos, player_mask, p1.frame);
      sprites.drawSelfMasked( p1.xpos, p1.ypos, player, p1.frame);
    }
  } else {
    sprites.drawErase( p1.xpos, p1.ypos, jumping_mask, 0);
    sprites.drawSelfMasked( p1.xpos, p1.ypos, jumping, 0);

  }

}


void updateCroco() {
  if (!p1.bite && !p1.killed) {
    if (croco.attacking) {
      // CROCODILE ATTACK!!!
      if (croco.attack <= 0) {
        // back to POS
        croco.frameChange = 3;
        croco.xpos -= 1;
        if (croco.xpos <= croco.POS) {
          croco.xpos = croco.POS;
          croco.attacking = false;
          croco.kicked = false;
        }

      } else {
        // go forward
        croco.frameChange = 2;
        croco.xpos += 2;
        croco.attack--;
      }

    } else {
      croco.frameChange = 4;
      croco.nextAttack--;
      if (croco.nextAttack <= 0) {
        croco.attacking = true;
        croco.attack = 45;
        croco.nextAttack = 30 + random(60);
      }
    }
  }
  // player hit??

  if (!gameover && !p1.jumping && !croco.kicked && croco.xpos + 54 >= p1.xpos) {
    p1.bite = true;
    gameover = true;

    sound.tone(200, 400);
    
  }

  if (arduboy.everyXFrames(croco.frameChange)) croco.frame = (croco.frame + 1) % 2;
  if (croco.kicked) {
    sprites.drawErase(croco.xpos, 48, croco2_mask, croco.frame);
    sprites.drawSelfMasked(croco.xpos, 48, croco2, croco.frame);
  } else {
    if (p1.bite && !p1.killed) {
      sprites.drawErase(croco.xpos, 48, crocobite_mask, 0);
      sprites.drawSelfMasked(croco.xpos, 48, crocobite, 0);
    } else {
      sprites.drawErase(croco.xpos, 48, croco1_mask, croco.frame);
      sprites.drawSelfMasked(croco.xpos, 48, croco1, croco.frame);
    }
  }

}

