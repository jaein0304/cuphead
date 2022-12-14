#pragma once

enum  OBJID {
	//OBJ_MONSTER, 
	OBJ_MONSTER_ONION, OBJ_MONSTER_POTATO, OBJ_MONSTER_CARROT, OBJ_MONSTER_DOMINO, OBJ_MONSTER_ROULETTE, OBJ_MONSTER_CASINO,
	OBJ_ELDERKETTLE, OBJ_KINGDICE, OBJ_CASINOKING,
	OBJ_TILE, 
	OBJ_BULLET, OBJ_SUPERBULLET, OBJ_FOLLOWBULLET, OBJ_EFFECT,
	OBJ_POTATOBULLET, OBJ_ONIONBULLET, OBJ_CARROTBULLET1, OBJ_CARROTBULLET2, OBJ_DOMINOBULLET1, OBJ_DOMINOBULLET2, OBJ_DOMINOBULLET3, OBJ_DOMINOBULLET4,
	OBJ_CUBE, OBJ_RECTANGLE, OBJ_EXIT, OBJ_TARGET,
	OBJ_PLAYER,
	OBJ_ITEM, OBJ_BLOCK,  OBJ_UI, OBJ_END };

enum SCENEID { SC_TITLE, SC_MENU, SC_ELDERHOUSE, SC_TUTORIAL, SC_ROOTSTAGE, SC_ROOTSTAGE2, SC_ROOTSTAGE3, SC_DICEHOUSE, SC_DOMINOSTAGE, SC_EDIT,SC_FINALSTAGE, SC_STAGEEND, SC_END };

//enum MONSTERTYPE { MT_POTATO, MT_ONION, MT_CARROT, MT_DOMINO, MT_ROULETTE, MT_END};

enum MONSTERPATTERN { POTATO_MOVE, POTATO_SHOOT, POTATO_END2 }; //x

enum TILETYPE { GREEN, RED, PURPLE, PEBBLE, BLUE, VIOLET, TILE_END };

enum PLAYERSTATE {
	IDLE, LIDLE,
	LRUN, RRUN,
	LJUMP, RJUMP,
	RDASH, LDASH,
	AIMUP,
	LDUCKIDLE, RDUCKIDLE,
	LDUCKSHOOT, RDUCKSHOOT,
	LSHOOT, RSHOOT, UPSHOOT, RSPECIALSHOOT, LSPECIALSHOOT,
	HIT, DEAD, END
};

//0312
enum MONSTERSTATE {
	Intro,
	Idle,
	BeforeAttack,
	ToAttack,
	Beam,
	FromAttack,
	Attack,
	Death,
	End
};

enum BULLETSTATE { BT_START, BT_LEFT, BT_RIGHT, BT_UP, BT_DOWN, BT_RU, BT_LU, BT_DEAD };

enum SPECIALBULLETSTATE { SBT_LEFT, SBT_RIGHT, SBT_UP, SBT_DEAD };

enum BULLETTYPE { BULLET_BASE, BULLET_FOLLOW, BULLET_END };

enum BULLETTYPE_MONSTER { 
	BULLET_MONSTER_BASIC,
	BULLET_MONSTER_CRYING, 
	BULLET_MONSTER_CARROTBOMB,
	BULLET_MONSTER_FOLLOW, 
	BULLET_MONSTER_GEM,
	BULLET_MONSTER_BIRD,
	BULLET_MONSTER_THORN,
	BULLET_MONSTER_END 
};

enum DIRECTION { DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_END };

enum RENDERID { RENDER_BACK, RENDER_GAMEOBJECT, RENDER_UI, RENDER_END };

enum ITEMTYPE { ITEM_1, ITEM_END };

enum CHANNELID { SOUND_EFFECT,
	SOUND_BGM, SOUND_ELDERBGM, SOUND_TUTORIALBGM, SOUND_ROOTBGM, SOUND_DICEBGM, SOUND_DOMINOBGM, SOUND_FINALBGM,
	SOUND_POTATOATTACK, SOUND_POTATODIE,
	SOUND_ONIONATTACK, SOUND_ONIONDIE,
	SOUND_CARROTATTACK1, SOUND_CARROTATTACK2, SOUND_CARROTDIE,
	SOUND_PLAYER, SOUND_MONSTER, MAXCHANNEL };

//enum BACKSOUNDID { SOUND_ELDER, SOUND_ROOT, SOUND_DICE, SOUND_DOMINO, SOUND_END };