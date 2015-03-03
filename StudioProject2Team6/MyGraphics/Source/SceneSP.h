#ifndef _SCENESP_H
#define _SCENESP_H

#include "Scene.h"
#include "DefineEnum.h"
#include "DefineItemClass.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
#include "Player.h"
#include "Npc.h"
#include "Container.h"
#include "DefineValues.h"
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <ctime>
#include "SFML\Audio.hpp"

using std::vector;
using std::string;

class SceneSP: public Scene
{
private:
	
	/*=======================================
				Collision Functions
	=======================================*/
	void checkPickUpItem();
	void checkCollision();
	void checkObjectCollision(float posX, float posY, float posZ, float widthX, float widthZ);
	void checkSupermarketCollision();
	void checkFreezerCollision();
	void checkCashierCollision();
	void checkElevatorCollision();
	bool checkReturnPoint();
	void checkWinLose();
	void resetGame();
	void addToInventory(CItem* pickedUp);
	/*=======================================
				All Render Functions
	=======================================*/
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderTGAUI(Mesh* mesh,float size, float x , float y);
	void RenderTGAInventory(Mesh* mesh,float size, float x , float y);
	void RenderSupermarket();
	void RenderShelves();
	void RenderShelves(CContainer* container);
	void RenderDoors();
	void RenderTrolleys();
	void RenderSamplestand();
	void RenderSamples();
	void RenderUI();
	void RenderTugofwarUI();
	void RenderDrunkmanUI();
	void RenderItem(); // Take in a CContainer location and populate it's contents
	void RenderCashierTables();
	void RenderInventory();
	void RenderFence();
	void RenderElevator();
	void RenderCharacters();
	void RenderCharacter(CNpc* npc);
	void RenderHand();
	void RenderTug();
	void RenderReturnPoint();
	void RenderBeerstand();
	void RenderMainMenu();		//Render Main Menu Screen
	void RenderSubMenu();		//Render Sub/Start Menu Screen
	void RenderWinLoseMenu();	//Render Win/Lose Menu Screen
	void RenderOffice();
	void RenderStorage();
	void RenderBuilding();
	void RenderCage();
	void RenderTroll();
	void RenderMiscEastereggs();
	void RenderEasteregg();
	/*=======================================
				All update functions
	=======================================*/
	void UpdateAI(double dt);			//Update AI 
	void UpdateTrolley(double dt);		//Update trolley
	void UpdateDoor(double dt);			//Update supermarket door
	void UpdateUI(double dt);			//Update Game User Interface
	void UpdateSamples();				//Update sample food stand
	void UpdateElevator(double dt);		//Update elevator in supermarket
	void UpdateMenu();					//Update Menus
	void UpdateMainMenu();
	void UpdateStartMenu();
	void UpdateWinLoseMenu();
	void UpdatePlaying(double dt);		//Update application while game is playing
	void UpdateTugofwar(double dt);		//Update the Tug-Of-War mini game
	void UpdateDrunkman(double dt);		//Update Drunk Man NPC
	void UpdatePlayerSelection();		//Update what the player is selecting
	void UpdateItemRotation(double dt);	//Update player inspection 
	void UpdateTugofwarguy(double dt);	//Update Tug-Of-War NPC
	void UpdateDrunkmanguy(double dt);	//Update Drunk-Man NPC
	void UpdateWalkingman(double dt);	//Update Walking-man NPC
	void UpdateLogisticman(double dt);	//Update Logistic-man NPC
	void UpdateGhostman(double dt);		//Update Ghost NPC
	void UpdateCustomer(double dt);     //Update Customer NPC
	void UpdateShoppers(double dt); 
	void UpdateLookingman(double dt);	//Update NPC that looks at shelves
	void UpdateChattingman(double dt);
	void UpdateLegAnimation(double dt);	//Update NPC leg animation
	void UpdateItemInspection();		//Update player holding and rotating the item
	void UpdateAITimer(double dt);
	void UpdatePaying();       //Update paying activity
	void UpdateCage(double dt);
	void UpdateGaben(double dt);
	void UpdateTroll(double dt);
	void UpdateMiscEasteregg(double dt);
	void UpdateEasteregg(double dt);
	/*=======================================
				All Init functions
	=======================================*/
	void DeclareLightParameters();
	void DeclareGLEnable();
	void DefineItem(CContainer* container, CItem item, int row);
	void initGeoType();
	void initCharacter();
	void initNPC();
	void initShelves();


	/*========================================
			Declare variables here
	=========================================*/
	
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	
	CContainer shelfSardineCan;
	bool toggleLight;
	bool toggleDoorFront;
	bool toggleDoorBack;
	bool elevatorDoorOpening;
	bool elevatorSecondFloor;
	bool b_isWithinInteractionItem;
	bool b_isWithinPayingCashier;
	bool b_is_Stealing;
	float interactionTimer;
	float LogisticinteractionTimer;
	float CustomerinteractionTimer;
	float moveDoorFront;
	float moveDoorBack;
	float trolleyrotation;
	float handrotationleftandright;
	float handtranslation;
	float diffX;
	float diffZ;
	float charactersrotation;
	float elevatorDoorY;
	float elevatorY;
	float itemYrotation;
	float itemXrotation;
	
	CEmptyItem emptyItem;
	bool win;
	bool lose;
	bool showTuginstruction;
	bool b_crouching;
	bool b_inspection;
	
	int i_sampleItems;
	int i_menuHandle;
	int i_drunkmanAct;
	int i_CashierAct;
	bool elevatorIdle;
	bool IsIntugofwar;
	string s_money;
	string s_position;
	string s_fps;
	string s_camera_target;
	string s_item_name;
	string s_item_price;
	string s_easter_counter;
	CPlayer * ptrplayer;
	CItem * ptrItem;
	CItem * ptrClass;
	CItem * ptrInvSelect;
	CNpc * ptrNPC;
	int selectionPointing;
	int inventoryPointing;
	CContainer* ptrContainer;
	vector<CContainer*> myContainerList; //Shelf vector
	vector<CItem*> myStockList;	//Supermarket stock vector
	vector<CItem*> myTreasureList; //Treasure item vector
	vector<CItem*> myCheckList; //Check list for items
	vector<CNpc*> myNPCList;
	struct Transformations
	{
		float translateX;
		float translateY;
		float translateZ;
		float rotateA;
	};

	//Sound Buffers
	sf::Music music;
public:
	SceneSP();
	~SceneSP();
	double timer;
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	
	//Camera3 camera;
	Camera3 camera;
	
	//render skybox
	void RenderSkyBox();

	MS modelStack, viewStack, projectionStack;
	
	Light lights[2];
	Transformations Cashier;
	void RenderMesh(Mesh *mesh, bool enableLight);
};


#endif

