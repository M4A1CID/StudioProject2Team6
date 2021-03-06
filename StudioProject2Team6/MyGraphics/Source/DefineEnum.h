/******************************************************************************/
/*!
\file	DefineEnum.h
\author Edmund Ang , Jeffrey Teo, John Leong, Xue Tian
\brief
Contains all enumeration 
*/
/******************************************************************************/

#ifndef _DEFINE_ENUM_H
#define _DEFINE_ENUM_H

enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_TEXT,	
		GEO_FRONT,
		GEO_BOTTOM,
		GEO_BACK,
		GEO_TOP,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_SUPERMARKET,
		GEO_STORAGEANDOFFICE,
		GEO_OFFICECOMPUTER,
		GEO_FERRIS,
		GEO_ATM,
		GEO_PANDACHEESE,
		GEO_BOX,
		GEO_TROLLEY,
		GEO_SHELF,
		GEO_CASHIER,
		GEO_DOOR,
		GEO_ICEBOX,
		GEO_MEATSHELF,
		GEO_FOODSHELF,
		GEO_SAMPLESTAND,
		GEO_CAN_SARDINE,
		GEO_CAN_PEAS,
		GEO_CAN_BROWN,
		GEO_CAN_TOMATO,
		GEO_CAN_BEANS,
		GEO_CAN_MELON,
		GEO_CAN_VARGA,
		//========New Can===========
		GEO_CAN_BRAN,
		GEO_CAN_SODA,
		GEO_CAN_GLUWATER,
		GEO_CAN_ROOTBEERFLOATS,
		GEO_CAN_MTNDEW,
		GEO_CAN_SODAFEST,
		GEO_CAN_REDMONSTER,
		GEO_CAN_HUMANS,
		GEO_CEREAL_1,
		GEO_CEREAL_2,
		GEO_CEREAL_3,
		GEO_CEREAL_4,
		GEO_CEREAL_5,
		GEO_EASTEREGG_1,
		GEO_EASTEREGG_2,
		GEO_EASTEREGG_3,
		GEO_EASTEREGG_4,
		GEO_EASTEREGG_5,
		GEO_EASTEREGG_6,
		GEO_WINEBOTTLE_1,
		GEO_WINEBOTTLE_2,
		GEO_WINEBOTTLE_3,
		GEO_WINEBOTTLE_4,
		GEO_WINEBOTTLE_5,
		GEO_CAGE,
		GEO_CAGEWALL,
		GEO_BUILDING,
		GEO_FENCE,
		GEO_ELEVATOR,
		GEO_ELEVATORDOOR,
		GEO_HANDS,
		GEO_UI_SCREEN,
		GEO_CASHIER_LEGANDFEET,
		GEO_CASHIER_HEADBODY,
		GEO_CASHIER_ARM,
		//////////////////////
		GEO_DRUNKMAN_LEGANDFEET,
		GEO_DRUNKMAN_HEADBODY,
		GEO_DRUNKMAN_ARM,
		///////////////////////////
		GEO_LOGISTICSTAFF_LEGANDFEET,
		GEO_LOGISTICSTAFF_HEADBODY,
		GEO_LOGISTICSTAFF_ARM,
		//////////////////////////////
		GEO_NormalNpc1_LEGANDFEET,
		GEO_NormalNpc1_HEADBODY,
		GEO_NormalNpc1_ARM,
		//////////////////////////////
		GEO_NormalNpc2_LEGANDFEET,
		GEO_NormalNpc2_HEADBODY,
		GEO_NormalNpc2_ARM,
		/*============================*/
		GEO_GHOSTNPC_LEGANDFEET,
		GEO_GHOSTNPC_HEADANDBODY,
		GEO_GHOSTNPC_ARM,
		GEO_ITEM_SELECT,
		GEO_MAIN_MENU_TITLE,
		GEO_GABEN,
		GEO_BALL,
		NUM_GEOMETRY,
	};
enum ROW_TYPE
{
	ROW_TOP,
	ROW_MIDDLE,
	ROW_BOTTOM,
	NUM_ROW,
};
enum UNIFORM_TYPE
{
	U_MVP = 0,
	U_MODELVIEW,
	U_MODELVIEW_INVERSE_TRANSPOSE,
	U_MATERIAL_AMBIENT,
	U_MATERIAL_DIFFUSE,
	U_MATERIAL_SPECULAR,
	U_MATERIAL_SHININESS,
	U_LIGHT0_POSITION,
	U_LIGHT0_TYPE,
	U_LIGHT0_COLOR,
	U_LIGHT0_POWER,
	U_LIGHT0_KC,
	U_LIGHT0_KL,
	U_LIGHT0_KQ,
	U_LIGHTENABLED,
	U_LIGHT0_SPOTDIRECTION,
	U_LIGHT0_COSCUTOFF,
	U_LIGHT0_COSINNER,
	U_LIGHT0_EXPONENT,

	U_LIGHT1_POSITION,
	U_LIGHT1_TYPE,
	U_LIGHT1_COLOR,
	U_LIGHT1_POWER,
	U_LIGHT1_KC,
	U_LIGHT1_KL,
	U_LIGHT1_KQ,
	U_LIGHT1_SPOTDIRECTION,
	U_LIGHT1_COSCUTOFF,
	U_LIGHT1_COSINNER,
	U_LIGHT1_EXPONENT,

	U_NUMLIGHTS,
	//add these enum in UNIFORM_TYPE before U_TOTAL
	U_COLOR_TEXTURE_ENABLED,
	U_COLOR_TEXTURE,
	U_TEXT_ENABLED,
	U_TEXT_COLOR,

	U_TOTAL,
};
enum CHARACTER_JOB
{
	DRUNKMAN,
	CASHIER,
	CUSTOMER,
	PART_TIME_WORKER,
	TUG_OF_WAR_GUY,
	WALKING_GUY,
	WALKING_GUY_OUTSIDE_Z,
	WALKING_GUY_OUTSIDE_X,
	LOOKING_GUY,
	GHOST_GUY,
	CHATTING_GUY,
	EASTER_EGG_GUY,
	IDLE_GUY,
	SHOPPERS,
	BUILDING_GUY,
	ROTATING_MAN,
	NUM_JOB,
};
enum CHARACTER_STATE
{
	STATE_IDLE,
	STATE_FORWARD,
	STATE_LEFT,
	STATE_BACKWARD,
	STATE_JUMP,
	STATE_ROTATE,
	STATE_ROTATE2,
	STATE_RIGHT,
	STATE_INTOBUILDING,
	STATE_ACTIVE,
	STATE_REACTIVATE,
	NUM_STATE,
};
enum ANIMATION_TYPE
{
	IDLE,
	WALKING,
	RUNNING,
};
enum PLAY_SCENARIO
{
	PLAY_FREE_ROAM,
	PLAY_TREASURE_HUNT,
	PLAY_EASTER_EGG,
	NUM_PLAY,
};
enum DRUNKAI_STATE
{
	DRUNKIDLE,
	DRUNKCARRY,
	DRUNKOUTSIDE,
	NUM_AI,
};
enum CASHIERAI_STATE
{
	LOOKATCUSTOMER,
	LOOKATSCREEN,
	LOOKATITEM,
	NUM_CAI,
};

enum GAME_STATE
{
	MAIN_MENU,
	SUB_MENU,
	INSTRUCTION_MENU,
	PAUSE_MENU,
	GAME_PLAYING,
	WIN_LOSE_MENU,
	NUM_MENU,
};
enum MENU_BUTTONS
{
	MENU_START,
	MENU_INSTRUCTIONS,
	MENU_EXIT,
	MENU_FREE_ROAM,
	MENU_TREASURE_HUNT,
	MENU_EASTER_EGG_HUNT,
	MENU_RESUME,
	MENU_BACK,
	NUM_BUTTON,
};

#endif