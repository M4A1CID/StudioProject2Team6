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

	/*=============================================
	Init variables here
	=============================================*/
	i_menuHandle = MAIN_MENU;
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
	toggleLight = true;
	toggleDoorFront = false;
	toggleDoorBack = false;
	elevatorDoorOpening = false;
	elevatorSecondFloor = false;
	IsIntugofwar = false;
	win = false;
	lose = false;
	showTuginstruction = false;
	interactionTimer = 0.0f;
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
	meshList[GEO_MEATSHELF]->textureID = LoadTGA("Image//ContainerTexture.tga");
	meshList[GEO_FOODSHELF] = MeshBuilder::GenerateOBJ("foodshelf", "OBJ//FoodShelf.obj");
	meshList[GEO_FOODSHELF]->textureID = LoadTGA("Image//ContainerTexture.tga");
	meshList[GEO_SHELF] = MeshBuilder::GenerateOBJ("shelf", "OBJ//shelf.obj");
	meshList[GEO_SHELF]->textureID = LoadTGA("Image//Shelves.tga");
	meshList[GEO_CASHIER] = MeshBuilder::GenerateOBJ("cashier", "OBJ//cashiertable.obj");
	meshList[GEO_CASHIER]->textureID = LoadTGA("Image//cashRegisterTexture.tga");
	meshList[GEO_FENCE] = MeshBuilder::GenerateOBJ("fence", "OBJ//Fence.obj");
	meshList[GEO_FENCE]->textureID = LoadTGA("Image//Fence.tga");
	meshList[GEO_ELEVATOR] = MeshBuilder::GenerateOBJ("elevator", "OBJ//Elevator.obj");
	meshList[GEO_ELEVATOR]->textureID = LoadTGA("Image//Elevator.tga");
	meshList[GEO_ELEVATORDOOR] = MeshBuilder::GenerateOBJ("elevatordoor", "OBJ//Elevatordoor.obj");
	meshList[GEO_ELEVATORDOOR]->textureID = LoadTGA("Image//supermarket.tga");
	meshList[GEO_HANDS] = MeshBuilder::GenerateOBJ("elevatordoor", "OBJ//playerArm.obj");
	meshList[GEO_HANDS]->textureID = LoadTGA("Image//cashier.tga");
	meshList[GEO_MAIN_MENU_TITLE] = MeshBuilder::GenerateText("MenuSupermarket",1,1);
	meshList[GEO_MAIN_MENU_TITLE]->textureID = LoadTGA("Image//Menu_Supermarket.tga");
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
	EASTER EGG INIT
	=========================*/
	meshList[GEO_EASTEREGG_1] = MeshBuilder::GenerateOBJ("easterEgg1","OBJ//EasterEgg1.obj");
	meshList[GEO_EASTEREGG_1]->textureID = LoadTGA("Image//EasterEgg1.tga");
	meshList[GEO_EASTEREGG_2] = MeshBuilder::GenerateOBJ("easterEgg2","OBJ//EasterEgg2.obj");
	meshList[GEO_EASTEREGG_2]->textureID = LoadTGA("Image//EasterEgg2.tga");
	meshList[GEO_EASTEREGG_3] = MeshBuilder::GenerateOBJ("easterEgg3","OBJ//EasterEgg3.obj");
	meshList[GEO_EASTEREGG_3]->textureID = LoadTGA("Image//EasterEgg3.tga");
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

}
void SceneSP::initCharacter()
{
	ptrplayer = new CPlayer(100,0,8);

	//Tug of war NPC
	ptrNPC = new CNpc(0,0,0,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,IDLE,TUG_OF_WAR_GUY);
	myNPCList.push_back(ptrNPC);
	//-12,17,28
	ptrNPC = new CNpc(-6,17,28,GEO_DRUNKMAN_HEADBODY,GEO_DRUNKMAN_ARM,GEO_DRUNKMAN_LEGANDFEET,IDLE,DRUNKMAN);
	myNPCList.push_back(ptrNPC);

	//Walk around supermarket
	ptrNPC = new CNpc(-5,0,13,GEO_NormalNpc1_HEADBODY,GEO_NormalNpc1_ARM,GEO_NormalNpc1_LEGANDFEET,IDLE,WALKING_GUY);
	myNPCList.push_back(ptrNPC);

	//ptrNPC = new CNpc(8,0,-4,GEO_NormalNpc2_HEADBODY,GEO_NormalNpc2_ARM,GEO_NormalNpc2_LEGANDFEET,IDLE,CUSTOMER);
	//myNPCList.push_back(ptrNPC);

	//ptrNPC = new CNpc(12,0,-4,GEO_LOGISTICSTAFF_HEADBODY,GEO_LOGISTICSTAFF_ARM,GEO_LOGISTICSTAFF_LEGANDFEET,IDLE,PART_TIME_WORKER);
	//myNPCList.push_back(ptrNPC);
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

	ptrClass = new CEasterEgg3;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfTwo",5,5,5,20,0,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CEasterEgg2;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfThree",5,5,5,26,0,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CGluWaterCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf16",5,5,5,8,0,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CMtnDewCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf17",5,5,5,2,0,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	//==============================================================================
	ptrClass =  new CEasterEgg1;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfFour",5,5,5,26,0,18,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CCerealBox5;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfFive",5,5,5,20,0,18,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CCerealBox4;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfSix",5,5,5,14,0,18,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CPeasCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf18",5,5,5,8,0,18,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CSardineCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf19",5,5,5,2,0,18,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	//==================================================================================
	ptrClass = new CCerealBox1;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfSeven",5,5,5,26,0,16,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CCerealBox2;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfEight",5,5,5,20,0,16,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CCerealBox3;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfNine",5,5,5,14,0,16,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CRedMonsterCan;
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
	//==================================================================================
	ptrClass = new CHumanCan;
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

	ptrClass = new CSodaCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf22",5,5,5,8,0,4,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CSardineCan;
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

	ptrClass = new CSodaFestCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf14",5,5,5,20,0,6,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

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
	ptrClass = new CBeansCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfOne",5,5,5,-12,17,28,180);
	myContainerList.push_back(ptrContainer);	//Push back into vector list
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CEasterEgg3;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfTwo",5,5,5,-18,17,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CEasterEgg2;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfThree",5,5,5,-24,17,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CGluWaterCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf16",5,5,5,-30,17,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CMtnDewCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf17",5,5,5,-36,17,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
	//==================================================================================
	ptrClass = new CEasterEgg2;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"ShelfThree",5,5,5,4,17,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CGluWaterCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf16",5,5,5,10,17,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CMtnDewCan;
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf17",5,5,5,16,17,28,180);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
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
	std::stringstream ss_fps,ss_position,ss_money, ss_camera;

	ss_camera << camera.target.x << "," << camera.target.y << "," << camera.target.z;
	s_camera_target = ss_camera.str();

	ss_fps << 1/dt;
	s_fps = ss_fps.str();

	ss_position << camera.position.x << "," << camera.position.y << "," << camera.position.z;
	s_position = ss_position.str();

	ss_money << ptrplayer->getMoney();
	s_money = ss_money.str();

}
void SceneSP::UpdateAI(double dt)
{
	UpdateTugofwarguy(dt);
	UpdateWalkingman(dt);
}
void SceneSP::UpdateTrolley(double dt)
{
	if(Application::IsKeyPressed(VK_LEFT)&& !Application::IsKeyPressed('R'))
	{
		handrotationleftandright += (camera.CAMERA_SPEED)*dt;
	}
	if(Application::IsKeyPressed(VK_RIGHT)&& !Application::IsKeyPressed('R'))
	{
		handrotationleftandright -= (camera.CAMERA_SPEED)*dt;
	}
	if(Application::IsKeyPressed('E') || PunchTimerLimiter == false)
	{
		if(PunchTimerLimiter == true)
		{
			PunchTimerLimiter = false;
		}
		else
		{
			handtranslation += (2.0f)*dt;
			if(handtranslation > 1.0f)
			{
				PunchTimerLimiter = true;
				handtranslation = 0.0f;
			}
		}
	}
}
void SceneSP::UpdateMenu()
{
	//If at main menu
	if(i_menuHandle == MAIN_MENU)
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
				if(selectionPointing == MENU_EXIT)
				{
					interactionTimer = 0;
					//Exit shit here
				}
			}
		}
	}

	//If at SUB/Character menu 
	if(i_menuHandle == SUB_MENU)
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
					i_menuHandle = GAME_PLAYING;
					
				}
				if(selectionPointing == MENU_TREASURE_HUNT)
				{
					//DO TREASURE HUNT HERE
					i_menuHandle = GAME_PLAYING;
				}
				if(selectionPointing == MENU_EASTER_EGG_HUNT)
				{
					//DO EASTER EGG HUNT HERE
					i_menuHandle == GAME_PLAYING;
				}
			}
		}
	}
}
void SceneSP::UpdateItemRotation(double dt)
{
	if(Application::IsKeyPressed(VK_RIGHT)&& Application::IsKeyPressed('R'))
	{
		itemYrotation+=dt*itemRotationSpeedMultiplyer;
	}
	if(Application::IsKeyPressed(VK_LEFT) && Application::IsKeyPressed('R'))
	{
		itemYrotation-=dt*itemRotationSpeedMultiplyer;
	}
	if(Application::IsKeyPressed(VK_DOWN)&& Application::IsKeyPressed('R'))
	{
		itemXrotation+=dt*itemRotationSpeedMultiplyer;
	}
	if(Application::IsKeyPressed(VK_UP) && Application::IsKeyPressed('R'))
	{
		itemXrotation-=dt*itemRotationSpeedMultiplyer;
	}
	if(!Application::IsKeyPressed('R'))
	{
		itemXrotation = 0.f;
		itemYrotation = 0.f;
	}
}
void SceneSP::UpdatePlaying(double dt)
{
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
	if(Application::IsKeyPressed(VK_CONTROL))
	{
		b_crouching = true;
	}
	else
	{
		b_crouching = false;
	}
	if(b_crouching)
	{
		//First floor crouching
		if(camera.position.y>3.1f && camera.position.y < 4.6f)
		{
			camera.position.y-=dt*5;
			camera.target.y -=dt*5;
		}
		//Second floor crouching
		if(camera.position.y > 19.1f && camera.position.y < 23.1f)
		{
			camera.position.y-=dt*5;
			camera.target.y -=dt*5;
		}
		
	}
	else
	{
		//First floor crouching
		if(camera.position.y <= 4.5f && camera.position.y >= 3.0f)
		{
			camera.position.y+=dt*5;
			camera.target.y+=dt*5;
		}
		//Second floor crouching
		if(camera.position.y <21.5f && camera.position.y >= 19.f)
		{
			camera.position.y+=dt*5;
			camera.target.y+=dt*5;
		}
	}

	UpdatePlayerSelection();
	UpdateUI(dt);
	UpdateTugofwar(dt);
	UpdateAI(dt);
	UpdateItemRotation(dt);
	if(Application::IsKeyPressed('F1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('F2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('F3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed('F4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	if(Application::IsKeyPressed('F5'))
	{
		toggleLight = true;
	}
	if(Application::IsKeyPressed('F6'))
	{
		toggleLight = false;
	}



	UpdateUI(dt);
	checkPickUpItem();
	if(!IsIntugofwar)
		camera.UpdateMovement(dt);
	camera.UpdateView(dt);
	UpdateTrolley(dt);
	UpdateElevator(dt);
	UpdateDoor(dt);
	UpdateSamples();
	checkSupermarketCollision();
	checkFreezerCollision();
	checkShelfCollision();
	checkCashierCollision();
	checkElevatorCollision();
	checkReturnPoint();
	checkNPCCollision();
	if(Application::IsKeyPressed('U'))
		Cashier.translateY += (float) 50 * dt;
	//Down
	if(Application::IsKeyPressed('5'))
		Cashier.translateY -= (float) 50 * dt;
	//Back
	if(Application::IsKeyPressed('6'))
		Cashier.translateX += (float) 50 * dt;
	//Front
	if(Application::IsKeyPressed('7'))
		Cashier.translateX -= (float) 50 * dt;
	//Right
	if(Application::IsKeyPressed('8'))
		Cashier.translateZ += (float) 50 * dt;
	//Left
	if(Application::IsKeyPressed('9'))
		Cashier.translateZ -= (float) 50 * dt;
	//Rotate anti clockwise
	if(Application::IsKeyPressed('T'))
		Cashier.rotateA += (float) 50 * dt;
	//Rotate clockwise
	if(Application::IsKeyPressed('F'))
		Cashier.rotateA -= (float) 50 * dt;
}
void SceneSP::Update(double dt)
{
	interactionTimer+=dt;
	if(i_menuHandle == MAIN_MENU || i_menuHandle == SUB_MENU)
	{
		UpdateMenu();
	}
	if(i_menuHandle == GAME_PLAYING)
	{
		UpdatePlaying(dt);
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
							camera.position.y += dt*elevatorSpeed;
							camera.target.y +=dt*elevatorSpeed;
							elevatorY+=dt*elevatorSpeed;
							elevatorIdle = false;
						}
						else if(elevatorSecondFloor)
						{
							//Move elevator down
							camera.position.y-=dt*elevatorSpeed;
							camera.target.y-=dt*elevatorSpeed;
							elevatorY-=dt*elevatorSpeed;
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
			elevatorDoorY+=dt*5;
		}
	}
	else //if door is closing
	{
		if(!(elevatorDoorY < checkElevatorYposMin))
		{
			elevatorDoorY-= dt*5;
		}
	}
}
void SceneSP::UpdateDoor(double dt)
{
	//Front door control
	if((camera.position.z < 50.0f && camera.position.z > 0.0f) && (camera.position.x > -30.0f  && camera.position.x < -10.0f))
		toggleDoorFront = true;
	else
		toggleDoorFront = false;
	if(toggleDoorFront)
	{
		if(moveDoorFront > -8.0f)
			moveDoorFront -= 10.0f * dt;
	}
	else
	{
		if(moveDoorFront < 0.0f)
			moveDoorFront += 10.0f * dt;
	}
	//Back door control
	if((camera.position.z < 0.0f && camera.position.z > -50.0f) && (camera.position.x > 10.0f && camera.position.x < 35.0f))
		toggleDoorBack = true;
	else
		toggleDoorBack = false;
	if(toggleDoorBack)
	{
		if(moveDoorBack > -7.0f)
			moveDoorBack -= 10.0f * dt;
	}
	else
	{
		if(moveDoorBack < 0.0f)
			moveDoorBack += 10.0f * dt;
	}
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
void SceneSP::UpdateSamples()
{
	if(Application::IsKeyPressed('E') && interactionTimer > interactionTimerLimiter)
	{
		if((camera.position.x > 25.0f && camera.position.x < 35.0f) && (camera.position.z > -8.0f && camera.position.z < -2.0f))
		{
			interactionTimer = 0.0f;
			i_sampleItems--;
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
		camera.position.x -= 0.001*camera.CAMERA_SPEED;
		camera.target.x -= 0.001*camera.CAMERA_SPEED;
		if(Application::IsKeyPressed(VK_SPACE) && interactionTimer > TugofwarTimerLimiter)
		{//update camera based on tugs
			interactionTimer = 0.0f;
			camera.position.x += 0.025*camera.CAMERA_SPEED;
			camera.target.x += 0.025*camera.CAMERA_SPEED;
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
void SceneSP::UpdateDrunkman(double dt)
{
	myNPCList[1]->setRotation(90);

}
void SceneSP::UpdateTugofwarguy(double dt)
{
	if(!IsIntugofwar)
	{
		myNPCList[0]->setRotation(0);
		myNPCList[0]->setXpos(7.0f);
		myNPCList[0]->setZpos(1.5f);
		myNPCList[0]->setLeftArm(30);
		myNPCList[0]->setRightArm(-30);
	}
	else //if(IsIntugofwar)
	{
		myNPCList[0]->setRotation(90);
		myNPCList[0]->setXpos(camera.position.x - 4);
		myNPCList[0]->setZpos(camera.position.z);
		myNPCList[0]->setLeftArm(40);
	}
}
void SceneSP::UpdateWalkingman(double dt)
{
	myNPCList[2]->setLeftArm(20);
	myNPCList[2]->setRightArm(-20);
	if(myNPCList[2]->getCharacterState()==0)
	{
		myNPCList[2]->setZpos(myNPCList[2]->getZpos()+(5 * dt));
		if(myNPCList[2]->getZpos() > 22)
		{
			myNPCList[2]->setCharacterState(1);
			myNPCList[2]->setRotation(90);
			myNPCList[2]->setZpos(21);
		}
	}
	if(myNPCList[2]->getCharacterState()==1)
	{
		myNPCList[2]->setXpos(myNPCList[2]->getXpos()+(5 * dt));
		if(myNPCList[2]->getXpos() > 33)
		{
			myNPCList[2]->setCharacterState(2);
			myNPCList[2]->setRotation(180);
			myNPCList[2]->setXpos(32);
		}
	}
	if(myNPCList[2]->getCharacterState()==2)
	{
		myNPCList[2]->setZpos(myNPCList[2]->getZpos()-(5 * dt));
		if(myNPCList[2]->getZpos() < 12)
		{
			myNPCList[2]->setCharacterState(3);
			myNPCList[2]->setRotation(-90);
			myNPCList[2]->setZpos(13);
		}
	}
	if(myNPCList[2]->getCharacterState()==3)
	{
		myNPCList[2]->setXpos(myNPCList[2]->getXpos()-(5 * dt));
		if(myNPCList[2]->getXpos() < -6)
		{
			myNPCList[2]->setCharacterState(0);
			myNPCList[2]->setRotation(0);
			myNPCList[2]->setXpos(-5);
		}
	}
}
void SceneSP::RenderUI()
{
	//RenderText(meshList[GEO_UI_SCREEN],"",Color(),1,0,0);
	RenderTGAUI(meshList[GEO_UI_SCREEN],1,40,20);
	RenderTextOnScreen(meshList[GEO_TEXT], "Money: $"+ s_money, Color(0, 1, 0), 3,0, 19);
	RenderTextOnScreen(meshList[GEO_TEXT], "Target: "+ s_camera_target, Color(0, 1, 0), 2,0, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS: "+ s_fps, Color(0, 1, 0), 3,0, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], "(X,Y,Z): "+ s_position, Color(0, 1, 0), 2, 0, 0);
	RenderTugofwarUI();
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
		RenderMainMenu();

		break;
		//Do sub menu here
	case SUB_MENU:
		RenderSubMenu();
		break;
	case GAME_PLAYING:
		RenderHand();
		RenderSkyBox();		//Renders out Skybox
		RenderCharacters();//Render out characters
		RenderItem();		//Renders out items
		RenderTug();
		RenderSupermarket();//Renders out Supermarket
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
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-22.9f, 2.5f, -21.1f);
	RenderMesh(meshList[GEO_FENCE], toggleLight);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-22.9f, 2.5f, -16.f);
	RenderMesh(meshList[GEO_FENCE], toggleLight);
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
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-12.9f, 2.5f, -16.f);
	RenderMesh(meshList[GEO_FENCE], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-2.9f, 2.5f, -21.1f);
	RenderMesh(meshList[GEO_FENCE], toggleLight);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-2.9f, 2.5f, -16.f);
	RenderMesh(meshList[GEO_FENCE], toggleLight);
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
	
	//Free will hands
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x,camera.position.y,camera.position.z);

	{
		/*
		modelStack.PushMatrix();
		modelStack.Rotate((180+trolleyrotation),0,1,0);
		modelStack.Rotate(-45,1,0,0);
		modelStack.Translate(0.5,-1.5,2.5);
		RenderMesh(meshList[GEO_HANDS], toggleLight);
		modelStack.PopMatrix();
		*/
		modelStack.PushMatrix();
		modelStack.Rotate((180+handrotationleftandright),0,1,0);
		modelStack.Translate(-0.2,-4.5,-1+handtranslation);
		RenderMesh(meshList[GEO_HANDS], toggleLight);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();


	//Render ITEM on HAND
	//TODO: Inspect rotation
	
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
	/*//Hands on trolley
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x,0,camera.position.z);
	{
	modelStack.PushMatrix();
	modelStack.Rotate((180+trolleyrotation),0,1,0);
	modelStack.Translate(-0.25,0,-0.7);
	RenderMesh(meshList[GEO_HANDS], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate((180+trolleyrotation),0,1,0);
	modelStack.Translate(0.6,0,-0.7);
	RenderMesh(meshList[GEO_HANDS], toggleLight);
	modelStack.PopMatrix();
	}
	modelStack.PopMatrix();*/
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
	modelStack.Rotate(npc->getRotation(),0,1,0);
	modelStack.PushMatrix();

	//head and body
	RenderMesh(meshList[npc->getHeadType()], toggleLight);

	//Left arm
	modelStack.PushMatrix();
	modelStack.Translate(0.3 , 0.0, 0);
	modelStack.Rotate(npc->getLeftArm(),0,1,0);
	RenderMesh(meshList[npc->getArmType()], toggleLight);
	modelStack.PopMatrix();
	//Right arm
	modelStack.PushMatrix();
	modelStack.Translate(-0.3 , 0.0, 0);
	modelStack.Rotate(npc->getRightArm(),0, 1,0);
	RenderMesh(meshList[npc->getArmType()], toggleLight);
	modelStack.PopMatrix();
	//leg and feet
	modelStack.PushMatrix();
	modelStack.Translate(0.2, 2.3, 0);
	modelStack.Rotate(npc->getLeftLeg(),1,0,0);
	RenderMesh(meshList[npc->getLegType()], toggleLight);
	modelStack.PopMatrix();
	//leg and feet 
	modelStack.PushMatrix();
	modelStack.Translate(-0.2, 2.3, 0);
	modelStack.Rotate(npc->getRightLeg(),1,0,0);
	RenderMesh(meshList[npc->getLegType()], toggleLight);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}
void SceneSP::RenderMainMenu()
{
	RenderTGAUI(meshList[GEO_MAIN_MENU_TITLE], 3, 40, 40);
	RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_START], Color(0, 1, 0), 2, 17, 15);
	RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_CREDIT], Color(0, 1, 0), 2, 17, 14);
	RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_EXIT], Color(0, 1, 0), 2, 17, 13);
	if(selectionPointing == MENU_START)//If pointing at START button
	{
		RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_START], Color(1, 1, 0), 2, 17, 15);
	}
	if(selectionPointing == MENU_CREDIT)//If pointing at START button
	{
		RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_CREDIT], Color(1, 1, 0), 2, 17, 14);
	}
	if(selectionPointing == MENU_EXIT)//If pointing at START button
	{
		RenderTextOnScreen(meshList[GEO_TEXT], menuTextArray[MENU_EXIT], Color(1, 1, 0), 2, 17, 13);
	}
}
void SceneSP::RenderSubMenu()
{
	RenderTGAUI(meshList[GEO_MAIN_MENU_TITLE], 3, 40, 40);
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
void SceneSP::RenderCharacters()
{
	for(unsigned int i = 0; i< myNPCList.size(); ++i)
	{
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
	RenderShelves();		//Render Shelves in Supermarket
	RenderSamplestand();	//Render Sample Food Stand in Supermarket
	RenderCashierTables();	//Render Cashier table in Supermarket
	RenderFence();          //Render Fence in Supermarket
	RenderElevator();       //Render Elevator in Supermarket
	RenderTrolleys();       //Render Trolleys in Supermarket
	RenderReturnPoint();	//Render Return Point in Supermarket


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
		modelStack.Translate(1.5f - (x * 1), 3.6f, 25.0f);
		RenderMesh(meshList[GEO_CAN_SARDINE], toggleLight);
		modelStack.PopMatrix();
	}
}
void SceneSP::RenderReturnPoint()
{
	//-37.f, 0.2f, 13.f
	modelStack.PushMatrix();
	modelStack.Translate(returnPointBoxPosX, returnPointBoxPosY, returnPointBoxPosZ);
	RenderMesh(meshList[GEO_ICEBOX], toggleLight);
	modelStack.PopMatrix();
}
void SceneSP::RenderSamplestand() //added the container and trolley here for now 
{
	modelStack.PushMatrix();
	modelStack.Translate(10.0f,0.0f,-5.0f);
	modelStack.Rotate(90.0f,0,1,0);	
	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 0.0f, 25.0f);
	RenderMesh(meshList[GEO_SAMPLESTAND], toggleLight);
	modelStack.PopMatrix();
	RenderSamples();
	modelStack.PopMatrix();

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

	modelStack.PushMatrix();
	modelStack.Translate(-21.0f,0.0f,11.0f);
	RenderMesh(meshList[GEO_FOODSHELF], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-19.0f,17.0f,0.0f);
	RenderMesh(meshList[GEO_FOODSHELF], toggleLight);
	modelStack.PopMatrix();

}
void SceneSP::RenderTug()
{
	if(IsIntugofwar)
	{
		modelStack.PushMatrix();
		modelStack.Translate(myNPCList[0]->getXpos()+2,myNPCList[0]->getYpos()+3.6,myNPCList[0]->getZpos()-1);
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
		RenderTGAInventory(meshList[ptrplayer->getVector()[i]->getGeoType()],3,22.3+(i*5),0.5);
	}
}
void SceneSP::checkPickUpItem()
{
	if(Application::IsKeyPressed('E') && interactionTimer > interactionTimerLimiter)
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
						if(ptrplayer->getItem(inventoryPointing)->getName() == emptyItem.getName())
						{
							addToInventory(myStockList[chosen]);
							myStockList[chosen]->setActiveState(false);
							std::cout << "Item " <<myStockList[chosen]->getName() << " removed! \n";
						}
					}
				}

			}
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
	}
}
void SceneSP::checkShelfCollision()
{
	if(camera.position.y < 10)
	{
		//1st row
		if((camera.position.x > SboundX1 && camera.position.x < SboundX2) && (camera.position.z > SboundZ1 && camera.position.z < SboundZ2))
		{
			diffZ = camera.position.z - (SboundZ1);
			camera.position.z = SboundZ1;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if((camera.position.x > SboundX1 && camera.position.x < SboundX3) && (camera.position.z > SboundZ2 && camera.position.z < SboundZ3))
		{
			diffX = camera.position.x - (SboundX1);
			camera.position.x = SboundX1;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		if((camera.position.x > SboundX4 && camera.position.x < SboundX2) && (camera.position.z > SboundZ2 && camera.position.z < SboundZ3))
		{
			diffX = camera.position.x - (SboundX2);
			camera.position.x = SboundX2;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		//2nd row
		if((camera.position.x > SboundX1 && camera.position.x < SboundX2) && (camera.position.z > SboundZ4 && camera.position.z < SboundZ5))
		{
			diffZ = camera.position.z - (SboundZ4);
			camera.position.z = SboundZ4;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if((camera.position.x > SboundX1 && camera.position.x < SboundX2) && (camera.position.z > SboundZ6 && camera.position.z < SboundZ7))
		{
			diffZ = camera.position.z - (SboundZ7);
			camera.position.z = SboundZ7;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if((camera.position.x > SboundX1 && camera.position.x < SboundX3) && (camera.position.z > SboundZ5 && camera.position.z < SboundZ8))
		{
			diffX = camera.position.x - (SboundX1);
			camera.position.x = SboundX1;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		if((camera.position.x > SboundX4 && camera.position.x < SboundX2) && (camera.position.z > SboundZ5 && camera.position.z < SboundZ8))
		{
			diffX = camera.position.x - (SboundX2);
			camera.position.x = SboundX2;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		//3rd row
		if((camera.position.x > SboundX1 && camera.position.x < SboundX2) && (camera.position.z > SboundZ9 && camera.position.z < SboundZ10))
		{
			diffZ = camera.position.z - (SboundZ9);
			camera.position.z = SboundZ9;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if((camera.position.x > SboundX1 && camera.position.x < SboundX2) && (camera.position.z > SboundZ11 && camera.position.z < SboundZ12))
		{
			diffZ = camera.position.z - (SboundZ12);
			camera.position.z = SboundZ12;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if((camera.position.x > SboundX1 && camera.position.x < SboundX3) && (camera.position.z > SboundZ10 && camera.position.z < SboundZ13))
		{
			diffX = camera.position.x - (SboundX1);
			camera.position.x = SboundX1;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		if((camera.position.x > SboundX4 && camera.position.x < SboundX2) && (camera.position.z > SboundZ10 && camera.position.z < SboundZ13))
		{
			diffX = camera.position.x - (SboundX2);
			camera.position.x = SboundX2;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
	}
}
void SceneSP::checkFreezerCollision()
{
	if(camera.position.y < 10)
	{
		if((camera.position.x > FboundX1 && camera.position.x < FboundX3) && (camera.position.z > FboundZ1 && camera.position.z < FboundZ2))
		{
			diffX = camera.position.x - (FboundX1);
			camera.position.x = FboundX1;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		if((camera.position.x > FboundX3 && camera.position.x < FboundX2) && (camera.position.z > FboundZ1 && camera.position.z < FboundZ3))
		{
			diffZ = camera.position.z - (FboundZ1);
			camera.position.z = FboundZ1;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
	}
}
void SceneSP::checkCashierCollision()
{
	if(camera.position.y < 10)
	{
		//Cashier table 1
		if((camera.position.x > CboundX1 && camera.position.x < CboundX2) && (camera.position.z > CboundZ1 && camera.position.z < CboundZ2))
		{
			diffX = camera.position.x - (CboundX2);
			camera.position.x = CboundX2;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		if((camera.position.x > CboundX3 && camera.position.x < CboundX2) && (camera.position.z > CboundZ3 && camera.position.z < CboundZ2))
		{
			diffZ = camera.position.z - (CboundZ2);
			camera.position.z = CboundZ2;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if((camera.position.x > CboundX3 && camera.position.x < CboundX4) && (camera.position.z > CboundZ1 && camera.position.z < CboundZ2))
		{
			diffX = camera.position.x - (CboundX3);
			camera.position.x = CboundX3;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		if((camera.position.x > CboundX3 && camera.position.x < CboundX2) && (camera.position.z > CboundZ1 && camera.position.z < CboundZ4))
		{
			diffZ = camera.position.z - (CboundZ1);
			camera.position.z = CboundZ1;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		//Cashier table 2
		if((camera.position.x > CboundX5 && camera.position.x < CboundX6) && (camera.position.z > CboundZ1 && camera.position.z < CboundZ2))
		{
			diffX = camera.position.x - (CboundX6);
			camera.position.x = CboundX6;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		if((camera.position.x > CboundX7 && camera.position.x < CboundX6) && (camera.position.z > CboundZ3 && camera.position.z < CboundZ2))
		{
			diffZ = camera.position.z - (CboundZ2);
			camera.position.z = CboundZ2;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if((camera.position.x > CboundX7 && camera.position.x < CboundX8) && (camera.position.z > CboundZ1 && camera.position.z < CboundZ2))
		{
			diffX = camera.position.x - (CboundX7);
			camera.position.x = CboundX7;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		if((camera.position.x > CboundX7 && camera.position.x < CboundX6) && (camera.position.z > CboundZ1 && camera.position.z < CboundZ4))
		{
			diffZ = camera.position.z - (CboundZ1);
			camera.position.z = CboundZ1;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		//Cashier table 3
		if((camera.position.x > CboundX9 && camera.position.x < CboundX10) && (camera.position.z > CboundZ5 && camera.position.z < CboundZ2))
		{
			diffX = camera.position.x - (CboundX10);
			camera.position.x = CboundX10;
			camera.target.x -= diffX;
			diffX = 0.0f;
		}
		if((camera.position.x > CboundX11 && camera.position.x < CboundX10) && (camera.position.z > CboundZ3 && camera.position.z < CboundZ2))
		{
			diffZ = camera.position.z - (CboundZ2);
			camera.position.z = CboundZ2;
			camera.target.z -= diffZ;
			diffZ = 0.0f;
		}
		if((camera.position.x > CboundX11 && camera.position.x < CboundX12) && (camera.position.z > CboundZ5 && camera.position.z < CboundZ2))
		{
			diffX = camera.position.x - (CboundX11);
			camera.position.x = CboundX11;
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
void SceneSP::checkReturnPoint()
{
	//If triggering interaction
	if(Application::IsKeyPressed('E') && interactionTimer > interactionTimerLimiter)
	{
		//If within RETURN POINT boundary
		if((camera.position.x > returnPointBoxPosX-returnPointBoxWidthOffset)&& camera.position.x < (returnPointBoxPosX+returnPointBoxInteractionWidth+returnPointBoxWidthOffset))
		{
			if(camera.position.z > (returnPointBoxPosZ - returnPointBoxInteractionLength) && camera.position.z < (returnPointBoxPosZ + returnPointBoxInteractionLength))
			{
				if(camera.position.y > returnPointBoxPosY && camera.position.y < (returnPointBoxPosY + returnPointBoxInteractionHeight))
				{
					//Is within boundary
					interactionTimer = 0;
					std::cout << "Item returned: " <<ptrplayer->getItem(inventoryPointing)->getName() << std::endl;
					ptrplayer->setInventory(&emptyItem,inventoryPointing);
					ptrInvSelect = ptrplayer->getItem(inventoryPointing);
					
				}
			}
		}
	}
}
void SceneSP::checkNPCCollision()
{
	for(unsigned int i = 0; i< myNPCList.size(); ++i)
	{
		if((camera.position.y - myNPCList[i]->getYpos() < 10) && (camera.position.y - myNPCList[i]->getYpos() > 0))
		{
			//check z
			if((camera.position.x > myNPCList[i]->getXpos()-2 && camera.position.x < myNPCList[i]->getXpos()+2) && 
				(camera.position.z > myNPCList[i]->getZpos()+1 && camera.position.z < myNPCList[i]->getZpos()+2))
			{
				diffZ = camera.position.z - (myNPCList[i]->getZpos()+2);
				camera.position.z = myNPCList[i]->getZpos()+2;
				camera.target.z -= diffZ;
				diffZ = 0.0f;
			}
			if((camera.position.x > myNPCList[i]->getXpos()-2 && camera.position.x < myNPCList[i]->getXpos()+2) && 
				(camera.position.z > myNPCList[i]->getZpos()-2 && camera.position.z < myNPCList[i]->getZpos()-1))
			{
				diffZ = camera.position.z - (myNPCList[i]->getZpos()-2);
				camera.position.z = myNPCList[i]->getZpos()-2;
				camera.target.z -= diffZ;
				diffZ = 0.0f;
			}
			//check x
			if((camera.position.x > myNPCList[i]->getXpos()+1 && camera.position.x < myNPCList[i]->getXpos()+2) && 
				(camera.position.z > myNPCList[i]->getZpos()-2 && camera.position.z < myNPCList[i]->getZpos()+2))
			{
				diffX = camera.position.x - (myNPCList[i]->getXpos()+2);
				camera.position.x = myNPCList[i]->getXpos()+2;
				camera.target.x -= diffX;
				diffX = 0.0f;
			}
			if((camera.position.x > myNPCList[i]->getXpos()-2 && camera.position.x < myNPCList[i]->getXpos()-1) && 
				(camera.position.z > myNPCList[i]->getZpos()-2 && camera.position.z < myNPCList[i]->getZpos()+2))
			{
				diffX = camera.position.x - (myNPCList[i]->getXpos()-2);
				camera.position.x = myNPCList[i]->getXpos()-2;
				camera.target.x -= diffX;
				diffX = 0.0f;
			}
		}
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
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

