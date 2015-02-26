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
static float SboundX1 = -2.0f;
static float SboundX2 = 30.0f;
static float SboundX3 = 0.0f;
static float SboundX4 = 28.0f;
static float SboundX5 = 26.0f;
static float SboundZ1 = 26.0f;
static float SboundZ2 = 27.0f;
static float SboundZ3 = 30.0f;
static float SboundZ4 = 13.0f;
static float SboundZ5 = 15.0f;
static float SboundZ6 = 19.0f;
static float SboundZ7 = 21.0f;
static float SboundZ8 = 18.9f;
static float SboundZ9 = 1.0f;
static float SboundZ10 = 3.0f;
static float SboundZ11 = 7.0f;
static float SboundZ12 = 9.0f;
static float SboundZ13 = 6.9f;
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
//World size for skybox
static float world_size = 3000.0f;

//Interaction distance checks
static float interactionDistanceZ = 4.0f;
static float interactionDistanceX = 1.0f;
static float interactionDistanceYMax = 4.7f;
static float interactionDistanceYMin = 4.0f;


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
//Punch limiter
static bool PunchTimerLimiter = true;

//Menu string text
static std::string menuTextArray[6] = {"START","Credits","Exit","Free Roam","Treasure Hunt","Easter Egg Hunt"};