/*
 * 
 *  ZOOESCAPE
 * 
 *  Fernando Jerez 2017
 * 
 *  Entry for the Arduboy Jam (May 2017)
 * 
 *  
 * 
 */

#include <Arduboy2.h>
#include <ArduboyTones.h>
Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

Sprites sprites;

#include "globals.h"
#include "parrot.h"
#include "crocodile.h"
#include "rhino.h"
#include "monkey.h"
#include "player.h"
#include "obstacles.h"
#include "scenario.h"

#include "functions.h"

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);
  arduboy.initRandomSeed();
  arduboy.setTextWrap(false);

}

void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();
  if (title) {

    // TITLE SCREEN

    arduboy.drawBitmap(0, 0,  titleIMG, 128, 64, 1);
    if (arduboy.justPressed(B_BUTTON) || arduboy.justPressed(A_BUTTON)) title = false;

    // credits marquee
    arduboy.setCursor(marqueePos, 56);
    arduboy.print(marqueeTxt);
    marqueePos--;
    if (marqueePos < marqueeLength ) {
      marqueePos = 128;
    }



  } else {

    arduboy.setCursor(0, 0);
    arduboy.print("SCORE:");
    arduboy.print(score);
    arduboy.print(" TOP:");
    arduboy.print(top);
    if (pause) {
      arduboy.setCursor(50, 28);
      arduboy.print("PAUSE");
      if (arduboy.justPressed(A_BUTTON) && !arduboy.pressed(B_BUTTON)) pause = false;
    } else {
      if (!gameover && arduboy.justPressed(A_BUTTON)) pause = true;
      if (gameover) {
        if (arduboy.justPressed(B_BUTTON) && p1.ypos > 64) {
          gameover = false;
          title = true;

          score = 0;

          p1.ypos = p1.SUELO;
          p1.vx = 0;
          p1.bite = false;
          p1.hit = 0;
          p1.killed = false;
          distance = 0;
          p1.jumping = false;
          p1.jump = 0;

          croco.xpos = croco.POS;
          croco.nextAttack = 60;
          croco.attack = 0;

          ob1.spawn = 100;
          ob1.xpos = 128;
          ob1.ypos = 48;

          rhino.xpos = -20;
          rhino.contFrames = 0;
          rhino.chargetime = 200;
          rhino.charging = false;
        }
        ob1.go = false;
      } else {

        fenceX = -(arduboy.frameCount % 8);

        score++;
        if (score > top) top = score;
      }
      sprites.drawSelfMasked(fenceX, 50, fence, 0);

      // PLAYER
      updatePlayer();


      // rhino pos


      rhino.contFrames++;
      if (gameover) {
        if (!p1.killed) {
          rhino.xpos = min(128, rhino.xpos + 2);
          rhino.frameRate = 4;
        }

      } else {
        if (!rhino.charging) {
          rhino.xpos = -20 + round(5 * sin((float)rhino.contFrames * 0.2)) ;
          rhino.chargetime--;
          if (rhino.chargetime == 0) {
            rhino.charging = true;
            rhino.charge = random(30, 45);
          }
        } else {
          rhino.charge--;
          if (rhino.charge > 0) rhino.xpos++;
          if (rhino.charge < 0) rhino.xpos--;
          if (rhino.charge < 0 && rhino.xpos <= -20) {
            rhino.chargetime = max(5, (50 + random(100)) - score / 10) ;
            rhino.charging = false;
            rhino.contFrames = 0;
          }


        }
        rhino.frameRate = 4;
      }
      // rhino kills player
      if (rhino.xpos + 44 >= p1.xpos) {
        if (!p1.killed && p1.vx == 0) {
          p1.vx = -8;
          sound.tone(800, 100);
          delay(100);
          sound.tone(500, 100);
          delay(100);
          sound.tone(200, 100);
        }

        p1.killed = true;
        gameover = true;
      }

      if (arduboy.everyXFrames(rhino.frameRate)) rhino.frame = (rhino.frame + 1) % 2;
      if (arduboy.everyXFrames(rhino.frameRate)) monkeyFrame = (monkeyFrame + 1) % 2;
      if (arduboy.everyXFrames(10)) parrotFrame = (parrotFrame + 1) % 2;


      sprites.drawErase(1, 9, parrot_mask, parrotFrame);
      sprites.drawSelfMasked(1, 9, parrot, parrotFrame);

      if (!p1.killed) {
        sprites.drawErase(rhino.xpos, 32, rhinoimg_mask, rhino.frame);
        sprites.drawSelfMasked(rhino.xpos, 32, rhinoimg, rhino.frame);
      } else {
        sprites.drawErase(rhino.xpos, 32, rhinoimg_mask, 2);
        sprites.drawSelfMasked(rhino.xpos, 32, rhinoimg, 2);
      }

      sprites.drawErase(rhino.xpos + 23, 24, monkey_mask, monkeyFrame);
      sprites.drawSelfMasked(rhino.xpos + 23, 24, monkey, monkeyFrame);

      // CROCODILE
      updateCroco();

      // OBSTACLES
      //ob1
      if (ob1.go) {
        if (!ob1.hit) {
          if (!gameover) ob1.xpos += ob1.vx;
        } else {
          ob1.ypos += 2;
        }
        if (ob1.xpos < -16 || ob1.ypos > 64) {
          // reset obstacle
          ob1.go = false;
          ob1.xpos = 128;
          ob1.ypos = 48;
          ob1.spawn =  random(30);
          ob1.frame = random(4);
          ob1.hit = false;
        }
        // player hit
        if (!p1.jumping && ob1.xpos >= (p1.xpos - 14) && ob1.xpos <= p1.xpos + 24) {
          p1.hit = 15;
          ob1.hit = true;
          sound.tone(400, 100);
        }
        sprites.drawErase(ob1.xpos, ob1.ypos, obstacles_mask, ob1.frame);
        sprites.drawSelfMasked(ob1.xpos, ob1.ypos, obstacles, ob1.frame);
      } else {
        ob1.spawn--;
        if (ob1.spawn <= 0) ob1.go = true;
      }
    }
  }
  arduboy.display();

}
