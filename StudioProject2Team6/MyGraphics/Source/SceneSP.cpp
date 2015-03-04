#include "SceneSP.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Vertex.h"
#include "LoadTGA.h"

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;
SceneSP::SceneSP()
{
}
SceneSP::~SceneSP()
{
}
void SceneSP::Init()
{
	DeclareGLEnable(); //Handle glEnable things

	//Initialize all meshes to NULL
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}

	/*===============================
			Music and Sound here
	==============================*/
	if(!music.openFromFile(backgroundSound))
	{
		std::cout << "ERROR OPENING MUSIC FILE" << std::endl;
	}
	music.setLoop(true);
	music.setVolume(50.0f);
	music.play();
	

	/*=============================================
	Init variables here
	=============================================*/
	i_menuHandle = MAIN_MENU;
	i_drunkmanAct = DRUNKIDLE;
	i_CashierAct = LOOKATCUSTOMER;
	initCharacter(); //Initilize the player
	//Initialize all Inventory to NULL
	ptrItem = new CEmptyItem;
	for(int i = 0; i< ptrplayer->getMaxItemCapacity();++i)
	{
		ptrplayer->setInventory(ptrItem);
	}
	ptrInvSelect = ptrplayer->getItem(0);
	initGeoType(); //Initilize all Geo Types
	initShelves();//Initilize all shelves
	falling = false;
	b_is_Stealing = false;
	b_crouching = false;
	toggleLight = true;
	toggleDoorFront = false;
	toggleDoorBack = false;
	elevatorDoorOpening = false;
	elevatorSecondFloor = false;
	b_inspection = false;
	b_isWithinPayingCashier = false;
	b_dinged = true;
	IsIntugofwar = false;
	win = false;
	lose = false;
	showTuginstruction = false;
	b_isWithinInteractionItem = false;
	interactionTimer = 0.0f;
	LogisticinteractionTimer = 0.0f;
	CustomerinteractionTimer = 0.0f;
	f_soundTimer = 0.0f;
	moveDoorFront = 0.0f;
	moveDoorBack = 0.0f;
	trolleyrotation = 0.0f;
	handrotationleftandright = 0.0f;
	handtranslation = 0.0f;
	diffX = 0.0f;
	diffZ = 0.0f;
	elevatorY = 0.f;
	elevatorDoorY = 0.f;
	itemYrotation = 0.f;
	itemXrotation = 0.f;
	elevatorIdle = true; // Set default elevator to IDLE
	charactersrotation = 20.0f;
	i_sampleItems = 4;
	inventoryPointing=0;
	selectionPointing = MENU_START;
	//Initialize camera settings
	camera.Init(Vector3(0, 4.5, 100), Vector3(0, 0, 0), Vector3(0, 1, 0));
	ATMMoney = 50.0f;

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 5000.f);
	projectionStack.LoadMatrix(projection);

	DeclareLightParameters(); //Declare Light parameters

	////////////////////////////////////////////
	Cashier.translateX = 0;
	Cashier.translateY = 0;
	Cashier.translateZ = 0;
	Cashier.rotateA = 0;
}
void SceneSP::initGeoType()
{
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16,16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//anime.tga");
	meshList[GEO_UI_SCREEN] = MeshBuilder::GenerateText("UI",1,1);
	meshList[GEO_UI_SCREEN]->textureID = LoadTGA("Image//UI.tga");
	meshList[GEO_ITEM_SELECT] = MeshBuilder::GenerateText("ItemSelection",1,1);
	meshList[GEO_ITEM_SELECT]->textureID = LoadTGA("Image//selectionHighlight.tga");
	meshList[GEO_SUPERMARKET] = MeshBuilder::GenerateOBJ("supermarket", "OBJ//supermarket.obj");
	meshList[GEO_SUPERMARKET]->textureID = LoadTGA("Image//supermarket.tga");
	meshList[GEO_STORAGEANDOFFICE] = MeshBuilder::GenerateOBJ("supermarket", "OBJ//PartofSuperMarket.obj");
	meshList[GEO_STORAGEANDOFFICE]->textureID = LoadTGA("Image//supermarket.tga");
	meshList[GEO_DOOR] = MeshBuilder::GenerateOBJ("door", "OBJ//door.obj");
	meshList[GEO_DOOR]->textureID = LoadTGA("Image//UI.tga");
	meshList[GEO_TROLLEY] = MeshBuilder::GenerateOBJ("trolley", "OBJ//trolley.obj");
	meshList[GEO_TROLLEY]->textureID = LoadTGA("Image//trolley.tga");
	meshList[GEO_SAMPLESTAND] = MeshBuilder::GenerateOBJ("samplestand", "OBJ//sample_stand.obj");
	meshList[GEO_SAMPLESTAND]->textureID = LoadTGA("Image//sample_stand.tga");
	meshList[GEO_ICEBOX] = MeshBuilder::GenerateOBJ("Icebox", "OBJ//Container.obj");
	meshList[GEO_ICEBOX]->textureID = LoadTGA("Image//ContainerTexture.tga");
	meshList[GEO_MEATSHELF] = MeshBuilder::GenerateOBJ("meatshelf", "OBJ//meatshelf.obj");
	meshList[GEO_MEATSHELF]->textureID = LoadTGA("Image//Meatshelf.tga");
	meshList[GEO_FOODSHELF] = MeshBuilder::GenerateOBJ("foodshelf", "OBJ//FoodShelf.obj");
	meshList[GEO_FOODSHELF]->textureID = LoadTGA("Image//Foodshelf.tga");
	meshList[GEO_SHELF] = MeshBuilder::GenerateOBJ("shelf", "OBJ//shelf.obj");
	meshList[GEO_SHELF]->textureID = LoadTGA("Image//Shelves.tga");
	meshList[GEO_CASHIER] = MeshBuilder::GenerateOBJ("cashier", "OBJ//cashiertable.obj");
	meshList[GEO_CASHIER]->textureID = LoadTGA("Image//cashRegisterTexture.tga");
	meshList[GEO_FENCE] = MeshBuilder::GenerateOBJ("fence", "OBJ//Fence.obj");
	meshList[GEO_FENCE]->textureID = LoadTGA("Image//Fence.tga");
	meshList[GEO_ELEVATOR] = MeshBuilder::GenerateOBJ("elevator", "OBJ//Elevator.obj");
	meshList[GEO_ELEVATOR]->textureID = LoadTGA("Image//Elevator.tga");
	meshList[GEO_ELEVATORDOOR] = MeshBuilder::GenerateOBJ("elevatordoor", "OBJ//Elevatordoor.obj");
	meshList[GEO_ELEVATORDOOR]->textureID = LoadTGA("Image//UI.tga");
	meshList[GEO_HANDS] = MeshBuilder::GenerateOBJ("playerhand", "OBJ//playerArm.obj");
	meshList[GEO_HANDS]->textureID = LoadTGA("Image//cashier.tga");
	meshList[GEO_MAIN_MENU_TITLE] = MeshBuilder::GenerateText("MenuSupermarket",1,1);
	meshList[GEO_MAIN_MENU_TITLE]->textureID = LoadTGA("Image//Menu_Supermarket.tga");
	meshList[GEO_BOX] = MeshBuilder::GenerateOBJ("box", "OBJ//box.obj");
	meshList[GEO_BOX]->textureID = LoadTGA("Image//box.tga");
	meshList[GEO_OFFICECOMPUTER] = MeshBuilder::GenerateOBJ("office computer", "OBJ//office.obj");
	meshList[GEO_OFFICECOMPUTER]->textureID = LoadTGA("Image//Office.tga");
	meshList[GEO_BUILDING] = MeshBuilder::GenerateOBJ("building", "OBJ//Building.obj");
	meshList[GEO_BUILDING]->textureID = LoadTGA("Image//Building.tga");
	meshList[GEO_CAGE] = MeshBuilder::GenerateQuad("cage", Color(1, 1, 1), 1.0f);
	meshList[GEO_CAGE]->textureID = LoadTGA("Image//TheCage.tga");
	meshList[GEO_CAGEWALL] = MeshBuilder::GenerateQuad("cage", Color(0, 0, 0), 1.0f);
	meshList[GEO_CAGEWALL]->textureID = LoadTGA("Image//TheCage.tga");
	meshList[GEO_GABEN] = MeshBuilder::GenerateText("gaben",1,1);
	meshList[GEO_GABEN]->textureID = LoadTGA("Image//AllHailGabe.tga");//GEO_FERRIS
	meshList[GEO_FERRIS] = MeshBuilder::GenerateOBJ("Ferris wheel", "OBJ//FerrisWheel.obj");
	meshList[GEO_FERRIS]->textureID = LoadTGA("Image//FerrisWheel.tga");
	meshList[GEO_ATM] = MeshBuilder::GenerateOBJ("ATM", "OBJ//atm.obj");
    meshList[GEO_ATM]->textureID = LoadTGA("Image//atm.tga");
	/*=============================
	Init all food items
	==============================*/
	meshList[GEO_CAN_SARDINE] = MeshBuilder::GenerateOBJ("sardineCan","OBJ//canned_food_1.obj");
	meshList[GEO_CAN_SARDINE]->textureID = LoadTGA("Image//canned_food_1.tga");
	meshList[GEO_CAN_PEAS] = MeshBuilder::GenerateOBJ("peasCan","OBJ//canned_food_2.obj");
	meshList[GEO_CAN_PEAS]->textureID = LoadTGA("Image//canned_food_2.tga");
	meshList[GEO_CAN_BROWN] = MeshBuilder::GenerateOBJ("brownCan","OBJ//canned_food_3.obj");
	meshList[GEO_CAN_BROWN]->textureID = LoadTGA("Image//canned_food_3.tga");
	meshList[GEO_CAN_TOMATO] = MeshBuilder::GenerateOBJ("tomatoCan","OBJ//canned_food_4.obj");
	meshList[GEO_CAN_TOMATO]->textureID = LoadTGA("Image//canned_food_4.tga");
	meshList[GEO_CAN_BEANS] = MeshBuilder::GenerateOBJ("beansCan","OBJ//canned_food_5.obj");
	meshList[GEO_CAN_BEANS]->textureID = LoadTGA("Image//canned_food_5.tga");
	meshList[GEO_CAN_MELON] = MeshBuilder::GenerateOBJ("melonCan","OBJ//canned_food_6.obj");
	meshList[GEO_CAN_MELON]->textureID = LoadTGA("Image//canned_food_6.tga");
	meshList[GEO_CAN_VARGA] = MeshBuilder::GenerateOBJ("vargaCan","OBJ//canned_food_7&8.obj");
	meshList[GEO_CAN_VARGA]->textureID = LoadTGA("Image//canned_food_7.tga");
	meshList[GEO_CAN_BRAN] = MeshBuilder::GenerateOBJ("branCan","OBJ//canned_food_7&8.obj");
	meshList[GEO_CAN_BRAN]->textureID = LoadTGA("Image//canned_food_8.tga");
	meshList[GEO_CAN_SODA] = MeshBuilder::GenerateOBJ("sodaCan","OBJ//canned_food_9.obj");
	meshList[GEO_CAN_SODA]->textureID = LoadTGA("Image//canned_food_9.tga");
	meshList[GEO_CAN_MTNDEW] = MeshBuilder::GenerateOBJ("mtndewCan","OBJ//canned_food_10.obj");
	meshList[GEO_CAN_MTNDEW]->textureID = LoadTGA("Image//canned_food_10.tga");
	meshList[GEO_CAN_GLUWATER] = MeshBuilder::GenerateOBJ("gluwaterCan","OBJ//canned_food_11.obj");
	meshList[GEO_CAN_GLUWATER]->textureID = LoadTGA("Image//canned_food_11.tga");
	meshList[GEO_CAN_ROOTBEERFLOATS] = MeshBuilder::GenerateOBJ("rootbeerfloatCan","OBJ//canned_food_12.obj");
	meshList[GEO_CAN_ROOTBEERFLOATS]->textureID = LoadTGA("Image//canned_food_12.tga");
	meshList[GEO_CAN_SODAFEST] = MeshBuilder::GenerateOBJ("sodafestCan","OBJ//canned_food_13.obj");
	meshList[GEO_CAN_SODAFEST]->textureID = LoadTGA("Image//canned_food_13.tga");
	meshList[GEO_CAN_REDMONSTER] = MeshBuilder::GenerateOBJ("redmonsterCan","OBJ//canned_food_14.obj");
	meshList[GEO_CAN_REDMONSTER]->textureID = LoadTGA("Image//canned_food_14.tga");
	meshList[GEO_CAN_HUMANS] = MeshBuilder::GenerateOBJ("humanCan","OBJ//canned_food_15.obj");
	meshList[GEO_CAN_HUMANS]->textureID = LoadTGA("Image//canned_food_15.tga");
	/*-----Add canned food here-----*/
	meshList[GEO_CEREAL_1] = MeshBuilder::GenerateOBJ("cerealBox1","OBJ//cereal_box_1.obj");
	meshList[GEO_CEREAL_1]->textureID = LoadTGA("Image//cereal_box_1.tga");
	meshList[GEO_CEREAL_2] = MeshBuilder::GenerateOBJ("cerealBox2","OBJ//cereal_box_2.obj");
	meshList[GEO_CEREAL_2]->textureID = LoadTGA("Image//cereal_box_2.tga");
	meshList[GEO_CEREAL_3] = MeshBuilder::GenerateOBJ("cerealBox3","OBJ//cereal_box_3.obj");
	meshList[GEO_CEREAL_3]->textureID = LoadTGA("Image//cereal_box_3.tga");
	meshList[GEO_CEREAL_4] = MeshBuilder::GenerateOBJ("cerealBox4","OBJ//cereal_box_4.obj");
	meshList[GEO_CEREAL_4]->textureID = LoadTGA("Image//cereal_box_4.tga");
	meshList[GEO_CEREAL_5] = MeshBuilder::GenerateOBJ("cerealBox5","OBJ//cereal_box_5.obj");
	meshList[GEO_CEREAL_5]->textureID = LoadTGA("Image//cereal_box_5.tga");
	/*========================
	WINEBOTTLE INIT
	=========================*/
	meshList[GEO_WINEBOTTLE_1] = MeshBuilder::GenerateOBJ("WINEBOTTLE1","OBJ//winebottle_1.obj");
	meshList[GEO_WINEBOTTLE_1]->textureID = LoadTGA("Image//Wine_1.tga");
	meshList[GEO_WINEBOTTLE_2] = MeshBuilder::GenerateOBJ("WINEBOTTLE2","OBJ//winebottle_2.obj");
	meshList[GEO_WINEBOTTLE_2]->textureID = LoadTGA("Image/Wine_2.tga");
	meshList[GEO_WINEBOTTLE_3] = MeshBuilder::GenerateOBJ("WINEBOTTLE3","OBJ//winebottle_3.obj");
	meshList[GEO_WINEBOTTLE_3]->textureID = LoadTGA("Image//Wine_3.tga");
	meshList[GEO_WINEBOTTLE_4] = MeshBuilder::GenerateOBJ("WINEBOTTLE4","OBJ//winebottle_4.obj");
	meshList[GEO_WINEBOTTLE_4]->textureID = LoadTGA("Image//Wine_4.tga");
	meshList[GEO_WINEBOTTLE_5] = MeshBuilder::GenerateOBJ("WINEBOTTLE5","OBJ//winebottle_5.obj");
	meshList[GEO_WINEBOTTLE_5]->textureID = LoadTGA("Image//Wine_5.tga");
	/*========================
	EASTER EGG INIT
	=========================*/
	meshList[GEO_EASTEREGG_1] = MeshBuilder::GenerateOBJ("easterEgg1","OBJ//EasterEgg1.obj");
	meshList[GEO_EASTEREGG_1]->textureID = LoadTGA("Image//EasterEgg1.tga");
	meshList[GEO_EASTEREGG_2] = MeshBuilder::GenerateOBJ("easterEgg2","OBJ//EasterEgg2.obj");
	meshList[GEO_EASTEREGG_2]->textureID = LoadTGA("Image//EasterEgg2.tga");
	meshList[GEO_EASTEREGG_3] = MeshBuilder::GenerateOBJ("easterEgg3","OBJ//EasterEgg3.obj");
	meshList[GEO_EASTEREGG_3]->textureID = LoadTGA("Image//EasterEgg3.tga");
	meshList[GEO_EASTEREGG_4] = MeshBuilder::GenerateOBJ("No time","OBJ//EasterEgg4,5,6.obj");
	meshList[GEO_EASTEREGG_4]->textureID = LoadTGA("Image//EasterEgg4.tga");
	meshList[GEO_EASTEREGG_5] = MeshBuilder::GenerateOBJ("easterEgg5","OBJ//EasterEgg4,5,6.obj");
	meshList[GEO_EASTEREGG_5]->textureID = LoadTGA("Image//EasterEgg5.tga");
	meshList[GEO_EASTEREGG_6] = MeshBuilder::GenerateOBJ("Nic Cage","OBJ//EasterEgg4,5,6.obj");
	meshList[GEO_EASTEREGG_6]->textureID = LoadTGA("Image//EasterEgg6.tga");
	/*========================
	SKYBOX INIT
	=========================*/
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f,true);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//skybox_bottom.tga",true);
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");
	meshList[GEO_CASHIER] = MeshBuilder::GenerateOBJ("cashier", "OBJ//cashiertable.obj");
	meshList[GEO_CASHIER]->textureID = LoadTGA("Image//cashRegisterTexture.tga");
	/////////////////////////////////////////////////////////////////////
	meshList[GEO_CASHIER_ARM] = MeshBuilder::GenerateOBJ("cashier arm", "OBJ//Arm.obj");
	meshList[GEO_CASHIER_ARM]->textureID = LoadTGA("Image//cashier.tga");
	meshList[GEO_CASHIER_HEADBODY] = MeshBuilder::GenerateOBJ("cashier head and body", "OBJ//headandbody.obj");
	meshList[GEO_CASHIER_HEADBODY]->textureID = LoadTGA("Image//cashier.tga");
	meshList[GEO_CASHIER_LEGANDFEET] = MeshBuilder::GenerateOBJ("cashier head and body", "OBJ//legandfeet.obj");
	meshList[GEO_CASHIER_LEGANDFEET]->textureID = LoadTGA("Image//cashier.tga");
	/////////////////////////////////////////////////////////////////////
	meshList[GEO_DRUNKMAN_ARM] = MeshBuilder::GenerateOBJ("drunkman arm", "OBJ//Arm.obj");
	meshList[GEO_DRUNKMAN_ARM]->textureID = LoadTGA("Image//Drunkman.tga");
	meshList[GEO_DRUNKMAN_HEADBODY] = MeshBuilder::GenerateOBJ("drunkman head and body", "OBJ//headandbody.obj");
	meshList[GEO_DRUNKMAN_HEADBODY]->textureID = LoadTGA("Image//Drunkman.tga");
	meshList[GEO_DRUNKMAN_LEGANDFEET] = MeshBuilder::GenerateOBJ("drunkman head and body", "OBJ//legandfeet.obj");
	meshList[GEO_DRUNKMAN_LEGANDFEET]->textureID = LoadTGA("Image//Drunkman.tga");
	///////////////////////////////////////////////////////////////////////
	meshList[GEO_LOGISTICSTAFF_ARM] = MeshBuilder::GenerateOBJ("logisticstaff arm", "OBJ//Arm.obj");
	meshList[GEO_LOGISTICSTAFF_ARM]->textureID = LoadTGA("Image//Logisticstaff.tga");
	meshList[GEO_LOGISTICSTAFF_HEADBODY] = MeshBuilder::GenerateOBJ("logisticstaff head and body", "OBJ//headandbody.obj");
	meshList[GEO_LOGISTICSTAFF_HEADBODY]->textureID = LoadTGA("Image//Logisticstaff.tga");
	meshList[GEO_LOGISTICSTAFF_LEGANDFEET] = MeshBuilder::GenerateOBJ("logisticstaff head and body", "OBJ//legandfeet.obj");
	meshList[GEO_LOGISTICSTAFF_LEGANDFEET]->textureID = LoadTGA("Image//Logisticstaff.tga");
	/////////////////////////////////////////////////////////////////////////////
	meshList[GEO_NormalNpc1_ARM] = MeshBuilder::GenerateOBJ("NormalNpc1 arm", "OBJ//Arm.obj");
	meshList[GEO_NormalNpc1_ARM]->textureID = LoadTGA("Image//NormalNpc1.tga");
	meshList[GEO_NormalNpc1_HEADBODY] = MeshBuilder::GenerateOBJ("NormalNpc1 head and body", "OBJ//headandbody.obj");
	meshList[GEO_NormalNpc1_HEADBODY]->textureID = LoadTGA("Image//NormalNpc1.tga");
	meshList[GEO_NormalNpc1_LEGANDFEET] = MeshBuilder::GenerateOBJ("NormalNpc1 head and body", "OBJ//legandfeet.obj");
	meshList[GEO_NormalNpc1_LEGANDFEET]->textureID = LoadTGA("Image//NormalNpc1.tga");
	//////////////////////////////////////////////////////////////////////////////
	meshList[GEO_NormalNpc2_ARM] = MeshBuilder::GenerateOBJ("NormalNpc2 arm", "OBJ//Arm.obj");
	meshList[GEO_NormalNpc2_ARM]->textureID = LoadTGA("Image//NormalNpc2.tga");
	meshList[GEO_NormalNpc2_HEADBODY] = MeshBuilder::GenerateOBJ("NormalNpc2 head and body", "OBJ//headandbody.obj");
	meshList[GEO_NormalNpc2_HEADBODY]->textureID = LoadTGA("Image//NormalNpc2.tga");
	meshList[GEO_NormalNpc2_LEGANDFEET] = MeshBuilder::GenerateOBJ("NormalNpc2 head and body", "OBJ//legandfeet.obj");
	meshList[GEO_NormalNpc2_LEGANDFEET]->textureID = LoadTGA("Image//NormalNpc2.tga");
	/*=============================================================================*/
	meshList[GEO_GHOSTNPC_LEGANDFEET] = MeshBuilder::GenerateOBJ("GhostNpc leg and feet", "OBJ//legandfeet.obj");
	meshList[GEO_GHOSTNPC_LEGANDFEET] ->textureID = LoadTGA("Image//GhostNPC.tga");
	meshList[GEO_GHOSTNPC_HEADANDBODY] = MeshBuilder::GenerateOBJ("GhostNpc head and body", "OBJ//headandbody.obj");
	meshList[GEO_GHOSTNPC_HEADANDBODY]->textureID = LoadTGA("Image//GhostNPC.tga");
	meshList[GEO_GHOSTNPC_ARM] = MeshBuilder::GenerateOBJ("GhostNpc arm", "OBJ//Arm.obj");
	meshList[GEO_GHOSTNPC_ARM]->textureID = LoadTGA("Image//GhostNPC.tga");
}
void SceneSP::initCharacter()
{
	ptrplayer = new CPlayer(100,0,8);

	//Tug of war NPC
	ptrNPC = new CNpc(0,0,0,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_IDLE,IDLE,TUG_OF_WAR_GUY,true);
	myNPCList.push_back(ptrNPC);
	//Drunkman NPC
	ptrNPC = new CNpc(-6.f,17.7f,27.f,GEO_DRUNKMAN_HEADBODY,GEO_DRUNKMAN_ARM,GEO_DRUNKMAN_LEGANDFEET,STATE_IDLE,IDLE,DRUNKMAN,true);
	myNPCList.push_back(ptrNPC);

	//Walk around supermarket
	ptrNPC = new CNpc(-5.f,0.f,13.f,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_FORWARD,WALKING,WALKING_GUY,true);
	myNPCList.push_back(ptrNPC);

	ptrNPC = new CNpc(-5.f,0.f,7.f,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_FORWARD,WALKING,WALKING_GUY,true);
	myNPCList.push_back(ptrNPC);

	//Look at stuff
	ptrNPC = new CNpc(1.5f,0.f,25.f,GEO_NormalNpc2_HEADBODY,GEO_NormalNpc2_ARM,GEO_CASHIER_LEGANDFEET,STATE_IDLE,IDLE,LOOKING_GUY,true);
	myNPCList.push_back(ptrNPC);
	//Chatting
	ptrNPC = new CNpc(11.f,17.f,25.f,GEO_DRUNKMAN_HEADBODY,GEO_NormalNpc2_ARM,GEO_CASHIER_LEGANDFEET,STATE_IDLE,IDLE,CHATTING_GUY,true);
	myNPCList.push_back(ptrNPC);
	//idle
	ptrNPC = new CNpc(-2.f,17.f,-22.f,GEO_DRUNKMAN_HEADBODY,GEO_NormalNpc2_ARM,GEO_CASHIER_LEGANDFEET,STATE_IDLE,IDLE,IDLE_GUY,true);
	myNPCList.push_back(ptrNPC);

	//Ghost npc
	ptrNPC = new CNpc(-20.f,-2.f,45.f,GEO_GHOSTNPC_HEADANDBODY,GEO_GHOSTNPC_ARM,GEO_GHOSTNPC_LEGANDFEET,STATE_IDLE,IDLE,GHOST_GUY,true);
	myNPCList.push_back(ptrNPC);
	//cashier 1
	ptrNPC = new CNpc(-26.f,0.f,-18.f,GEO_CASHIER_HEADBODY,GEO_CASHIER_ARM,GEO_CASHIER_LEGANDFEET,STATE_IDLE,IDLE,CASHIER,true);
	myNPCList.push_back(ptrNPC);
	//cashier 2
	ptrNPC = new CNpc(-16.f,0.f,-18.f,GEO_CASHIER_HEADBODY,GEO_CASHIER_ARM,GEO_CASHIER_LEGANDFEET,STATE_IDLE,IDLE,CASHIER,true);
	myNPCList.push_back(ptrNPC);
	//cashier 3
	ptrNPC = new CNpc(-6.f,0.f,-18.f,GEO_CASHIER_HEADBODY,GEO_CASHIER_ARM,GEO_CASHIER_LEGANDFEET,STATE_IDLE,IDLE,CASHIER,true);
	myNPCList.push_back(ptrNPC);

	//Customer at cashier 2
	ptrNPC = new CNpc(-16.f,0.f,-11.f,GEO_NormalNpc2_HEADBODY,GEO_NormalNpc2_ARM,GEO_NormalNpc2_LEGANDFEET,STATE_IDLE,IDLE,CUSTOMER,true);
	myNPCList.push_back(ptrNPC);
	ptrNPC = new CNpc(-16.f,0.f,-9.f,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc2_LEGANDFEET,STATE_IDLE,IDLE,CUSTOMER,true);
	myNPCList.push_back(ptrNPC);
	ptrNPC = new CNpc(-16.f,0.f,-7.f,GEO_NormalNpc2_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_IDLE,IDLE,CUSTOMER,true);
	myNPCList.push_back(ptrNPC);
	ptrNPC = new CNpc(-16.f,0.f,-5.f,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc2_ARM,GEO_NormalNpc2_LEGANDFEET,STATE_IDLE,IDLE,CUSTOMER,true);
	myNPCList.push_back(ptrNPC);
	ptrNPC = new CNpc(-16,0,-3,GEO_NormalNpc2_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_IDLE,IDLE,CUSTOMER,true);
	myNPCList.push_back(ptrNPC);

	//Customer at cashier 3
	ptrNPC = new CNpc(-6.f,0.f,-11.f,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_IDLE,IDLE,CUSTOMER,true);
	myNPCList.push_back(ptrNPC);
	ptrNPC = new CNpc(-6.f,0.f,-9.f,GEO_NormalNpc2_HEADBODY,GEO_NormalNpc2_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_IDLE,IDLE,CUSTOMER,true);
	myNPCList.push_back(ptrNPC);
	ptrNPC = new CNpc(-6.f,0.f,-7.f,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc2_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_IDLE,IDLE,CUSTOMER,true);
	myNPCList.push_back(ptrNPC);
	ptrNPC = new CNpc(-6.f,0.f,-5.f,GEO_NormalNpc2_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc2_LEGANDFEET,STATE_IDLE,IDLE,CUSTOMER,true);
	myNPCList.push_back(ptrNPC);
	ptrNPC = new CNpc(-6.f,0.f,-3.f,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc2_LEGANDFEET,STATE_IDLE,IDLE,CUSTOMER,true);
	myNPCList.push_back(ptrNPC);
	
	//Passer-bys outside supermarket
	ptrNPC = new CNpc(150.f,0.f,110.f,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_FORWARD,WALKING,WALKING_GUY_OUTSIDE,true);
	myNPCList.push_back(ptrNPC);

	//Passer-bys outside supermarket
	ptrNPC = new CNpc(155.f,0.f,105.f,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_FORWARD,WALKING,WALKING_GUY_OUTSIDE,true);
	myNPCList.push_back(ptrNPC);

	//Passer-bys outside supermarket
	ptrNPC = new CNpc(160.f,0.f,100.f,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_FORWARD,WALKING,WALKING_GUY_OUTSIDE,true);
	myNPCList.push_back(ptrNPC);

	//Passer-bys outside supermarket
	ptrNPC = new CNpc(165.f,0.f,95.f,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_FORWARD,WALKING,WALKING_GUY_OUTSIDE,true);
	myNPCList.push_back(ptrNPC);

	//Passer-bys outside supermarket
	ptrNPC = new CNpc(-150.f,0.f,110.f,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_FORWARD,WALKING,WALKING_GUY_OUTSIDE,true);
	myNPCList.push_back(ptrNPC);

	//Passer-bys outside supermarket
	ptrNPC = new CNpc(-155.f,0.f,105.f,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_FORWARD,WALKING,WALKING_GUY_OUTSIDE,true);
	myNPCList.push_back(ptrNPC);

	//Passer-bys outside supermarket
	ptrNPC = new CNpc(-160.f,0.f,100.f,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_FORWARD,WALKING,WALKING_GUY_OUTSIDE,true);
	myNPCList.push_back(ptrNPC);

	//Passer-bys outside supermarket
	ptrNPC = new CNpc(-165.f,0.f,95.f,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_FORWARD,WALKING,WALKING_GUY_OUTSIDE,true);
	myNPCList.push_back(ptrNPC);

	//Logistic staff at level 2  //O(37.0f, 17.0f, 16.0f),S(36.0f, 17.0f, -14.0f)
	ptrNPC = new CNpc(28.f,17.f,25.f,GEO_LOGISTICSTAFF_HEADBODY,GEO_LOGISTICSTAFF_ARM,GEO_LOGISTICSTAFF_LEGANDFEET,STATE_ACTIVE,IDLE,PART_TIME_WORKER,true);
	myNPCList.push_back(ptrNPC);

	ptrNPC = new CNpc(26.f,17.f,26.f,GEO_LOGISTICSTAFF_HEADBODY,GEO_LOGISTICSTAFF_ARM,GEO_LOGISTICSTAFF_LEGANDFEET,STATE_IDLE,IDLE,PART_TIME_WORKER,true);
	myNPCList.push_back(ptrNPC);

	ptrNPC = new CNpc(27.f,17.f,-23.f,GEO_LOGISTICSTAFF_HEADBODY,GEO_LOGISTICSTAFF_ARM,GEO_LOGISTICSTAFF_LEGANDFEET,STATE_IDLE,IDLE,PART_TIME_WORKER,true);
	myNPCList.push_back(ptrNPC);

	ptrNPC = new CNpc(38.f,0.f,-5.f,GEO_LOGISTICSTAFF_HEADBODY,GEO_LOGISTICSTAFF_ARM,GEO_LOGISTICSTAFF_LEGANDFEET,STATE_IDLE,IDLE,PART_TIME_WORKER,true);
	myNPCList.push_back(ptrNPC);

	//EasterEggGuy
    ptrNPC = new CNpc(10.f,17.f,-25.f,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_IDLE,IDLE,EASTER_EGG_GUY,false);
	myNPCList.push_back(ptrNPC);

	//Building Guy
	 ptrNPC = new CNpc(-43,97,-50,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,STATE_IDLE,IDLE,BUILDING_GUY,true);
	myNPCList.push_back(ptrNPC);

}
void SceneSP::initShelves()
{
	//=============================================================================
	ptrClass = new CBeansCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfOne",5,5,5,14,0,28,180);
	myContainerList.push_back(ptrContainer);	//Push back into vector list
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);

	ptrClass = new CBranCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfTwo",5,5,5,20,0,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);

	ptrClass = new CVargaCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfThree",5,5,5,26,0,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);

	ptrClass = new CGluWaterCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf16",5,5,5,8,0,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);

	ptrClass = new CMtnDewCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf17",5,5,5,2,0,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);
	//==============================================================================
	ptrClass =  new CTomatoCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfFour",5,5,5,26,0,18,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);

	ptrClass = new CMelonCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfFive",5,5,5,20,0,18,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);

	ptrClass = new CRedMonsterCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfSix",5,5,5,14,0,18,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);

	ptrClass = new CPeasCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf18",5,5,5,8,0,18,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);

	ptrClass = new CSardineCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf19",5,5,5,2,0,18,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);
	//==================================================================================
	ptrClass = new CBrownCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfSeven",5,5,5,26,0,16,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);

	ptrClass = new CSardineCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfEight",5,5,5,20,0,16,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CPeasCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfNine",5,5,5,14,0,16,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CEasterEgg1;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf20",5,5,5,8,0,16,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CRootBeerFloatsCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf21",5,5,5,2,0,16,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);
	//==================================================================================
	ptrClass = new CBrownCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfTen",5,5,5,26,0,4,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CMtnDewCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfEleven",5,5,5,20,0,4,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CRootBeerFloatsCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfTwelve",5,5,5,14,0,4,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CVargaCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf22",5,5,5,8,0,4,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row;

	ptrClass = new CEasterEgg2;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf23",5,5,5,2,0,4,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	//==================================================================================
	ptrClass = new CSodaCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf13",5,5,5,26,0,6,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);

	ptrClass = new CSodaFestCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf14",5,5,5,20,0,6,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);

	ptrClass = new CRedMonsterCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf15",5,5,5,14,0,6,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CTomatoCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf24",5,5,5,8,0,6,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CMelonCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf25",5,5,5,2,0,6,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	//Second layer
	ptrClass = new CCerealBox1;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfOne",5,5,5,-12,17,28,180);
	myContainerList.push_back(ptrContainer);	//Push back into vector list
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);

	ptrClass = new CCerealBox2;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfTwo",5,5,5,-18,17,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);

	ptrClass = new CCerealBox3;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfThree",5,5,5,-24,17,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);

	ptrClass = new CCerealBox4;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf16",5,5,5,-30,17,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);
	
	ptrClass = new CCerealBox5;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf17",5,5,5,-36,17,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);
	//==================================================================================
	ptrClass = new CEasterEgg1;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfThree",5,5,5,4,17,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);

	ptrClass = new CEasterEgg2;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf16",5,5,5,10,17,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);

	ptrClass = new CHumanCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf17",5,5,5,16,17,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	myTreasureList.push_back(ptrClass);
	//==================================================================================
}
void SceneSP::DefineItem(CContainer* container, CItem item, int row)
{
	if(row == ROW_TOP)
	{
		for(int i = 0; i<container->getFirstStock();++i)
		{
			ptrItem = new CItem(item.getName(),item.getPrice(),item.getGeoType(),container->getXpos()+RenderItemTopRowXOffSet-i,container->getYpos()+RenderItemTopRowYOffSet,container->getZpos());
			myStockList.push_back(ptrItem);
		}
	}
	if(row == ROW_MIDDLE)
	{
		for(int i = 0; i<container->getSecondStock();++i)
		{
			ptrItem = new CItem(item.getName(),item.getPrice(),item.getGeoType(),container->getXpos()+RenderItemMiddleRowXOffSet-i,container->getYpos()+RenderItemMiddleRowYOffSet,container->getZpos());
			myStockList.push_back(ptrItem);
		}
	}
	if(row == ROW_BOTTOM)
	{
		for(int i = 0; i<container->getThirdStock();++i)
		{
			ptrItem = new CItem(item.getName(),item.getPrice(),item.getGeoType(),container->getXpos()+RenderItemBottomRowXOffSet-i,container->getYpos()+RenderItemBottomRowYOffSet,container->getZpos());
			myStockList.push_back(ptrItem);
		}
	}


}
void SceneSP::addToInventory(CItem* pickedUp)
{

	ptrplayer->setInventory(pickedUp,inventoryPointing);
	std::cout<< "Inventory added: " << pickedUp->getName() << std::endl;
	interactionTimer = 0.0f;
}
void SceneSP::DeclareGLEnable()
{
	// Set background color to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);
	//Enable back face culling
	glEnable(GL_CULL_FACE);
	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Load vertex and fragment shaders
	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Text.fragmentshader" );

	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);
}
void SceneSP::DeclareLightParameters()
{
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID,"lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID,"lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID,"lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID,"lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID,"lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID,"lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID,"lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID,"lights[1].exponent");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID,"numLights");

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");


	glUseProgram(m_programID);

	lights[0].type = Light::LIGHT_SPOT;
	lights[0].position.Set(55, -60, -110);
	lights[0].color.Set(1, 0, 1);
	lights[0].power = 4;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(40));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(1.f, 1.f, 0.f);

	lights[1].type = Light::LIGHT_POINT;
	lights[1].position.Set(0, 0, 0);
	lights[1].color.Set(1, 1, 1);
	lights[1].power = 1;
	lights[1].kC = 1.f;
	lights[1].kL = 0.01f;
	lights[1].kQ = 0.001f;
	lights[1].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[1].cosInner = cos(Math::DegreeToRadian(30));
	lights[1].exponent = 3.f;
	lights[1].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);
	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	glUniform1i(m_parameters[U_NUMLIGHTS], 2);
	glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &lights[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], lights[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], lights[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], lights[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], lights[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], lights[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], lights[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], lights[1].exponent);



}
void SceneSP::UpdateUI(double dt)
{
	std::stringstream ss_fps,ss_position,ss_money, ss_camera,ss_item_price;

	ss_camera << camera.target.x << "," << camera.target.y << "," << camera.target.z;
	s_camera_target = ss_camera.str();

	ss_fps << 1/dt;
	s_fps = ss_fps.str();

	ss_position << camera.position.x << "," << camera.position.y << "," << camera.position.z;
	s_position = ss_position.str();

	ss_money << ptrplayer->getMoney();
	s_money = ss_money.str();

	ss_item_price <<  ptrplayer->getItem(inventoryPointing)->getPrice();
	s_item_price = ss_item_price.str();

}
void SceneSP::UpdateItemInspection()
{
	if(Application::IsKeyPressed('R'))
	{
		b_inspection = true;
	}
	else
	{
		b_inspection = false;
	}
}
void SceneSP::UpdateAI(double dt)
{
	UpdateTugofwarguy(dt);
	UpdateWalkingman(dt);
	UpdateWalkingmanoutside(dt);
	UpdateDrunkmanguy(dt);
	UpdateGhostman(dt);
	UpdateLookingman(dt);
	UpdateLogisticman(dt);
	UpdateCustomer(dt);
	UpdateChattingman(dt);
	UpdateShoppers(dt);
	UpdateLegAnimation(dt);
	UpdateBuildingGuy(dt);
	
}
void SceneSP::UpdateEasterEggGuy(double dt)
{
	//if press "E" active state = true
	if (Application::IsKeyPressed('E'))
	{
		if ((camera.position.x > 0.0f && camera.position.x < 11.0f) &&(camera.position.z > -26.0f && camera.position.z < 0.0f ))
		{
			for(unsigned int i = 0; i < myNPCList.size(); ++i)
			{
				if(myNPCList[i]->getCharacterJob() == EASTER_EGG_GUY)
				{
					myNPCList[i]->setActive(true);
					//translation code

					myNPCList[i]->setYpos(myNPCList[i]->getYpos()+myNPCList[i]->getmoveSpd() * static_cast<float>(dt));
					if(myNPCList[i]->getYpos()>23)
					myNPCList[i]->setYpos(17.0f);

					myNPCList[i]->setYpos(myNPCList[i]->getYpos()+myNPCList[i]->getmoveSpd() * static_cast<float>(dt));
					if(myNPCList[i]->getYpos()>23.f)
						myNPCList[i]->setYpos(17.f);

				}
			}
			
		}
	}
}	
void SceneSP::UpdateBuildingGuy(double dt)
{
	for(unsigned int i = 0; i < myNPCList.size(); ++i)
	{
		if(myNPCList[i]->getCharacterJob() == BUILDING_GUY)
		{
			if ((camera.position.x > -60.0f && camera.position.x < -10.0f) && (camera.position.z > -50.0f && camera.position.z < -10.0f ))
			{

				if(!falling)
				{
					myNPCList[i]->setCharacterState(STATE_FORWARD);
				}
			}
			if(myNPCList[i]->getCharacterState() == STATE_FORWARD)
			{
				myNPCList[i]->setZpos(myNPCList[i]->getZpos()-(myNPCList[i]->getmoveSpd() * float(dt)));
				//If off the ledge
				if (myNPCList[i]->getZpos() < -35.0f)
				{
					falling = true;
					myNPCList[i]->setCharacterState(STATE_JUMP);
				}
			}
			if (falling == true)
			{	
				//If jumping off the building
				if(myNPCList[i]->getCharacterState() == STATE_JUMP)
				{
					//if not yet landed on floor
					if (myNPCList[i]->getYpos() > 1.0f)
					{
						myNPCList[i]->setmoveSpd(50.0f);
						myNPCList[i]->setYpos(myNPCList[i]->getYpos()-(myNPCList[i]->getmoveSpd() * float(dt)));

					}
					else
					{
						myNPCList[i]->setXRotation(90.0f);
						myNPCList[i]->setCharacterState(STATE_IDLE);
					}
				}
			}

		}

		
	}
}                   
void SceneSP::UpdateTrolley(double dt)
{
	if(Application::IsKeyPressed(VK_LEFT)&& !Application::IsKeyPressed('R'))
	{
		if(reversed)
			handrotationleftandright -= (camera.CAMERA_SPEED)*float(dt);
		else
			handrotationleftandright += (camera.CAMERA_SPEED)*float(dt);
	}
	if(Application::IsKeyPressed(VK_RIGHT)&& !Application::IsKeyPressed('R'))
	{
		if(reversed)
			handrotationleftandright += (camera.CAMERA_SPEED)*float(dt);
		else
		handrotationleftandright -= (camera.CAMERA_SPEED)*float(dt);
	}
	if(Application::IsKeyPressed('E') || PunchTimerLimiter == false)
	{
		if(PunchTimerLimiter == true)
		{
			PunchTimerLimiter = false;
		}
		else
		{
			handtranslation += (2.0f)*float(dt);
			if(handtranslation > 1.0f)
			{
				PunchTimerLimiter = true;
				handtranslation = 0.0f;
			}
		}
	}
}
void SceneSP::UpdateMainMenu()
{
	if(interactionTimer > menuTImerLimiter)
		{
			if(Application::IsKeyPressed(VK_DOWN))
			{
				if(selectionPointing < MENU_EXIT)
				{
					interactionTimer = 0;
					selectionPointing++;
				}
				else
				{
					interactionTimer = 0;
					selectionPointing = MENU_START; //RESET TO START
				}
			}
			if(Application::IsKeyPressed(VK_UP))
			{
				if(selectionPointing > MENU_START)
				{
					interactionTimer = 0;
					selectionPointing--;
				}
				else
				{
					interactionTimer = 0;
					selectionPointing = MENU_EXIT; //RESET TO EXIT
				}
			}

			if(Application::IsKeyPressed(VK_RETURN))
			{
				if(selectionPointing == MENU_START)
				{
					interactionTimer = 0;
					selectionPointing = MENU_FREE_ROAM;
					i_menuHandle = SUB_MENU;

				}
				if(selectionPointing == MENU_INSTRUCTIONS)
				{
					interactionTimer = 0;
					//Instruction Page
					i_menuHandle = INSTRUCTION_MENU;
					selectionPointing = MENU_BACK;
				}
			}
		}
}
void SceneSP::UpdateStartMenu()
{
	if(interactionTimer > menuTImerLimiter)
		{
			if(Application::IsKeyPressed(VK_DOWN))
			{
				if(selectionPointing < MENU_EASTER_EGG_HUNT)
				{
					interactionTimer = 0;
					selectionPointing++;

				}
				else
				{
					interactionTimer = 0;
					selectionPointing = MENU_FREE_ROAM;
				}
			}
			if(Application::IsKeyPressed(VK_UP))
			{
				if(selectionPointing > MENU_FREE_ROAM)
				{
					interactionTimer = 0;
					selectionPointing--;

				}
				else
				{
					interactionTimer= 0;
					selectionPointing = MENU_EASTER_EGG_HUNT;
				}
			}
			if(Application::IsKeyPressed(VK_RETURN))
			{
				if(selectionPointing == MENU_FREE_ROAM)
				{
					//FREE ROAM HERE
					ptrplayer->setCharacterJob(PLAY_FREE_ROAM);
					i_menuHandle = GAME_PLAYING;
					music.stop();

				}
				if(selectionPointing == MENU_TREASURE_HUNT)
				{
					//DO TREASURE HUNT HERE
					unsigned int random =0;
					std::srand((unsigned int)time(0)); //Seed the random number generator
					for(int i = 0; i< i_total_items_to_find; ++i)
					{
						random =  rand()%myTreasureList.size();
						myCheckList.push_back(myTreasureList[random]); //New item to find everytime
						myTreasureList.erase(myTreasureList.begin()+random);
					}
					ptrplayer->setCharacterJob(PLAY_TREASURE_HUNT);
					i_menuHandle = GAME_PLAYING;
					music.stop();
				}
				if(selectionPointing == MENU_EASTER_EGG_HUNT)
				{
					//DO EASTER EGG HUNT HERE
					ptrplayer->setCharacterJob(PLAY_EASTER_EGG);
					i_menuHandle = GAME_PLAYING;
					music.stop();
				}
			}
		}
}
void SceneSP::UpdateWinLoseMenu()
{
	selectionPointing = MENU_BACK;
	//Reset the world
	
	if(Application::IsKeyPressed(VK_RETURN))
	{
		if(selectionPointing == MENU_BACK)
		{
			//TO DO 
			resetGame();
		}
	}
}
void SceneSP::UpdateInstructionMenu()
{
	if(interactionTimer > menuTImerLimiter)
	{
		if(Application::IsKeyPressed(VK_RETURN))
		{
			if(selectionPointing == MENU_BACK)
			{
				interactionTimer = 0;
				selectionPointing = MENU_START;
				i_menuHandle = MAIN_MENU;

			}

		}
	}
}
void SceneSP::UpdateMenu()
{
	//If at main menu
	if(i_menuHandle == MAIN_MENU)
	{
		UpdateMainMenu();
	}

	//If at SUB/Character menu 
	if(i_menuHandle == SUB_MENU)
	{
		UpdateStartMenu();
	}
	if(i_menuHandle == INSTRUCTION_MENU)
	{
		UpdateInstructionMenu();
	}
	if(i_menuHandle == PAUSE_MENU)
	{
		UpdatePauseMenu();
	}
	//If at Win/Lose Menu
	if(i_menuHandle == WIN_LOSE_MENU)
	{
		UpdateWinLoseMenu();
	}
}
void SceneSP::UpdatePauseMenu()
{

	if(interactionTimer > menuTImerLimiter)
	{

		if(Application::IsKeyPressed(VK_DOWN))
		{
			if(selectionPointing < MENU_BACK)
			{
				interactionTimer = 0;
				selectionPointing++;

			}
			else
			{
				interactionTimer = 0;
				selectionPointing = MENU_RESUME;
			}
		}
		if(Application::IsKeyPressed(VK_UP))
		{
			if(selectionPointing > MENU_RESUME)
			{
				interactionTimer = 0;
				selectionPointing--;

			}
			else
			{
				interactionTimer= 0;
				selectionPointing = MENU_BACK;
			}
		}

		if(Application::IsKeyPressed(VK_RETURN))
		{
			interactionTimer = 0;
			if(selectionPointing == MENU_RESUME)
			{
				i_menuHandle = GAME_PLAYING;
			}
			if(selectionPointing == MENU_BACK)
			{
				resetGame();
			}
		}
	}
}
void SceneSP::resetGame()
{
	myNPCList.clear();
	myCheckList.clear();
	myContainerList.clear();
	myStockList.clear();
	myTreasureList.clear();
	Init();
}
void SceneSP::UpdateItemRotation(double dt)
{
	if(Application::IsKeyPressed(VK_RIGHT)&& Application::IsKeyPressed('R'))
	{
		itemYrotation+=float(dt)*itemRotationSpeedMultiplyer;
	}
	if(Application::IsKeyPressed(VK_LEFT) && Application::IsKeyPressed('R'))
	{
		itemYrotation-=float(dt)*itemRotationSpeedMultiplyer;
	}
	if(Application::IsKeyPressed(VK_DOWN)&& Application::IsKeyPressed('R'))
	{
		itemXrotation+=float(dt)*itemRotationSpeedMultiplyer;
	}
	if(Application::IsKeyPressed(VK_UP) && Application::IsKeyPressed('R'))
	{
		itemXrotation-=float(dt)*itemRotationSpeedMultiplyer;
	}
	if(!Application::IsKeyPressed('R'))
	{
		itemXrotation = 0.f;
		itemYrotation = 0.f;
	}
}
void SceneSP::UpdateEasteregg(double dt)
{	
	std::stringstream ss_easterCounter;
	std::stringstream ss_easterCount;
	ss_easterCounter << getCounter;
	ss_easterCount << numEastereggs;
	s_easter_counter = ss_easterCounter.str();
	s_easter_count = ss_easterCount.str();
	easterTimer += float(dt);
	if(ptrplayer->getCharacterJob() == PLAY_EASTER_EGG)
	{
		UpdateMiscEasteregg(dt);
		UpdateCage(dt);
		UpdateGaben(dt);
		UpdateTroll(dt);
		if(getCounter == numEastereggs)
		{
			winEaster = true;
		}
		if(winEaster == true && Application::IsKeyPressed(VK_RETURN))
		{
			closeEaster = true;
		}
	}
}
void SceneSP::UpdatePlaying(double dt)
{
	//3d sound
	music.setPosition(0.0f, 0.0f, 0.0f);
	sf::Listener::setPosition(camera.position.x, camera.position.y, camera.position.z);
	sf::Listener::setGlobalVolume(800.f);
	if(music.getStatus() == false)
	{
		if(!music.openFromFile(ambientSound))
		{
			std::cout << "ERROR OPENING MUSIC FILE" << std::endl;
		}
		music.setLoop(true);
		music.setVolume(50.0f);
		music.play();
	}
	checkWinLose();
	if(Application::IsKeyPressed(VK_F1)) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed(VK_F2)) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed(VK_F3))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed(VK_F4))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	if(Application::IsKeyPressed(VK_F5))
	{
		toggleLight = true;
	}
	if(Application::IsKeyPressed(VK_F6))
	{
		toggleLight = false;
	}
	//If player is crouching
	if(Application::IsKeyPressed(VK_CONTROL))
	{
		b_crouching = true;
		if(Application::IsKeyPressed(VK_SHIFT)&&easterTimer > easterLimiter2)
		{
			easterTimer = 0.0f;
			if(!music.openFromFile(soundFXArray[5]))
			{
				std::cout << "ERROR OPENING MUSIC FILE" << std::endl;
			}
			music.setLoop(false);
			music.setVolume(50.0f);
			music.play();
		}
	}
	else
	{
		b_crouching = false;
	}
	if(Application::IsKeyPressed('P'))
	{
		selectionPointing = MENU_RESUME;
		i_menuHandle = PAUSE_MENU;
	}
	//If player is crouching at elevator
	if(b_crouching)
	{
		if(elevatorIdle)
		{
			//First floor crouching
			if(camera.position.y>3.1f && camera.position.y < 4.7f)
			{
				camera.position.y-=float(dt)*5;
				camera.target.y -=float(dt)*5;
			}
			//Second floor crouching
			if(camera.position.y > 19.1f && camera.position.y < 22.f)
			{
				camera.position.y-=float(dt)*5;
				camera.target.y -=float(dt)*5;
			}
		}

	}
	else //Not crouching anymore
	{
		if(elevatorIdle)
		{
			//First floor crouching
			if(camera.position.y <= 4.5f && camera.position.y >= 2.0f)
			{
				camera.position.y+=float(dt)*5;
				camera.target.y+=float(dt)*5;
			}
			//Second floor crouching
			if(camera.position.y <21.5f && camera.position.y >= 19.f)
			{
				camera.position.y+=float(dt)*5;
				camera.target.y+=float(dt)*5;
			}
		}
	}

	UpdatePlayerSelection();
	UpdateUI(dt);
	UpdateTugofwar(dt);
	UpdateDrunkman(dt);
	UpdateAI(dt);
	UpdateItemRotation(dt);
	UpdateItemInspection();
	UpdateEasteregg(dt);
	UpdateATM();
	reverseTimer += float(dt);
	
	UpdatePaying();//Update playing paying

	UpdateUI(dt);
	checkPickUpItem();
	if(!IsIntugofwar && !caged)
		camera.UpdateMovement(dt,reversed);
	camera.UpdateView(dt,reversed);
	UpdateTrolley(dt);
	UpdateElevator(dt);
	UpdateDoor(dt);
	UpdateSamples();
	UpdateEasterEggGuy(dt);
	checkCollision();
	checkReturnPoint();
	
}
void SceneSP::UpdateAITimer(double dt)
{
	for(unsigned int i = 0; i< myNPCList.size(); ++i)
	{
		myNPCList[i]->setNPCTimer(myNPCList[i]->getNPCTimer()+static_cast<float>(dt));
	}
}
void SceneSP::Update(double dt)
{
	CustomerinteractionTimer+=float(dt);
	LogisticinteractionTimer+=float(dt);
	interactionTimer+=float(dt);
	UpdateAITimer(dt);
	f_soundTimer += float(dt);
	
	if(i_menuHandle == GAME_PLAYING )
	{
		UpdatePlaying(dt);
	}
	else
	{
		UpdateMenu();
	}
	

}
void SceneSP::UpdateElevator(double dt)
{
	//If player is within elevator interaction boundary
	if(camera.position.x > checkElevatorXposMin && camera.position.x < checkElevatorXposMax)
	{
		if(camera.position.z > checkElevatorZposMin && camera.position.z < checkElevatorZposMax)
		{

			if(Application::IsKeyPressed('E') && interactionTimer > interactionTimerLimiter && elevatorIdle)
			{
				if(elevatorDoorOpening) //Check toggling
				{
					interactionTimer = 0;
					elevatorDoorOpening = false;
					std::cout << "Door closing!" << std::endl;
				}
				else
				{
					interactionTimer = 0;
					elevatorDoorOpening = true;
					std::cout << "Door opening!" << std::endl;

				}
			}
			//If player is INSIDE elevator
			if(camera.position.x > checkInnerElevatorXposMin && camera.position.x < checkInnerElevatorXposMax)
			{
				if(camera.position.z > checkInnerElevatorZposMin && camera.position.z < checkInnerElevatorZposMax)
				{
					//if elevator door is closed
					if(!elevatorDoorOpening)
					{
						if(!(elevatorSecondFloor))
						{
							//Move elevator up
							camera.position.y += float(dt)*elevatorSpeed;
							camera.target.y +=float(dt)*elevatorSpeed;
							elevatorY+=float(dt)*elevatorSpeed;
							elevatorIdle = false;
						}
						else if(elevatorSecondFloor)
						{
							//Move elevator down
							camera.position.y-=float(dt)*elevatorSpeed;
							camera.target.y-=float(dt)*elevatorSpeed;
							elevatorY-=float(dt)*elevatorSpeed;
							elevatorIdle = false;
						}
					}
				}
			}
		}
	}



	//Handle second floor boolean here
	if(elevatorY > secondFloorYpositionMax)
	{
		elevatorIdle = true;
		elevatorDoorOpening = true;
		elevatorSecondFloor = true;
	}
	if(elevatorY < secondFloorYpositionMin)
	{
		elevatorIdle = true;
		elevatorDoorOpening = true;
		elevatorSecondFloor = false;
	}
	//Handle opening and closing here
	if(elevatorDoorOpening) //if door is going up
	{

		if(!(elevatorDoorY > checkElevatorYposMax))
		{
			elevatorDoorY+=float(dt)*5;
			b_dinged = false;
		}		
	}
	else //if door is closing
	{
		if(!(elevatorDoorY < checkElevatorYposMin))
		{
			elevatorDoorY-= float(dt)*5;
		}
		else
		{
			if(b_dinged == false)
			{
				b_dinged = true;
				if(!sound.openFromFile(soundFXArray[6]))
				{
					std::cout << "ERROR OPENING MUSIC FILE" << std::endl;
				}
				sound.setLoop(false);
				sound.setVolume(50.0f);
				sound.play();
			}
		}
	}
}
void SceneSP::UpdateATM()
{
	std::stringstream ss_atmBalance;
	ss_atmBalance << ATMMoney;
	s_atm_balance = ss_atmBalance.str();
	//check area//-15 //38
	if ((camera.position.x > -6 && camera.position.x < 7) && (camera.position.z > 32 && camera.position.z < 40))
	{
		//if pressed E
		if(Application::IsKeyPressed('E') && interactionTimer > interactionTimerLimiter)
		{
			if(ATMMoney > 0)//deduct money from atm
			{
				interactionTimer = 0.0f;
				ptrplayer->setMoney(ptrplayer->getMoney()+5.0f);
				ATMMoney -= 5.0f;
			}
		}
	}
}
void SceneSP::UpdateDoor(double dt)
{
	static bool test = false;
	static bool test2 = false;
	static bool sounded = false;
	for(unsigned int i = 0; i < myNPCList.size(); ++i)//check npc pos
	{
		if(((myNPCList[i]->getZpos() < -15.0f && myNPCList[i]->getZpos() > -40.0f) && (myNPCList[i]->getXpos() > 10.0f && myNPCList[i]->getXpos() < 35.0f))&&
			myNPCList[i]->getYpos()<5
			)//Back door control
		{
			toggleDoorBack = true;
			test = true;
			break;
		}
		else
			toggleDoorBack = false;
	}
	for(unsigned int i = 0; i < myNPCList.size(); ++i)
	{
		if(((myNPCList[i]->getZpos() < 45.0f && myNPCList[i]->getZpos() > 15.0f) && (myNPCList[i]->getXpos() > -30.0f  && myNPCList[i]->getXpos() < -10.0f))&&
			myNPCList[i]->getYpos()<5
			)
		{
			toggleDoorFront = true;
			test2 = true;
			break;
		}
		else
			toggleDoorFront = false;
	}
	if(!test)
	{
		if((camera.position.z < -15.0f && camera.position.z > -40.0f) && (camera.position.x > 10.0f && camera.position.x < 35.0f))
			toggleDoorBack = true;
		else
			toggleDoorBack = false;
	}
	if(!test2)
	{
		if((camera.position.z < 45.0f && camera.position.z > 15.0f) && (camera.position.x > -30.0f && camera.position.x < -10.0f))
			toggleDoorFront = true;
		else
			toggleDoorFront = false;
	}
	test = false;
	test2 = false;
	if(toggleDoorBack)
	{
		if(moveDoorBack > -7.0f)
		{
			moveDoorBack -= 10.0f * float(dt);
			sounded = true;
		}
	}
	else
	{
		if(moveDoorBack < 0.0f)
		{
			moveDoorBack += 10.0f * float(dt);
			sounded = true;
		}
	}
	if(toggleDoorFront)
	{
		if(moveDoorFront > -8.0f)
		{
			moveDoorFront -= 10.0f * float(dt);
			sounded = true;
		}
	}
	else
	{
		if(moveDoorFront < 0.0f)
		{
			moveDoorFront += 10.0f * float(dt);
			sounded = true;
		}
	}
	if((sounded == true && f_soundTimer > soundLimiter)&&camera.position.y<10.0f)
	{
		f_soundTimer = 0.0f;
		if(!sound.openFromFile(soundFXArray[7]))
		{
			std::cout << "ERROR OPENING MUSIC FILE" << std::endl;
		}
		sound.setLoop(false);
		sound.setVolume(800.0f);
		sound.play();
	}
	sounded = false;
}
void SceneSP::UpdatePlayerSelection()
{
	if(Application::IsKeyPressed('1'))
	{
		if(ptrplayer->getItemHeld()>0)
		{
			ptrInvSelect = ptrplayer->getItem(0);
			inventoryPointing = 0;
			std::cout << ptrInvSelect->getName();
		}
	}
	if(Application::IsKeyPressed('2'))
	{
		if(ptrplayer->getItemHeld()>0)
		{
			ptrInvSelect = ptrplayer->getItem(1);
			inventoryPointing =1;
			std::cout << ptrInvSelect->getName();
		}
	}
	if(Application::IsKeyPressed('3'))
	{
		if(ptrplayer->getItemHeld()>0)
		{
			ptrInvSelect = ptrplayer->getItem(2);
			inventoryPointing =2;
			std::cout << ptrInvSelect->getName();
		}
	}
	if(Application::IsKeyPressed('4'))
	{
		if(ptrplayer->getItemHeld()>0)
		{
			ptrInvSelect = ptrplayer->getItem(3);
			inventoryPointing =3;
			std::cout << ptrInvSelect->getName();
		}
	}
	if(Application::IsKeyPressed('5'))
	{
		if(ptrplayer->getItemHeld()>0)
		{
			ptrInvSelect = ptrplayer->getItem(4);
			inventoryPointing =4;
			std::cout << ptrInvSelect->getName();
		}
	}
	if(Application::IsKeyPressed('6'))
	{
		if(ptrplayer->getItemHeld()>0)
		{
			ptrInvSelect = ptrplayer->getItem(5);
			inventoryPointing =5;
			std::cout << ptrInvSelect->getName();
		}
	}
	if(Application::IsKeyPressed('7'))
	{
		if(ptrplayer->getItemHeld()>0)
		{
			ptrInvSelect = ptrplayer->getItem(6);
			inventoryPointing =6;
			std::cout << ptrInvSelect->getName();
		}
	}
	if(Application::IsKeyPressed('8'))
	{
		if(ptrplayer->getItemHeld()>0)
		{
			ptrInvSelect = ptrplayer->getItem(7);
			inventoryPointing =7;
			std::cout << ptrInvSelect->getName();
		}
	}

}
void SceneSP::UpdatePaying()
{
	//If player is within paying zone of cashier
	if((camera.position.x > -29.0f && camera.position.x < -23.0f) && (camera.position.z > -13.f && camera.position.z < -7.0f) && (camera.position.y >3.0f && camera.position.y < 5.0f))
	{
		b_isWithinPayingCashier = true;
		//If player is paying
		if (Application::IsKeyPressed('E') && interactionTimer > interactionTimerLimiter)
		{
			//If player money is greater than price of item
			if(ptrplayer->getMoney() >= ptrplayer->getVector()[inventoryPointing]->getPrice())
			{
				//Reset the intereaction timer
				interactionTimer = 0;
				std::cout << "Item paid: " << ptrplayer->getVector()[inventoryPointing]->getName() << std::endl;
				//Deduct from player money total price
				ptrplayer->setMoney(ptrplayer->getMoney() - ptrplayer->getVector()[inventoryPointing]->getPrice());
				
				//Check if item paid is == random checklist items
				for(unsigned int i = 0; i<myCheckList.size();++i)
				{

					if(ptrplayer->getVector()[inventoryPointing]->getName() == myCheckList[i]->getName()
						&& ptrplayer->getVector()[inventoryPointing]->getPrice() == myCheckList[i]->getPrice()
						&& ptrplayer->getVector()[inventoryPointing]->getGeoType() == myCheckList[i]->getGeoType())
					{
						myCheckList[i]->setName(clearText);
					}
				}

				//Set inventory to empty afterwards
				ptrplayer->setInventory(ptrEmpty,inventoryPointing);
				ptrInvSelect = ptrplayer->getItem(inventoryPointing);
			}
		}
	}
	else
	{
		b_isWithinPayingCashier = false;
	}

	

	
}
void SceneSP::UpdateSamples()
{
	if(Application::IsKeyPressed('E') && interactionTimer > interactionTimerLimiter)
	{
		if((camera.position.x > 25.0f && camera.position.x < 35.0f) && (camera.position.z > -8.0f && camera.position.z < -2.0f))
		{
			interactionTimer = 0.0f;
			i_sampleItems--;
			if(!sound.openFromFile(soundFXArray[8]))
			{
				std::cout << "ERROR OPENING MUSIC FILE" << std::endl;
			}
			sound.setLoop(false);
			sound.setVolume(50.0f);
			sound.play();
		}
	}
}
void SceneSP::UpdateTugofwar(double dt)
{
	if(((Application::IsKeyPressed('E') && (IsIntugofwar == false))&&
		((camera.position.z > -2 && camera.position.z < 1.1) && (camera.position.x > 7 && camera.position.x < 13)))&&
		camera.position.y < 10
		)//Initiate tug of war conditions
	{//Initiate tug of war sequence
		IsIntugofwar = true;
		diffX = camera.position.x - 20;
		diffZ = camera.position.z - 0;
		camera.position.x = 20;
		camera.position.z = 0;
		camera.target.x -= diffX;
		camera.target.z -=diffZ;
		diffX = diffZ = 0;
		showTuginstruction = true;
	}
	if(Application::IsKeyPressed(VK_SPACE) && (showTuginstruction == true))
	{//Stop showing tug of war instructions
		showTuginstruction = false;
	}
	if(IsIntugofwar == true && showTuginstruction == false)
	{//While in tug of war sequence
		camera.position.x -= 0.001f*camera.CAMERA_SPEED;
		camera.target.x -= 0.001f*camera.CAMERA_SPEED;
		if(Application::IsKeyPressed(VK_SPACE) && interactionTimer > TugofwarTimerLimiter)
		{//update camera based on tugs
			interactionTimer = 0.0f;
			camera.position.x += 0.025f*camera.CAMERA_SPEED;
			camera.target.x += 0.025f*camera.CAMERA_SPEED;
		}
		if(camera.position.x > 32)//win condition
		{
			IsIntugofwar = false;
			win = true;
		}
		if(camera.position.x < 3)//lose condition
		{
			IsIntugofwar = false;
			lose = true;
		}
	}
	if(Application::IsKeyPressed('A') || Application::IsKeyPressed('S') || Application::IsKeyPressed('D') || Application::IsKeyPressed('W'))
	{//reset win/lose message
		win = false;
		lose = false;
	}
}
void SceneSP::UpdateTugofwarguy(double dt)
{
	if(!IsIntugofwar)
	{
		myNPCList[0]->setYRotation(0);
		myNPCList[0]->setXpos(7.0f);
		myNPCList[0]->setZpos(1.5f);
		myNPCList[0]->setLeftArm(30);
		myNPCList[0]->setRightArm(-30);
	}
	else //if(IsIntugofwar)
	{
		myNPCList[0]->setYRotation(90);
		myNPCList[0]->setXpos(camera.position.x - 4);
		myNPCList[0]->setZpos(camera.position.z);
		myNPCList[0]->setLeftArm(40);
	}
}
void SceneSP::UpdateDrunkman(double dt)
{
	for(unsigned int i = 0; i < myNPCList.size(); ++i)
	{
		if(myNPCList[i]->getCharacterJob() == DRUNKMAN)
		{
			if(Application::IsKeyPressed('E') && (i_drunkmanAct == DRUNKIDLE)	
				&&(camera.position.z > myNPCList[i]->getZpos()-6 && camera.position.z <myNPCList[i]->getZpos()+6)
				&&(camera.position.x > myNPCList[i]->getXpos()-6 && camera.position.x < myNPCList[i]->getXpos()+6)
				&&(camera.position.y > myNPCList[i]->getYpos())
				)
			{
				i_drunkmanAct = DRUNKCARRY;
			}

			if(Application::IsKeyPressed('E') && (i_drunkmanAct == DRUNKCARRY)	
				&&(camera.position.z < 45.0f && camera.position.z > 15.0f)
				&&(camera.position.x > -30.0f  && camera.position.x < -10.0f)
				&&(camera.position.y > 1.0f  && camera.position.y < 16.0f))
			{
				i_drunkmanAct = DRUNKOUTSIDE;
			}
		}
	}
}
void SceneSP::UpdateDrunkmanguy(double dt)
{
	for(unsigned int i = 0; i < myNPCList.size(); ++i)
	{
		if(myNPCList[i]->getCharacterJob() == DRUNKMAN)
		{
			if(i_drunkmanAct == DRUNKIDLE)
			{
				myNPCList[i]->setYRotation(180);
				myNPCList[i]->setXRotation(90);
			}
			else if(i_drunkmanAct == DRUNKCARRY)
			{
				myNPCList[i]->setXpos(camera.position.x);
				myNPCList[i]->setYpos(camera.position.y+2);
				myNPCList[i]->setZpos(camera.position.z+3);
			}
			else
			{
				myNPCList[i]->setXpos(-25.f);
				myNPCList[i]->setYpos(0.7f);
				myNPCList[i]->setZpos(60.f);
			}
		}
	}
}
void SceneSP::UpdateWalkingmanoutside(double dt)
{
	for(unsigned int i = 0; i < myNPCList.size(); ++i)
	{
		if(myNPCList[i]->getCharacterJob() == WALKING_GUY_OUTSIDE)
		{
			
			if(myNPCList[i]->getCharacterState() == STATE_FORWARD)
			{
				if(myNPCList[i]->getZpos() > 190.f)
				{
					
					myNPCList[i]->setCharacterState(STATE_BACKWARD);
					myNPCList[i]->setYRotation(180);

				}
				myNPCList[i]->setZpos((myNPCList[i]->getZpos())+(myNPCList[i]->getmoveSpd()*float(dt)));
			
				
			}
			
			if(myNPCList[i]->getCharacterState() == STATE_BACKWARD)
			{ 
				if(myNPCList[i]->getZpos() < 110.f)
				{
		
					myNPCList[i]->setCharacterState(STATE_FORWARD);
					myNPCList[i]->setYRotation(0);
	
				}
				myNPCList[i]->setZpos((myNPCList[i]->getZpos())-(myNPCList[i]->getmoveSpd()*float(dt)));
			}

		}
	}
}
void SceneSP::UpdateWalkingman(double dt)
{
	for(unsigned int i = 0; i < myNPCList.size(); ++i)
	{
		if(myNPCList[i]->getCharacterJob() == WALKING_GUY)
		{
			myNPCList[i]->setAnimationType(WALKING);
			myNPCList[i]->setmoveSpd(5.0f);
			myNPCList[i]->setLeftArm(WalkingNpcInitArm);
			myNPCList[i]->setRightArm(-WalkingNpcInitArm);
			if(myNPCList[i]->getCharacterState()==STATE_FORWARD)
			{
				if(myNPCList[i]->getZpos() > 21.f)
				{
					myNPCList[i]->setCharacterState(STATE_LEFT);
					myNPCList[i]->setYRotation(90.f);
				}
				myNPCList[i]->setZpos(myNPCList[i]->getZpos()+(myNPCList[i]->getmoveSpd() * float(dt)));
			}
			if(myNPCList[i]->getCharacterState()==STATE_LEFT)
			{
				if(myNPCList[i]->getXpos() > 32.f)
				{
					myNPCList[i]->setCharacterState(STATE_BACKWARD);
					myNPCList[i]->setYRotation(180.f);
				}
				myNPCList[i]->setXpos(myNPCList[i]->getXpos()+(myNPCList[i]->getmoveSpd() * float(dt)));
			}
			if(myNPCList[i]->getCharacterState()==STATE_BACKWARD)
			{
				if(myNPCList[i]->getZpos() < 13.f)
				{
					myNPCList[i]->setCharacterState(STATE_RIGHT);
					myNPCList[i]->setYRotation(-90.f);
				}
				myNPCList[i]->setZpos(myNPCList[i]->getZpos()-(myNPCList[i]->getmoveSpd() * float(dt)));
			}
			if(myNPCList[i]->getCharacterState()==STATE_RIGHT)
			{
				if(myNPCList[i]->getXpos() < -5.f)
				{
					myNPCList[i]->setCharacterState(STATE_FORWARD);
					myNPCList[i]->setYRotation(0.f);
				}
				myNPCList[i]->setXpos(myNPCList[i]->getXpos()-(myNPCList[i]->getmoveSpd() * float(dt)));
			}
		}
	}

}
void SceneSP::UpdateGhostman(double dt)
{
	for(unsigned int i = 0; i< myNPCList.size(); ++i)
	{
		if(myNPCList[i]->getCharacterJob() == GHOST_GUY)
		{
			static bool GisFlying = false;
			static bool GFlyDir = true;
			static bool GMoveDir = true;
			myNPCList[i]->setLeftLeg(GhostNpcInitLeg);
			myNPCList[i]->setRightLeg(GhostNpcInitLeg);
			myNPCList[i]->setYRotation(GhostNpcInitRot);
			myNPCList[i]->setmoveSpd(7.0f);
			if(((camera.position.z < GhostNpcAppearBoundZ1 && camera.position.z > GhostNpcAppearBoundZ2) && (camera.position.x > GhostNpcAppearBoundX1 && camera.position.x < GhostNpcAppearBoundX2)) ||
				camera.position.z > GhostNpcAppearBoundZ3
				)
				myNPCList[i]->setCharacterState(STATE_IDLE);
			else
				myNPCList[i]->setCharacterState(STATE_FORWARD);
			if(myNPCList[i]->getCharacterState() == STATE_FORWARD)
			{
				myNPCList[i]->setActive(true);
				if(GisFlying == false)
				{
					myNPCList[i]->setYpos(GhostNpcResetYPos);
					GisFlying = true;
				}
				else
				{
					if(GFlyDir == true)
					{
						myNPCList[i]->setYpos(myNPCList[i]->getYpos() + myNPCList[i]->getmoveSpd() * float(dt));
						if(myNPCList[i]->getYpos() > GhostNpcMoveBoundY1)
							GFlyDir = false;
					}
					else
					{
						myNPCList[i]->setYpos(myNPCList[i]->getYpos() - myNPCList[i]->getmoveSpd() * float(dt));
						if(myNPCList[i]->getYpos() < GhostNpcMoveBoundY2)
							GFlyDir = true;
					}
					if(GMoveDir == true)
					{
						myNPCList[i]->setXpos(myNPCList[i]->getXpos() + myNPCList[i]->getmoveSpd() * float(dt));
						if(myNPCList[i]->getXpos() > GhostNpcMoveBoundX1)
							GMoveDir = false;
					}
					else
					{
						myNPCList[i]->setXpos(myNPCList[i]->getXpos() - myNPCList[i]->getmoveSpd() * float(dt));
						if(myNPCList[i]->getXpos() < GhostNpcMoveBoundX2)
							GMoveDir = true;
					}
				}
			}
			if(myNPCList[i]->getCharacterState() == STATE_IDLE)
			{
				myNPCList[i]->setYpos(-10.f);
				GisFlying = false;
				myNPCList[i]->setActive(false);
			}
		}
	}
}
void SceneSP::UpdateLookingman(double dt)
{
	static int counter = 0;
	for(unsigned int i = 0; i< myNPCList.size(); ++i)
	{
		if(myNPCList[i]->getCharacterJob() == LOOKING_GUY)
		{
			myNPCList[i]->setLeftArm(30);
			myNPCList[i]->setRightArm(-30);
			if(myNPCList[i]->getCharacterState() == STATE_IDLE)
			{
				myNPCList[i]->setLeftLeg(0.0f);//reset leg rotations
				myNPCList[i]->setRightLeg(0.0f);
				myNPCList[i]->setAnimationType(IDLE);
				if(myNPCList[i]->getNPCTimer() > NPCLookLimiter)
				{
					myNPCList[i]->setNPCTimer(0.0f);
					myNPCList[i]->setYRotation(myNPCList[i]->getYRotation()+90.0f);
					myNPCList[i]->setCharacterState(STATE_LEFT);
					if(counter == 2)
						myNPCList[i]->setCharacterState(STATE_BACKWARD);
					if(counter == 3)
						myNPCList[i]->setCharacterState(STATE_RIGHT);
				}
			}
			else
				myNPCList[i]->setAnimationType(WALKING);
			if(myNPCList[i]->getCharacterState() == STATE_LEFT)
			{
				if(myNPCList[i]->getXpos() > 26 && counter == 0)
				{
					myNPCList[i]->setCharacterState(STATE_IDLE);
					myNPCList[i]->setYRotation(0);
					counter = 1;
				}
				if(myNPCList[i]->getXpos() > 32 && counter == 1)
				{
					myNPCList[i]->setCharacterState(STATE_IDLE);
					counter = 2;
				}
				if(myNPCList[i]->getXpos() > 1.5 && counter == 4)
				{
					myNPCList[i]->setXpos(1.5);
					myNPCList[i]->setYRotation(0);
					myNPCList[i]->setCharacterState(STATE_IDLE);
					counter = 0;
				}
				myNPCList[i]->setXpos(myNPCList[i]->getXpos()+(myNPCList[i]->getmoveSpd() * float(dt)));
			}
			if(myNPCList[i]->getCharacterState() == STATE_BACKWARD)
			{
				if(myNPCList[i]->getZpos() < 9)
				{
					myNPCList[i]->setYRotation(-90.f);
					myNPCList[i]->setCharacterState(STATE_RIGHT);
				}
				myNPCList[i]->setZpos(myNPCList[i]->getZpos()-(myNPCList[i]->getmoveSpd() * float(dt)));
			}
			if(myNPCList[i]->getCharacterState() == STATE_RIGHT)
			{
				if(myNPCList[i]->getXpos() < 8 && counter == 2)
				{
					myNPCList[i]->setYRotation(180.f);
					myNPCList[i]->setCharacterState(STATE_IDLE);
					counter = 3;
				}
				if(myNPCList[i]->getXpos() < -8 && counter == 3)
				{
					myNPCList[i]->setYRotation(0.f);
					myNPCList[i]->setCharacterState(STATE_FORWARD);
					counter = 4;
				}
				myNPCList[i]->setXpos(myNPCList[i]->getXpos()-(myNPCList[i]->getmoveSpd() * float(dt)));
			}
			if(myNPCList[i]->getCharacterState() == STATE_FORWARD)
			{
				if(myNPCList[i]->getZpos() > 25.0f)
				{
					myNPCList[i]->setZpos(25.0f);
					myNPCList[i]->setYRotation(90);
					myNPCList[i]->setCharacterState(STATE_LEFT);
				}
				myNPCList[i]->setZpos(myNPCList[i]->getZpos()+(myNPCList[i]->getmoveSpd() * float(dt)));
			}
		}

	}
}
void SceneSP::UpdateLogisticman(double dt)
{
	for(unsigned int i = 0; i< myNPCList.size(); ++i)
	{
		if(myNPCList[i]->getCharacterJob() == PART_TIME_WORKER)
		{
			if(myNPCList[i]->getCharacterState() == STATE_IDLE)
			{
				myNPCList[i]->setLeftArm(WalkingNpcInitArm);
				myNPCList[i]->setRightArm(-WalkingNpcInitArm);
				myNPCList[i]->setYRotation(270.0f);
			}

			if(myNPCList[i]->getCharacterState() == STATE_ACTIVE)
			{
				myNPCList[i]->setLeftArm(WalkingNpcInitArm);
				myNPCList[i]->setRightArm(-WalkingNpcInitArm);
				myNPCList[i]->setYRotation(270.0f);
				if(LogisticinteractionTimer > NPCLookLimiter && (myNPCList[i]->getZpos() < -20.f))
				{
					myNPCList[i]->setYRotation(0.0f);
					myNPCList[i]->setAnimationType(WALKING);
					myNPCList[i]->setmoveSpd(5.0f);
					myNPCList[i]->setCharacterState(STATE_FORWARD);
				}
				if(LogisticinteractionTimer > NPCLookLimiter && (myNPCList[i]->getZpos() > 24.f))
				{
					myNPCList[i]->setYRotation(180.0f);
					myNPCList[i]->setAnimationType(WALKING);
					myNPCList[i]->setmoveSpd(5.0f);
					myNPCList[i]->setCharacterState(STATE_BACKWARD);
				}

			}
			if(myNPCList[i]->getCharacterState() == STATE_FORWARD)
			{
				if(myNPCList[i]->getZpos() > 24.f)
				{
					LogisticinteractionTimer = 0;
					myNPCList[i]->setAnimationType(IDLE);
					myNPCList[i]->setmoveSpd(0.0f);
					myNPCList[i]->setLeftLeg(0.0f);
					myNPCList[i]->setRightLeg(0.0f);
					myNPCList[i]->setCharacterState(STATE_ACTIVE);
				}
				myNPCList[i]->setZpos((myNPCList[i]->getZpos())+(myNPCList[i]->getmoveSpd()*float(dt)));
			}
			if(myNPCList[i]->getCharacterState() == STATE_BACKWARD)
			{
				if(myNPCList[i]->getZpos() < -20.f)
				{
					LogisticinteractionTimer = 0;
					myNPCList[i]->setAnimationType(IDLE);
					myNPCList[i]->setmoveSpd(0.0f);
					myNPCList[i]->setLeftLeg(0.0f);
					myNPCList[i]->setRightLeg(0.0f);
					myNPCList[i]->setCharacterState(STATE_ACTIVE);
				}
				myNPCList[i]->setZpos((myNPCList[i]->getZpos())-(myNPCList[i]->getmoveSpd()*float(dt)));
			}

		}
	}
}
void SceneSP::UpdateCustomer(double dt)
{
	for(unsigned int i = 0; i< myNPCList.size(); ++i)
	{
		for(unsigned int j = 0; j< myNPCList.size(); ++j)
		{
			if((myNPCList[i]->getCharacterJob() == CUSTOMER && myNPCList[i]->getCharacterState() == STATE_ACTIVE)
				&&(myNPCList[j]->getCharacterJob() == CASHIER && myNPCList[j]->getCharacterState() == STATE_ACTIVE)
				&&((myNPCList[i]->getXpos()) < (myNPCList[j]->getXpos()+1) && (myNPCList[i]->getXpos()) > (myNPCList[j]->getXpos()-1)))
			{
				myNPCList[i]->setLeftArm(WalkingNpcInitArm);
				myNPCList[i]->setRightArm(-WalkingNpcInitArm);
				if(i_CashierAct==LOOKATCUSTOMER)
				{
					myNPCList[j]->setLeftArm(WalkingNpcInitArm);
					myNPCList[j]->setRightArm(-WalkingNpcInitArm);
					if(CustomerinteractionTimer > 10.0f)
					{
						CustomerinteractionTimer = 0;
						i_CashierAct = LOOKATITEM;
					}
				}
				if(i_CashierAct==LOOKATITEM)
				{
					myNPCList[j]->setLeftArm(WalkingNpcInitArm);
					myNPCList[j]->setRightArm(-WalkingNpcInitArm);
					myNPCList[j]->setYRotation(-20.0f);
					if(CustomerinteractionTimer > 10.0f)
					{
						CustomerinteractionTimer = 0;
						i_CashierAct = LOOKATSCREEN;
					}
				}
				if(i_CashierAct==LOOKATSCREEN)
				{
					myNPCList[j]->setLeftArm(WalkingNpcInitArm);
					myNPCList[j]->setRightArm(-WalkingNpcInitArm);
					myNPCList[j]->setYRotation(20.0f);
					if(CustomerinteractionTimer > 10.0f)
					{
						CustomerinteractionTimer = 0;
						i_CashierAct = LOOKATCUSTOMER;
						myNPCList[i]->setCharacterState(STATE_FORWARD);
						myNPCList[j]->setCharacterState(STATE_IDLE);
					}
				}
			}
		}
	}

	for(unsigned int i = 0; i< myNPCList.size(); ++i)
	{
		for(unsigned int j = 0; j< myNPCList.size(); ++j)
		{
			if((myNPCList[i]->getCharacterJob() == CUSTOMER && myNPCList[i]->getCharacterState() == STATE_FORWARD)
				&&(myNPCList[j]->getCharacterJob() == CASHIER))
			{
				myNPCList[i]->setAnimationType(WALKING);
				myNPCList[i]->setmoveSpd(5.0f);
				myNPCList[i]->setYRotation(90.f);
				myNPCList[i]->setXpos((myNPCList[i]->getXpos())+(2*float(dt)));
				if(myNPCList[i]->getXpos() >= (myNPCList[j]->getXpos()+5.f) && myNPCList[i]->getXpos() <= (myNPCList[j]->getXpos()+8.f))
				{
					myNPCList[i]->setCharacterState(STATE_RIGHT);
				}
			}
			if((myNPCList[i]->getCharacterJob() == CUSTOMER && myNPCList[i]->getCharacterState() == STATE_RIGHT)
				&&(myNPCList[j]->getCharacterJob() == CASHIER))
			{
				myNPCList[i]->setAnimationType(WALKING);
				myNPCList[i]->setmoveSpd(5.0f);
				myNPCList[i]->setYRotation(180);
				myNPCList[i]->setZpos(myNPCList[i]->getZpos() - (2*float(dt)));
				if(myNPCList[i]->getZpos() >= (myNPCList[j]->getZpos()-9.f) && myNPCList[i]->getZpos() <= (myNPCList[j]->getZpos()-8.f))
				{
					myNPCList[i]->setCharacterState(STATE_LEFT);
				}
			}
			if((myNPCList[i]->getCharacterJob() == CUSTOMER && myNPCList[i]->getCharacterState() == STATE_LEFT)
				&&(myNPCList[j]->getCharacterJob() == CASHIER))
			{
				myNPCList[i]->setAnimationType(WALKING);
				myNPCList[i]->setmoveSpd(5.0f);
				myNPCList[i]->setYRotation(90);
				myNPCList[i]->setXpos((myNPCList[i]->getXpos())+(2*float(dt)));
				if(myNPCList[i]->getXpos() >= 23.f && myNPCList[i]->getXpos() <= 25.f)
				{
					myNPCList[i]->setCharacterState(STATE_BACKWARD);
				}
			}
			if((myNPCList[i]->getCharacterJob() == CUSTOMER && myNPCList[i]->getCharacterState() == STATE_BACKWARD)
				&&(myNPCList[j]->getCharacterJob() == CASHIER))
			{
				myNPCList[i]->setAnimationType(WALKING);
				myNPCList[i]->setmoveSpd(5.0f);
				myNPCList[i]->setYRotation(180);
				myNPCList[i]->setZpos((myNPCList[i]->getZpos())-(2*float(dt)));
				if(myNPCList[i]->getZpos() >= -131 && myNPCList[i]->getZpos() <= -129)
				{
				   myNPCList[i]->setCharacterState(STATE_INTOBUILDING);
				}
			}
						if((myNPCList[i]->getCharacterJob() == CUSTOMER && myNPCList[i]->getCharacterState() == STATE_INTOBUILDING)
				&&(myNPCList[j]->getCharacterJob() == CASHIER))
			{
				myNPCList[i]->setAnimationType(WALKING);
				myNPCList[i]->setmoveSpd(5.0f);
				myNPCList[i]->setYRotation(90);
				myNPCList[i]->setXpos((myNPCList[i]->getXpos())+(2*float(dt)));
				if(myNPCList[i]->getXpos() >= 74 && myNPCList[i]->getXpos() <= 76)
				{
					myNPCList[i]->setCharacterState(STATE_REACTIVATE);
				}//
			}

			if(myNPCList[i]->getCharacterJob() == CUSTOMER && myNPCList[i]->getCharacterState() == STATE_IDLE)
			{
				myNPCList[i]->setYRotation(180.0f);
				if(myNPCList[j]->getCharacterJob() == CASHIER && myNPCList[j]->getCharacterState() == STATE_IDLE)
				{
					if (((myNPCList[i]->getZpos() - myNPCList[j]->getZpos()) <= 7) && ((myNPCList[i]->getXpos()) < (myNPCList[j]->getXpos()+1) && (myNPCList[i]->getXpos()) > (myNPCList[j]->getXpos()-1)) )
					{
						myNPCList[i]->setAnimationType(IDLE);
				        myNPCList[i]->setLeftLeg(0.0f);
				        myNPCList[i]->setRightLeg(0.0f);
						myNPCList[j]->setCharacterState(STATE_ACTIVE);
						myNPCList[i]->setCharacterState(STATE_ACTIVE);
					}
					else if(((myNPCList[i]->getZpos() - myNPCList[j]->getZpos()) >= 7) && ((myNPCList[i]->getXpos()) < (myNPCList[j]->getXpos()+1) && (myNPCList[i]->getXpos()) > (myNPCList[j]->getXpos()-1)))
					{
						myNPCList[i]->setAnimationType(WALKING);
						myNPCList[i]->setmoveSpd(1.0f);
						myNPCList[i]->setZpos((myNPCList[i]->getZpos())-(myNPCList[i]->getmoveSpd()*float(dt)));
					}
				}
			myNPCList[i]->setAnimationType(IDLE);
			myNPCList[i]->setLeftLeg(0.0f);
			myNPCList[i]->setRightLeg(0.0f);
			}
		}
	}
}
void SceneSP::UpdateChattingman(double dt)
{
	static int counter = 0;
	static float Zcon = 0;
	static float Xcon = 0;
	for(unsigned int i = 0; i< myNPCList.size(); ++i)
	{
		if(myNPCList[i]->getCharacterJob() == IDLE_GUY)
			myNPCList[i]->setYRotation(180.0f);
		if(myNPCList[i]->getCharacterJob() == CHATTING_GUY)
		{
			if(myNPCList[i]->getCharacterState() == STATE_IDLE)
			{
				myNPCList[i]->setLeftLeg(0.0f);//reset leg rotations
				myNPCList[i]->setRightLeg(0.0f);
				myNPCList[i]->setAnimationType(IDLE);
				Zcon = myNPCList[i]->getZpos();
				Xcon = myNPCList[i]->getXpos();
				if(myNPCList[i]->getNPCTimer() > NPCLookLimiter)
				{
					myNPCList[i]->setNPCTimer(0.0f);
					myNPCList[i]->setYRotation(myNPCList[i]->getYRotation()+180.0f);
					myNPCList[i]->setCharacterState(STATE_BACKWARD);
					if(counter == 1)
					{
						myNPCList[i]->setYRotation(90);
						myNPCList[i]->setCharacterState(STATE_LEFT);
					}
				}
			}
			else
				myNPCList[i]->setAnimationType(WALKING);
			if(myNPCList[i]->getCharacterState() == STATE_BACKWARD)
			{
				if(myNPCList[i]->getZpos() < Zcon - 47)
				{
					myNPCList[i]->setYRotation(myNPCList[i]->getYRotation()+90);
					myNPCList[i]->setCharacterState(STATE_RIGHT);
					counter = 1;
				}
				myNPCList[i]->setZpos(myNPCList[i]->getZpos()-(myNPCList[i]->getmoveSpd() * float(dt)));
			}
			if(myNPCList[i]->getCharacterState() == STATE_RIGHT)
			{
				if(myNPCList[i]->getXpos() < Xcon - 11)
				{
					myNPCList[i]->setCharacterState(STATE_IDLE);
					myNPCList[i]->setNPCTimer(0.0f);
				}
				myNPCList[i]->setXpos(myNPCList[i]->getXpos()-(myNPCList[i]->getmoveSpd() * float(dt)));
			}
			if(myNPCList[i]->getCharacterState() == STATE_LEFT)
			{
				if(myNPCList[i]->getXpos() > Xcon + 11)
				{
					myNPCList[i]->setYRotation(myNPCList[i]->getYRotation()-90.f);
					myNPCList[i]->setCharacterState(STATE_FORWARD);
				}
				myNPCList[i]->setXpos(myNPCList[i]->getXpos()+(myNPCList[i]->getmoveSpd() * float(dt)));
			}
			if(myNPCList[i]->getCharacterState() == STATE_FORWARD)
			{
				if(myNPCList[i]->getZpos() > Zcon+47)
				{
					myNPCList[i]->setYRotation(0);
					myNPCList[i]->setCharacterState(STATE_IDLE);
					myNPCList[i]->setNPCTimer(0.0f);
					myNPCList[i]->setXpos(11.0f);
					myNPCList[i]->setZpos(25.0f);
					counter = 0;
				}
				myNPCList[i]->setZpos(myNPCList[i]->getZpos()+(myNPCList[i]->getmoveSpd() * float(dt)));
			}
		}
	}
}
void SceneSP::UpdateShoppers(double dt)
{
	for(unsigned int i = 0; i < myNPCList.size(); ++i)
	{
		if(myNPCList[i]->getCharacterJob() == LOOKING_GUY)
		{
			for(unsigned int j = 0; j < myNPCList.size(); ++j)
			{
				if(myNPCList[j]->getCharacterJob() == CUSTOMER && myNPCList[j]->getCharacterState() == STATE_REACTIVATE)
				{
					myNPCList[j]->setXpos(-75.f);
					myNPCList[j]->setYpos(0.f);
					myNPCList[j]->setZpos(195.f);
					myNPCList[j]->setAnimationType(IDLE);
					myNPCList[j]->setmoveSpd(0.f);
					myNPCList[j]->setLeftLeg(0.f);
					myNPCList[j]->setRightLeg(0.f);
					myNPCList[j]->setCharacterJob(SHOPPERS);
					myNPCList[j]->setCharacterState(STATE_ACTIVE);
				}
				if(myNPCList[j]->getCharacterJob() == SHOPPERS && myNPCList[j]->getCharacterState() == STATE_ACTIVE)
				{
					myNPCList[j]->setmoveSpd(5.0f);
					myNPCList[j]->setAnimationType(WALKING);
					myNPCList[j]->setYRotation(90.f);
					myNPCList[j]->setXpos((myNPCList[j]->getXpos())+(5*float(dt)));
					if(((myNPCList[j]->getXpos()) < -19.f) && ((myNPCList[j]->getXpos()) > -21.f))
					{
						myNPCList[j]->setAnimationType(IDLE);
						myNPCList[j]->setmoveSpd(0.0f);
						myNPCList[j]->setCharacterState(STATE_FORWARD);
					}
				}
				if(myNPCList[j]->getCharacterJob() == SHOPPERS && myNPCList[j]->getCharacterState() == STATE_FORWARD)
				{
					myNPCList[j]->setmoveSpd(5.0f);
					myNPCList[j]->setAnimationType(WALKING);
					myNPCList[j]->setYRotation(180.f);
					myNPCList[j]->setZpos((myNPCList[j]->getZpos())-(5*float(dt)));
					if(((myNPCList[j]->getZpos()) < 24.f) && ((myNPCList[j]->getZpos()) > 22.f))
					{
						myNPCList[j]->setAnimationType(IDLE);
						myNPCList[j]->setmoveSpd(0.0f);
						myNPCList[j]->setCharacterState(STATE_RIGHT);
					}
				}
				if(myNPCList[j]->getCharacterJob() == SHOPPERS && myNPCList[j]->getCharacterState() == STATE_RIGHT)
				{
					myNPCList[j]->setmoveSpd(5.0f);
					myNPCList[j]->setAnimationType(WALKING);
					myNPCList[j]->setYRotation(90);
					myNPCList[j]->setXpos((myNPCList[j]->getXpos())+(5.f*float(dt)));
					if((myNPCList[j]->getXpos() > 30.f) && (myNPCList[j]->getXpos() < 32.f))
					{
						myNPCList[j]->setAnimationType(IDLE);
						myNPCList[j]->setmoveSpd(0.0f);
						myNPCList[j]->setCharacterState(STATE_BACKWARD);
					}
				}
				if(myNPCList[j]->getCharacterJob() == SHOPPERS && myNPCList[j]->getCharacterState() == STATE_BACKWARD)
				{
					myNPCList[j]->setmoveSpd(5.0f);
					myNPCList[j]->setAnimationType(WALKING);
					myNPCList[j]->setYRotation(180.f);
					myNPCList[j]->setZpos((myNPCList[j]->getZpos())-(5*float(dt)));
					if((myNPCList[j]->getZpos() > 10.f) && (myNPCList[j]->getZpos() < 12.f))
					{
						myNPCList[j]->setAnimationType(IDLE);
						myNPCList[j]->setmoveSpd(0.0f);
						myNPCList[j]->setCharacterState(STATE_LEFT);
					}
				}
				if(myNPCList[j]->getCharacterJob() == SHOPPERS && myNPCList[j]->getCharacterState() == STATE_LEFT)
				{
					myNPCList[j]->setmoveSpd(5.0f);
					myNPCList[j]->setAnimationType(WALKING);
					myNPCList[j]->setYRotation(270);
					myNPCList[j]->setXpos((myNPCList[j]->getXpos())-(5*float(dt)));
					if((myNPCList[j]->getXpos() > -16.3f) && (myNPCList[j]->getXpos() < -15.7f))
					{
						myNPCList[j]->setAnimationType(IDLE);
						myNPCList[j]->setmoveSpd(0.0f);
						myNPCList[j]->setCharacterState(STATE_IDLE);
					}
				}
				if(myNPCList[j]->getCharacterJob() == SHOPPERS && myNPCList[j]->getCharacterState() == STATE_IDLE)
				{
					myNPCList[j]->setmoveSpd(5.0f);
					myNPCList[j]->setAnimationType(WALKING);
					myNPCList[j]->setYRotation(180);
					myNPCList[j]->setZpos((myNPCList[j]->getZpos())-(5.f*float(dt)));
					if(((myNPCList[j]->getZpos()) < -9.f) && ((myNPCList[j]->getZpos()) > -10.f))
					{
						myNPCList[j]->setAnimationType(IDLE);
						myNPCList[j]->setmoveSpd(0.0f);
						myNPCList[j]->setLeftArm(90.0f);
						myNPCList[j]->setRightArm(270.0f);
						myNPCList[j]->setCharacterJob(CUSTOMER);
						myNPCList[j]->setCharacterState(STATE_IDLE);
					}
				}
			}
		}
	}
}
void SceneSP::UpdateLegAnimation(double dt)
{
	for(unsigned int i = 0; i< myNPCList.size(); ++i)
	{
		if(myNPCList[i]->getAnimationType() == WALKING)
		{
			if(myNPCList[i]->getLeftLeg()>(maxlegRot))
				myNPCList[i]->setlegRotDir(true);
			if(myNPCList[i]->getLeftLeg()<(-maxlegRot))
				myNPCList[i]->setlegRotDir(false);
			if(myNPCList[i]->getlegRotDir() == false)
				myNPCList[i]->setLeftLeg(myNPCList[i]->getLeftLeg() + (myNPCList[i]->getmoveSpd() * spdMod * float(dt)));
			else
				myNPCList[i]->setLeftLeg(myNPCList[i]->getLeftLeg() - (myNPCList[i]->getmoveSpd() * spdMod * float(dt)));
			if(myNPCList[i]->getlegRotDir() == false)
				myNPCList[i]->setRightLeg(myNPCList[i]->getRightLeg() - (myNPCList[i]->getmoveSpd() * spdMod * float(dt)));
			else
				myNPCList[i]->setRightLeg(myNPCList[i]->getRightLeg() + (myNPCList[i]->getmoveSpd() * spdMod * float(dt)));
		}
	}
}
void SceneSP::UpdateCage(double dt)
{
	if(Application::IsKeyPressed('E') && ((camera.position.x > 42.0f && camera.position.x < 50.0f) && (camera.position.z < -10.0f && camera.position.z > -30.0f)))
	{
		diffX = camera.position.x-0.0f;
		diffZ = camera.position.z-(65.0f);
		diffY = camera.position.y-(-30.0f);
		camera.position.y = -30.0f;
		camera.target.y -= diffY;
		camera.position.x = 0.0f;
		camera.target.x -= diffX;
		camera.position.z = 65.0f;
		camera.target.z -= diffZ;
		diffX = diffZ = diffY = 0.0f;
		caged = true;
		if(easterTimer > easterLimiter)
		{
			easterTimer = resetValue;
			if(!easter.openFromFile(soundFXArray[2]))
			{
				std::cout << "ERROR OPENING MUSIC FILE" << std::endl;
			}
			easter.setLoop(false);
			easter.setVolume(50.0f);
			easter.play();
		}
		if(!getCaged)
		{
			getCaged = true;
			getCounter++;
		}
	}
	if(caged)
	{
		cagedPos += 15 * float(dt);
		if(cagedPos > 60)
		{
			caged = false;
			cagedPos = -75.0f;
			diffX = camera.position.x-(0.0f);
			diffZ = camera.position.z-(100.0f);
			diffY = camera.position.y-(4.5f);
			camera.position.y = 4.5f;
			camera.target.y -= diffY;
			camera.position.x = 0.0f;
			camera.target.x -= diffX;
			camera.position.z = 100.0f;
			camera.target.z -= diffZ;
			diffX = diffZ = diffY = 0.0f;
		}
	}
}
void SceneSP::UpdateGaben(double dt)
{
	if(Application::IsKeyPressed('G')&&summonG == 0)
		summonG++;
	if(Application::IsKeyPressed('A')&&summonG == 1)
		summonG++;
	if(Application::IsKeyPressed('B')&&summonG == 2)
		summonG++;
	if(Application::IsKeyPressed('E')&&summonG == 3)
		summonG++;
	if(Application::IsKeyPressed('N')&&summonG == 4)
	{
		gabed = true;
		if(!easter.openFromFile(soundFXArray[0]))
		{
			std::cout << "ERROR OPENING MUSIC FILE" << std::endl;
		}
		easter.setLoop(false);
		easter.setVolume(50.0f);
		easter.play();
		if(!getGabed)
		{
			getGabed = true;
			getCounter++;
		}
	}
	if(gabed)
		moveG += 20 * float(dt);
	if(moveG > 95)
	{
		summonG = 0;
		moveG = 0.0f;
		gabed = false;
	}
}
void SceneSP::UpdateTroll(double dt)
{
	if((camera.position.x > 31 && camera.position.x < 35) && (camera.position.z > -28 && camera.position.z < -24))
	{
		if((camera.position.y > 10 && reversed == false) && Application::IsKeyPressed('E'))
		{
			if(easterTimer > easterLimiter)
			{
				easterTimer = resetValue;
				if(!easter.openFromFile(soundFXArray[3]))
				{
					std::cout << "ERROR OPENING MUSIC FILE" << std::endl;
				}
				easter.setLoop(false);
				easter.setVolume(50.0f);
				easter.play();
			}
			easterTimer = 0.0f;
			reversed = true;
			reverseTimer = 0.0f;
			if(!getTrolled)
			{
				getTrolled = true;
				getCounter++;
			}
		}
	}
	if(reverseTimer > reverseLimiter)
		reversed = false;
}
void SceneSP::UpdateMiscEasteregg(double dt)
{
	if(((camera.position.x > 31 && camera.position.x < 35) && (camera.position.z > -28 && camera.position.z < -24)) ||
		((camera.position.x > 42.0f && camera.position.x < 50.0f) && (camera.position.z < -10.0f && camera.position.z > -30.0f)) ||
		((camera.position.x > 36.0f && camera.position.x < 39.0f) && (camera.position.z < -6.0f && camera.position.z > -10.0f)) ||
		((camera.position.x > -29.5f && camera.position.x < -28.0f) && (camera.position.z < -20.0f && camera.position.z > -22.5f))//rroll
		)
	{
		inRange = true;//display interaction text
	}
	else
		inRange = false;
	if((camera.position.x > 36.0f && camera.position.x < 39.0f) && (camera.position.z < -6.0f && camera.position.z > -10.0f) && Application::IsKeyPressed('E'))
	{//no time easter egg
		if(easterTimer > easterLimiter)
		{
			easterTimer = 0.0f;
			if(!easter.openFromFile(soundFXArray[1]))
			{
				std::cout << "ERROR OPENING MUSIC FILE" << std::endl;
			}
			easter.setLoop(false);
			easter.setVolume(50.0f);
			easter.play();
			if(!getTimed)
			{
				getTimed = true;
				getCounter++;
			}
		}
	}
	if((camera.position.x > -29.5f && camera.position.x < -28.0f) && (camera.position.z < -20.0f && camera.position.z > -22.5f) && Application::IsKeyPressed('E'))
	{
		if(easterTimer > easterLimiter)
		{
			easterTimer = 0.0f;
			if(!easter.openFromFile(soundFXArray[4]))
			{
				std::cout << "ERROR OPENING MUSIC FILE" << std::endl;
			}
			easter.setLoop(false);
			easter.setVolume(50.0f);
			easter.play();
			if(!getRicked)
			{
				getRicked = true;
				getCounter++;
			}
		}
	}
}
void SceneSP::RenderEasteregg()
{
	if(ptrplayer->getCharacterJob() == PLAY_EASTER_EGG)
	{
		RenderCage();
		RenderTroll();
		RenderMiscEastereggs();
		RenderTextOnScreen(meshList[GEO_TEXT], "Easter eggs found:"+s_easter_counter+"/"+s_easter_count, Color(1, 0, 0), 2.5,0, 20);
		if(inRange)
			RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to interact",Color(0,1,0),2,1,16);
		if(winEaster)
		{
			for(int i = 0;i<10;i++)
			{
				RenderTextOnScreen(meshList[GEO_TEXT],winEasterArray[i],Color(0.f+0.1f*i,0,1.f-0.1f*i),3.f,2+0.8f*i,9.7f);
				RenderTextOnScreen(meshList[GEO_TEXT],winEasterArray1[i],Color(0.f,1.f-0.1f*i,0.f+0.1f*i),3.f,10.f+0.8f*i,9.7f);
				RenderTextOnScreen(meshList[GEO_TEXT],winEasterArray2[i],Color(1.f-0.1f*i,0+0.1f*i,0),3.f,18.f+0.8f*i,9.7f);
			}
			RenderTextOnScreen(meshList[GEO_TEXT],"Press 'enter' to continue",Color(1,1,0),2,8,13);
		}
	}
}
void SceneSP::RenderMiscEastereggs()
{
	if(gabed)
		RenderTGAUI(meshList[GEO_GABEN], 1, moveG, 30);
	modelStack.PushMatrix();
	modelStack.Translate(38.7f, 0.0f, -5.0f);
	RenderMesh(meshList[GEO_EASTEREGG_4], toggleLight);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-29.5f, 17.0f, -26.0f);
	RenderMesh(meshList[GEO_EASTEREGG_5], toggleLight);
	modelStack.PopMatrix();
}
void SceneSP::RenderUI()
{
	//RenderText(meshList[GEO_UI_SCREEN],"",Color(),1,0,0);
	RenderTGAUI(meshList[GEO_UI_SCREEN],1,40,20);
	if(b_isWithinInteractionItem) //If player is able to pick up
	{
		RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to pick up " +s_item_name,Color(0,1,0),2,1,16);
	}
	//If player is inspecting the item
	if(b_inspection)
	{
		RenderTextOnScreen(meshList[GEO_TEXT],"Price of " + ptrplayer->getItem(inventoryPointing)->getName()+": $" +s_item_price,Color(0,1,0),2,1,7);
	}
	//If player is within return point zone and holding an item
	if(checkReturnPoint() && (ptrplayer->getItem(inventoryPointing)->getName() != ptrEmpty->getName()))
	{
		RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to return " + ptrplayer->getItem(inventoryPointing)->getName(),Color(0,1,0),2,1,6);
	}
	//If player is within Cashier zone and holding an item
	if(b_isWithinPayingCashier && (ptrplayer->getItem(inventoryPointing)->getName() != ptrEmpty->getName()))
	{
		RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to pay for " + ptrplayer->getItem(inventoryPointing)->getName(),Color(0,1,0),2,1,6);
	}
	//If treasure hunting mode chosen
	if(ptrplayer->getCharacterJob() == PLAY_TREASURE_HUNT)
	{
		for(int i = 0; i<i_total_items_to_find;++i)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], myCheckList[i]->getName(), Color(0, 1, 0), 2.f,0.f, 3.f+i);
		}
	}
	RenderTGAInventory(meshList[GEO_ITEM_SELECT],5.f,22.5f+(inventoryPointing*5.0f),2.5f);
	RenderTextOnScreen(meshList[GEO_TEXT], "Money: $"+ s_money, Color(0, 1, 0), 3.f,0.f, 19.f);
	RenderTextOnScreen(meshList[GEO_TEXT], s_UI_Play_Mode[ptrplayer->getCharacterJob()] + " mode",Color(0,1,0),2.f,0.f,27.f);
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS: "+ s_fps, Color(0, 1, 0), 3.f,0.f, 1.f);
	RenderTextOnScreen(meshList[GEO_TEXT], "(X,Y,Z): "+ s_position, Color(0, 1, 0), 2, 0, 0);
	RenderTugofwarUI();
	RenderDrunkmanUI();
}
void SceneSP::RenderTugofwarUI()
{
	if(win)
		RenderTextOnScreen(meshList[GEO_TEXT], "YOU WIN!!!!", Color(0, 1, 0), 4, 5, 5);
	if(lose)
		RenderTextOnScreen(meshList[GEO_TEXT], "YOU LOSE!!!!", Color(0, 1, 0), 4, 5, 5);
	if(showTuginstruction)
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'space' to tug!", Color(0, 1, 0), 3, 3, 9);
	if((((camera.position.z > -2 && camera.position.z < 1.1) && (camera.position.x > 7 && camera.position.x < 13)) &&
		IsIntugofwar == false) && camera.position.y <10
		)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to", Color(0, 1, 0), 3, 8, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], "partake in a Tug-of-war!", Color(0, 1, 0), 3, 1, 9);
	}
}
void SceneSP::RenderDrunkmanUI()
{
	if((i_drunkmanAct == DRUNKIDLE)	
		&&(camera.position.z > 26.0f && camera.position.z < 28.0f)
		&&(camera.position.x > -5.0f && camera.position.x < -2.5f)
		&&(camera.position.y > 16.0f && camera.position.y < 25.0f))
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to", Color(0, 1, 0), 3, 8, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], "carry the drunk man", Color(0, 1, 0), 3, 3, 9);
		RenderTextOnScreen(meshList[GEO_TEXT], "to the entrance", Color(0, 1, 0), 3, 6, 8);
	}

	if(i_drunkmanAct == DRUNKCARRY
		&&(camera.position.z < 45.0f && camera.position.z > 15.0f)
		&&(camera.position.x > -30.0f  && camera.position.x < -10.0f)
		&&(camera.position.y > 1.0f  && camera.position.y < 16.0f))
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to", Color(0, 1, 0), 3, 8, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], "throw the drunk man", Color(0, 1, 0), 3, 3, 9);
		RenderTextOnScreen(meshList[GEO_TEXT], "out of the store", Color(0, 1, 0), 3, 6, 8);
	}
}
void SceneSP::Render()
{
	//clear depth and color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 MVP;
	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	if(lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	//RenderMesh(meshList[GEO_AXES],false);

	switch(i_menuHandle)
	{

	case MAIN_MENU:
		//do menu here
		RenderTGAUI(meshList[GEO_MAIN_MENU_TITLE], 3, 40, 40);
		RenderMainMenu();
		break;


		//Do sub menu here
	case SUB_MENU:
		RenderTGAUI(meshList[GEO_MAIN_MENU_TITLE], 3, 40, 40);
		RenderSubMenu();
		break;

		//Do instruction Menu here
	case INSTRUCTION_MENU:
		RenderTGAUI(meshList[GEO_MAIN_MENU_TITLE], 3, 40, 40);
		RenderInstructionMenu();
		break;

		//Do win lose menu here
	case WIN_LOSE_MENU:
		RenderTGAUI(meshList[GEO_MAIN_MENU_TITLE], 3, 40, 40);
		RenderWinLoseMenu();
		break;

		//Do pause menu here
	case PAUSE_MENU:
		RenderTGAUI(meshList[GEO_MAIN_MENU_TITLE], 3, 40, 40);
		RenderPauseMenu();
		break;
	case GAME_PLAYING:
		RenderHand();
		RenderSkyBox();		//Renders out Skybox
		RenderCharacters();//Render out characters
		RenderItem();		//Renders out items
		RenderTug();
		RenderBeerstand();
		RenderBuilding();
		RenderFerrisWheel();
		RenderSupermarket();//Renders out Supermarket
		RenderEasteregg();
		RenderUI();			//Renders out UI
		RenderInventory();	//Render inventory after UI to place above
		break;
	}
}
void SceneSP::RenderSkyBox()
{	
	modelStack.PushMatrix();
		modelStack.Translate(camera.position.x, camera.position.y-world_size/10, camera.position.z);

		modelStack.PushMatrix();
			modelStack.Scale(world_size, world_size, world_size);
			modelStack.Translate(0, 0.495f, -0.495f);
			RenderMesh(meshList[GEO_FRONT], false);
		modelStack.PopMatrix();


		modelStack.PushMatrix();
			modelStack.Scale(world_size, world_size, world_size);
			modelStack.Translate(0, 0.495f, 0.495f);
			modelStack.Rotate(180, 0 , 1, 0);
			RenderMesh(meshList[GEO_BACK], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Scale(world_size, world_size, world_size);
			modelStack.Translate(0, 0.965f, 0);
			modelStack.Rotate(90, 1 ,0 ,0);
			RenderMesh(meshList[GEO_TOP], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Scale(world_size, world_size, world_size);	
			modelStack.Translate(-0.495f, 0.495f, 0); 
			modelStack.Rotate(90, 0 , 1, 0);
			RenderMesh(meshList[GEO_LEFT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Scale(world_size, world_size, world_size); 
			modelStack.Translate(0.495f,0.495f, 0);	
			modelStack.Rotate(-90, 0 , 1, 0);
			RenderMesh(meshList[GEO_RIGHT], false);
		modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(0, -0.05f, 0);
		modelStack.Scale( world_size, world_size, world_size);
		modelStack.Rotate(-90, 1 ,0, 0);
		RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

}
void SceneSP::RenderElevator()
{
	modelStack.PushMatrix();
		modelStack.Translate(RenderElevatorPosX, elevatorY, RenderElevatorPosZ);
		RenderMesh(meshList[GEO_ELEVATOR], toggleLight);
		modelStack.PushMatrix();

		modelStack.Translate(ElevatorDoorPosX, elevatorDoorY,ElevatorDoorPosZ);
		RenderMesh(meshList[GEO_ELEVATORDOOR], toggleLight);
		modelStack.PopMatrix();
	modelStack.PopMatrix();     

}
void SceneSP::RenderFence()
{
	modelStack.PushMatrix();

		modelStack.Translate(-22.9f, 2.5f, -26.f);
		RenderMesh(meshList[GEO_FENCE], toggleLight);

		modelStack.PushMatrix();
			modelStack.Translate(0.0f, 0.0f, 4.9f);
			RenderMesh(meshList[GEO_FENCE], toggleLight);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(0.0f, 0.0f, 10.f);
			RenderMesh(meshList[GEO_FENCE], toggleLight);
		modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-30.5f, 2.5f, -21.1f);
		RenderMesh(meshList[GEO_FENCE], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-30.5f, 2.5f, -16.0f);
		RenderMesh(meshList[GEO_FENCE], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-12.9f, 2.5f, -21.1f);
		RenderMesh(meshList[GEO_FENCE], toggleLight);
		modelStack.PushMatrix();
			modelStack.Translate(0.0f, 0.0f, 5.0f);
			RenderMesh(meshList[GEO_FENCE], toggleLight);
		modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-2.9f, 2.5f, -21.1f);
		RenderMesh(meshList[GEO_FENCE], toggleLight);
		modelStack.PushMatrix();
			modelStack.Translate(0.0f, 0.0f, 5.0f);
			RenderMesh(meshList[GEO_FENCE], toggleLight);
		modelStack.PopMatrix();
	modelStack.PopMatrix();
}
void SceneSP::RenderCashierTables()
{
	modelStack.PushMatrix();
		modelStack.Translate(-26.f, 0.f, -15.f);
		modelStack.Rotate(180,0,1,0);
		RenderMesh(meshList[GEO_CASHIER], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-16.f, 0.f, -15.f);
	    modelStack.Rotate(180,0,1,0);
		RenderMesh(meshList[GEO_CASHIER], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-6.f, 0.f, -15.f);
		modelStack.Rotate(180,0,1,0);
		RenderMesh(meshList[GEO_CASHIER], toggleLight);
	modelStack.PopMatrix();
}
void SceneSP::RenderTrolleys()
{
	for(float i=0; i<8;++i)
	{
		modelStack.PushMatrix();
			modelStack.Translate(-37.f, 0.2f, 13.f+(i*2));
			modelStack.Rotate(0,0,1,0);
			RenderMesh(meshList[GEO_TROLLEY], toggleLight);
		modelStack.PopMatrix();
	}

	if(false)
	{
		modelStack.PushMatrix();
			modelStack.Translate(camera.position.x,0,camera.position.z);
		{
			modelStack.PushMatrix();
				modelStack.Rotate((180+trolleyrotation),0,1,0);
				modelStack.Translate(0,0,3.5);
				RenderMesh(meshList[GEO_TROLLEY], toggleLight);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}

}
void SceneSP::RenderHand()
{
	modelStack.PushMatrix();
	    modelStack.Translate(camera.position.x,camera.position.y,camera.position.z);
	{
		/*=============================
		Put item on hand
		=============================*/
		modelStack.PushMatrix();
			modelStack.Rotate((180+handrotationleftandright),0,1,0);
			modelStack.Translate(-0.2f,-4.5f,-1.f+handtranslation);
			RenderMesh(meshList[GEO_HANDS], toggleLight);
			if(ptrInvSelect->getName() != emptyItem.getName() && !(Application::IsKeyPressed('R')))
			{
			modelStack.PushMatrix();
				modelStack.Translate(-0.6f,3.5f,3.f);
				RenderMesh(meshList[ptrInvSelect->getGeoType()],toggleLight);
			modelStack.PopMatrix();

			}
		modelStack.PopMatrix();

		}
	modelStack.PopMatrix();

	if(b_inspection)
	{
		modelStack.PushMatrix();
			modelStack.Translate(camera.target.x,camera.target.y-0.2f,camera.target.z);
			modelStack.Rotate(handrotationleftandright+itemYrotation,0,1,0);
			modelStack.Rotate(itemXrotation,1,0,0);
		modelStack.Scale(0.5f,0.5f,0.5f);
		
		if(ptrInvSelect->getName() != emptyItem.getName())
		{
			RenderMesh(meshList[ptrInvSelect->getGeoType()],toggleLight);
		}
		modelStack.PopMatrix();
	}
}
void SceneSP::RenderTGAUI(Mesh* mesh, float size, float x , float y)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(x, y, 0);
	modelStack.Scale(40, 40,40);

	RenderMesh(mesh,false);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}
void SceneSP::RenderTGAInventory(Mesh* mesh,float size, float x , float y)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size,size);

	RenderMesh(mesh,false);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}
void SceneSP::RenderCharacter(CNpc* npc)
{
	modelStack.PushMatrix();
		modelStack.Translate(npc->getXpos() , npc->getYpos(), npc->getZpos());//translate everything
		modelStack.Rotate(npc->getYRotation(),0,1,0);
		modelStack.Rotate(npc->getXRotation(),1,0,0);
		modelStack.Rotate(npc->getZRotation(),0,0,1);

		modelStack.PushMatrix();

			//head and body
			RenderMesh(meshList[npc->getHeadType()], toggleLight);

			//Left arm
			modelStack.PushMatrix();
				modelStack.Translate(0.3f , 0.f, 0.f);
				modelStack.Rotate(npc->getLeftArm(),0.f,1.f,0.f);
				RenderMesh(meshList[npc->getArmType()], toggleLight);
			modelStack.PopMatrix();
				//Right arm
			modelStack.PushMatrix();
				modelStack.Translate(-0.3f , 0.f, 0.f);
				modelStack.Rotate(npc->getRightArm(),0.f, 1.f,0.f);
				RenderMesh(meshList[npc->getArmType()], toggleLight);
			modelStack.PopMatrix();
			//leg and feet
			modelStack.PushMatrix();
				modelStack.Translate(0.2f, 2.3f, 0.f);
				modelStack.Rotate(npc->getLeftLeg(),1.f,0.f,0.f);
				RenderMesh(meshList[npc->getLegType()], toggleLight);
			modelStack.PopMatrix();
			//leg and feet 
			modelStack.PushMatrix();
				modelStack.Translate(-0.2f, 2.3f, 0.f);
				modelStack.Rotate(npc->getRightLeg(),1.f,0.f,0.f);
				RenderMesh(meshList[npc->getLegType()], toggleLight);
			modelStack.PopMatrix();

		modelStack.PopMatrix();
		
	modelStack.PopMatrix();
}
void SceneSP::RenderMainMenu()
{
	
	RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_START], Color(0, 1, 0), 2, 17, 15);
	RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_INSTRUCTIONS], Color(0, 1, 0), 2, 17, 14);
	RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_EXIT], Color(0, 1, 0), 2, 17, 13);
	if(selectionPointing == MENU_START)//If pointing at START button
	{
		RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_START], Color(1, 1, 0), 2, 17, 15);
	}
	if(selectionPointing == MENU_INSTRUCTIONS)//If pointing at START button
	{
		RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_INSTRUCTIONS], Color(1, 1, 0), 2, 17, 14);
	}
	if(selectionPointing == MENU_EXIT)//If pointing at START button
	{
		RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_EXIT], Color(1, 1, 0), 2, 17, 13);
	}
}
void SceneSP::RenderSubMenu()
{
	
	RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_FREE_ROAM], Color(0, 1, 0), 2, 17, 15);
	RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_TREASURE_HUNT], Color(0, 1, 0), 2, 17, 14);
	RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_EASTER_EGG_HUNT], Color(0, 1, 0), 2, 17, 13);
	if(selectionPointing == MENU_FREE_ROAM)//If pointing at START button
	{
		RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_FREE_ROAM], Color(1, 1, 0), 2, 17, 15);
	}
	if(selectionPointing == MENU_TREASURE_HUNT)//If pointing at START button
	{
		RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_TREASURE_HUNT], Color(1, 1, 0), 2, 17, 14);
	}
	if(selectionPointing == MENU_EASTER_EGG_HUNT)//If pointing at START button
	{
		RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_EASTER_EGG_HUNT], Color(1, 1, 0), 2, 17, 13);
	}
}
void SceneSP::RenderWinLoseMenu()
{
	
	if(b_is_Stealing)
	{
		RenderTextOnScreen(meshList[GEO_TEXT],"You stole items from the store!", Color(1, 0, 0), 2, 5, 13);
	}
	else
	{
		RenderTextOnScreen(meshList[GEO_TEXT],"You found all items from the store!", Color(0, 1, 0), 2, 3, 13);
	}
	RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_BACK], Color(1, 1, 0), 2, 12, 5);
}
void SceneSP::RenderInstructionMenu()
{
	RenderTextOnScreen(meshList[GEO_TEXT], "Arrow keys to look", Color(0, 1, 0), 2, 2, 20);
	RenderTextOnScreen(meshList[GEO_TEXT], "WASD to Move", Color(0, 1, 0), 2, 2, 19);
	RenderTextOnScreen(meshList[GEO_TEXT], "Press 'P' to pause", Color(0, 1, 0), 2, 2, 18);
	RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to interact with the world", Color(0, 1, 0), 2, 2, 17);
	RenderTextOnScreen(meshList[GEO_TEXT], "Press 'R' to inspect held item", Color(0, 1, 0), 2, 2, 16);
	RenderTextOnScreen(meshList[GEO_TEXT], "Use '1' to '8' for inventory select", Color(0, 1, 0), 2, 2, 15);
	RenderTextOnScreen(meshList[GEO_TEXT], "Press SHIFT to run",Color(0, 1, 0), 2, 2, 14);
	RenderTextOnScreen(meshList[GEO_TEXT], "Press Ctrl to crouch", Color(0, 1, 0), 2, 2, 13);
	RenderTextOnScreen(meshList[GEO_TEXT], "Press Esc to end application", Color(0, 1, 0), 2, 2, 10);


	RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_BACK], Color(1, 1, 0), 2, 12, 5);
}
void SceneSP::RenderPauseMenu()
{

	RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_RESUME], Color(0, 1, 0), 2, 12, 15);
	RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_BACK], Color(0, 1, 0), 2, 12, 14);
	if(selectionPointing == MENU_RESUME) //If pointing at Resume button
	{
		RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_RESUME], Color(1, 1, 0), 2, 12, 15);
	}
	if(selectionPointing == MENU_BACK)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_BACK], Color(1, 1, 0), 2, 12, 14);
	}
}
void SceneSP::RenderCharacters()
{
	for(unsigned int i = 0; i< myNPCList.size(); ++i)
	{
		if(myNPCList[i]->getActive()==true)
			RenderCharacter(myNPCList[i]);
	}
}
void SceneSP::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}
void SceneSP::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(0.5f + i * 1.0f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}
void SceneSP::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if(enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{	
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	//mesh->Render();

	if(mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render(); //this line should only be called once 
	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
void SceneSP::RenderSupermarket()
{
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_SUPERMARKET], toggleLight);
	RenderMesh(meshList[GEO_STORAGEANDOFFICE], toggleLight);
	RenderOffice();
	RenderStorage();
	RenderShelves();		//Render Shelves in Supermarket
	RenderSamplestand();	//Render Sample Food Stand in Supermarket
	RenderCashierTables();  //Render Cashier table in Supermarket
	RenderIceBox();         
	RenderMeatShelf();
	RenderFence();          //Render Fence in Supermarket
	RenderElevator();       //Render Elevator in Supermarket
	RenderTrolleys();       //Render Trolleys in Supermarket
	RenderReturnPoint();	//Render Return Point in Supermarket
	RenderATM();


	RenderDoors();			//Render Alpha Doors AFTER EVERYTHING in Supermarket

	modelStack.PopMatrix();
}
void SceneSP::RenderShelves()
{
	for(unsigned int i = 0; i< myContainerList.size(); ++i)
	{
		RenderShelves(myContainerList[i]);
	}

}
void SceneSP::RenderShelves(CContainer* container)
{
	modelStack.PushMatrix();
		modelStack.Translate(container->getXpos(),container->getYpos(),container->getZpos());
		modelStack.Rotate(container->getRotation(),0,1,0);
		RenderMesh(meshList[GEO_SHELF],toggleLight);
	modelStack.PopMatrix();
}
void SceneSP::RenderDoors()
{
	//Front doors
	modelStack.PushMatrix();
		modelStack.Translate(moveDoorFront, 0.0f, 0.0f);

		modelStack.PushMatrix();
			modelStack.Translate(-25.0f, 0.0f, 30.5f);
			RenderMesh(meshList[GEO_DOOR], toggleLight);
		modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-moveDoorFront, 0.0f, 0.0f);

		modelStack.PushMatrix();
			modelStack.Translate(-15.2f, 11.2f, 30.5f);
			modelStack.Rotate(180,0,0,1);
			RenderMesh(meshList[GEO_DOOR], toggleLight);
		modelStack.PopMatrix();

	modelStack.PopMatrix();
	//Back doors
	modelStack.PushMatrix();
		modelStack.Translate(moveDoorBack, 0.0f, 0.0f);
	
		modelStack.PushMatrix();
			modelStack.Translate(17.5f, 0.0f, -30.0f);
			RenderMesh(meshList[GEO_DOOR], toggleLight);
		modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-moveDoorBack, 0.0f, 0.0f);

		modelStack.PushMatrix();
			modelStack.Translate(27.3f, 11.2f, -30.0f);
			modelStack.Rotate(180,0,0,1);
			RenderMesh(meshList[GEO_DOOR], toggleLight);
		modelStack.PopMatrix();
	
	modelStack.PopMatrix();
}
void SceneSP::RenderSamples()
{
	for(int x = 0; x< i_sampleItems;x++)
	{
		modelStack.PushMatrix();
			modelStack.Translate(1.5f - (x * 1), 3.6f, 0.0f);
			RenderMesh(meshList[GEO_CAN_SARDINE], toggleLight);
		modelStack.PopMatrix();
	}
}
void SceneSP::RenderReturnPoint()
{
	modelStack.PushMatrix();
		modelStack.Translate(returnPointBoxPosX, returnPointBoxPosY, returnPointBoxPosZ);
		RenderMesh(meshList[GEO_ICEBOX], toggleLight);
	modelStack.PopMatrix();
}
void SceneSP::RenderSamplestand() //added the container and trolley here for now 
{
	modelStack.PushMatrix();
		modelStack.Translate(35.0f,0.0f,-5.0f);
		modelStack.Rotate(90.0f,0,1,0);	
		RenderMesh(meshList[GEO_SAMPLESTAND], toggleLight);
		RenderSamples();
	modelStack.PopMatrix();
}
void SceneSP::RenderATM()
{
	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 0.0f, 32.0f);
	modelStack.Rotate(180.0f,0,1,0);
	RenderMesh(meshList[GEO_ATM], toggleLight);
	modelStack.PopMatrix();
	if ((camera.position.x > -6 && camera.position.x < 7) && (camera.position.z > 32 && camera.position.z < 40))
	{
		RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to withdraw",Color(0,1,0),2,1,16);
		RenderTextOnScreen(meshList[GEO_TEXT], "Balance:"+s_atm_balance, Color(1, 1, 0), 3, 16.5, 19);
	}
}
void SceneSP::RenderIceBox()
{
	modelStack.PushMatrix();
	modelStack.Translate(37.0f, 0.0f, 25.0f);
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_ICEBOX], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.0f,0.0f,-9.0f);
	RenderMesh(meshList[GEO_ICEBOX], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.0f,0.0f,-18.0f);
	RenderMesh(meshList[GEO_ICEBOX], toggleLight);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}
void SceneSP::RenderMeatShelf()
{
	//16,17,-28
	modelStack.PushMatrix();
	modelStack.Translate(13.0f, 17.0f, -26.0f);
	RenderMesh(meshList[GEO_MEATSHELF], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1.0f, 17.0f, -26.0f);
	RenderMesh(meshList[GEO_MEATSHELF], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-11.0f, 17.0f, -26.0f);
	RenderMesh(meshList[GEO_MEATSHELF], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-23.0f, 17.0f, -26.0f);
	RenderMesh(meshList[GEO_MEATSHELF], toggleLight);
	modelStack.PopMatrix();
}
void SceneSP::RenderBeerstand()
{
	modelStack.PushMatrix();//1st floor
		modelStack.Translate(-21.0f,0.0f,11.0f);
		RenderMesh(meshList[GEO_FOODSHELF], toggleLight);

		modelStack.PushMatrix();
			modelStack.Translate(0.0f,3.6f,0.0f);
			RenderMesh(meshList[GEO_WINEBOTTLE_1], toggleLight);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(0.0f,1.6f,2.5f);
			RenderMesh(meshList[GEO_WINEBOTTLE_5], toggleLight);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(0.0f,1.6f,-2.5f);
			RenderMesh(meshList[GEO_WINEBOTTLE_2], toggleLight);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(-2.5f,1.6f,0.0f);
			RenderMesh(meshList[GEO_WINEBOTTLE_2], toggleLight);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(-2.5f,1.6f,-2.5f);
			RenderMesh(meshList[GEO_WINEBOTTLE_3], toggleLight);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(-2.5f,1.6f,2.5f);
			RenderMesh(meshList[GEO_WINEBOTTLE_3], toggleLight);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(2.5f,1.6f,0.0f);
			RenderMesh(meshList[GEO_WINEBOTTLE_5], toggleLight);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(2.5f,1.6f,2.5f);
			RenderMesh(meshList[GEO_WINEBOTTLE_4], toggleLight);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(2.5f,1.6f,-2.5f);
			RenderMesh(meshList[GEO_WINEBOTTLE_4], toggleLight);
		modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-19.0f,17.0f,0.0f);
		RenderMesh(meshList[GEO_FOODSHELF], toggleLight);
	
		modelStack.PushMatrix();
			modelStack.Translate(0.0f,3.6f,0.0f);
			RenderMesh(meshList[GEO_WINEBOTTLE_1], toggleLight);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(0.0f,1.6f,2.5f);
			RenderMesh(meshList[GEO_WINEBOTTLE_5], toggleLight);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
			modelStack.Translate(0.0f,1.6f,-2.5f);
			RenderMesh(meshList[GEO_WINEBOTTLE_2], toggleLight);
		modelStack.PopMatrix();
	
		modelStack.PushMatrix();
			modelStack.Translate(-2.5f,1.6f,0.0f);
			RenderMesh(meshList[GEO_WINEBOTTLE_2], toggleLight);
		modelStack.PopMatrix();
	
		modelStack.PushMatrix();
			modelStack.Translate(-2.5f,1.6f,2.5f);
			RenderMesh(meshList[GEO_WINEBOTTLE_3], toggleLight);
		modelStack.PopMatrix();
	
		modelStack.PushMatrix();
			modelStack.Translate(-2.5f,1.6f,-2.5f);
			RenderMesh(meshList[GEO_WINEBOTTLE_3], toggleLight);
		modelStack.PopMatrix();
	
		modelStack.PushMatrix();
			modelStack.Translate(2.5f,1.6f,0.0f);
			RenderMesh(meshList[GEO_WINEBOTTLE_5], toggleLight);
		modelStack.PopMatrix();
	
		modelStack.PushMatrix();
			modelStack.Translate(2.5f,1.6f,2.5f);
			RenderMesh(meshList[GEO_WINEBOTTLE_4], toggleLight);
		modelStack.PopMatrix();
	
		modelStack.PushMatrix();
			modelStack.Translate(2.5f,1.6f,-2.5f);
			RenderMesh(meshList[GEO_WINEBOTTLE_4], toggleLight);
		modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-8.0f,17.0f,27.0f);
		RenderMesh(meshList[GEO_WINEBOTTLE_5], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-8.0f,17.0f,25.0f);
		RenderMesh(meshList[GEO_WINEBOTTLE_4], toggleLight);
	modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-8.0f,17.0f,29.0f);
		RenderMesh(meshList[GEO_WINEBOTTLE_1], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-4.0f,17.0f,29.0f);
		RenderMesh(meshList[GEO_WINEBOTTLE_2], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-4.0f,17.0f,25.0f);
		RenderMesh(meshList[GEO_WINEBOTTLE_3], toggleLight);
	modelStack.PopMatrix();
}
void SceneSP::RenderFerrisWheel()
{
	modelStack.PushMatrix();
		modelStack.Translate(0.0f,0.0f,260.0f);
		modelStack.Scale(10,10,10);
		RenderMesh(meshList[GEO_FERRIS], toggleLight);
	modelStack.PopMatrix();
}
void SceneSP::RenderBuilding()
{
	
	modelStack.PushMatrix();
		modelStack.Translate(150.0f,0.0f,32.5f);
		modelStack.Rotate(-90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(75.0f,0.0f,65.0f);
		modelStack.Rotate(-90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(150.0f,0.0f,97.5f);
		modelStack.Rotate(-90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(75.0f,0.0f,130.0f);
		modelStack.Rotate(-90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
		modelStack.Translate(150.0f,0.0f,162.5f);
		modelStack.Rotate(-90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(75.0f,0.0f,195.0f);
		modelStack.Rotate(-90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(150.0f,0.0f,227.5f);
		modelStack.Rotate(-90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(33.0f,0.0f,326.5f);
		modelStack.Rotate(180,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-28.0f,0.0f,326.5f);
		modelStack.Rotate(180,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(100.0f,0.0f,310.0f);
		modelStack.Rotate(180,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-95.0f,0.0f,310.0f);
		modelStack.Rotate(180,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();
	//---
	modelStack.PushMatrix();
		modelStack.Translate(-150.0f,0.0f,32.5f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-75.0f,0.0f,65.0f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
		modelStack.Translate(-150.0f,0.0f,97.5f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-75.0f,0.0f,130.0f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();
		
	modelStack.PushMatrix();
		modelStack.Translate(-150.0f,0.0f,162.5f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-75.0f,0.0f,195.0f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-150.0f,0.0f,227.5f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();
	//--
	modelStack.PushMatrix();
		modelStack.Translate(150.0f,0.0f,-32.5f);
		modelStack.Rotate(-90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(75.0f,0.0f,-65.0f);
		modelStack.Rotate(-90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
		modelStack.Translate(150.0f,0.0f,-97.5f);
		modelStack.Rotate(-90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(75.0f,0.0f,-130.0f);
		modelStack.Rotate(-90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
		modelStack.Translate(150.0f,0.0f,-162.5f);
		modelStack.Rotate(-90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(75.0f,0.0f,-195.0f);
		modelStack.Rotate(-90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
		modelStack.Translate(150.0f,0.0f,-227.5f);
		modelStack.Rotate(-90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(28.0f,0.0f,-260.0f);
		modelStack.Rotate(0,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();
	//
	modelStack.PushMatrix();
		modelStack.Translate(-150.0f,0.0f,-32.5f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-75.0f,0.0f,-65.0f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
		modelStack.Translate(-150.0f,0.0f,-97.5f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-75.0f,0.0f,-130.0f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-150.0f,0.0f,-162.5f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-75.0f,0.0f,-195.0f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-150.0f,0.0f,-227.5f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-32.0f,0.0f,-260.0f);
		RenderMesh(meshList[GEO_BUILDING], toggleLight);
	modelStack.PopMatrix();
}
void SceneSP::RenderTug()
{
	if(IsIntugofwar)
	{
		modelStack.PushMatrix();
			modelStack.Translate(myNPCList[0]->getXpos()+2.f,myNPCList[0]->getYpos()+3.6f,myNPCList[0]->getZpos()-1.f);
			modelStack.Rotate(90,0,0,1);
			RenderMesh(meshList[GEO_CAN_SARDINE], toggleLight);
		modelStack.PopMatrix();
	}
}
void SceneSP::RenderItem()
{
	for(unsigned int i = 0; i< myStockList.size(); ++i)
	{
		if(myStockList[i]->getActiveState()) //If Item is active
		{
			modelStack.PushMatrix();
				modelStack.Translate(myStockList[i]->getXpos(),myStockList[i]->getYpos(),myStockList[i]->getZpos());
				RenderMesh(meshList[myStockList[i]->getGeoType()],toggleLight);
			modelStack.PopMatrix();
		}
	}
}
void SceneSP::RenderInventory()
{
	for( int i = 0; i< ptrplayer->getItemHeld();++i)
	{
		RenderTGAInventory(meshList[ptrplayer->getVector()[i]->getGeoType()],3.f,22.3f+(i*5.f),0.5f);
	}
}
void SceneSP::RenderOffice()
{
	modelStack.PushMatrix();
		modelStack.Translate(37.0f, 17.0f, 14.0f);
		modelStack.Rotate(270,0,1,0);
		RenderMesh(meshList[GEO_OFFICECOMPUTER], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(37.0f, 17.0f, 18.0f);
		modelStack.Rotate(270,0,1,0);
		RenderMesh(meshList[GEO_OFFICECOMPUTER], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(37.0f, 17.0f, 22.0f);
		modelStack.Rotate(270,0,1,0);
		RenderMesh(meshList[GEO_OFFICECOMPUTER], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(37.0f, 17.0f, 26.0f);
		modelStack.Rotate(270,0,1,0);
		RenderMesh(meshList[GEO_OFFICECOMPUTER], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(22.0f, 17.0f, 14.0f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_OFFICECOMPUTER], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(22.0f, 17.0f, 18.0f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_OFFICECOMPUTER], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(23.0f, 17.0f, 22.0f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_OFFICECOMPUTER], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(23.0f, 17.0f, 26.0f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_OFFICECOMPUTER], toggleLight);
	modelStack.PopMatrix();
}
void SceneSP::RenderStorage()
{
	for(int i=0;i<4;i++)
	{
		modelStack.PushMatrix();
			modelStack.Translate(36.0f, 17.0f, -14.0f-(i*4));
			modelStack.Rotate(270,0,1,0);
			RenderMesh(meshList[GEO_BOX], toggleLight);
		modelStack.PopMatrix();
	}
	for(int i=0;i<4;i++)
	{
		modelStack.PushMatrix();
			modelStack.Translate(24.0f, 17.0f, -14.0f-(i*4));
			modelStack.Rotate(270,0,1,0);
			RenderMesh(meshList[GEO_BOX], toggleLight);
		modelStack.PopMatrix();
	}
	modelStack.PushMatrix();
		modelStack.Translate(30.0f, 17.0f, -26.0f);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_BOX], toggleLight);
	modelStack.PopMatrix();
}
void SceneSP::RenderCage()
{
	modelStack.PushMatrix();
		modelStack.Translate(42.7f, 0.0f, -27.0f);
		RenderMesh(meshList[GEO_EASTEREGG_6], toggleLight);
	modelStack.PopMatrix();
	if(caged)
	{
		modelStack.PushMatrix();

			modelStack.PushMatrix();
				modelStack.Translate(0.0f, -30.0f, cagedPos);
				modelStack.Scale(50.0f,50.0f,50.0f);
				RenderMesh(meshList[GEO_CAGE], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();//bot
				modelStack.Translate(0.0f, -30.0f, 70.0f);
				modelStack.Scale(50.0f,50.0f,50.0f);
				modelStack.Rotate(180.0f,1,0,0);
				RenderMesh(meshList[GEO_CAGEWALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();//bot
				modelStack.Translate(0.0f, -54.0f, 0.0f);
				modelStack.Scale(50.0f,50.0f,150.0f);
				modelStack.Rotate(-90.0f,1,0,0);
				RenderMesh(meshList[GEO_CAGEWALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();//top
				modelStack.Translate(0.0f, -6.0f, 0.0f);
				modelStack.Scale(50.0f,50.0f,150.0f);
				modelStack.Rotate(90.0f,1,0,0);
				RenderMesh(meshList[GEO_CAGEWALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Translate(-24.0f, -29.0f, 0.0f);
				modelStack.Scale(50.0f,50.0f,150.0f);
				modelStack.Rotate(90.0f,0,1,0);
				RenderMesh(meshList[GEO_CAGEWALL], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Translate(24.0f, -29.0f, 0.0f);
				modelStack.Scale(50.0f,50.0f,150.0f);
				modelStack.Rotate(-90.0f,0,1,0);
				RenderMesh(meshList[GEO_CAGEWALL], true);
			modelStack.PopMatrix();

		modelStack.PopMatrix();
	}
}
void SceneSP::RenderTroll()
{
	if(reversed)	//RenderTextOnScreen(meshList[GEO_TEXT], "Money: $"+ s_money, Color(0, 1, 0), 3,0, 19);
		RenderTextOnScreen(meshList[GEO_TEXT], "Reversed!", Color(1, 1, 0), 3, 18, 19);
	modelStack.PushMatrix();
		modelStack.Translate(33.0f, 17.0f, -27.0f);
		RenderMesh(meshList[GEO_EASTEREGG_3], toggleLight);
	modelStack.PopMatrix();
}

void SceneSP::checkPickUpItem()
{

	float magnitudeFromTarget = 0.f;
	float magnitudeFromPosition = 0.f;
	float previous = 99.0f;
	int chosen = 0;
	for(unsigned int i = 0; i<myStockList.size();++i)
	{
		if(myStockList[i]->getActiveState()) //If Item is available for taking
		{
			//Distance between Camera Target and Item position = Sqrt( (x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 )
			magnitudeFromTarget = sqrt( (camera.target.x - myStockList[i]->getXpos()+itemXoffset) *(camera.target.x - myStockList[i]->getXpos()+itemXoffset) 
				+ (camera.target.y - myStockList[i]->getYpos()+itemYoffset) * (camera.target.y - myStockList[i]->getYpos()+itemYoffset) 
				+ (camera.target.z - myStockList[i]->getZpos()+itemZoffset) * (camera.target.z - myStockList[i]->getZpos()+itemZoffset));


			//Get lowest magnitude of Item from target
			if(previous > magnitudeFromTarget)
			{
				previous = magnitudeFromTarget;
				//Distance between Camera Position and Item position= Sqrt( (x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 )
				magnitudeFromPosition = sqrt( (camera.position.x - myStockList[i]->getXpos()+itemXoffset) *(camera.position.x - myStockList[i]->getXpos()+itemXoffset) 
					+ (camera.position.y - myStockList[i]->getYpos()+itemYoffset) * (camera.position.y - myStockList[i]->getYpos()+itemYoffset) 
					+ (camera.position.z - myStockList[i]->getZpos()+itemZoffset) * (camera.position.z - myStockList[i]->getZpos()+itemZoffset));

				if(magnitudeFromPosition <= interactionDistance)
				{
					chosen = i;
					b_isWithinInteractionItem = true;
					s_item_name = myStockList[chosen]->getName();
				}
				else
				{
					
					b_isWithinInteractionItem = false;
				}



			}

		}

	}
	if(Application::IsKeyPressed('E') && (interactionTimer > interactionTimerLimiter) && myStockList[chosen]->getActiveState() && b_isWithinInteractionItem)
	{
		if(ptrplayer->getItem(inventoryPointing)->getName() == emptyItem.getName())
		{
			addToInventory(myStockList[chosen]);
			myStockList[chosen]->setActiveState(false);
			std::cout << "Item " <<myStockList[chosen]->getName() << " removed! \n";
			ptrInvSelect = ptrplayer->getItem(inventoryPointing);
		}
	}
}
void SceneSP::checkCollision()
{
	checkSupermarketCollision();
	checkElevatorCollision();
	checkObjectCollision(13.0f, 17.0f, -26.0f, 8.0f, 4.0f);//meat shelves
	checkObjectCollision(1.0f, 17.0f, -26.0f, 8.0f, 4.0f);
	checkObjectCollision(-11.0f, 17.0f, -26.0f, 8.0f, 4.0f);
	checkObjectCollision(-23.0f, 17.0f, -26.0f, 8.0f, 4.0f);
	checkObjectCollision(-21.0f, 0.0f, 11.0f, 5.0f, 5.0f);//food stand
	checkObjectCollision(-19.0f, 17.0f, 0.0f, 5.0f, 5.0f);
	checkObjectCollision(-37.0f, 0.0f, 0.0f, 4.0f, 6.0f);
	checkObjectCollision(37.0f, 0.0f, 25.0f, 4.0f, 5.5f);//freezer
	checkObjectCollision(37.0f, 0.0f, 16.0f, 4.0f, 5.5f);
	checkObjectCollision(37.0f, 0.0f, 7.0f, 4.0f, 5.5f);
	checkObjectCollision(-26.0f, 0.0f, -20.0f, 5.0f, 11.0f);//cashier tables
	checkObjectCollision(-16.0f, 0.0f, -18.0f, 4.0f, 7.5f);
	checkObjectCollision(-6.0f, 0.0f, -18.0f, 4.0f, 7.5f);
	checkObjectCollision(0.0f, 0.0f, 32.0f, 3.0f, 4.0f);//atm
	checkObjectCollision(30.0f, 17.0f, -26.0f, 3.0f, 3.0f);//boxes
	for(int i = 0; i<4;i++)
	{
		checkObjectCollision(36.0f, 17.0f, -14.0f-(4*i), 3.0f, 3.0f);//boxes
		checkObjectCollision(24.0f, 17.0f, -14.0f-(4*i), 3.0f, 3.0f);
		checkObjectCollision(37.0f, 17.0f, 14.0f+(4*i), 3.0f, 3.0f);//computers
		checkObjectCollision(24.0f, 17.0f, 14.0f+(4*i), 3.0f, 3.0f);
	}
	for(unsigned int i = 0; i< myNPCList.size(); ++i)//NPC collision
		checkObjectCollision(myNPCList[i]->getXpos(),myNPCList[i]->getYpos(), myNPCList[i]->getZpos(), 2.0f, 2.0f);
	for(unsigned int i = 0; i< myContainerList.size(); ++i)//Shelf collision
		checkObjectCollision(myContainerList[i]->getXpos(), myContainerList[i]->getYpos(), myContainerList[i]->getZpos(), ShelfWidthX, ShelfWidthZ);
	checkObjectCollision(35.0f, 0.0f, -5.0f, 2.0f, 4.0f);//sample stand
	checkObjectCollision(75.0f, 0.0f, 65.0f, 32.0f, 32.0f);//outside buildings
	checkObjectCollision(75.0f, 0.0f, 130.0f, 32.0f, 32.0f);
	checkObjectCollision(75.0f, 0.0f, 195.0f, 32.0f, 32.0f);
	checkObjectCollision(75.0f, 0.0f, -65.0f, 32.0f, 32.0f);
	checkObjectCollision(75.0f, 0.0f, -130.0f, 32.0f, 32.0f);
	checkObjectCollision(75.0f, 0.0f, -195.0f, 32.0f, 32.0f);
	checkObjectCollision(-75.0f, 0.0f, 65.0f, 32.0f, 32.0f);
	checkObjectCollision(-75.0f, 0.0f, 130.0f, 32.0f, 32.0f);
	checkObjectCollision(-75.0f, 0.0f, 195.0f, 32.0f, 32.0f);
	checkObjectCollision(-75.0f, 0.0f, -65.0f, 32.0f, 32.0f);
	checkObjectCollision(-75.0f, 0.0f, -130.0f, 32.0f, 32.0f);
	checkObjectCollision(-75.0f, 0.0f, -195.0f, 32.0f, 32.0f);
	checkObjectCollision(23.0f, 17.0f, 11.0f, 5.5f, 3.0f);//logistic staff room
	checkObjectCollision(36.0f, 17.0f, 11.0f, 4.0f, 3.0f);
	checkObjectCollision(23.0f, 17.0f, -11.0f, 5.5f, 3.0f);
	checkObjectCollision(36.0f, 17.0f, -11.0f, 4.0f, 3.0f);
}
void SceneSP::checkObjectCollision(float posX, float posY, float posZ, float widthX, float widthZ)
{
	if((camera.position.y - posY < 10) && (camera.position.y - posY > 0))
	{
		if((camera.position.x > (posX + widthX - (Coffset)) && camera.position.x < (posX + widthX)) && 
			(camera.position.z > (posZ - widthZ + (Coffset/2)) && camera.position.z < (posZ + widthZ - (Coffset/2))))
		{
			diffX = camera.position.x - (posX + widthX);
			camera.position.x = posX + widthX;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		if((camera.position.x > (posX - widthX) && camera.position.x < (posX - widthX + Coffset)) && 
			(camera.position.z > (posZ - widthZ + (Coffset / 2)) && camera.position.z < (posZ + widthZ - (Coffset / 2))))
		{
			diffX = camera.position.x - (posX - widthX);
			camera.position.x = posX- widthX;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		if((camera.position.x > (posX - widthX+ (Coffset / 2)) && camera.position.x < (posX + widthX)- (Coffset / 2)) && 
			(camera.position.z > (posZ - widthZ) && camera.position.z < (posZ - widthZ + Coffset)))
		{
			diffZ = camera.position.z - (posZ - widthZ);
			camera.position.z = posZ - widthZ;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if((camera.position.x > (posX - widthX+ (Coffset / 2)) && camera.position.x < (posX + widthX)- (Coffset / 2)) && 
			(camera.position.z > (posZ + widthZ - Coffset) && camera.position.z < (posZ + widthZ)))
		{
			diffZ = camera.position.z - (posZ + widthZ);
			camera.position.z = posZ + widthZ;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
	}
}
void SceneSP::checkSupermarketCollision()
{
	if((camera.position.x > boundX1 && camera.position.x < boundX2) && (camera.position.z > boundZ1 && camera.position.z < boundZ2))
	{
		diffX = camera.position.x - (boundX1);
		camera.position.x = boundX1;
		camera.target.x -= diffX;
		diffX = 0.0f;
	}
	if((camera.position.x > boundX2 && camera.position.x < boundX3) && (camera.position.z > boundZ1 && camera.position.z < boundZ2))
	{
		diffX = camera.position.x - (boundX3);
		camera.position.x = boundX3;
		camera.target.x -= diffX;
		diffX = 0.0f;
	}
	if((camera.position.x > boundX1 && camera.position.x < boundX5) && (camera.position.z > boundZ1 && camera.position.z < boundZ3))
	{
		diffZ = camera.position.z - (boundZ1);
		camera.position.z = boundZ1;
		camera.target.z -= diffZ;
		diffZ = 0.0f;
	}
	if((camera.position.x > boundX1 && camera.position.x < boundX5) && (camera.position.z > boundZ3 && camera.position.z < boundZ6))
	{
		diffZ = camera.position.z - (boundZ6);
		camera.position.z = boundZ6;
		camera.target.z -= diffZ;
		diffZ = 0.0f;
	}
	if((camera.position.x > boundX1 && camera.position.x < boundX6) && (camera.position.z > boundZ4 && camera.position.z < boundZ2))
	{
		diffZ = camera.position.z - (boundZ2);
		camera.position.z = boundZ2;
		camera.target.z -= diffZ;
		diffZ = 0.0f;
	}
	if((camera.position.x > boundX1 && camera.position.x < boundX6) && (camera.position.z > boundZ5 && camera.position.z < boundZ4))
	{
		diffZ = camera.position.z - (boundZ5);
		camera.position.z = boundZ5;
		camera.target.z -= diffZ;
		diffZ = 0.0f;
	}
	if((camera.position.x > boundX10 && camera.position.x < boundX4) && (camera.position.z > boundZ4 && camera.position.z < boundZ2))
	{
		diffZ = camera.position.z - (boundZ2);
		camera.position.z = boundZ2;
		camera.target.z -= diffZ;
		diffZ = 0.0f;
	}
	if((camera.position.x > boundX10 && camera.position.x < boundX4) && (camera.position.z > boundZ5 && camera.position.z < boundZ4))
	{
		diffZ = camera.position.z - (boundZ5);
		camera.position.z = boundZ5;
		camera.target.z -= diffZ;
		diffZ = 0.0f;
	}
	if((camera.position.x > boundX7 && camera.position.x < boundX4) && (camera.position.z > boundZ1 && camera.position.z < boundZ2))
	{
		diffX = camera.position.x - (boundX4);
		camera.position.x = boundX4;
		camera.target.x -= diffX;
		diffX = 0.0f;
	}
	if((camera.position.x > boundX8 && camera.position.x < boundX7) && (camera.position.z > boundZ1 && camera.position.z < boundZ2))
	{
		diffX = camera.position.x - (boundX8);
		camera.position.x = boundX8;
		camera.target.x -= diffX;
		diffX = 0.0f;
	}
	if((camera.position.x > boundX9 && camera.position.x < boundX4) && (camera.position.z > boundZ1 && camera.position.z < boundZ3))
	{
		diffZ = camera.position.z - (boundZ1);
		camera.position.z = boundZ1;
		camera.target.z -= diffZ;
		diffZ = 0.0f;
	}
	if((camera.position.x > boundX9 && camera.position.x < boundX4) && (camera.position.z > boundZ3 && camera.position.z < boundZ6))
	{
		diffZ = camera.position.z - (boundZ6);
		camera.position.z = boundZ6;
		camera.target.z -= diffZ;
		diffZ = 0.0f;
	}
	if(camera.position.y > 10)
	{//top floor
		if((camera.position.x > boundX6 && camera.position.x < boundX10) && (camera.position.z > boundZ4 && camera.position.z < boundZ2))
		{
			diffZ = camera.position.z - (boundZ2);
			camera.position.z = boundZ2;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if((camera.position.x > boundX6 && camera.position.x < boundX10) && (camera.position.z > boundZ5 && camera.position.z < boundZ4))
		{
			diffZ = camera.position.z - (boundZ5);
			camera.position.z = boundZ5;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if((camera.position.x > boundX5 && camera.position.x < boundX9) && (camera.position.z > boundZ1 && camera.position.z < boundZ3))
		{
			diffZ = camera.position.z - (boundZ1);
			camera.position.z = boundZ1;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if((camera.position.x > boundX5 && camera.position.x < boundX9) && (camera.position.z > boundZ3 && camera.position.z < boundZ6))
		{
			diffZ = camera.position.z - (boundZ6);
			camera.position.z = boundZ6;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if(((camera.position.x > 18 && camera.position.x < 18+2) && (camera.position.z > -23 && camera.position.z < -8)) ||
			((camera.position.x > 18 && camera.position.x < 18+2) && (camera.position.z > 10 && camera.position.z < 26.5f))
			)
		{//logistic staff room
			diffX = camera.position.x - (18);
			camera.position.x = 18;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		
		}
	if(camera.position.y < 10)
	{
		if((camera.position.x > -36 && camera.position.x < -34) && (camera.position.z > 10 && camera.position.z < 39))
		{
			diffX = camera.position.x - (-34);
			camera.position.x = -34;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		if((camera.position.x > -38 && camera.position.x < -34) && (camera.position.z > 10 && camera.position.z < 12))
		{
			diffZ = camera.position.z - (10);
			camera.position.z = 10;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if(camera.position.z > 222 && camera.position.z < 225)
		{
			diffZ = camera.position.z - (222);
			camera.position.z = 222;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if(camera.position.z > -225 && camera.position.z < -222)
		{
			diffZ = camera.position.z - (-222);
			camera.position.z = -222;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if(camera.position.x > 104 && camera.position.x < 107)
		{
			diffX = camera.position.x - (104);
			camera.position.x = 104;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		if(camera.position.x > -107 && camera.position.x < -104)
		{
			diffX = camera.position.x - (-104);
			camera.position.x = -104;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
	}
}
void SceneSP::checkElevatorCollision()
{
	if(camera.position.y < 10)
	{
		if((camera.position.x > EboundX1 && camera.position.x < EboundX2) && (camera.position.z > EboundZ1 && camera.position.z < EboundZ2))
		{//Inner
			diffX = camera.position.x - (EboundX1);
			camera.position.x = EboundX1;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
	}
	if(camera.position.y > 10)
	{
		if((camera.position.x > EboundX1 && camera.position.x < EboundX2) && (camera.position.z > EboundZ1 && camera.position.z < EboundZ3))
		{//Inner top
			diffX = camera.position.x - (EboundX1);
			camera.position.x = EboundX1;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		if((camera.position.x > EboundX2 && camera.position.x < EboundX3) && (camera.position.z > EboundZ1 && camera.position.z < EboundZ3))
		{//Outer top
			diffX = camera.position.x - (EboundX3);
			camera.position.x = EboundX3;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
	}
	if(!elevatorDoorOpening)
	{
		if((camera.position.x > RenderElevatorPosX-4 && camera.position.x < RenderElevatorPosX+4) && (camera.position.z > RenderElevatorPosZ+4 && camera.position.z < RenderElevatorPosZ+6))
		{//Outer elevator door
			diffZ = camera.position.z - (RenderElevatorPosZ+6);
			camera.position.z = RenderElevatorPosZ+6;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if((camera.position.x > RenderElevatorPosX-4 && camera.position.x < RenderElevatorPosX+4) && (camera.position.z > RenderElevatorPosZ+2 && camera.position.z < RenderElevatorPosZ+4))
		{//Inner elevator door
			diffZ = camera.position.z - (RenderElevatorPosZ+2);
			camera.position.z = RenderElevatorPosZ+2;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
	}
}
bool SceneSP::checkReturnPoint()
{
	
	//If within RETURN POINT boundary
	if((camera.position.x > returnPointBoxPosX-returnPointBoxWidthOffset)&& camera.position.x < (returnPointBoxPosX+returnPointBoxInteractionWidth+returnPointBoxWidthOffset))
	{
		if(camera.position.z > (returnPointBoxPosZ - returnPointBoxInteractionLength) && camera.position.z < (returnPointBoxPosZ + returnPointBoxInteractionLength))
		{
			if(camera.position.y > returnPointBoxPosY && camera.position.y < (returnPointBoxPosY + returnPointBoxInteractionHeight))
			{
				//If triggering interaction
				if(Application::IsKeyPressed('E') && interactionTimer > interactionTimerLimiter)
				{
					//Is within boundary
					interactionTimer = 0;
					std::cout << "Item returned: " <<ptrplayer->getItem(inventoryPointing)->getName() << std::endl;
					ptrplayer->setInventory(&emptyItem,inventoryPointing);
					ptrInvSelect = ptrplayer->getItem(inventoryPointing);

				}
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
void SceneSP::checkWinLose()
{
	//If player is exiting by Exit Gate and in Treasure hunter mode
	if((camera.position.x >12 && camera.position.x < 33) && camera.position.z <-31 &&  ptrplayer->getCharacterJob() == PLAY_TREASURE_HUNT)
	{
		//Init pass check to 0
		int checklistPass = 0;
		for(unsigned int i = 0; i< myCheckList.size();++i)
		{
			//Check number of items cleared
			if(myCheckList[i]->getName() == clearText)
			{
				++checklistPass;
			}
		}
		

		//Check if Total clear is equal to checklist size
		if(checklistPass == myCheckList.size())
		{
			i_menuHandle = WIN_LOSE_MENU;
		}
	}
	if((((camera.position.x >12 && camera.position.x < 33) && camera.position.z <-31)||((camera.position.x >-29 && camera.position.x < -10)&& camera.position.z >30)) 
		&&  ptrplayer->getCharacterJob() == PLAY_TREASURE_HUNT)
	{
		//Search through player's inventory
		for(unsigned int i = 0; i< ptrplayer->getVector().size(); ++i)
		{
			//If player has existing item when walking out, player is stealing
			if(ptrplayer->getVector()[i]->getName() != ptrEmpty->getName())
			{
				b_is_Stealing = true;
				i_menuHandle = WIN_LOSE_MENU;
			}
		}
	}


	if(closeEaster)
	{
		getCaged = false;
		getGabed = false;
		getTrolled = false;
		getTimed = false;
		getCounter = 0;
		winEaster = false;
		closeEaster = false;
		i_menuHandle = WIN_LOSE_MENU;
	}
}
void SceneSP::Exit()
{
	// Cleanup here
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i] != NULL)
			delete meshList[i];
	}
	delete ptrplayer;
	delete ptrClass;
	delete ptrContainer;
	delete ptrItem;
	delete ptrNPC;
	music.stop();
	sound.stop();
	easter.stop();
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

