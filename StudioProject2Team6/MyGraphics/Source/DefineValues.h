/******************************************************************************/
/*!
\file	DefineValues.h
\author Edmund Ang , Jeffrey Teo, John Leong, Xue Tian
\brief
Header file for hardcoded variables
*/
/******************************************************************************/
#define _DEFINE_VALUES_H

/*=======================================
		Supermarket bounds values
=======================================*/
static float f_boundX1 =-41.5f;
static float f_boundX2 = -39.5f;
static float f_boundX3 =-37.5f;
static float f_boundX4 = 42.5f;
static float f_boundX5 = 14.0f;
static float f_boundX6 = -27.0f;
static float f_boundX7 = 40.5f;
static float f_boundX8 = 38.5f;
static float f_boundX9 = 28.5f;
static float f_boundX10 = -12.0f;
static float f_boundZ1 = -31.5f;
static float f_boundZ2 = 32.5f;
static float f_boundZ3 = -29.5f;
static float f_boundZ4 = 30.5f;
static float f_boundZ5 = 28.5f;
static float f_boundZ6 = -27.5f;
/*=======================================
		Shelf bounds values
=======================================*/
static float f_ShelfWidthX = 6.5f;
static float f_ShelfWidthZ = 2.0f;
/*=======================================
		Elevator bounds values
=======================================*/
static float f_EboundX1 = -32.0f;
static float f_EboundX2 = -31.0f;
static float f_EboundX3 = -29.0f;
static float f_EboundZ1 = -28.5f;
static float f_EboundZ2 = -13.0f;
static float f_EboundZ3 = -21.0f;
/*=======================================
		Ghost man values
=======================================*/
static float f_GhostNpcInitLeg = 180.0f;
static float f_GhostNpcInitRot = 180.0f;
static float f_GhostNpcResetYPos = -2.0f;
static float f_GhostNpcAppearBoundX1 = -30.0f;
static float f_GhostNpcAppearBoundX2 = -10.0f;
static float f_GhostNpcAppearBoundZ1 = 45.0f;
static float f_GhostNpcAppearBoundZ2 = 15.0f;
static float f_GhostNpcAppearBoundZ3 = 30.0f;
static float f_GhostNpcMoveBoundX1 = -7.0f;
static float f_GhostNpcMoveBoundX2 = -35.0f;
static float f_GhostNpcMoveBoundY1 = 8.0f;
static float f_GhostNpcMoveBoundY2 = -2.0f;
/*=======================================
		Walking man values
=======================================*/
static float f_WalkingNpcInitArm = 20.0f;
//Looking man npc
static float f_NPCLookLimiter = 10.0f;

//Leg Animation
static float f_spdMod = 13.0f;
static float f_maxlegRot = 35.0f;

//Collision offset
static float f_Coffset = 2.0f;

//Easteregg gamemode
const int i_numEastereggs = 5;

//Winning easter egg message
const std::string winEasterArray[10] = {"Y","o","u"," ","f","o","u","n","d"," "};
const std::string winEasterArray1[10] = {"a","l","l"," ","t","h","e"," ","e","a"};
const std::string winEasterArray2[10] = {"s","t","e","r"," ","e","g","g","s","!"};

//Gaben
static bool b_gabed = false;
static int i_summonG = 0;
static float f_moveG = 0.0f;

//troll
static bool b_reversed = false;
static float f_reverseTimer = 0.0f;
static float f_reverseLimiter = 5.0f;

//World size for skybox
static float f_world_size = 3000.0f;

//Interaction distance checks
static float f_interactionDistance = 3.5f;
static float f_interactionDistanceFirstFloorY = 3.0f;

//Item XYZ offset
static float f_itemXoffset = 0.0f;
static float f_itemYoffset = -1.0f;
static float f_itemZoffset = 0.0f;

//Render item X position offset
static float f_RenderItemTopRowXOffSet = 2.0f;
static float f_RenderItemMiddleRowXOffSet = 2.0f;
static float f_RenderItemBottomRowXOffSet = 2.0f;

//Render item Y position offset
static float f_RenderItemTopRowYOffSet = 5.05f;
static float f_RenderItemMiddleRowYOffSet = 2.95f;
static float f_RenderItemBottomRowYOffSet = 1.4f;

//Render Elevator Lift position
static float f_RenderElevatorPosX = -35.f;
static float f_RenderElevatorPosZ = -25.f;
static float f_ElevatorDoorPosX = 0.0f;
static float f_ElevatorDoorPosZ = 3.45f;

//Bound checking for opening lift doors
static float f_checkElevatorXposMin = -38.f;
static float f_checkElevatorXposMax = -31.f;
static float f_checkElevatorZposMin = -28.5f;
static float f_checkElevatorZposMax = -5.f;
static float f_checkElevatorYposMin = 0.f;
static float checkElevatorYposMax = 10.f;

//Inner bound checking for Elevator
static float f_checkInnerElevatorXposMin = -39.f;
static float f_checkInnerElevatorXposMax = -32.f;
static float f_checkInnerElevatorZposMin = -29.f;
static float f_checkInnerElevatorZposMax = -23.f;


static float f_secondFloorYpositionMax = 17.f;
static float f_secondFloorYpositionMin = 0.0f;

const static float f_elevatorSpeed = 5.0f;
const static float f_elevatorDoorSpeed = 15.0f;
//Bound checking for RETURN POINT
static float f_returnPointBoxPosX = -37.f;
static float f_returnPointBoxPosY = 0.f;
static float f_returnPointBoxPosZ = 0.f;
//Width, Length, Height for RETURN POINT
static float f_returnPointBoxWidth = 4.0f; //Use this for collision?
static float f_returnPointBoxLength = 4.0f;//Use this for collision?
static float f_returnPointBoxHeight = 4.0f;//Use this for collision?
static float f_returnPointBoxWidthOffset = 2.f;
static float f_returnPointBoxInteractionLength = 7.5f;
static float f_returnPointBoxInteractionWidth = 4.0f;
static float f_returnPointBoxInteractionHeight = 7.0f;

//Timer limiters
static float f_interactionTimerLimiter = 0.5f;
static float f_menuTImerLimiter = 0.2f;

//Tug of war limiter
static float f_TugofwarTimerLimiter = 0.3f;

//Item rotation speed
static float f_itemRotationSpeedMultiplyer =60.f;
static CItem* ptrEmpty = new CEmptyItem;

//Punch limiter
static bool b_PunchTimerLimiter = true;

//Menu string text
static std::string menuTextArray[8] = {"START","Instructions","Exit","Free Roam","Treasure Hunt","Easter Egg Hunt","Resume game","Back to main menu"};
static std::string s_UI_Play_Mode[3] = {"Free Roam","Treasure Hunt", "Easter Egg Hunt"};
static std::string backgroundSound = "Sound\\Carefree.ogg";
static std::string ambientSound = "Sound\\ambient.ogg";
static std::string clearText = "CLEAR!";

//Sounds
const std::string soundFXArray[9] = {"Sound/holy.ogg","Sound/time.ogg","Sound/jaws.ogg","Sound/troll.ogg","Sound/rick.ogg",
									"Sound/sonic.ogg","Sound/ding.ogg","Sound/door.ogg","Sound/eat.ogg"};
const float f_soundLimiter = 3.0f;

//reset value
const float f_resetValue = 0.0f;
const int f_resetIntValue = 0;
