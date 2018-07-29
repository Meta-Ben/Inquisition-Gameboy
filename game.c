
#include <gb/gb.h>
#include <rand.h>
#include <gb/console.h>
#include <gb/drawing.h>
#include <stdio.h>

#include "graphics.h"

#define MAX_TIMER 30
#define MAX_TIMER_BANDIT 30
#define MAX_SPRITE 16
#define MAX_MOB_SPRITE 4
#define NB_BANDIT 3
#define BANDIT_RUN 1
#define BANDIT_FOLLOW 2
#define MAX_TIMER_SCROLLBKG 10
#define HAMMER_DISTANCE 8

typedef struct Bandit{
  UBYTE pv;
  UBYTE PosX, PosY;
  UBYTE speed;
  UBYTE damage;
  UBYTE t;
  UBYTE comportement;
  UBYTE timerAnimationWalkBandit;
  UBYTE timerAnimationAttackBandit;
  UBYTE timerAnimationDyingBandit;
  UBYTE isWalkingBandit;
  UBYTE isAttackingBandit;
  UBYTE isDyingBandit;
  
} Bandit;

Bandit bandits[NB_BANDIT];
UBYTE pickComportement;

UBYTE posXJudge = 80;
UBYTE posYJudge = 100;


UBYTE JudgeSpeed = 2;
UBYTE JudgeJumbSpeed = 2;
UBYTE JudgePV = 3;

UBYTE ScoreDistance = 0;
UBYTE ScoreKill = 0;

UBYTE TimerAnimationWalk = MAX_TIMER;
UBYTE TimerAnimationJump = MAX_TIMER;
UBYTE TimerAnimationAttack = MAX_TIMER;
UBYTE TimerAnimationHurt = MAX_TIMER/2;
UBYTE TimerScrollBKG = MAX_TIMER_SCROLLBKG;

UBYTE isJumping = 0;
UBYTE isWalking = 0;
UBYTE isAttacking = 0;
UBYTE isHurt = 0;
UBYTE i = 0;

UBYTE borderRight = SCREENWIDTH-4;
UBYTE borderLeft = 4;
UBYTE borderTop = 45;
UBYTE borderBottom = SCREENHEIGHT-38;

UBYTE hammerPos = posXJudge + HAMMER_DISTANCE;

UBYTE score_bandit_digitUn = 0;
UBYTE score_bandit_digitDeux = 0;
UBYTE score_bandit_digitTrois = 0;

UBYTE distance = 0;

UBYTE score_distance_digitUn = 0;
UBYTE score_distance_digitDeux = 0;
UBYTE score_distance_digitTrois = 0;



void drawBanditIdle(UBYTE numero, UBYTE posX, UBYTE posY);

void initBandits();

void checkCollideBorder(UBYTE newPosX, UBYTE newPosY);

void checkColliderHammerAttack();
void JudgeDoHurt();
void drawJudgeAttack1(){


  set_sprite_data(0, MAX_SPRITE, JUDGEATTACK1);

  set_sprite_tile(0, 0);
  move_sprite(0, posXJudge-8, posYJudge-8);

  set_sprite_tile(1, 1);
  move_sprite(1, posXJudge-8, posYJudge);

  set_sprite_tile(2, 2);
  move_sprite(2, -5, -5);


  set_sprite_tile(3, 3);
  move_sprite(3, posXJudge, posYJudge);

  set_sprite_tile(4, 4);
  move_sprite(4, posXJudge-8, posYJudge+8);

  set_sprite_tile(5, 5);
  move_sprite(5, posXJudge-8, posYJudge+16);


  set_sprite_tile(6, 6);
  move_sprite(6, posXJudge, posYJudge+8);

  set_sprite_tile(7, 7);
  move_sprite(7, posXJudge, posYJudge+16);

  set_sprite_tile(8, 8);
  move_sprite(8, -5, -5);

  set_sprite_tile(9, 9);
  move_sprite(9, -5, -5);

  set_sprite_tile(10, 10);
  move_sprite(10, -5, -5);

  set_sprite_tile(11, 11);
  move_sprite(11, -5, -5);

  set_sprite_tile(12, 12);
  move_sprite(12, posXJudge+8, posYJudge+8);

  set_sprite_tile(13, 13);
  move_sprite(13, posXJudge+8, posYJudge+16);

  set_sprite_tile(14, 14);
  move_sprite(14, -5, -5);

  set_sprite_tile(15, 15);
  move_sprite(15, -5, -5);

  
  set_win_tiles(3, 0, 1, 1, attackLook);


}

void drawJudgeAttack2(){


  set_sprite_data(0, MAX_SPRITE, JUDGEATTACK2);


  set_sprite_tile(0, 0);
  move_sprite(0, posXJudge-8, posYJudge-8);
  
  set_sprite_tile(1, 1);
  move_sprite(1, posXJudge-8, posYJudge);

  set_sprite_tile(2, 2);
  move_sprite(2, -5, -5);


  set_sprite_tile(3, 3);
  move_sprite(3, posXJudge, posYJudge);

  set_sprite_tile(4, 4);
  move_sprite(4, posXJudge-8, posYJudge+8);

  set_sprite_tile(5, 5);
  move_sprite(5, posXJudge-8, posYJudge+16);


  set_sprite_tile(6, 6);
  move_sprite(6, posXJudge, posYJudge+8);

  set_sprite_tile(7, 7);
  move_sprite(7, posXJudge, posYJudge+16);

  set_sprite_tile(8, 8);
  move_sprite(8, -5, -5);

  set_sprite_tile(9, 9);
  move_sprite(9, posXJudge+8, posYJudge);

  set_sprite_tile(10, 10);
  move_sprite(10, -5, -5);

  set_sprite_tile(11, 11);
  move_sprite(11, -5, -5);


  set_sprite_tile(12, 12);
  move_sprite(12, posXJudge+8, posYJudge+8);

  set_sprite_tile(13, 13);
  move_sprite(13, posXJudge+8, posYJudge+16);

  set_sprite_tile(14, 14);
  move_sprite(14, posXJudge+16, posYJudge+8);

  set_sprite_tile(15, 15);
  move_sprite(15, posXJudge+16, posYJudge+16);

  set_win_tiles(3, 0, 1, 1, attackLook);
  
}
void drawJudgeIDLE(){

  set_sprite_data(0, MAX_SPRITE, JUDGEIDLE);

  set_sprite_tile(0, 0);
  move_sprite(0, posXJudge-8, posYJudge-8);
  
  set_sprite_tile(1, 1);
  move_sprite(1, posXJudge-8, posYJudge);

  set_sprite_tile(2, 2);
  move_sprite(2, -5, -5);


  set_sprite_tile(3, 3);
  move_sprite(3, posXJudge, posYJudge);

  set_sprite_tile(4, 4);
  move_sprite(4, posXJudge-8, posYJudge+8);

  set_sprite_tile(5, 5);
  move_sprite(5, posXJudge-8, posYJudge+16);


  set_sprite_tile(6, 6);
  move_sprite(6, posXJudge, posYJudge+8);

  set_sprite_tile(7, 7);
  move_sprite(7, posXJudge, posYJudge+16);

  set_sprite_tile(8, 8);
  move_sprite(8, -5, -5);

  set_sprite_tile(9, 9);
  move_sprite(9, -5, -5);

  set_sprite_tile(10, 10);
  move_sprite(10, -5, -5);

  set_sprite_tile(11, 11);
  move_sprite(11, -5, -5);

  set_sprite_tile(12, 12);
  move_sprite(12, posXJudge+8, posYJudge+8);

  set_sprite_tile(13, 13);
  move_sprite(13, posXJudge+8, posYJudge+16);

  set_sprite_tile(14, 14);
  move_sprite(14, -5, -5);

  set_sprite_tile(15, 15);
  move_sprite(15, -5, -5);

  set_win_tiles(3, 0, 1, 1, simpleLook);
}

void drawJudgeJUMP(){


  set_sprite_data(0, MAX_SPRITE, JUDGEJUMP);

  set_sprite_tile(0, 0);
  move_sprite(0, posXJudge-8, posYJudge-8);
  
  set_sprite_tile(1, 1);
  move_sprite(1, posXJudge-8, posYJudge);

  set_sprite_tile(2, 2);
  move_sprite(2, -5, -5);


  set_sprite_tile(3, 3);
  move_sprite(3, posXJudge, posYJudge);

  set_sprite_tile(4, 4);
  move_sprite(4, posXJudge-8, posYJudge+8);

  set_sprite_tile(5, 5);
  move_sprite(5, posXJudge-8, posYJudge+16);


  set_sprite_tile(6, 6);
  move_sprite(6, posXJudge, posYJudge+8);

  set_sprite_tile(7, 7);
  move_sprite(7, posXJudge, posYJudge+16);

  set_sprite_tile(8, 8);
  move_sprite(8, -5, -5);

  set_sprite_tile(9, 9);
  move_sprite(9, posXJudge+8, posYJudge);

  set_sprite_tile(10, 10);
  move_sprite(10, -5, -5);

  set_sprite_tile(11, 11);
  move_sprite(11, -5, -5);


  set_sprite_tile(12, 12);
  move_sprite(12, posXJudge+8, posYJudge+8);



  set_sprite_tile(13, 13);
  move_sprite(13, posXJudge+8, posYJudge+16);

  set_sprite_tile(14, 14);
  move_sprite(14, -5, -5);

  set_sprite_tile(15, 15);
  move_sprite(15, -5, -5);

  set_win_tiles(3, 0, 1, 1, jumpLook);

}

void drawJudgeWalk1(){

  set_sprite_data(0, MAX_SPRITE, JUDGEWALK1);

  set_sprite_tile(0, 0);
  move_sprite(0, posXJudge-8, posYJudge-8);
  
  set_sprite_tile(1, 1);
  move_sprite(1, posXJudge-8, posYJudge);

  set_sprite_tile(2, 2);
  move_sprite(2, -5, -5);


  set_sprite_tile(3, 3);
  move_sprite(3, posXJudge, posYJudge);

  set_sprite_tile(4, 4);
  move_sprite(4, posXJudge-8, posYJudge+8);

  set_sprite_tile(5, 5);
  move_sprite(5, posXJudge-8, posYJudge+16);


  set_sprite_tile(6, 6);
  move_sprite(6, posXJudge, posYJudge+8);

  set_sprite_tile(7, 7);
  move_sprite(7, posXJudge, posYJudge+16);

  set_sprite_tile(8, 8);
  move_sprite(8, -5, -5);

  set_sprite_tile(9, 9);
  move_sprite(9, -5, -5);

  set_sprite_tile(10, 10);
  move_sprite(10, -5, -5);

  set_sprite_tile(11, 11);
  move_sprite(11, -5, -5);


  set_sprite_tile(12, 12);
  move_sprite(12, posXJudge+8, posYJudge+8);



  set_sprite_tile(13, 13);
  move_sprite(13, posXJudge+8, posYJudge+16);

  set_sprite_tile(14, 14);
  move_sprite(14, -5, -5);

  set_sprite_tile(15, 15);
  move_sprite(15, -5, -5);

  set_win_tiles(3, 0, 1, 1, simpleLook);


}

void drawJudgeWalk2(){

  set_sprite_data(0, MAX_SPRITE, JUDGEWALK2);

  set_sprite_tile(0, 0);
  move_sprite(0, posXJudge-8, posYJudge-8);
  
  set_sprite_tile(1, 1);
  move_sprite(1, posXJudge-8, posYJudge);

  set_sprite_tile(2, 2);
  move_sprite(2, -5, -5);


  set_sprite_tile(3, 3);
  move_sprite(3, posXJudge, posYJudge);

  set_sprite_tile(4, 4);
  move_sprite(4, posXJudge-8, posYJudge+8);

  set_sprite_tile(5, 5);
  move_sprite(5, posXJudge-8, posYJudge+16);


  set_sprite_tile(6, 6);
  move_sprite(6, posXJudge, posYJudge+8);

  set_sprite_tile(7, 7);
  move_sprite(7, posXJudge, posYJudge+16);

  set_sprite_tile(8, 8);
  move_sprite(8, -5, -5);

  set_sprite_tile(9, 9);
  move_sprite(9, -5, -5);

  set_sprite_tile(10, 10);
  move_sprite(10, -5, -5);

  set_sprite_tile(11, 11);
  move_sprite(11, -5, -5);


  set_sprite_tile(12, 12);
  move_sprite(12, posXJudge+8, posYJudge+8);



  set_sprite_tile(13, 13);
  move_sprite(13, posXJudge+8, posYJudge+16);

  set_sprite_tile(14, 14);
  move_sprite(14, -5, -5);

  set_sprite_tile(15, 15);
  move_sprite(15, -5, -5);



}

void drawJudgeHurt(){

 set_sprite_data(0, MAX_SPRITE, JUDGEHURT);

 set_sprite_tile(0, 0);
 move_sprite(0, posXJudge-8, posYJudge-8);

 set_sprite_tile(1, 1);
 move_sprite(1, posXJudge-8, posYJudge);

 set_sprite_tile(2, 2);
 move_sprite(2, -5, -5);


 set_sprite_tile(3, 3);
 move_sprite(3, posXJudge, posYJudge);

 set_sprite_tile(4, 4);
 move_sprite(4, posXJudge-8, posYJudge+8);

 set_sprite_tile(5, 5);
 move_sprite(5, posXJudge-8, posYJudge+16);


 set_sprite_tile(6, 6);
 move_sprite(6, posXJudge, posYJudge+8);

 set_sprite_tile(7, 7);
 move_sprite(7, posXJudge, posYJudge+16);

 set_sprite_tile(8, 8);
 move_sprite(8, -5, -5);

 set_sprite_tile(9, 9);
 move_sprite(9, posXJudge+8, posYJudge);

 set_sprite_tile(10, 10);
 move_sprite(10, -5, -5);

 set_sprite_tile(11, 11);
 move_sprite(11, -5, -5);


 set_sprite_tile(12, 12);
 move_sprite(12, posXJudge+8, posYJudge+8);



 set_sprite_tile(13, 13);
 move_sprite(13, posXJudge+8, posYJudge+16);

 set_sprite_tile(14, 14);
 move_sprite(14, -5, -5);

 set_sprite_tile(15, 15);
 move_sprite(15, -5, -5);

 set_win_tiles(3, 0, 1, 1, hurtLook);

}

void drawBanditIdle(UBYTE numero, UBYTE posX, UBYTE posY){
  set_sprite_data(MAX_SPRITE+MAX_MOB_SPRITE*numero, MAX_MOB_SPRITE, banditIDLE);

  set_sprite_tile(MAX_SPRITE+MAX_MOB_SPRITE*numero, MAX_SPRITE+MAX_MOB_SPRITE*numero);
  move_sprite(MAX_SPRITE+MAX_MOB_SPRITE*numero, posX, posY-8);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+1, MAX_SPRITE+MAX_MOB_SPRITE*numero+1);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+1, posX, posY);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+2, MAX_SPRITE+MAX_MOB_SPRITE*numero+2);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+2, posX+8, posY-8);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+3, MAX_SPRITE+MAX_MOB_SPRITE*numero+3);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+3, posX+8, posY );
}

void drawBanditWalk1(UBYTE numero, UBYTE posX, UBYTE posY){
  set_sprite_data(MAX_SPRITE+MAX_MOB_SPRITE*numero, MAX_MOB_SPRITE, banditWalk1);

  set_sprite_tile(MAX_SPRITE+MAX_MOB_SPRITE*numero, MAX_SPRITE+MAX_MOB_SPRITE*numero);
  move_sprite(MAX_SPRITE+MAX_MOB_SPRITE*numero, posX, posY-8);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+1, MAX_SPRITE+MAX_MOB_SPRITE*numero+1);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+1, posX, posY);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+2, MAX_SPRITE+MAX_MOB_SPRITE*numero+2);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+2, posX+8, posY-8);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+3, MAX_SPRITE+MAX_MOB_SPRITE*numero+3);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+3, posX+8, posY );

}

void drawBanditWalk2(UBYTE numero, UBYTE posX, UBYTE posY){
  set_sprite_data(MAX_SPRITE+MAX_MOB_SPRITE*numero, MAX_MOB_SPRITE, banditWalk2);

  set_sprite_tile(MAX_SPRITE+MAX_MOB_SPRITE*numero, MAX_SPRITE+MAX_MOB_SPRITE*numero);
  move_sprite(MAX_SPRITE+MAX_MOB_SPRITE*numero, posX, posY-8);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+1, MAX_SPRITE+MAX_MOB_SPRITE*numero+1);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+1, posX, posY);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+2, MAX_SPRITE+MAX_MOB_SPRITE*numero+2);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+2, posX+8, posY-8);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+3, MAX_SPRITE+MAX_MOB_SPRITE*numero+3);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+3, posX+8, posY );

}

void drawBanditAttack1(UBYTE numero, UBYTE posX, UBYTE posY){
  set_sprite_data(MAX_SPRITE+MAX_MOB_SPRITE*numero, MAX_MOB_SPRITE, banditAttack1);

  set_sprite_tile(MAX_SPRITE+MAX_MOB_SPRITE*numero, MAX_SPRITE+MAX_MOB_SPRITE*numero);
  move_sprite(MAX_SPRITE+MAX_MOB_SPRITE*numero, posX, posY-8);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+1, MAX_SPRITE+MAX_MOB_SPRITE*numero+1);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+1, posX, posY);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+2, MAX_SPRITE+MAX_MOB_SPRITE*numero+2);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+2, posX+8, posY-8);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+3, MAX_SPRITE+MAX_MOB_SPRITE*numero+3);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+3, posX+8, posY );

}

void drawBanditAttack2(UBYTE numero, UBYTE posX, UBYTE posY){
  set_sprite_data(MAX_SPRITE+MAX_MOB_SPRITE*numero, MAX_MOB_SPRITE, banditAttack2);

  set_sprite_tile(MAX_SPRITE+MAX_MOB_SPRITE*numero, MAX_SPRITE+MAX_MOB_SPRITE*numero);
  move_sprite(MAX_SPRITE+MAX_MOB_SPRITE*numero, posX, posY-8);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+1, MAX_SPRITE+MAX_MOB_SPRITE*numero+1);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+1, posX, posY);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+2, MAX_SPRITE+MAX_MOB_SPRITE*numero+2);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+2, posX+8, posY-8);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+3, MAX_SPRITE+MAX_MOB_SPRITE*numero+3);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+3, posX+8, posY );

}

void drawBanditDead(UBYTE numero, UBYTE posX, UBYTE posY){
  set_sprite_data(MAX_SPRITE+MAX_MOB_SPRITE*numero, MAX_MOB_SPRITE, banditDead);

  set_sprite_tile(MAX_SPRITE+MAX_MOB_SPRITE*numero, MAX_SPRITE+MAX_MOB_SPRITE*numero);
  move_sprite(MAX_SPRITE+MAX_MOB_SPRITE*numero, posX, posY-8);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+1, MAX_SPRITE+MAX_MOB_SPRITE*numero+1);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+1, posX, posY);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+2, MAX_SPRITE+MAX_MOB_SPRITE*numero+2);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+2, posX+8, posY-8);

  set_sprite_tile((MAX_SPRITE+MAX_MOB_SPRITE*numero)+3, MAX_SPRITE+MAX_MOB_SPRITE*numero+3);
  move_sprite((MAX_SPRITE+MAX_MOB_SPRITE*numero)+3, posX+8, posY );

}

void BanditWalk(UBYTE numero, UBYTE posX, UBYTE posY){
  bandits[numero].isWalkingBandit = 1;


  if(bandits[numero].isAttackingBandit == 0){
    if(bandits[numero].timerAnimationWalkBandit >= MAX_TIMER/2){
      drawBanditWalk1(numero+1, posX, posY);
    } else if(bandits[numero].timerAnimationWalkBandit >= 0 && bandits[numero].timerAnimationWalkBandit < MAX_TIMER/2){
      drawBanditWalk2(numero+1, posX, posY);
    }

    bandits[numero].timerAnimationWalkBandit--;

    if(bandits[numero].timerAnimationWalkBandit <= 0){
      bandits[numero].timerAnimationWalkBandit = MAX_TIMER;

    }
  }


}


void BanditAttack(UBYTE numero, UBYTE posX, UBYTE posY){
  bandits[numero].isAttackingBandit = 1;
  bandits[numero].isWalkingBandit = 0;

  if(bandits[numero].timerAnimationAttackBandit >= MAX_TIMER/2){
    drawBanditAttack1(numero+1, posX, posY);
  }  else if(bandits[numero].timerAnimationAttackBandit >= 0 && bandits[numero].timerAnimationAttackBandit < MAX_TIMER/2){
    drawBanditAttack2(numero+1, posX, posY);
    if(isHurt == 0){
       isHurt = 1;
    }
   



  }

  bandits[numero].timerAnimationAttackBandit--;

  if (bandits[numero].timerAnimationAttackBandit <= 0){

    bandits[numero].timerAnimationAttackBandit = MAX_TIMER;

  }
}

void BanditDie(UBYTE numero, UBYTE posX, UBYTE posY){
  bandits[numero].isDyingBandit = 1;
  bandits[numero].isWalkingBandit = 0;
  bandits[numero].isAttackingBandit = 0;


   drawBanditDead(numero+1, posX, posY);
 


 bandits[numero].timerAnimationDyingBandit--;

 if(bandits[numero].timerAnimationDyingBandit <= 0){
  bandits[numero].timerAnimationDyingBandit = MAX_TIMER;
  drawBanditDead(numero+1, -5, -5);
  bandits[numero].pv = 0;
  
}


}
void JudgeDoHurt(){
  isHurt = 1;


  if(isAttacking == 0){
    drawJudgeHurt();
  }


  TimerAnimationHurt--;

  if(TimerAnimationHurt <= 0){
    TimerAnimationHurt = MAX_TIMER/2;
    isHurt = 0;
    JudgePV--;
    posXJudge -= 8;
     drawJudgeHurt();
  }
  


}
void JudgeWalk(){


  isWalking = 1;

  if(isJumping == 0 && isAttacking == 0 && isHurt == 0){
    if(TimerAnimationWalk >= MAX_TIMER/2){
      drawJudgeWalk1();
    } else if(TimerAnimationWalk >= 0 && TimerAnimationWalk < MAX_TIMER/2){
      drawJudgeWalk2();
    } 

    TimerAnimationWalk--;

    if (TimerAnimationWalk <= 0){

      TimerAnimationWalk = MAX_TIMER;

    }
  }

}

void JudgeGroundAttack(){
  isAttacking = 1;

  if(TimerAnimationAttack >= MAX_TIMER/2){
    drawJudgeAttack1();
  } else if(TimerAnimationAttack >= 0 && TimerAnimationAttack < MAX_TIMER/2){
    drawJudgeAttack2();
    checkColliderHammerAttack();

  }

  TimerAnimationAttack--;

  if (TimerAnimationAttack <= 0){

    TimerAnimationAttack = MAX_TIMER;
    isAttacking = 0;

  }

}

void JudgeDoJump(){

  if(TimerAnimationJump > MAX_TIMER/2){
   drawJudgeJUMP();
   posYJudge -= JudgeJumbSpeed;

 }
 else if(TimerAnimationJump >= 0 && TimerAnimationJump <= MAX_TIMER/2){
   drawJudgeJUMP();
   posYJudge += JudgeJumbSpeed;
 }

 TimerAnimationJump--;

 if(TimerAnimationJump <= 0){
  TimerAnimationJump = MAX_TIMER;
  isJumping = 0;
  
}


}
void initBandits(){

  for(i = 0; i < NB_BANDIT; i++){
    bandits[i].pv = 0;
    bandits[i].speed = 1;
    bandits[i].damage = 1;
    bandits[i].PosX = -5;
    bandits[i].PosY = -5;
    bandits[i].t = i+1;
    bandits[i].comportement = 0;
    bandits[i].timerAnimationWalkBandit = MAX_TIMER_BANDIT;
    bandits[i].timerAnimationAttackBandit = MAX_TIMER_BANDIT;
    bandits[i].timerAnimationDyingBandit = MAX_TIMER_BANDIT;
    bandits[i].isAttackingBandit = 0;
    bandits[i].isWalkingBandit = 0;
    bandits[i].isDyingBandit = 0;
  }


}

void generateBandits(){

  UBYTE nbBanditToDraw = 3;

  if(ScoreDistance <= 50){
    nbBanditToDraw = NB_BANDIT ;
  } else if(ScoreDistance <= 100){
   nbBanditToDraw = NB_BANDIT - 1;
 } else if (ScoreDistance > 100){
   nbBanditToDraw = NB_BANDIT;
 }

 for(i = 0; i < nbBanditToDraw; i++){
  if(bandits[i].pv == 0){
    bandits[i].pv = 1;
    bandits[i].isDyingBandit = 0;
    bandits[i].PosX = borderRight +16;
    bandits[i].timerAnimationDyingBandit = MAX_TIMER;
    bandits[i].timerAnimationAttackBandit = MAX_TIMER;
    bandits[i].timerAnimationWalkBandit = MAX_TIMER;
    do{
      bandits[i].PosY = rand() % borderBottom;
    }while(bandits[i].PosY > borderBottom+16 || bandits[i].PosY < borderTop+16);

    if(i > 0){
      do{
        bandits[i].PosY = rand() % borderBottom;
      }while(bandits[i].PosY == bandits[i-1].PosY || bandits[i].PosY > borderBottom+16 || bandits[i].PosY < borderTop+16);
    }

    bandits[i].t = i+1;

    pickComportement = rand() % 100;
    if(pickComportement > 99){
      bandits[i].comportement = 1;
    }else{
      bandits[i].comportement = 2;
    }
    bandits[i].isWalkingBandit = 1;

  }

}

}

void moveBandits(){

  for(i = 0; i < NB_BANDIT; i++){
    if(bandits[i].pv == 1){

      if(bandits[i].isDyingBandit == 0){
        if(bandits[i].isWalkingBandit == 1){
          BanditWalk(bandits[i].t-1, bandits[i].PosX, bandits[i].PosY);
          switch(bandits[i].comportement){
            case BANDIT_RUN:
            bandits[i].PosX -= bandits[i].speed;
            break;

            case BANDIT_FOLLOW:
            if(isJumping == 0){
              bandits[i].PosY = posYJudge+16;
            }

            bandits[i].PosX -= bandits[i].speed;
            break;
          }
        }


        if(bandits[i].PosX < borderLeft){
          bandits[i].pv = 0;
        }
        if(bandits[i].PosX < posXJudge+8 && bandits[i].PosX > posXJudge && bandits[i].PosY < posYJudge+24  && bandits[i].PosY > posYJudge+8){
          if(isJumping == 0){

            BanditAttack(bandits[i].t-1, bandits[i].PosX, bandits[i].PosY);

          }

        }else{
          bandits[i].isWalkingBandit = 1;
          bandits[i].isAttackingBandit = 0;
        }


      } else {
        BanditDie(bandits[i].t-1, bandits[i].PosX, bandits[i].PosY);
      }
    }

  }


}

void checkColliderHammerAttack(){

  for(i = 0; i < NB_BANDIT; i++){
    if(bandits[i].pv == 1 && bandits[i].isDyingBandit == 0){
      if(bandits[i].PosX < posXJudge+8 && bandits[i].PosX > posXJudge && bandits[i].PosY < posYJudge+24  && bandits[i].PosY > posYJudge+8){
        bandits[i].isDyingBandit = 1;

        score_bandit_digitUn++;
        if(score_bandit_digitUn > 9){
          score_bandit_digitUn = 0;
          score_bandit_digitDeux++;
        }
        if(score_bandit_digitDeux > 9){
          score_bandit_digitDeux = 0;
          score_bandit_digitTrois++;
        }
        if(score_bandit_digitTrois > 9){
          score_bandit_digitUn = 0;
          score_bandit_digitDeux = 0;
          score_bandit_digitTrois = 0;
        }
 
      } 
    }
  }

}
void checkCollideBorder(UBYTE newPosX, UBYTE newPosY){

  if(isJumping == 0){

    if(newPosY < borderTop){
      posYJudge = borderTop;
    }

    if(newPosY > borderBottom){
      posYJudge = borderBottom;
    }

  }

  if(newPosX > borderRight){
    posXJudge = borderRight;
  }

  if(newPosX < borderLeft){
    posXJudge = borderLeft;
  }

}

void moveJudge(){

  if(joypad()){
    if(joypad() & J_RIGHT){
      if(isAttacking == 0){
        posXJudge += JudgeSpeed;
      }
      
      checkCollideBorder(posXJudge, posYJudge);
      JudgeWalk();
    }
    if(joypad() & J_UP){
      if(isJumping == 0 && isAttacking == 0){
        posYJudge -= JudgeSpeed;
      }
      checkCollideBorder(posXJudge, posYJudge);
      JudgeWalk();

    }
    if(joypad() & J_DOWN){
      if(isJumping == 0 && isAttacking == 0){
        posYJudge += JudgeSpeed;
      }
      checkCollideBorder(posXJudge, posYJudge);
      JudgeWalk();
    }

    if(joypad() & J_LEFT){
      if(isAttacking == 0){
        posXJudge -= JudgeSpeed;
      }
      
      checkCollideBorder(posXJudge, posYJudge);
      JudgeWalk();
    }
    if(joypad() & J_A){
      if(isJumping == 0 && isAttacking == 0){
        isJumping = 1;
      }
    }
    if(joypad() & J_B){
      if(isJumping == 0){
        isAttacking = 1;
      }
    }
  }else{

    isWalking = 0;
  }

  if(isHurt == 1){
      JudgeDoHurt();

  }


}



void scrollCity(){


  if(TimerScrollBKG % 2 == 0){
    scroll_bkg(1,0);
    posXJudge--;
    for(i = 0; i < NB_BANDIT; i++){
      bandits[i].PosX--;
    }

    checkCollideBorder(posXJudge, posYJudge);
  } 

  TimerScrollBKG--;

  if (TimerScrollBKG <= 0){

    TimerScrollBKG = MAX_TIMER_SCROLLBKG;

  }
}

void drawScoreBandit(){

    set_win_tiles(50, 0, 1, 1, zero+score_bandit_digitUn);
    set_win_tiles(49, 0, 1, 1, zero+score_bandit_digitDeux);
    set_win_tiles(48, 0, 1, 1, zero+score_bandit_digitTrois);

}
void drawScoreDistance(){
    set_win_tiles(44, 0, 1, 1, zero+score_distance_digitUn);
    set_win_tiles(43, 0, 1, 1, zero+score_distance_digitDeux);
    set_win_tiles(42, 0, 1, 1, zero+score_distance_digitTrois);
}

void calculateScoreDistance(){
    if(distance > 155){
      score_distance_digitUn++;
      distance = 0;
    }

    if(score_distance_digitUn > 9){
      score_distance_digitUn = 0;
      score_distance_digitDeux++;
    } else if(score_distance_digitDeux > 9){
      score_distance_digitDeux = 0;
      score_distance_digitTrois++;
    } else if(score_distance_digitTrois > 9){
      score_distance_digitUn = 0;
      score_distance_digitDeux = 0;
      score_distance_digitTrois = 0;
    }

}

void drawPv(){
  switch(JudgePV){
    case 3:
    set_win_tiles(39, 0, 1, 1, heartFill);
    set_win_tiles(38, 0, 1, 1, heartFill);
    set_win_tiles(37, 0, 1, 1, heartFill);

    break;

    case 2:
    set_win_tiles(39, 0, 1, 1, heartEmpty);
    set_win_tiles(38, 0, 1, 1, heartFill);
    set_win_tiles(37, 0, 1, 1, heartFill);

    break;

    case 1:
    set_win_tiles(39, 0, 1, 1, heartEmpty);
    set_win_tiles(38, 0, 1, 1, heartEmpty);
    set_win_tiles(37, 0, 1, 1, heartFill);

    break;

    case 0:
    set_win_tiles(39, 0, 1, 1, heartEmpty);
    set_win_tiles(38, 0, 1, 1, heartEmpty);
    set_win_tiles(37, 0, 1, 1, heartEmpty);

    break;
  }

}

int main(){
  UWORD seed;
  seed = DIV_REG;
  initarand(seed);
  SPRITES_8x8;




  DISPLAY_OFF;
  DISPLAY_ON;
  HIDE_BKG;
  HIDE_SPRITES;
  HIDE_WIN;

  set_bkg_data(0, 43 + 26, decors_data);


  set_bkg_tiles(0, 0, 32, 16, CityMap);


  set_win_tiles(0, 0, 20, 2, HUD_MAP);
  SHOW_SPRITES;
  SHOW_BKG;
  SHOW_WIN;

  move_win(7, borderBottom + 22); //HUD






  initBandits();

  while(1)
  {

   distance++;
   drawScoreBandit();
   drawPv();
   calculateScoreDistance();
   drawScoreDistance();
   scrollCity();
   generateBandits();
   moveJudge();

   if(isJumping == 1){
    if(isHurt == 0){
      JudgeDoJump();
    }

  }

  if(isAttacking == 1){
    JudgeGroundAttack();
  }

  if(isJumping == 0 && isWalking == 0 && isAttacking == 0 && isHurt == 0){
    drawJudgeIDLE();
  }

  moveBandits();

  SHOW_SPRITES;
}
return 0;

}