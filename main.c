#include <acknex.h>
#include <default.c>

var FMusic;
var FPlayerLife = 5;
var FPlayerHealth = 4;
var FPlayerHitTimer =0;
var FPlayerPickupCount =0;
var FPlayerAttack=0;
var FPlayerCanMove=1;
var FBossHealth=0;
var fcrouch=false;
var FCutScene=0;
var FBarGirl=0;

	var lcanjump=true;

var GameProgress =0;

var boss_coins;

STRING* FString1="Здарова отец, вижу ты зубы не";
STRING* FString2="бережешь, раз пришел сюда.";
STRING* FString3="*Нажмите Enter для продолжения";
STRING* FString4="Это еще не конец, тебе просто повезло!";
STRING* FString5="Радуйся своей 'победе'...";
STRING* FString7="VoroneTZ представляет";
STRING* FString8="специально для theBatya Game Jam 2021";
STRING* FString9="Очередная пьяная и одинокая ночь...";
STRING* FString10="Очередные безумные сны...";
STRING* FString11="Ночь 1";
STRING* FString12="Рок тусовка";
STRING* FString13="Ночь 2";
STRING* FString14="Казино";
STRING* FString15="Ночь 3";
STRING* FString16="Зависимость";
STRING* FString17="Ночь 4";
STRING* FString18="Obsession";
STRING* FString19="Так началась новая жизнь...";
STRING* FString20="Конец.";
STRING* FString21="В своих снах я мог добится...";
STRING* FString22="Справедливости... и ее...";
STRING* FString23="Его же рот этого казино!";
STRING* FString24="Ты опять пришел ко мне?";
STRING* FString25="Велком ту зе джангл";
STRING* FString26="бейби!";
STRING* FString27="Без препаратов уснуть всё тяжелее";
STRING* FString28="Пытаюсь убежать от реальности...";
STRING* FString29="Что это?!";
STRING* FString30="Неужели...";
STRING* FString31="Это я...";
STRING* FString32="Ты должен понять...";
STRING* FString33="Мы с тобой больше не вместе...";
STRING* FString34="Мяу...";
STRING* FString35="А ведь ни кто не нужен,";
STRING* FString36="когда есть такой хороший котик.";
STRING* FString37="Колода в другом порядке";
STRING* FString38="разложена.. запечатанная..";
STRING* FString39="Конец близок";
STRING* FString40="Надеюсь ты все поймешь";

STRING* FString41="Создано для theBatya Game Jam 2021";
STRING* FString42="Идея @VoroneTZ";
STRING* FString43="Оператор @VoroneTZ";
STRING* FString44="Художник @VoroneTZ";
STRING* FString45="Программист @VoroneTZ";
STRING* FString46="Левел дизаин @VoroneTZ";
STRING* FString47="Актеры: @VoroneTZ";
STRING* FString48="Актеры: @dragonborn_earl";
STRING* FString49="Актеры: @cherry_verner";
STRING* FString50="Отдельное спасибо друзьям за поддержку";
STRING* FString51="2021 VTZ Games";

BMAP* bDialog = "dialog.dds";

SOUND* miss_snd = "miss.wav"; 
SOUND* fire0_snd = "fire-0.wav"; 
SOUND* lift_snd = "machan.wav"; 
SOUND* hit1_snd = "hit1.wav"; 
SOUND* hit2_snd = "hit2.wav"; 
SOUND* hit_snd = "hit.wav"; 
SOUND* fall_snd = "migstart.wav"; 
SOUND* dostal3_snd = "dostal3.wav"; 
SOUND* explo1_snd = "explo1.wav"; 


PANEL* panel_hud =
{
	pos_x = 10;
	pos_y = 10;
	digits(20,30, "Life: %.0f", "System#20b", 1, FPlayerLife); 
	digits(20,50, "Health: %.0f", "System#20b", 1, FPlayerHealth); 
	digits(20,70, "Score: %.0f", "System#20b", 1, FPlayerPickupCount); 
	flags =  OUTLINE;
}

PANEL* panel_boss =
{
	pos_x = 100;
	pos_y = 10;
	digits(20,70, "BOSS HEALTH: %.0f", "System#30b", 1, FBossHealth); 
	flags =  OUTLINE;
}


PANEL* panel_black =
{
	pos_x = 0; pos_y = 0;
	size_x = 1920; size_y = 1080;
	red = 0;
	green = 0;
	blue = 0;
	
	flags =  SHOW | LIGHT | TRANSLUCENT ;
	
}

action ABarGirl()
{
	while(1)
	{
		
	
			my.frame = FBarGirl;
			
		wait(1);
	}
}

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

PANEL* panel_dialog_boss2 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString23, "System#50b", 1, NULL); 
	digits(50,125, FString24, "System#50b", 1, NULL); 
	digits(50,200, FString3, "System#50b", 1, NULL);
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_dialog_boss2_end =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString37, "System#50b", 1, NULL); 
	digits(50,125, FString38, "System#50b", 1, NULL); 
	digits(50,200, FString3, "System#50b", 1, NULL);
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_dialog_boss3 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString25, "System#50b", 1, NULL); 
	digits(50,125, FString26, "System#50b", 1, NULL); 
	digits(50,200, FString3, "System#50b", 1, NULL);
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_dialog_boss3_1 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString39, "System#50b", 1, NULL); 
	digits(50,125, FString40, "System#50b", 1, NULL); 
	digits(50,200, FString3, "System#50b", 1, NULL);
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_dialog_boss3_end =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString29, "System#50b", 1, NULL); 
	digits(50,125, FString30, "System#50b", 1, NULL); 
	digits(50,200, FString31, "System#50b", 1, NULL);
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

PANEL* panel_dialog_intro1 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString7, "System#50b", 1, NULL); 
	digits(50,125, FString8, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_dialog_intro2 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString9, "System#50b", 1, NULL); 
	digits(50,125, FString10, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_dialog_intro3 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString11, "System#50b", 1, NULL); 
	digits(50,125, FString12, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_dialog_intro4 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString15, "System#50b", 1, NULL); 
	digits(50,125, FString18, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_dialog_level2_1 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString21, "System#50b", 1, NULL); 
	digits(50,125, FString22, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_dialog_level2_2 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString13, "System#50b", 1, NULL); 
	digits(50,125, FString14, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_dialog_level3_1 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString27, "System#50b", 1, NULL); 
	digits(50,125, FString28, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_dialog_level3_2 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString15, "System#50b", 1, NULL); 
	digits(50,125, FString16, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_dialog_level4_1 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString32, "System#50b", 1, NULL); 
	digits(50,125, FString33, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_dialog_level4_2 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString34, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_title1 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString41, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_title2 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString42, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_title3 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString43, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_title4 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString44, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}
PANEL* panel_title5 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString45, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}
PANEL* panel_title6 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString46, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_title7 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString47, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_title8 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString48, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_title9 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString49, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_title10 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString51, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_dialog_level4_3 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString35, "System#50b", 1, NULL); 
	digits(50,125, FString36, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
}

PANEL* panel_dialog_level4_5 =
{
	pos_x = 380;
	pos_y = 70;
	digits(50,50, FString19, "System#50b", 1, NULL); 
	digits(50,125, FString20, "System#50b", 1, NULL); 
	layer = 11; 
	flags =  OVERLAY;
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
function FHitPlayer()
{
if (FPlayerHitTimer<1)
	{
		snd_play(hit_snd,100,0);
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
		snd_play(lift_snd,100,0);
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

action platform_city1()
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
		snd_play(lift_snd,100,0);
		var i;
		for (i=0; i<1500; i++) 
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


action AGhost()
{
		set(my,PASSABLE);
		snd_play(fire0_snd,100,0);
	my.z=my.z-80;
	if (my.x>player.x){my.pan=90;}
   if (my.x<player.x){my.pan=270;}	
	var i;
   for (i=0; i<500; i++) 
   {
   	c_move(me,vector(0,1,0),vector(0,0,0),IGNORE_SPRITES | GLIDE);
   	if (vec_dist(my.x,player.x)  <150)
   	if (FPlayerAttack<30)
      			{
      				boss_coins=boss_coins-1;
      				FHitPlayer();		
      			}
   	wait(1);
   }	
   snd_play(explo1_snd,100,0);
   ent_remove(me);
}

action ADarkPlayer()
{
	my.x=player.x-800;
	vec_scale(my.scale_x,1.9);
//	set(my, UNLIT);
	var i;
	var anim;
	for (i=0;i<600;i++)
	{
		my.x=my.x+1;
		anim=anim+0.2*time_step;
		if (anim>4)	{anim=1;}
		my.frame=anim+3;
		wait(1);
	}
	snd_play(dostal3_snd,100,0);
	my.frame=18;
	wait(-2);
	my.frame=13;
	wait(-1);
	set(panel_black,SHOW);
	panel_black.alpha = 100;
	wait(-0.2);
	my.x=my.x+20;
	my.frame=14;
	panel_black.alpha = 0;
	wait(-0.2);
	panel_black.alpha = 100;
	wait(-0.2);
	my.x=my.x+20;
	my.frame=7;
	panel_black.alpha = 0;
	wait(-0.2);
		panel_black.alpha = 100;
	wait(-0.2);
	my.x=my.x+20;
	my.frame=8;
	panel_black.alpha = 0;
	wait(-0.2);
		panel_black.alpha = 100;
	wait(-0.2);
	my.x=my.x+9;
	my.frame=14;
	panel_black.alpha = 0;
	wait(-0.2);
	panel_black.alpha = 100;
	wait(-2);
	set(panel_dialog,SHOW);
	set(panel_dialog_level4_2,SHOW);
	wait(-2);
	reset(panel_dialog,SHOW);
	reset(panel_dialog_level4_2,SHOW);	
	panel_black.alpha = 0;
	player.x=-18591;
	player.y=37;
	player.z=748;
	FCutScene=7;
	wait(-2);
	FCutScene=2;
	player.pan=90;
	wait(-1);
	set(panel_dialog,SHOW);
	set(panel_dialog_level4_3,SHOW);
	wait(-3);
	reset(panel_dialog,SHOW);
	reset(panel_dialog_level4_3,SHOW);
	wait(-1);
	media_play("black_sabbath-paranoid.mid",NULL,50);
	set(panel_dialog,SHOW);
	set(panel_dialog_level4_5,SHOW);
	wait(-1);
	reset(panel_dialog_level4_5,SHOW);
	panel_black.alpha = 100;
	set(panel_title1,SHOW);
	wait(-2);
	reset(panel_title1,SHOW);
		set(panel_title2,SHOW);
	wait(-2);
	reset(panel_title2,SHOW);
		set(panel_title3,SHOW);
	wait(-2);
	reset(panel_title3,SHOW);
		set(panel_title4,SHOW);
	wait(-2);
	reset(panel_title4,SHOW);
		set(panel_title5,SHOW);
	wait(-2);
	reset(panel_title5,SHOW);
		set(panel_title6,SHOW);
	wait(-2);
	reset(panel_title6,SHOW);
		set(panel_title7,SHOW);
	wait(-2);
	reset(panel_title7,SHOW);
		set(panel_title8,SHOW);
	wait(-2);
	reset(panel_title8,SHOW);
		set(panel_title9,SHOW);
	wait(-2);
	reset(panel_title9,SHOW);
		set(panel_title10,SHOW);
	wait(-2);
	reset(panel_title10,SHOW);
}

action ALastL()
{
//	set(my, UNLIT);
vec_scale(my.scale_x,1.9);
}

action ALastBoss()
{
	my.frame=5;
	my.pan=-90;
	var i;
	var anim;
	while(vec_dist(my.x,player.x)>500)
	{
		wait(1);	
	}

	FPlayerCanMove=0;
	my.frame=6;
	wait(-1);
	my.frame=5;
	set(panel_dialog,SHOW);
	set(panel_dialog_level4_1,SHOW);
	wait(-1);
	my.frame=6;
	wait(-1);
	my.frame=5;
	reset(panel_dialog,SHOW);
	reset(panel_dialog_level4_1,SHOW);
	ENTITY* sereja;
	sereja=ent_create("lastboss+6.dds",vector(my.x - 70, my.y+10, my.z),ALastL);	
	sereja.frame=5;
//	my.pan=my.pan+180;
	FCutScene=5;
	wait(-1);
	sereja.frame=6;
	wait(-1);
	sereja.frame=5;
	my.frame=6;
	FCutScene=6;
	my.pan=90;
	sereja.pan=90;
	for (i=0; i<1000; i++)
	{
		my.x=my.x-0.5;
		sereja.x=my.x+5;
		anim=anim+0.2*time_step;
		if (anim>4)	{anim=1;}
		my.frame=anim;
		sereja.frame=anim;
		wait(1);
	}
	FCutScene=5;
	wait(-2);
	FCutScene=0;
	my.z=2000;
		FPlayerCanMove=0;
		wait(-1);
	for (i=0;i<2; i++)
	{
		ent_create("ghost.dds",vector(player.x - 300, player.y, player.z),AGhost);	
		wait(-2);
		ent_create("ghost.dds",vector(player.x + 300, player.y, player.z),AGhost);	
		wait(-2);
	}	
	wait(-2);
	FPlayerCanMove=0;
	wait(1);
	ent_create("player2+20.dds",player.x,ADarkPlayer);
		media_stop(FMusic);	
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

action ABoss2SuperPower()
{
	set(my,PASSABLE);
	my.z=my.z+80;
	if (my.x>player.x){my.pan=90;}
   if (my.x<player.x){my.pan=270;}	
	var i;
   for (i=0; i<500; i++) 
   {
   	c_move(me,vector(0,1,0),vector(0,0,0),IGNORE_SPRITES | GLIDE);
   	if (vec_dist(my.x,player.x)  <150)
   	if (fcrouch==false)
      			{
      				boss_coins=boss_coins-1;
      				FHitPlayer();		
      			}
   	wait(1);
   }	
   ent_remove(me);
}

function FLoadLevel2()
{
	GameProgress=2;
	FBarGirl=1;
	FCutScene=0;
	FPlayerCanMove = 1;
	media_stop(FMusic);
	level_load("intro.wmb");
camera.arc= 60;
wait(-1);
	panel_black.alpha = 100;
		var i=1;
	
	{
	while (panel_black.alpha >1)
	{
		panel_black.alpha -= 8*time_step; 
		if (i<=50)
	   i=i+0.2;
		wait(2);
	}
	panel_black.alpha = 0;
	}
	
	set(panel_dialog,SHOW);
	set(panel_dialog_level2_1,SHOW);
	wait(-4);
	reset(panel_dialog,SHOW);
	reset(panel_dialog_level2_1,SHOW);
	wait(-1);
	set(panel_dialog,SHOW);
	set(panel_dialog_level2_2,SHOW);
	wait(-4);
	reset(panel_dialog,SHOW);
	reset(panel_dialog_level2_2,SHOW);
	wait(-1);
	
		panel_black.alpha = 0;
	var i=50;
	while (i>1)
	{
	while (panel_black.alpha <100)
	{
		panel_black.alpha += 8*time_step; 
		if (i>1)
		media_tune(FMusic,i,0,0);
		i=i-0.2;
		wait(2);
	}
	panel_black.alpha = 100;
		
	}
	
		level_load("lvl2.wmb");
	//	ent_sky = ent_createlayer("spacecube1+6.bmp", SKY | CUBE, 1);  
		camera.arc=20;
		FMusic =	media_play("motley_crue-girls_girls_girls.mid",NULL,50);
		
			media_tune(FMusic,1,0,0);
	panel_black.alpha = 100;
		var i=1;
		wait(-2);
		FCheckPlayer();
	{
	while (panel_black.alpha >1)
	{
		panel_black.alpha -= 8*time_step; 
		if (i<=50)
		media_tune(FMusic,i,0,0);
	   i=i+0.2;
		wait(2);
	}
	panel_black.alpha = 0;
		media_tune(FMusic,50,0,0);	
	}
	
		set(panel_hud, SHOW);
	
			while (FCutScene==0)
	{
		FCheckPlayer();
		wait(1);
	}	
	
}

function FLoadLevel3()
{
	GameProgress=3;
	FCutScene=0;
	FPlayerCanMove = 1;
	media_stop(FMusic);
	level_load("intro.wmb");
camera.arc= 60;
wait(-1);
	panel_black.alpha = 100;
		var i=1;
	
	{
	while (panel_black.alpha >1)
	{
		panel_black.alpha -= 8*time_step; 
		if (i<=50)
	   i=i+0.2;
		wait(2);
	}
	panel_black.alpha = 0;
	}
	
	set(panel_dialog,SHOW);
	set(panel_dialog_level3_1,SHOW);
	wait(-4);
	reset(panel_dialog,SHOW);
	reset(panel_dialog_level3_1,SHOW);
	wait(-1);
	set(panel_dialog,SHOW);
	set(panel_dialog_level3_2,SHOW);
	wait(-4);
	reset(panel_dialog,SHOW);
	reset(panel_dialog_level3_2,SHOW);
	wait(-1);
	
		panel_black.alpha = 0;
	var i=50;
	while (i>1)
	{
	while (panel_black.alpha <100)
	{
		panel_black.alpha += 8*time_step; 
		if (i>1)
		media_tune(FMusic,i,0,0);
		i=i-0.2;
		wait(2);
	}
	panel_black.alpha = 100;
		
	}
	
		level_load("lvl3.wmb");
	//	ent_sky = ent_createlayer("spacecube1+6.bmp", SKY | CUBE, 1);  
		camera.arc=20;
		FMusic =	media_play("guns_n_roses-welcome_to_the_jungle.mid",NULL,50);
		
			media_tune(FMusic,1,0,0);
	panel_black.alpha = 100;
		var i=1;
		wait(-2);
		FCheckPlayer();
	{
	while (panel_black.alpha >1)
	{
		panel_black.alpha -= 8*time_step; 
		if (i<=50)
		media_tune(FMusic,i,0,0);
	   i=i+0.2;
		wait(2);
	}
	panel_black.alpha = 0;
		media_tune(FMusic,50,0,0);	
	}
	
		set(panel_hud, SHOW);
	
			while (FCutScene==0)
	{
		FCheckPlayer();
		wait(1);
	}	
	
}

function FLoadLevel4()
{
	GameProgress=4;
	FCutScene=0;
	FPlayerCanMove = 1;
	media_stop(FMusic);

	
		level_load("lvl4.wmb");
	//	ent_sky = ent_createlayer("spacecube1+6.bmp", SKY | CUBE, 1);  
		camera.arc=20;
		FMusic =	media_play("01917.mp3",NULL,50);
		
		//	media_tune(FMusic,1,0,0);
	panel_black.alpha = 100;
		var i=1;
		wait(-2);
		FCheckPlayer();
	{
	while (panel_black.alpha >1)
	{
		panel_black.alpha -= 8*time_step; 
		if (i<=50)
	//	media_tune(FMusic,i,0,0);
	   i=i+0.2;
		wait(2);
	}
	panel_black.alpha = 0;
	//	media_tune(FMusic,50,0,0);	
	}
	
		set(panel_hud, SHOW);
		set(panel_dialog,SHOW);
		set(panel_dialog_intro4,SHOW);
		wait(-2);
		reset(panel_dialog,SHOW);
		reset(panel_dialog_intro4,SHOW);
	
			while (FCutScene==0)
	{
		FCheckPlayer();
		wait(1);
	}	
	
}



action ABoss1()
{
	boss_coins =1000;
	my.skill5=5;
	vec_set(my.min_x,vector(-20,-20,-240)); // set bounding box to individual values
   vec_set(my.max_x,vector(20,20,150));
   FBossHealth =0;
   	vec_set(my.min_x,vector(-20,-20,-240)); // set bounding box to individual values
   vec_set(my.max_x,vector(20,20,150));
	FBossHealth=0;
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
		FBossHealth =my.skill5*100;
		set(panel_boss,SHOW);
		if (my.x>player.x){my.pan=90;}
      if (my.x<player.x){my.pan=270;}
      var dist_down; 
      if (c_trace(my.x,vector(my.x,my.y,my.z-5000),IGNORE_ME | IGNORE_PASSABLE | IGNORE_SPRITES | USE_BOX) > 0)
         dist_down = my.z + vFeet.z - target.z; // get distance between player's feet and the ground
      else
         dist_down = 0;
		
	   if (dist_down > 0)  // above floor, fall down with increasing speed
         dist_down = clamp(dist_down,0,accelerate(speed_down,5,0.1));
      else                // on or below floor, set downward speed to zero
         speed_down = 0;
      lplayer_direction =0; 
         
      if (random (5) > 4.995)	// пуляем супер способность
      	{
      		my.frame = 10;
      			snd_play(fire0_snd,100,0);
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
      			snd_play(hit_snd,100,0);
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
         
       c_move(me,vector(0,(my.skill4/8)*dist_ahead,0),vector(0,0,-dist_down),IGNORE_PASSABLE | IGNORE_SPRITES | GLIDE); // move the player

	wait(1);	
	}	
	reset(panel_boss,SHOW);
	set(panel_dialog,SHOW);
	set(panel_dialog_boss1_end,SHOW);
	FPlayerCanMove = 0;
	player.z=my.z;
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
		FBarGirl=2;
		wait(-1);
		FCutScene=2;
		wait(-1);
		FBarGirl=1;
		
		
			panel_black.alpha = 0;
	var i=50;
	while (i>1)
	{
	while (panel_black.alpha <100)
	{
		panel_black.alpha += 8*time_step; 
		if (i>1)
		media_tune(FMusic,i,0,0);
		i=i-0.2;
		wait(2);
	}
	panel_black.alpha = 100;
		
	}
	
	FLoadLevel2();
}

action ABoss2()
{
	boss_coins =2000;
	my.skill5=7;
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
		my.frame = 15;
		wait(1);
	}															// запускаем диалог
	
		FPlayerCanMove = 0;	
		set(panel_dialog,SHOW);
		set(panel_dialog_boss2,SHOW);
		while(key_enter==false){
			LAnimPercent=LAnimPercent+1*time_step;
			if (LAnimPercent>20){LAnimPercent=0;}
			my.frame = 15;
			if (LAnimPercent>10){my.frame = 16;}
			wait(1);
		}	
		reset(panel_dialog,SHOW);	
		reset(panel_dialog_boss2,SHOW);	
		FPlayerCanMove = 1;
		
															// начало битвы
		
	while (my.skill5>0)
	{
		set(panel_boss,SHOW);
		FBossHealth =my.skill5*100;
		if (my.x>player.x){my.pan=90;}
      if (my.x<player.x){my.pan=270;}
      var dist_down; 
      if (c_trace(my.x,vector(my.x,my.y,my.z-5000),IGNORE_ME | IGNORE_PASSABLE | IGNORE_SPRITES | USE_BOX) > 0)
         dist_down = my.z + vFeet.z - target.z; // get distance between player's feet and the ground
      else
         dist_down = 0;
		
	   if (dist_down > 0)  // above floor, fall down with increasing speed
         dist_down = clamp(dist_down,0,accelerate(speed_down,5,0.1));
      else                // on or below floor, set downward speed to zero
         speed_down = 0;
      lplayer_direction =0; 
         
      if (random (5) > 4.99)	// пуляем супер способность
      	{
      		my.frame = 10;
      			snd_play(fire0_snd,100,0);
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
      			snd_play(hit_snd,100,0);
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
         
       c_move(me,vector(0,(my.skill4/8)*dist_ahead,0),vector(0,0,-dist_down),IGNORE_PASSABLE | IGNORE_SPRITES | GLIDE); // move the player

	wait(1);	
	}
	reset(panel_boss,SHOW);	
	set(panel_dialog,SHOW);
	set(panel_dialog_boss2_end,SHOW);
	FPlayerCanMove = 0;
	player.z=my.z;
	while(key_enter==false){
			LAnimPercent=LAnimPercent+1*time_step;
			if (LAnimPercent>20){LAnimPercent=0;}
			my.frame = 1;
			if (LAnimPercent>10){my.frame = 2;}
			wait(1);
		}
		reset(panel_dialog,SHOW);
	reset(panel_dialog_boss2_end,SHOW);
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
		FBarGirl=2;
		wait(-1);
		FCutScene=2;
		FBarGirl=1;
		
		
			panel_black.alpha = 0;
	var i=50;
	while (i>1)
	{
	while (panel_black.alpha <100)
	{
		panel_black.alpha += 8*time_step; 
		if (i>1)
		media_tune(FMusic,i,0,0);
		i=i-0.2;
		wait(2);
	}
	panel_black.alpha = 100;
		
	}
	
	FLoadLevel3();
}

action ABoss3()
{
	boss_coins =3000;
	my.skill5=10;
	FBossHealth=0;
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
		my.frame = 1;
		wait(1);
	}															// запускаем диалог
	
		FPlayerCanMove = 0;	
		set(panel_dialog,SHOW);
		set(panel_dialog_boss3,SHOW);
		while(key_enter==false){
			LAnimPercent=LAnimPercent+1*time_step;
			if (LAnimPercent>20){LAnimPercent=0;}
			my.frame = 2;
			if (LAnimPercent>10){my.frame = 1;}
			wait(1);
		}	
		reset(panel_dialog,SHOW);	
		reset(panel_dialog_boss3,SHOW);	
		FPlayerCanMove = 1;
		
															// начало битвы
		
	while (my.skill5>0)
	{
		set(panel_boss,SHOW);
		FBossHealth =my.skill5*100;
		if (my.x>player.x){my.pan=90;}
      if (my.x<player.x){my.pan=270;}
      var dist_down; 
      if (c_trace(my.x,vector(my.x,my.y,my.z-5000),IGNORE_ME | IGNORE_PASSABLE | IGNORE_SPRITES | USE_BOX) > 0)
         dist_down = my.z + vFeet.z - target.z; // get distance between player's feet and the ground
      else
         dist_down = 0;
		
	   if (dist_down > 0)  // above floor, fall down with increasing speed
         dist_down = clamp(dist_down,0,accelerate(speed_down,5,0.1));
      else                // on or below floor, set downward speed to zero
         speed_down = 0;
      lplayer_direction =0; 
         
      if (random (5) > 4.995)	// пуляем супер способность
      	{
      		my.frame = 10;
      		snd_play(hit1_snd,100,0);
      		wait(-0.2);	
      		my.frame = 11;
      		wait(-0.2);
      		my.frame = 12;
      		ent_create("hook2.dds",my.x,ABoss2SuperPower);
      		wait(-0.1);
      		my.frame = 1;
      		wait(-0.1);
      		my.frame = 2;
      	}
      	
      	if (random (5) < 0.005)	// пуляем супер способность
      	{
      		my.frame = 13;
      		snd_play(hit2_snd,100,0);
      		wait(-0.2);	
      		my.frame = 14;
      		wait(-0.2);
      		my.frame = 15;
      		ent_create("hook1.dds",my.x,ABoss1SuperPower);
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
      			my.frame = 16;	
      			my.skill5=my.skill5-0.5; //получение урона
      			snd_play(hit_snd,100,0);
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
         
       c_move(me,vector(0,(my.skill4/8)*dist_ahead,0),vector(0,0,-dist_down),IGNORE_PASSABLE | IGNORE_SPRITES | GLIDE); // move the player

	wait(1);	
	}
	reset(panel_boss,SHOW);	
	set(panel_dialog,SHOW);
	set(panel_dialog_boss3_1,SHOW);
	FPlayerCanMove = 0;
	player.z=my.z;
	while(key_enter==false){
			LAnimPercent=LAnimPercent+1*time_step;
			if (LAnimPercent>20){LAnimPercent=0;}
			my.frame = 1;
			if (LAnimPercent>10){my.frame = 2;}
			wait(1);
		}
		reset(panel_dialog,SHOW);
	reset(panel_dialog_boss3_1,SHOW);
		my.frame = 17;	
	FPlayerCanMove = 0;
	FPlayerPickupCount = FPlayerPickupCount+boss_coins;
	while(player.x<6908)
	{
		FCutScene=1;
		player.x=player.x+8*time_step;
		wait(1);
	}	media_stop(FMusic);
	player.z=player.z-80;
	FCutScene=2;
	wait(-1);
	set(panel_dialog,SHOW);
	set(panel_dialog_boss3_end,SHOW);
	wait(-2);
	reset(panel_dialog,SHOW);
	reset(panel_dialog_boss3_end,SHOW);	
	wait(-1);	
	player.x=player.x+50;
	snd_play(fall_snd,100,0);
	FCutScene=4;	
			panel_black.alpha = 0;
	var i=50;
	while (i>1)
	{
	while (panel_black.alpha <100)
	{
			player.z=player.z-10;
		panel_black.alpha += 8*time_step; 
		if (i>1)
		media_tune(FMusic,i,0,0);
		i=i-0.2;
		wait(2);
	}
	panel_black.alpha = 100;
		
	}
	
	FLoadLevel4();
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
      if (c_trace(my.x,vector(my.x,my.y,my.z-5000),IGNORE_ME | IGNORE_SPRITES | IGNORE_PASSABLE | USE_BOX) > 0)
         dist_down = my.z + vFeet.z - target.z; // get distance between player's feet and the ground
      else
         dist_down = -1;
		
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
      		if (FPlayerAttack>50){my.skill5=0;snd_play(hit_snd,100,0);}
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
         
       c_move(me,vector(0,(my.skill4/8)*dist_ahead,0),vector(0,0,-dist_down),IGNORE_PASSABLE | IGNORE_SPRITES | GLIDE); // move the player
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
         
      if (FPlayerAttack==0 && key_space){FPlayerAttack=1; snd_play(miss_snd,100,0);}
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
		my.y=player.y-30;
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
			if (FCutScene==4){my.frame=12;}
			if (FCutScene==5){my.frame=18;my.pan=90;}
			if (FCutScene==6){my.frame=19;my.pan=90;}
			if (FCutScene==7){my.frame=20;my.pan=90;}
      wait(1);
	}
	my.frame=12;
	wait(-2);
	
	
}



function FLoadLevel1()
{
	FBarGirl=1;
	GameProgress=1;
	FCutScene=0;
	FPlayerCanMove = 1;
	media_stop(FMusic);
		level_load("lvl1.wmb");
	//	ent_sky = ent_createlayer("spacecube1+6.bmp", SKY | CUBE, 1);  
		camera.arc=20;
		FMusic =	media_play("megadeth-hangar_18.mid",NULL,50);
		
			media_tune(FMusic,1,0,0);
	panel_black.alpha = 100;
		var i=1;
		wait(-2);
		FCheckPlayer();
	{
	while (panel_black.alpha >1)
	{
		panel_black.alpha -= 8*time_step; 
		if (i<=50)
		media_tune(FMusic,i,0,0);
	   i=i+0.2;
		wait(2);
	}
	panel_black.alpha = 0;
		media_tune(FMusic,50,0,0);	
	}
	
		set(panel_hud, SHOW);
	
			while (FCutScene==0)
	{
		FCheckPlayer();
		wait(1);
	}	
}

function FLoadInto()
{
	set(panel_black, SHOW);
level_load("intro.wmb");
camera.arc= 60;
wait(-1);
	panel_black.alpha = 100;
		var i=1;
	
	{
	while (panel_black.alpha >1)
	{
		panel_black.alpha -= 8*time_step; 
		if (i<=50)
	   i=i+0.2;
		wait(2);
	}
	panel_black.alpha = 0;
	}
	
	set(panel_dialog,SHOW);
	set(panel_dialog_intro1,SHOW);
	wait(-4);
	reset(panel_dialog,SHOW);
	reset(panel_dialog_intro1,SHOW);
	wait(-1);
	set(panel_dialog,SHOW);
	set(panel_dialog_intro2,SHOW);
	wait(-4);
	reset(panel_dialog,SHOW);
	reset(panel_dialog_intro2,SHOW);
	wait(-1);
	set(panel_dialog,SHOW);
	set(panel_dialog_intro3,SHOW);
	wait(-4);
	reset(panel_dialog,SHOW);
	reset(panel_dialog_intro3,SHOW);
	wait(-1);
	
		panel_black.alpha = 0;
	var i=50;
	while (i>1)
	{
	while (panel_black.alpha <100)
	{
		panel_black.alpha += 8*time_step; 
		if (i>1)
		media_tune(FMusic,i,0,0);
		i=i-0.2;
		wait(2);
	}
	panel_black.alpha = 100;
		
	}
	
	FLoadLevel1();
}



function FContinueGame()
{
	if (GameProgress==0)
	{
		FLoadInto();
	}
	if (GameProgress==1)
	{
		FLoadLevel1();
	}
		if (GameProgress==2)
	{
		FLoadLevel2();
	}
		if (GameProgress==3)
	{
		FLoadLevel3();
	}
		if (GameProgress==4)
	{
		FLoadLevel4();
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
//FLoadLevel4();	
	wait(-1);	
	sky_color.red = 0;
sky_color.green = 0;
sky_color.blue = 0; // bright blue sky   
	
	
}