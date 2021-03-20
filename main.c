#include <acknex.h>
#include <default.c>

var FMusic;
var FPlayerLife = 30;
var FPlayerHealth = 4;
var FPlayerHitTimer =0;
var FPlayerPickupCount =0;
var FPlayerAttack=0;
var FPlayerCanMove=1;
var FBossHealth=0;
var fcrouch=false;
var FCutScene=0;

	var lcanjump=true;

var GameProgress =0;

var boss_coins;

STRING* FString1=" ак ты посмел €витс€ в мой бар?";
STRING* FString2="—ейчас ты у мен€ получишь!";
STRING* FString3="*Ќажмите Enter дл€ продолжени€";
STRING* FString4="Ёто еще не конец, тебе просто повезло!";
STRING* FString5="–адуйс€ своей 'победе'...";

BMAP* bDialog = "dialog.dds";

action AAnimSprite()
{
while(1)
{
		my.frame += 1; 
		if (my.frame > my.skill2) 
		{ 
			my.frame = 1; // loop 
		}  
		wait (-0.5);
}
}

PANEL* panel_dialog =
{
	pos_x = 380;
	pos_y = 70;
	window(0,0,995,300,bDialog,0,0);
	layer = 10;
	flags =  OVERLAY;	
}

PANEL* panel_dialog_boss1 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString1, "System#50b", 1, NULL); 
	digits(50,125, FString2, "System#50b", 1, NULL); 
	digits(50,200, FString3, "System#50b", 1, NULL);
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_dialog_boss1_end =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString4, "System#50b", 1, NULL); 
	digits(50,125, FString5, "System#50b", 1, NULL); 
	digits(50,200, FString3, "System#50b", 1, NULL);
	layer = 11; 
	flags =  OVERLAY;
}

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



action platform_bar1()
{	var pos=0;
	while(1)
	{
		if (pos==0){
		while(vec_dist(my.x,player.x)>200)
		{		
			wait(-1);
		}
		wait(-1);
		FPlayerCanMove=0;
		var i;
		for (i=0; i<500; i++) 
		{
		my.z =my.z+1;
		player.z = player.z+1;
		wait(1);
		}
		FPlayerCanMove=1;
		pos=1;
		}
		if (pos==1 && player.z<400)
		{
			pos=0;
			my.z=my.z-500;
		}
		wait(1);
	}
}

action ABoss1SuperPower()
{
	set(my,PASSABLE);
	my.z=my.z-80;
	if (my.x>player.x){my.pan=90;}
   if (my.x<player.x){my.pan=270;}	
	var i;
   for (i=0; i<500; i++) 
   {
   	c_move(me,vector(0,1,0),vector(0,0,0),IGNORE_SPRITES | GLIDE);
   	if (vec_dist(my.x,player.x)  <150)
   	if (lcanjump==true)
      			{
      				boss_coins=boss_coins-1;
      				FHitPlayer();		
      			}
   	wait(1);
   }	
   ent_remove(me);
}

action ABoss1()
{
	boss_coins =1000;
	my.skill5=5;
	vec_set(my.min_x,vector(-20,-20,-240)); // set bounding box to individual values
   vec_set(my.max_x,vector(20,20,150));
   
   	vec_set(my.min_x,vector(-20,-20,-240)); // set bounding box to individual values
   vec_set(my.max_x,vector(20,20,150));
	
 	my.min_z *= 0.5;
 	var speed_down = 0;   // downward speed by gravity
   var anim_percent = 0; // animation percentage
   var lplayer_direction=0;
   VECTOR vFeet;
   vec_for_min(vFeet,me); // vFeet.z = distance from player origin to lowest vertex
   var lattacktimer;
   var lattackpercent;
   
   var LAnimPercent=0;
   if (my.x>player.x){my.pan=90;}
   if (my.x<player.x){my.pan=270;}	
   random_seed(0);
   while (vec_dist(my.x,player.x)>500) 			//ждем игрока
	{
		LAnimPercent=LAnimPercent+1*time_step;
		if (LAnimPercent>20){LAnimPercent=0;}
		my.frame = 1;
		if (LAnimPercent>10){my.frame = 2;}
		wait(1);
	}															// запускаем диалог
	
		FPlayerCanMove = 0;	
		set(panel_dialog,SHOW);
		set(panel_dialog_boss1,SHOW);
		while(key_enter==false){
			LAnimPercent=LAnimPercent+1*time_step;
			if (LAnimPercent>20){LAnimPercent=0;}
			my.frame = 1;
			if (LAnimPercent>10){my.frame = 2;}
			wait(1);
		}	
		reset(panel_dialog,SHOW);	
		reset(panel_dialog_boss1,SHOW);	
		FPlayerCanMove = 1;
		
															// начало битвы
		
	while (my.skill5>0)
	{
		if (my.x>player.x){my.pan=90;}
      if (my.x<player.x){my.pan=270;}
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
         
      if (random (5) > 4.99)	// пул€ем супер способность
      	{
      		my.frame = 10;
      		wait(-0.2);	
      		my.frame = 11;
      		wait(-0.2);
      		my.frame = 12;
      		ent_create("wave.dds",my.x,ABoss1SuperPower);
      		wait(-0.1);
      		my.frame = 1;
      		wait(-0.1);
      		my.frame = 2;
      	}
      
      if (vec_dist(my.x,player.x) >my.skill3) // пока игрок далеко- идем к нему
      {
      	lattacktimer = my.skill1;
      	//	if (my.x>player.x){lplayer_direction=-1;}
      	//	if (my.x<player.x){
      			lplayer_direction=1;
      			//}
      			
      					if (my.x>player.x){my.pan=90;}
      		if (my.x<player.x){my.pan=270;}		
      		
      		LAnimPercent = LAnimPercent+my.skill4*0.1*time_step;
      		if (LAnimPercent>4){LAnimPercent=1;}
      		
      		my.frame=LAnimPercent+2;		
      }
      else
      {
      	if (lattacktimer>0)
      	{
      		lattacktimer=lattacktimer-1;
      		lattackpercent=0;
      		my.frame = 1;
      	}
      	else
      	{
      		my.frame = 7+lattackpercent/30;
      		if (FPlayerAttack>50)
      		{
      			my.frame = 13;	
      			my.skill5=my.skill5-0.5; //получение урона
      			wait(-1);
      		}
      		lattackpercent=lattackpercent+10*time_step;
      		if (lattackpercent>90)
      		{
      			lattacktimer= my.skill1;
      			lattackpercent=0;      			
      		}
      		if (lattackpercent>50)
      		{
      			if (vec_dist(my.x,player.x)  <my.skill3)
      			{
      				FHitPlayer();
      				boss_coins = boss_coins-1;
      				//lattacktimer = my.skill1;
      				
      			}
      		}
      	} 
      	}
      	var dist_ahead = (lplayer_direction)*time_step;
      
      dist_ahead = sign(dist_ahead)*(abs(dist_ahead) + 0.5*dist_down); // adapt the speed on slopes	
         
       c_move(me,vector(0,(my.skill4/8)*dist_ahead,0),vector(0,0,-dist_down),IGNORE_PASSABLE | GLIDE); // move the player

	wait(1);	
	}	
	set(panel_dialog,SHOW);
	set(panel_dialog_boss1_end,SHOW);
	FPlayerCanMove = 0;
	while(key_enter==false){
			LAnimPercent=LAnimPercent+1*time_step;
			if (LAnimPercent>20){LAnimPercent=0;}
			my.frame = 1;
			if (LAnimPercent>10){my.frame = 2;}
			wait(1);
		}
		reset(panel_dialog,SHOW);
	reset(panel_dialog_boss1_end,SHOW);
		my.frame = 14;	
	FPlayerCanMove = 0;
	FPlayerPickupCount = FPlayerPickupCount+boss_coins;
	while(player.x<3955)
	{
		FCutScene=1;
		player.x=player.x+8*time_step;
		wait(1);
	}
	player.z=player.z+40;
	FCutScene=2;
	wait(-1);
		FCutScene=3;
		wait(-1);
		FCutScene=2;
}



PANEL* panel_hud =
{
	pos_x = 10;
	pos_y = 10;
	digits(20,30, "Life: %.0f", "System#20b", 1, FPlayerLife); 
	digits(20,50, "Health: %.0f", "System#20b", 1, FPlayerHealth); 
	digits(20,70, "Score: %.0f", "System#20b", 1, FPlayerPickupCount); 
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
	var j=100;
	my.skill5=1;
	vec_set(my.min_x,vector(-20,-20,-240)); // set bounding box to individual values
   vec_set(my.max_x,vector(20,20,150));
	//set(my,PASSABLE);
 	my.min_z *= 0.5;
 	var speed_down = 0;   // downward speed by gravity
   var anim_percent = 0; // animation percentage
   var lplayer_direction=0;
   VECTOR vFeet;
   vec_for_min(vFeet,me); // vFeet.z = distance from player origin to lowest vertex
   var lattacktimer;
   var lattackpercent;
   var lanimpercent=0;
   
	while (my.skill5>0)
	{

		my.frame = 1;
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
      if (vec_dist(my.x,player.x) >my.skill3) 
      {
      	if (vec_dist(my.x,player.x)  <my.skill2)
      	{
      		lattacktimer = my.skill1;
      	//	if (my.x>player.x){lplayer_direction=-1;}
      	//	if (my.x<player.x){
      			lplayer_direction=1;
      			//}
      			
      					if (my.x>player.x){my.pan=90;}
      		if (my.x<player.x){my.pan=270;}		
      		
      		lanimpercent = lanimpercent+my.skill4*0.1*time_step;
      		if (lanimpercent>4){lanimpercent=1;}
      		
      		my.frame=lanimpercent+1;	
      	}
      }
      else
      {
      	if (lattacktimer>0)
      	{
      		lattacktimer=lattacktimer-1;
      		lattackpercent=0;
      		my.frame = 1;
      	}
      	else
      	{
      		my.frame = 6+lattackpercent/30;
      		if (FPlayerAttack>50){my.skill5=0;}
      		lattackpercent=lattackpercent+10*time_step;
      		if (lattackpercent>90)
      		{
      			lattacktimer= my.skill1;
      			lattackpercent=0;      			
      		}
      		if (lattackpercent>50)
      		{
      			if (vec_dist(my.x,player.x)  <my.skill3)
      			{
      				FHitPlayer();
      				j=j-1;
      				//lattacktimer = my.skill1;
      				
      			}
      		}
      	} 
      	
      }
         
      var dist_ahead = (lplayer_direction)*time_step;
      
      dist_ahead = sign(dist_ahead)*(abs(dist_ahead) + 0.5*dist_down); // adapt the speed on slopes	
         
       c_move(me,vector(0,(my.skill4/8)*dist_ahead,0),vector(0,0,-dist_down),IGNORE_PASSABLE | GLIDE); // move the player
       wait(1);
	}
	set(my,PASSABLE);
	my.frame = 9;
	FPlayerPickupCount=FPlayerPickupCount+j;
//	ent_remove(me);
}

action ARealPlayer()
{	player = me;
	vec_set(my.min_x,vector(-20,-20,-240)); // set bounding box to individual values
   vec_set(my.max_x,vector(20,20,150));
//	if ((my.eflags&FAT) && (my.eflags&NARROW)) // when FAT+NARROW are both set
 	my.min_z *= 0.5;
 	var speed_down = 0;   // downward speed by gravity
   var anim_percent = 0; // animation percentage
   VECTOR vFeet;
   vec_for_min(vFeet,me); // vFeet.z = distance from player origin to lowest vertex
	var ljump =0;
	var lanimpercent=0;	
	var lacc=0;

	var lneedjumpacc=false;
	while (FPlayerLife>0)
	{
	lacc=0;
	fcrouch=false;
	if (key_s && lcanjump){fcrouch=true;}
	else
	{
			if (key_a){my.pan=90;lacc=1;}
      if (key_d){my.pan=270;lacc=1;}
      var dist_down; 
      if (c_trace(my.x,vector(my.x,my.y,my.z-5000),IGNORE_ME | IGNORE_PASSABLE | USE_BOX| IGNORE_SPRITES) > 0)
         dist_down = my.z + vFeet.z - target.z; // get distance between player's feet and the ground
      else
         dist_down =1;
		
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
      	if (key_w && lcanjump){ljump=150; lcanjump=false; lneedjumpacc =true;}} 
         
 		var dist_ahead = 7*(lacc)*time_step;
      dist_ahead = sign(dist_ahead)*(abs(dist_ahead) + 0.5*dist_down); // adapt the speed on slopes
      if (FPlayerCanMove==1){
      if (ljump<1){
      	c_move(me,vector(0,dist_ahead,0),vector(0,0,-dist_down),IGNORE_PASSABLE | GLIDE | IGNORE_SPRITES); // move the player
      }
      else
      {
      	
      	c_move(me,vector(0,dist_ahead,0),vector(0,0,dist_down),IGNORE_PASSABLE | GLIDE | IGNORE_SPRITES); // move the player
	}}

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
	} 
      camera.x =my.x;
		camera.y = my.y-4738;
		camera.z =my.z +276;
		camera.pan = -270;
		camera.tilt = 0;
      wait(1);
	}
}

action APlayer()
{
	//vec_set(my.min_x,vector(-20,-20,-240)); // set bounding box to individual values
   //vec_set(my.max_x,vector(20,20,150));
//	if ((my.eflags&FAT) && (my.eflags&NARROW)) // when FAT+NARROW are both set
	set(my,PASSABLE);
 	my.min_z *= 0.5;
 	var speed_down = 0;   // downward speed by gravity
   var anim_percent = 0; // animation percentage
   VECTOR vFeet;
   vec_for_min(vFeet,me); // vFeet.z = distance from player origin to lowest vertex
	var ljump =0;
	var lanimpercent=0;	
	var lacc=0;

	var lneedjumpacc=false;
	while (FPlayerLife>0)
	{
		my.x=player.x;
		my.y=player.y;
		my.z=player.z;
		
		if (key_a){my.pan=90;lacc=1;}
      if (key_d || FCutScene>0){my.pan=270;lacc=1;}	
      if (fcrouch){my.frame=3;} else	
      if (FPlayerHitTimer>0){my.frame=11;}
      else		
		if (FPlayerAttack>0)
		{
			my.frame=8;
			if (FPlayerAttack>40){my.frame=9;	}
			if (FPlayerAttack>60){my.frame=10;	}
		} else
		if (lcanjump==false)
		{
			if (ljump<70){my.frame=13;}
			if (ljump>70){my.frame=14;}
			if (lneedjumpacc==false){my.frame=15;}
		}
		else
		if (key_a||key_d||FCutScene==1)
		{
			
			lanimpercent = lanimpercent+my.skill4*0.1*time_step;
      		if (lanimpercent>4){lanimpercent=0;}
      		
      		my.frame=lanimpercent+4;
		}
		else
		{
			lacc=0;
				lanimpercent = lanimpercent+my.skill4*0.1*time_step;
      		if (lanimpercent>3){lanimpercent=0;}
      		
      		my.frame=lanimpercent;
		}
		if (FPlayerCanMove==0 &&FCutScene==0)	{
			lacc=0;
				lanimpercent = lanimpercent+my.skill4*0.1*time_step;
      		if (lanimpercent>3){lanimpercent=0;}
      		
      		my.frame=lanimpercent;
		}
		if (FCutScene==2){my.frame=16;}
			if (FCutScene==3){my.frame=17;}
      wait(1);
	}
	my.frame=12;
}

function FPlayerDeath()
{
	
}

function FCheckPlayer()
{
	set(player,TRANSLUCENT);
			player.alpha = 0;
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
					
		//	while (FPlayerHitTimer>=0)
			{
				FPlayerHitTimer -= 1 * time_step;
				wait(1);		
			}
	//	reset(player,TRANSLUCENT);
		}
	

	
}

function FLoadLevel1()
{
		level_load("lvl1.wmb");
	//	ent_sky = ent_createlayer("spacecube1+6.bmp", SKY | CUBE, 1);  
		camera.arc= 80;
		FMusic =	media_loop("megadeth-hangar_18.mid",NULL,50);	
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
	camera.arc=20;
	wait(-1);	
	sky_color.red = 0;
sky_color.green = 0;
sky_color.blue = 0; // bright blue sky   
	
	while (1)
	{
		FCheckPlayer();
		wait(1);
	}	
}