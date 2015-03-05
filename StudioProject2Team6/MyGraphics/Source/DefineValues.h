#define _DEFINE_VALUES_H

/*=======================================
		Supermarket bounds values
=======================================*/
static float boundX1 =-41.5f;
static float boundX2 = -39.5f;
static float boundX3 =-37.5f;
static float boundX4 = 42.5f;
static float boundX5 = 14.0f;
static float boundX6 = -27.0f;
static float boundX7 = 40.5f;
static float boundX8 = 38.5f;
static float boundX9 = 28.5f;
static float boundX10 = -12.0f;
static float boundZ1 = -31.5f;
static float boundZ2 = 32.5f;
static float boundZ3 = -29.5f;
static float boundZ4 = 30.5f;
static float boundZ5 = 28.5f;
static float boundZ6 = -27.5f;
/*=======================================
		Freezer bounds values
=======================================*/
static float FboundX1 = 34.0f;
static float FboundX2 = 40.0f;
static float FboundX3 = 36.0f;
static float FboundZ1 = 2.0f;
static float FboundZ2 = 30.0f;
static float FboundZ3 = 4.0f;
/*=======================================
		Shelf bounds values
=======================================*/
static float ShelfWidthX = 6.5f;
static float ShelfWidthZ = 2.0f;
/*=======================================
		Cashier table bounds values
=======================================*/
static float CboundX1 = -3.5f;
static float CboundX2 = -1.5f;
static float CboundX3 = -9.0f;
static float CboundX4 = -7.0f;
static float CboundX5 = -13.5f;
static float CboundX6 = -11.5f;
static float CboundX7 = -20.0f;
static float CboundX8 = -18.0f;
static float CboundX9 = -23.5f;
static float CboundX10 = -21.5f;
static float CboundX11 = -31.0f;
static float CboundX12 = -29.0f;
static float CboundZ1 = -25.0f;
static float CboundZ2 = -12.0f;
static float CboundZ3 = -14.0f;
static float CboundZ4 = -23.0f;
static float CboundZ5 = -29.0f;
/*=======================================
		Elevator bounds values
=======================================*/
static float EboundX1 = -32.0f;
static float EboundX2 = -31.0f;
static float EboundX3 = -29.0f;
static float EboundZ1 = -28.5f;
static float EboundZ2 = -13.0f;
static float EboundZ3 = -21.0f;
/*=======================================
		Ghost man values
=======================================*/
static float GhostNpcInitLeg = 180.0f;
static float GhostNpcInitRot = 180.0f;
static float GhostNpcResetYPos = -2.0f;
static float GhostNpcAppearBoundX1 = -30.0f;
static float GhostNpcAppearBoundX2 = -10.0f;
static float GhostNpcAppearBoundZ1 = 45.0f;
static float GhostNpcAppearBoundZ2 = 15.0f;
static float GhostNpcAppearBoundZ3 = 30.0f;
static float GhostNpcMoveBoundX1 = -7.0f;
static float GhostNpcMoveBoundX2 = -35.0f;
static float GhostNpcMoveBoundY1 = 8.0f;
static float GhostNpcMoveBoundY2 = -2.0f;
/*=======================================
		Walking man values
=======================================*/
static float WalkingNpcInitArm = 20.0f;
//Looking man npc
static float NPCLookLimiter = 10.0f;

//Leg Animation
static float spdMod = 13.0f;
static float maxlegRot = 35.0f;

//Collision offset
static float Coffset = 2.0f;

//Easteregg gamemode
const int numEastereggs = 5;

//Winning easter egg message
const std::string winEasterArray[10] = {"Y","o","u"," ","f","o","u","n","d"," "};
const std::string winEasterArray1[10] = {"a","l","l"," ","t","h","e"," ","e","a"};
const std::string winEasterArray2[10] = {"s","t","e","r"," ","e","g","g","s","!"};

//Gaben
static bool gabed = false;
static int summonG = 0;
static float moveG = 0.0f;

//troll
static bool reversed = false;
static float reverseTimer = 0.0f;
static float reverseLimiter = 5.0f;

//World size for skybox
static float world_size = 3000.0f;

//Interaction distance checks
static float interactionDistance = 3.5f;
static float interactionDistanceFirstFloorY = 3.0f;

//Item XYZ offset
static float itemXoffset = 0.0f;
static float itemYoffset = -1.0f;
static float itemZoffset = 0.0f;

//Render item X position offset
static float RenderItemTopRowXOffSet = 2.0f;
static float RenderItemMiddleRowXOffSet = 2.0f;
static float RenderItemBottomRowXOffSet = 2.0f;

//Render item Y position offset
static float RenderItemTopRowYOffSet = 5.05f;
static float RenderItemMiddleRowYOffSet = 2.95f;
static float RenderItemBottomRowYOffSet = 1.4f;

//Render Elevator Lift position
static float RenderElevatorPosX = -35.f;
static float RenderElevatorPosZ = -25.f;
static float ElevatorDoorPosX = 0.0f;
static float ElevatorDoorPosZ = 3.45f;

//Bound checking for opening lift doors
static float checkElevatorXposMin = -38.f;
static float checkElevatorXposMax = -31.f;
static float checkElevatorZposMin = -28.5f;
static float checkElevatorZposMax = -5.f;
static float checkElevatorYposMin = 0.f;
static float checkElevatorYposMax = 10.f;

//Inner bound checking for Elevator
static float checkInnerElevatorXposMin = -39.f;
static float checkInnerElevatorXposMax = -32.f;
static float checkInnerElevatorZposMin = -29.f;
static float checkInnerElevatorZposMax = -23.f;


static float secondFloorYpositionMax = 17.f;
static float secondFloorYpositionMin = 0.0f;

static float elevatorSpeed = 5.0f;

//Bound checking for RETURN POINT
static float returnPointBoxPosX = -37.f;
static float returnPointBoxPosY = 0.f;
static float returnPointBoxPosZ = 0.f;
//Width, Length, Height for RETURN POINT
static float returnPointBoxWidth = 4.0f; //Use this for collision?
static float returnPointBoxLength = 4.0f;//Use this for collision?
static float returnPointBoxHeight = 4.0f;//Use this for collision?
static float returnPointBoxWidthOffset = 2.f;
static float returnPointBoxInteractionLength = 7.5f;
static float returnPointBoxInteractionWidth = 4.0f;
static float returnPointBoxInteractionHeight = 7.0f;

//Timer limiters
static float interactionTimerLimiter = 0.5f;
static float menuTImerLimiter = 0.2f;

//Tug of war limiter
static float TugofwarTimerLimiter = 0.3f;

//Item rotation speed
static float itemRotationSpeedMultiplyer =60.f;
static CItem* ptrEmpty = new CEmptyItem;

//Punch limiter
static bool PunchTimerLimiter = true;

//Menu string text
static std::string menuTextArray[8] = {"START","Instructions","Exit","Free Roam","Treasure Hunt","Easter Egg Hunt","Resume game","Back to main menu"};
static std::string s_UI_Play_Mode[3] = {"Free Roam","Treasure Hunt", "Easter Egg Hunt"};
static std::string backgroundSound = "Sound\\Carefree.ogg";
static std::string ambientSound = "Sound\\ambient.ogg";
static std::string clearText = "CLEAR!";

//Sounds
const std::string soundFXArray[9] = {"Sound/holy.ogg","Sound/time.ogg","Sound/jaws.ogg","Sound/troll.ogg","Sound/rick.ogg",
									"Sound/sonic.ogg","Sound/ding.ogg","Sound/door.ogg","Sound/eat.ogg"};
const float soundLimiter = 3.0f;

//reset value
const float resetValue = 0.0f;
const int resetIntValue = 0;
