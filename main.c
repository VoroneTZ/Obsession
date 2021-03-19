#include <acknex.h>
#include <default.c>

var FMusic;
var FPlayerLife = 3;
var FPlayerHealth = 4;
var FPlayerHitTimer =0;
var FPlayerPickupCount =0;
var FPlayerAttack=0;

var GameProgress =0;

function FHitPlayer()
{
if (FPlayerHitTimer<1)
	{
		FPlayerHitTimer= 10;
		FPlayerHealth -= 1;		
		if (FPlayerHealth<1)
		{
			
			FPlayerLife -=1;
			if (FPlayerLife>0)
			{				
				FPlayerHealth=4;
				
			} 
		}
		
	}
}

PANEL* panel_hud =
{
	pos_x = 10;
	pos_y = 10;
	digits(20,30, "Life: %.0f", "Arial#20bi", 1, FPlayerLife); 
	digits(20,50, "Health: %.0f", "Arial#20bi", 1, FPlayerHealth); 
	digits(20,70, "Pickups: %.0f", "Arial#20bi", 1, FPlayerPickupCount); 
	flags = SHOW | OUTLINE;
}


PANEL* panel_black =
{
	pos_x = 0; pos_y = 0;
	size_x = 1920; size_y = 1080;
	red = 0;
	green = 0;
	blue = 0;
	
	flags = LIGHT | SHOW | TRANSLUCENT ;
	
}

action ANPC()
{
	my.skill5=1;
	if ((my.eflags&FAT) && (my.eflags&NARROW)) // when FAT+NARROW are both set
 	my.min_z *= 0.5;
 	var speed_down = 0;   // downward speed by gravity
   var anim_percent = 0; // animation percentage
   var lplayer_direction=0;
   VECTOR vFeet;
   vec_for_min(vFeet,me); // vFeet.z = distance from player origin to lowest vertex
   var lattacktimer;
   var lattackpercent;
	while (my.skill5>0)
	{
		var dist_down; 
      if (c_trace(my.x,vector(my.x,my.y,my.z-5000),IGNORE_ME | IGNORE_PASSABLE | USE_BOX) > 0)
         dist_down = my.z + vFeet.z - target.z; // get distance between player's feet and the ground
      else
         dist_down = 0;
		
	   if (dist_down > 0)  // above floor, fall down with increasing speed
         dist_down = clamp(dist_down,0,accelerate(speed_down,5,0.1));
      else                // on or below floor, set downward speed to zero
         speed_down = 0;
      lplayer_direction =0; 
      if (c_trace(vector(my.x,my.y,my.z),vector(player.x,player.y,player.z),IGNORE_ME | IGNORE_PASSABLE | USE_BOX |IGNORE_WORLD|IGNORE_MAPS) >my.skill3) 
      {
      	if (c_trace(vector(my.x,my.y,my.z),vector(player.x,player.y,player.z),IGNORE_ME | IGNORE_PASSABLE | USE_BOX) <my.skill2)
      	{
      		lattacktimer = my.skill1;
      		if (my.x>player.x){lplayer_direction=-1;}
      		if (my.x<player.x){lplayer_direction=1;}
      	}
      }
      else
      {
      	if (lattacktimer>0)
      	{
      		lattacktimer=lattacktimer-1;
      		lattackpercent=0;
      	}
      	else
      	{
      		if (FPlayerAttack>50){my.skill5=0;}
      		lattackpercent=lattackpercent+10*time_step;
      		if (lattackpercent>90)
      		{
      			lattacktimer= my.skill1;
      			lattackpercent=0;
      		}
      		if (lattackpercent>50)
      		{
      			if (c_trace(vector(my.x,my.y,my.z),vector(player.x,player.y,player.z),IGNORE_ME | IGNORE_PASSABLE | USE_BOX) <my.skill3)
      			{
      				FHitPlayer();
      				lattacktimer = my.skill1;
      			}
      		}
      	} 
      	
      }
         
      var dist_ahead = my.skill4*(lplayer_direction)*time_step;
      
      dist_ahead = sign(dist_ahead)*(abs(dist_ahead) + 0.5*dist_down); // adapt the speed on slopes	
         
       c_move(me,vector(dist_ahead,0,0),vector(0,0,-dist_down),IGNORE_PASSABLE | GLIDE); // move the player
       wait(1);
	}
	ent_remove(me);
}

action APlayer()
{
	player = me;
	if ((my.eflags&FAT) && (my.eflags&NARROW)) // when FAT+NARROW are both set
 	my.min_z *= 0.5;
 	var speed_down = 0;   // downward speed by gravity
   var anim_percent = 0; // animation percentage
   VECTOR vFeet;
   vec_for_min(vFeet,me); // vFeet.z = distance from player origin to lowest vertex
	var ljump =0;	
	var lcanjump=true;
	var lneedjumpacc=false;
	while (FPlayerLife>0)
	{
      var dist_down; 
      if (c_trace(my.x,vector(my.x,my.y,my.z-5000),IGNORE_ME | IGNORE_PASSABLE | USE_BOX) > 0)
         dist_down = my.z + vFeet.z - target.z; // get distance between player's feet and the ground
      else
         dist_down = 0;
		
	   if (dist_down > 0)  // above floor, fall down with increasing speed
         dist_down = clamp(dist_down,0,accelerate(speed_down,5,0.1));
      else                // on or below floor, set downward speed to zero
         speed_down = 0;
         
      if (FPlayerAttack==0 && key_space){FPlayerAttack=1;}
      if (FPlayerAttack>0){FPlayerAttack=FPlayerAttack+5*time_step;}
      if (FPlayerAttack>100){FPlayerAttack=0;}
         
      if (ljump>0){ljump=ljump-(15*time_step);speed_down=(ljump)/5;} 
      else
      { 
      	if (lcanjump==false && lneedjumpacc==true){speed_down = 0; lneedjumpacc=false;}
      	if ((c_trace(my.x,vector(my.x,my.y,my.z-5000),IGNORE_ME | IGNORE_PASSABLE | USE_BOX) <1)&& key_w==false){lcanjump=true;}
      	if (key_w && lcanjump){ljump=100; lcanjump=false; lneedjumpacc =true;}} 
         
 		var dist_ahead = 5*(key_d-key_a)*time_step;
      dist_ahead = sign(dist_ahead)*(abs(dist_ahead) + 0.5*dist_down); // adapt the speed on slopes
      
      if (ljump<1){
      	c_move(me,vector(dist_ahead,0,0),vector(0,0,-dist_down),IGNORE_PASSABLE | GLIDE); // move the player
      }
      else
      {
      	
      	c_move(me,vector(dist_ahead,0,0),vector(0,0,dist_down),IGNORE_PASSABLE | GLIDE); // move the player
		}

// 		if (dist_ahead != 0) // player is moving ahead
//      {
//         anim_percent += 1.3*dist_ahead; // 1.3 = walk cycle percentage per quant
//         ent_animate(me,"walk",anim_percent,ANM_CYCLE); // play the "walk" animation
//      }
//      else // player stands still
//      { 
//         anim_percent += 5*time_step; 
//         ent_animate(me,"stand",anim_percent,ANM_CYCLE); // play the "stand" animation
//      }
      camera.x =my.x;
		camera.y = my.y-738;
		camera.z =my.z +276;
		camera.pan = -270;
		camera.tilt = 345;
      wait(1);
	}
}

function FPlayerDeath()
{
	
}

function FCheckPlayer()
{
	if (FPlayerHealth==0)
	{
		FPlayerHealth=4;
		FPlayerLife = FPlayerLife-1;
		if (FPlayerLife<1)
		{
			FPlayerDeath();
		}
	}
	if (FPlayerHitTimer>0)
	{	
			set(player,TRANSLUCENT);
			player.alpha = 30;		
		//	while (FPlayerHitTimer>=0)
			{
				FPlayerHitTimer -= 1 * time_step;
				wait(1);		
			}
		reset(player,TRANSLUCENT);
		}
	

	
}

function FLoadLevel1()
{
		level_load("lvl1.wmb");
	//	ent_sky = ent_createlayer("spacecube1+6.bmp", SKY | CUBE, 1);  
		camera.arc= 80;
	//	FMusic =	media_loop("megadeth-hangar_18.mid",NULL,50);	
}

function FContinueGame()
{
	if (GameProgress==0)
	{
		FLoadLevel1();
	}
}


function main()
{
	
	camera.clip_near = 0;
	video_window(vector(0,0,0),vector(0,0,0),0,"Obsession");	
	video_screen = 0;
	video_mode = 12;
	
	shadow_stencil = 1;
	mouse_mode = 1;
	
//	if (game_load("Save",0)<=0){game_save("Save",0,SV_VARS);}
	
	FContinueGame();
	wait(-1);	
	
	
	while (1)
	{
		FCheckPlayer();
		wait(1);
	}	
}