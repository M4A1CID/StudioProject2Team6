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
static float GhostNpcMoveBoundX1 = -10.0f;
static float GhostNpcMoveBoundX2 = -30.0f;
static float GhostNpcMoveBoundY1 = 6.0f;
static float GhostNpcMoveBoundY2 = -2.0f;
static float GhostNpcMoveSpd = 4.0f;
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
static bool winEaster = false;
static bool closeEaster = false;
static bool inRange = false;
static float easterLimiter = 2.0f;
static float easterTimer = 2.0f;
static int getCounter = 0;
static bool getCaged = false;
static bool getGabed = false;
static bool getTrolled = false;
static bool getTimed = false;

//Cage
static bool caged = false;
static float cagedPos = -75.0f;
static float diffY = 0.0f;

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

static int i_total_items_to_find = 3;
static CItem* ptrEmpty = new CEmptyItem;

//Punch limiter
static bool PunchTimerLimiter = true;

//Menu string text
static std::string menuTextArray[7] = {"START","Credits","Exit","Free Roam","Treasure Hunt","Easter Egg Hunt","Back"};
static std::string s_UI_Play_Mode[3] = {"Free Roam","Treasure Hunt", "Easter Egg Hunt"};
static std::string backgroundSound = "Sound\\Carefree.ogg";
static std::string clearText = "CLEAR!";

//Sounds
static std::string gabenSound = "Sound/holy.ogg";
static std::string noTimeSound = "Sound/time.ogg";
static std::string jawsSound = "Sound/jaws.ogg";
static std::string trollSound = "Sound/troll.ogg";

//reset value
static float resetValue = 0.0f;
static int resetIntValue = 0;