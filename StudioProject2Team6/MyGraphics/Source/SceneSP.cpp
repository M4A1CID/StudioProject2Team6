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
	world_size = 3000.0f;

	initCharacter(); //Initilize the player
	initGeoType(); //Initilize all Geo Types
	initItems(); //Initilize all items
	initShelves();//Initilize all shelves
	toggleLight = true;
	toggleDoorFront = false;
	toggleDoorBack = false;
	interactionTimer = 0.0f;
	moveDoorFront = 0.0f;
	moveDoorBack = 0.0f;
	trolleyrotation = 0.0f;
	diffX = 0.0f;
	diffZ = 0.0f;
	charactersrotation = 20.0f;
	i_sampleItems = 4;
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
	meshList[GEO_DOOR] = MeshBuilder::GenerateOBJ("door", "OBJ//door.obj");
	meshList[GEO_DOOR]->textureID = LoadTGA("Image//supermarket.tga");
	meshList[GEO_TROLLEY] = MeshBuilder::GenerateOBJ("trolley", "OBJ//trolley.obj");
	meshList[GEO_TROLLEY]->textureID = LoadTGA("Image//trolley.tga");
	meshList[GEO_SAMPLESTAND] = MeshBuilder::GenerateOBJ("samplestand", "OBJ//sample_stand.obj");
	meshList[GEO_SAMPLESTAND]->textureID = LoadTGA("Image//sample_stand.tga");
	meshList[GEO_ICEBOX] = MeshBuilder::GenerateOBJ("Icebox", "OBJ//Container.obj");
	meshList[GEO_ICEBOX]->textureID = LoadTGA("Image//ContainerTexture.tga");
	meshList[GEO_SHELF] = MeshBuilder::GenerateOBJ("shelf", "OBJ//shelf.obj");
	meshList[GEO_SHELF]->textureID = LoadTGA("Image//supermarket.tga");
	meshList[GEO_CASHIER] = MeshBuilder::GenerateOBJ("cashier", "OBJ//cashiertable.obj");
	meshList[GEO_CASHIER]->textureID = LoadTGA("Image//cashRegisterTexture.tga");
	meshList[GEO_FENCE] = MeshBuilder::GenerateOBJ("fence", "OBJ//Fence.obj");
	meshList[GEO_FENCE]->textureID = LoadTGA("Image//cashRegisterTexture.tga");
	meshList[GEO_ELEVATOR] = MeshBuilder::GenerateOBJ("elevator", "OBJ//Elevator.obj");
	meshList[GEO_ELEVATOR]->textureID = LoadTGA("Image//supermarket.tga");
	meshList[GEO_ELEVATORDOOR] = MeshBuilder::GenerateOBJ("elevatordoor", "OBJ//Elevatordoor.obj");
	meshList[GEO_ELEVATORDOOR]->textureID = LoadTGA("Image//supermarket.tga");
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
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//skybox_front.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f,true);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//skybox_bottom.tga",true);
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//skybox_back.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//skybox_top.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//skybox_left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//skybox_right.tga");
	meshList[GEO_SHELF] = MeshBuilder::GenerateOBJ("shelf", "OBJ//shelf.obj");
	meshList[GEO_SHELF]->textureID = LoadTGA("Image//supermarket.tga");
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

	ptrNPC = new CNpc(0,0,0,GEO_DRUNKMAN_HEADBODY,GEO_DRUNKMAN_ARM,GEO_DRUNKMAN_LEGANDFEET,IDLE,DRUNKMAN);
	myNPCList.push_back(ptrNPC);
}
void SceneSP::initItems()
{
	//Init items	
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
	ptrClass = new CSodaCan;//RW
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf13",5,5,5,26,0,6,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CSodaFestCan;//RW
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf14",5,5,5,20,0,6,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CRedMonsterCan;//RW
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf15",5,5,5,14,0,6,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CTomatoCan;//RW
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf24",5,5,5,8,0,6,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	ptrClass = new CMelonCan;//RW
	ptrContainer = new CContainer(ptrClass,ptrClass,ptrClass,"Shelf25",5,5,5,2,0,6,0);
	myContainerList.push_back(ptrContainer);
	DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	//==================================================================================
	//				FROZEN FOOD ZONE
	//===================================================================================
	//ptrContainer = new CContainereasterEgg1,easterEgg1,easterEgg1,"ShelfTen",5,5,5,38,0,24,270);
	//myContainerList.push_back(ptrContainer);
	//DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	//DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	//DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	//ptrContainer = new CContainer(cerealBox4,cerealBox4,cerealBox4,"ShelfEleven",5,5,5,38,0,18,270);
	//myContainerList.push_back(ptrContainer);
	//DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	//DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	//DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row

	//ptrContainer = new CContainer(cerealBox5,cerealBox5,cerealBox5,"ShelfTwelve",5,5,5,38,0,12,270);
	//myContainerList.push_back(ptrContainer);
	//DefineItem(ptrContainer,ptrContainer->getTopItem(),ROW_TOP);		//Top row
	//DefineItem(ptrContainer,ptrContainer->getMiddleItem(),ROW_MIDDLE);	//Middle row
	//DefineItem(ptrContainer,ptrContainer->getBottomItem(),ROW_BOTTOM);	//Bottom row
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

	ptrplayer->setInventory(pickedUp);
	std::cout<< "Inventory added: " << pickedUp->getName() << std::endl;
	std::cout<< "Current itms held: " << ptrplayer->getItemHeld() << std::endl;
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
void SceneSP::UpdateTrolley(double dt)
{
	if(Application::IsKeyPressed(VK_LEFT))
	{
		trolleyrotation += (camera.CAMERA_SPEED)*dt;
	}
	if(Application::IsKeyPressed(VK_RIGHT))
	{
		trolleyrotation -= (camera.CAMERA_SPEED)*dt;
	}
}
void SceneSP::Update(double dt)
{
	interactionTimer+=dt;
	if(Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	if(Application::IsKeyPressed('5'))
	{
		toggleLight = true;
	}
	if(Application::IsKeyPressed('6'))
	{
		toggleLight = false;
	}



	UpdateUI(dt);
	checkPickUpItem();
	camera.Update(dt);
	UpdateTrolley(dt);

	UpdateDoor(dt);
	UpdateSamples();
	checkSupermarketCollision();
	checkFreezerCollision();
	checkShelfCollision();
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
void SceneSP::RenderUI()
{

	//RenderText(meshList[GEO_UI_SCREEN],"",Color(),1,0,0);
	RenderTGAUI(meshList[GEO_UI_SCREEN],1,40,20);
	RenderTextOnScreen(meshList[GEO_TEXT], "Money: $"+ s_money, Color(0, 1, 0), 3,0, 19);
	RenderTextOnScreen(meshList[GEO_TEXT], "Target: "+ s_camera_target, Color(0, 1, 0), 2,0, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS: "+ s_fps, Color(0, 1, 0), 3,0, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], "(X,Y,Z): "+ s_position, Color(0, 1, 0), 2, 0, 0);
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

	RenderMesh(meshList[GEO_AXES],false);



	RenderSkyBox();		//Renders out Skybox
	RenderSupermarket();//Renders out Supermarket
	RenderFence();
	RenderElevator();

	RenderCharacters();//Render out characters
	RenderItem();		//Renders out items
	RenderUI();			//Renders out UI
	RenderInventory();	//Render inventory after UI to place above
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
	modelStack.Rotate(90, 1 ,0, 0);
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
	modelStack.Translate(RenderElevatorPosX, 0, RenderElevatorPosZ);
	RenderMesh(meshList[GEO_ELEVATOR], toggleLight);
	modelStack.PushMatrix();

	modelStack.Translate(ElevatorDoorPosX, 0,ElevatorDoorPosY);
	RenderMesh(meshList[GEO_ELEVATORDOOR], toggleLight);
	modelStack.PopMatrix();
	modelStack.PopMatrix();     

}
void SceneSP::RenderFence()
{
	modelStack.PushMatrix();
	modelStack.Translate(-22.9, 2.5, -26);
	RenderMesh(meshList[GEO_FENCE], toggleLight);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-22.9, 2.5, -21.1);
	RenderMesh(meshList[GEO_FENCE], toggleLight);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-22.9, 2.5, -16);
	RenderMesh(meshList[GEO_FENCE], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-30.5, 2.5, -18);
	RenderMesh(meshList[GEO_FENCE], toggleLight);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-30.5, 2.5, -12.1);
	RenderMesh(meshList[GEO_FENCE], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-12.9, 2.5, -21.1);
	RenderMesh(meshList[GEO_FENCE], toggleLight);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-12.9, 2.5, -16);
	RenderMesh(meshList[GEO_FENCE], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-2.9, 2.5, -21.1);
	RenderMesh(meshList[GEO_FENCE], toggleLight);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(-2.9, 2.5, -16);
	RenderMesh(meshList[GEO_FENCE], toggleLight);
	modelStack.PopMatrix();
}
void SceneSP::RenderCashierTables()
{
	modelStack.PushMatrix();
	modelStack.Translate(-26, 0, -15);
	modelStack.Rotate(180,0,1,0);
	RenderMesh(meshList[GEO_CASHIER], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-16, 0, -15);
	modelStack.Rotate(180,0,1,0);
	RenderMesh(meshList[GEO_CASHIER], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-6, 0, -15);
	modelStack.Rotate(180,0,1,0);
	RenderMesh(meshList[GEO_CASHIER], toggleLight);
	modelStack.PopMatrix();


}
void SceneSP::RenderTrolleys()
{
	modelStack.PushMatrix();
	modelStack.Translate(-37, 0.2, 13);
	modelStack.Rotate(0,0,1,0);
	RenderMesh(meshList[GEO_TROLLEY], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-37, 0.2, 15);
	modelStack.Rotate(0,0,1,0);
	RenderMesh(meshList[GEO_TROLLEY], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-37, 0.2, 17);
	modelStack.Rotate(0,0,1,0);
	RenderMesh(meshList[GEO_TROLLEY], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-37, 0.2, 19);
	modelStack.Rotate(0,0,1,0);
	RenderMesh(meshList[GEO_TROLLEY], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-37, 0.2, 21);
	modelStack.Rotate(0,0,1,0);
	RenderMesh(meshList[GEO_TROLLEY], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-37, 0.2, 23);
	modelStack.Rotate(0,0,1,0);
	RenderMesh(meshList[GEO_TROLLEY], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-37, 0.2, 25);
	modelStack.Rotate(0,0,1,0);
	RenderMesh(meshList[GEO_TROLLEY], toggleLight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-37, 0.2, 27);
	modelStack.Rotate(0,0,1,0);
	RenderMesh(meshList[GEO_TROLLEY], toggleLight);
	modelStack.PopMatrix();

	if(true)
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
	modelStack.PushMatrix();

	//head and body
	RenderMesh(meshList[npc->getHeadType()], toggleLight);

	//arm
	modelStack.PushMatrix();
	modelStack.Translate(0.3 , 0.3, 0);
	modelStack.Rotate(90,0,1,0);
	RenderMesh(meshList[npc->getArmType()], toggleLight);
	modelStack.PopMatrix();
	//arm
	modelStack.PushMatrix();
	modelStack.Translate(-0.3 , 0.3, 0);
	modelStack.Rotate(270,0, 1,0);
	RenderMesh(meshList[npc->getArmType()], toggleLight);
	modelStack.PopMatrix();
	//leg and feet
	modelStack.PushMatrix();
	modelStack.Translate(0.2, 0, 0);
	RenderMesh(meshList[npc->getLegType()], toggleLight);
	modelStack.PopMatrix();
	//leg and feet 
	modelStack.PushMatrix();
	modelStack.Translate(-0.2, 0, 0);
	RenderMesh(meshList[npc->getLegType()], toggleLight);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}


void SceneSP::RenderCharacters()
{
	for(int i = 0; i< myNPCList.size(); ++i)
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
	RenderShelves();		//Render Shelves in Supermarket
	RenderDoors();			//Render Doors in Supermarket
	RenderSamplestand();	//Render Sample Food Stand in Supermarket
	RenderCashierTables();	//Render Cashier table in Supermarket
	RenderTrolleys();
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
	for(unsigned int i = 0; i< ptrplayer->getItemHeld();++i)
	{
		RenderTGAInventory(meshList[ptrplayer->getVector()[i]->getGeoType()],3,22.3+(i*5),0.5);
	}
}
void SceneSP::checkPickUpItem()
{
	if(Application::IsKeyPressed('E') && interactionTimer > interactionTimerLimiter)
	{

		for(unsigned int i = 0; i<myStockList.size();++i)
		{

			if(myStockList[i]->getActiveState())
			{
				if(camera.target.x >= myStockList[i]->getXpos()) //If camera X is greater than item X
				{
					if(((camera.target.x - myStockList[i]->getXpos()) <interactionDistanceX)&& (camera.target.x - myStockList[i]->getXpos()) >-interactionDistanceX) //If width is within 0.5f
					{
						if(camera.target.z >= myStockList[i]->getZpos()) //If camera Z is greater than item Z
						{
							if((camera.target.z - myStockList[i]->getZpos()) < interactionDistanceZ) //If width is within interactionDistanceZ
							{
								if(camera.target.y > interactionDistanceYMax && myStockList[i]->getYpos() > interactionDistanceYMax) //If looking at top row
								{
									if(ptrplayer->getItemHeld() < ptrplayer->getMaxItemCapacity())
									{
										addToInventory(myStockList[i]);
										myStockList[i]->setActiveState(false);
										std::cout << "Item " <<myStockList[i]->getName() << " removed! \n";
										break;
									}
								}
								else if (camera.target.y > interactionDistanceYMin && camera.target.y < interactionDistanceYMax) //If looking at middle row
								{
									if(myStockList[i]->getYpos()+2 >= interactionDistanceYMin && myStockList[i]->getYpos()<=interactionDistanceYMax)
									{
										if(ptrplayer->getItemHeld() < ptrplayer->getMaxItemCapacity())
										{
											addToInventory(myStockList[i]);
											myStockList[i]->setActiveState(false);
											std::cout << "Item " <<myStockList[i]->getName() << " removed! \n";
											break;
										}
									}
								}
								else //Looking at bottom row
								{
									if(camera.target.y < interactionDistanceYMin)
									{
										if(ptrplayer->getItemHeld() < ptrplayer->getMaxItemCapacity())
										{
											addToInventory(myStockList[i]);
											myStockList[i]->setActiveState(false);
											std::cout << "Item " <<myStockList[i]->getName() << " removed! \n";
											break;
										}
									}
								}
							}
						}
						else if(camera.target.z < myStockList[i]->getZpos()) //If item Z is greater than camera z
						{
							if((myStockList[i]->getZpos() - camera.target.z) < interactionDistanceZ)//If width is within interactionDistanceZ
							{
								if(camera.target.y > interactionDistanceYMax && myStockList[i]->getYpos() > interactionDistanceYMax) //If looking at top row
								{
									if(ptrplayer->getItemHeld() < ptrplayer->getMaxItemCapacity())
									{
										addToInventory(myStockList[i]);
										myStockList[i]->setActiveState(false);
										std::cout << "Item " <<myStockList[i]->getName() << " removed! \n";
										break;
									}
								}
								else if (camera.target.y > interactionDistanceYMin && camera.target.y < interactionDistanceYMax) //If looking at middle row
								{
									if(myStockList[i]->getYpos()+2 >= interactionDistanceYMin && myStockList[i]->getYpos()<=interactionDistanceYMax)
									{
										if(ptrplayer->getItemHeld() < ptrplayer->getMaxItemCapacity())
										{
											addToInventory(myStockList[i]);
											myStockList[i]->setActiveState(false);
											std::cout << "Item " <<myStockList[i]->getName() << " removed! \n";
											break;
										}
									}
								}
								else //Looking at bottom row
								{
									if(camera.target.y < interactionDistanceYMin)
									{
										if(ptrplayer->getItemHeld() < ptrplayer->getMaxItemCapacity())
										{
											addToInventory(myStockList[i]);
											myStockList[i]->setActiveState(false);
											std::cout << "Item " <<myStockList[i]->getName() << " removed! \n";
											break;
										}
									}
								}

							}
						}

					}
				}
				else if(camera.target.x < myStockList[i]->getXpos())//If item X  is greater than camera X
				{
					if((myStockList[i]->getXpos() - camera.target.x) < interactionDistanceX && (myStockList[i]->getXpos() - camera.target.x) > -interactionDistanceX) //If width is within 0.5f
					{
						if(camera.target.z >= myStockList[i]->getZpos()) //If camera Z is greater than item Z
						{
							if((camera.target.z - myStockList[i]->getZpos()) < interactionDistanceZ) //If width is within interactionDistanceZ
							{
								if((camera.target.y > interactionDistanceYMax) && (myStockList[i]->getYpos() > interactionDistanceYMax)) //If looking at top row
								{
									if(ptrplayer->getItemHeld() < ptrplayer->getMaxItemCapacity())
									{
										addToInventory(myStockList[i]);
										myStockList[i]->setActiveState(false);
										std::cout << "Item " <<myStockList[i]->getName() << " removed! \n";
										break;
									}
								}
								else if (camera.target.y >= interactionDistanceYMin && camera.target.y <= interactionDistanceYMax) //If looking at middle row
								{
									if(myStockList[i]->getYpos()+2 >= interactionDistanceYMin && myStockList[i]->getYpos()<=interactionDistanceYMax)
									{
										if(ptrplayer->getItemHeld() < ptrplayer->getMaxItemCapacity())
										{
											addToInventory(myStockList[i]);
											myStockList[i]->setActiveState(false);
											std::cout << "Item " <<myStockList[i]->getName() << " removed! \n";
											break;
										}
									}
								}
								else //Looking at bottom row
								{
									if(camera.target.y < interactionDistanceYMin)
									{
										if(ptrplayer->getItemHeld() < ptrplayer->getMaxItemCapacity())
										{
											addToInventory(myStockList[i]);
											myStockList[i]->setActiveState(false);
											std::cout << "Item " <<myStockList[i]->getName() << " removed! \n";
											break;
										}
									}
								}

							}
						}
						else if(camera.target.z < myStockList[i]->getZpos()) //If item Z is greater than camera z
						{
							if((myStockList[i]->getZpos() - camera.target.z) < interactionDistanceZ)//If width is within interactionDistanceZ
							{
								if(camera.target.y > interactionDistanceYMax && myStockList[i]->getYpos() > interactionDistanceYMax) //If looking at top row
								{
									if(ptrplayer->getItemHeld() < ptrplayer->getMaxItemCapacity())
									{
										addToInventory(myStockList[i]);
										myStockList[i]->setActiveState(false);
										std::cout << "Item " <<myStockList[i]->getName() << " removed! \n";
										break;
									}
								}
								else if (camera.target.y > interactionDistanceYMin && camera.target.y < interactionDistanceYMax) //If looking at middle row
								{
									if(myStockList[i]->getYpos()+2 >= interactionDistanceYMin && myStockList[i]->getYpos()<=interactionDistanceYMax)
									{
										if(ptrplayer->getItemHeld() < ptrplayer->getMaxItemCapacity())
										{
											addToInventory(myStockList[i]);
											myStockList[i]->setActiveState(false);
											std::cout << "Item " <<myStockList[i]->getName() << " removed! \n";
											break;
										}
									}
								}
								else //Looking at bottom row
								{
									if(camera.target.y < interactionDistanceYMin)
									{
										if(ptrplayer->getItemHeld() < ptrplayer->getMaxItemCapacity())
										{
											addToInventory(myStockList[i]);
											myStockList[i]->setActiveState(false);
											std::cout << "Item " <<myStockList[i]->getName() << " removed! \n";
											break;
										}
									}
								}

							}
						}
					}
				}
			}

		}
	}

}
void SceneSP::checkSupermarketCollision()
{
	/*if(((camera.position.x > -41.0f && camera.position.x < -38.0f) && (camera.position.z > -31.0f && camera.position.z < 32.0f)) ||
	((camera.position.x > -41.0f && camera.position.x < 14.0f) && (camera.position.z > -31.0f && camera.position.z < -28.0f)) ||
	((camera.position.x > -41.0f && camera.position.x < -27.0f) && (camera.position.z > 29.0f && camera.position.z < 32.0f)) ||
	((camera.position.x > -12.0f && camera.position.x < 42.0f) && (camera.position.z > 29.0f && camera.position.z < 32.0f)) ||
	((camera.position.x > 39.0f && camera.position.x < 42.0f) && (camera.position.z > -31.0f && camera.position.z < 32.0f))
	)
	{
	camera.CAMERA_SPEED = -100.0f;
	}
	else
	camera.CAMERA_SPEED = 150.0f;*/
	if((camera.position.x > boundX1 && camera.position.x < boundX2) && (camera.position.z > boundZ1 && camera.position.z < boundZ2))
	{
		/*camera.position.x -= camera.CAMERA_SPEED*0.02;
		camera.target.x -= camera.CAMERA_SPEED*0.02;*/
		diffX = camera.position.x - (boundX1);
		camera.position.x = boundX1;
		camera.target.x -= diffX;
		diffX = 0.0f;
	}
	if((camera.position.x > boundX2 && camera.position.x < boundX3) && (camera.position.z > boundZ1 && camera.position.z < boundZ2))
	{
		/*camera.position.x += camera.CAMERA_SPEED*0.02;
		camera.target.x += camera.CAMERA_SPEED*0.02;*/
		diffX = camera.position.x - (boundX3);
		camera.position.x = boundX3;
		camera.target.x -= diffX;
		diffX = 0.0f;
	}
	if((camera.position.x > boundX1 && camera.position.x < boundX5) && (camera.position.z > boundZ1 && camera.position.z < boundZ3))
	{
		/*	camera.position.z -= camera.CAMERA_SPEED*0.02;
		camera.target.z -= camera.CAMERA_SPEED*0.02;*/
		diffZ = camera.position.z - (boundZ1);
		camera.position.z = boundZ1;
		camera.target.z -= diffZ;
		diffZ = 0.0f;
	}
	if((camera.position.x > boundX1 && camera.position.x < boundX5) && (camera.position.z > boundZ3 && camera.position.z < boundZ6))
	{
		/*camera.position.z += camera.CAMERA_SPEED*0.02;
		camera.target.z += camera.CAMERA_SPEED*0.02;*/
		diffZ = camera.position.z - (boundZ6);
		camera.position.z = boundZ6;
		camera.target.z -= diffZ;
		diffZ = 0.0f;
	}
	if((camera.position.x > boundX1 && camera.position.x < boundX6) && (camera.position.z > boundZ4 && camera.position.z < boundZ2))
	{
		/*	camera.position.z += camera.CAMERA_SPEED*0.02;
		camera.target.z += camera.CAMERA_SPEED*0.02;*/
		diffZ = camera.position.z - (boundZ2);
		camera.position.z = boundZ2;
		camera.target.z -= diffZ;
		diffZ = 0.0f;
	}
	if((camera.position.x > boundX1 && camera.position.x < boundX6) && (camera.position.z > boundZ5 && camera.position.z < boundZ4))
	{
		/*camera.position.z -= camera.CAMERA_SPEED*0.02;
		camera.target.z -= camera.CAMERA_SPEED*0.02;*/
		diffZ = camera.position.z - (boundZ5);
		camera.position.z = boundZ5;
		camera.target.z -= diffZ;
		diffZ = 0.0f;
	}
	if((camera.position.x > -12.0f && camera.position.x < boundX4) && (camera.position.z > boundZ4 && camera.position.z < boundZ2))
	{
		/*camera.position.z += camera.CAMERA_SPEED*0.02;
		camera.target.z += camera.CAMERA_SPEED*0.02;*/
		diffZ = camera.position.z - (boundZ2);
		camera.position.z = boundZ2;
		camera.target.z -= diffZ;
		diffZ = 0.0f;
	}
	if((camera.position.x > -12.0f && camera.position.x < boundX4) && (camera.position.z > boundZ5 && camera.position.z < boundZ4))
	{
		//camera.position.z -= camera.CAMERA_SPEED*0.02;
		//camera.target.z -= camera.CAMERA_SPEED*0.02;
		diffZ = camera.position.z - (boundZ5);
		camera.position.z = boundZ5;
		camera.target.z -= diffZ;
		diffZ = 0.0f;
	}
	if((camera.position.x > boundX7 && camera.position.x < boundX4) && (camera.position.z > boundZ1 && camera.position.z < boundZ2))
	{
		/*camera.position.x += camera.CAMERA_SPEED*0.02;
		camera.target.x += camera.CAMERA_SPEED*0.02;*/
		diffX = camera.position.x - (boundX4);
		camera.position.x = boundX4;
		camera.target.x -= diffX;
		diffX = 0.0f;
	}
	if((camera.position.x > boundX8 && camera.position.x < boundX7) && (camera.position.z > boundZ1 && camera.position.z < boundZ2))
	{
		/*camera.position.x -= camera.CAMERA_SPEED*0.02;
		camera.target.x -= camera.CAMERA_SPEED*0.02;*/
		diffX = camera.position.x - (boundX8);
		camera.position.x = boundX8;
		camera.target.x -= diffX;
		diffX = 0.0f;
	}
	if((camera.position.x > boundX9 && camera.position.x < boundX4) && (camera.position.z > boundZ1 && camera.position.z < boundZ3))
	{
		/*camera.position.z -= camera.CAMERA_SPEED*0.02;
		camera.target.z -= camera.CAMERA_SPEED*0.02;*/
		diffZ = camera.position.z - (boundZ1);
		camera.position.z = boundZ1;
		camera.target.z -= diffZ;
		diffZ = 0.0f;
	}
	if((camera.position.x > boundX9 && camera.position.x < boundX4) && (camera.position.z > boundZ3 && camera.position.z < boundZ6))
	{
		/*camera.position.z += camera.CAMERA_SPEED*0.02;
		camera.target.z += camera.CAMERA_SPEED*0.02;*/
		diffZ = camera.position.z - (boundZ6);
		camera.position.z = boundZ6;
		camera.target.z -= diffZ;
		diffZ = 0.0f;
	}
}
void SceneSP::checkShelfCollision()
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
void SceneSP::checkFreezerCollision()
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

