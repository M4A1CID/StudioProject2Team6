/******************************************************************************/
/*!
\file	SceneSP.h
\author Edmund Ang , Jeffrey Teo, John Leong, Xue Tian
\brief
Header file for SceneSP 
*/
/******************************************************************************/

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
/******************************************************************************/
/*!
		Class SceneSP:
\brief	Defines the class for our entire scene
*/
/******************************************************************************/
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
	void RenderMainMenu();			//Render Main Menu Screen
	void RenderSubMenu();			//Render Sub/Start Menu Screen
	void RenderWinLoseMenu();		//Render Win/Lose Menu Screen
	void RenderInstructionMenu();	//Render instruction Screen
	void RenderPauseMenu();
	void RenderOffice();
	void RenderStorage();
	void RenderBuilding();
	void RenderIceBox();
	void RenderMeatShelf();
	void RenderFoodShelf();
	void RenderCage();
	void RenderTroll();
	void RenderMiscEastereggs();
	void RenderEasteregg();
	void RenderATM();
	void RenderFerrisWheel();
	/*=======================================
				All update functions
	=======================================*/
	void UpdateAI(double dt);			//Update AI 
	void UpdateHand(double dt);			//Update players hand
	void UpdateDoor(double dt);			//Update supermarket door
	void UpdateUI(double dt);			//Update Game User Interface
	void UpdateSamples();				//Update sample food stand
	void UpdateElevator(double dt);		//Update elevator in supermarket
	void UpdateMenu();					//Update Menus into 1 function
	void UpdateMainMenu();				//Update Main Menu
	void UpdateStartMenu();				//Update Start Menu with play scenarios
	void UpdateWinLoseMenu();			//Update winning and losing screen
	void UpdateInstructionMenu();		//Update instruction menu
	void UpdatePauseMenu();				//Update Pause menu
	void UpdatePlaying(double dt);		//Update application while game is playing
	void UpdateTugofwar(double dt);		//Update the Tug-Of-War mini game
	void UpdateDrunkman(double dt);		//Update Drunk Man NPC
	void UpdatePlayerSelection();		//Update what the player is selecting
	void UpdateItemRotation(double dt);	//Update player inspection 
	void UpdateTugofwarguy(double dt);	//Update Tug-Of-War NPC
	void UpdateDrunkmanguy(double dt);	//Update Drunk-Man NPC
	void UpdateWalkingman(double dt);	//Update Walking-man NPC
	void UpdateWalkingmanoutsideX(double dt);//Update Walking-man NPC
	void UpdateWalkingmanoutsideZ(double dt);//Update Walking-man NPC opp dir
	void UpdateLogisticman(double dt);	//Update Logistic-man NPC
	void UpdateGhostman(double dt);		//Update Ghost NPC
	void UpdateCustomer(double dt);     //Update Customer NPC
	void UpdateShoppers(double dt); 
	void UpdateLookingman(double dt);	//Update NPC that looks at shelves
	void UpdateChattingman(double dt);
	void UpdateLegAnimation(double dt);	//Update NPC leg animation
	void UpdateItemInspection();		//Update player holding and rotating the item
	void UpdateAITimer(double dt);
	void UpdatePaying();				//Update paying activity
	void UpdateCage(double dt);
	void UpdateGaben(double dt);
	void UpdateTroll(double dt);
	void UpdateMiscEasteregg(double dt);
	void UpdateEasteregg(double dt);
	void UpdateEasterEggGuy(double dt); 
	void UpdateATM(); //Update ATM
	void UpdateBuildingGuy(double dt);//Update building guy
	void UpdateRotatingMan(double dt);//Update rotating man
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
	bool b_quit;
	bool b_toggleLight;
	bool b_toggleDoorFront;
	bool b_toggleDoorBack;
	bool b_elevatorDoorOpening;
	bool b_elevatorSecondFloor;
	bool b_isWithinInteractionItem;
	bool b_isWithinPayingCashier;
	bool b_is_Stealing;
	bool b_dinged;
	bool b_falling;
	bool b_winEaster;
	bool b_closeEaster;
	bool b_inRange;
	bool b_getCaged;
	bool b_getGabed;
	bool b_getTrolled;
	bool b_getTimed;
	bool b_getRicked;
	bool b_caged;
	bool b_win;
	bool b_lose;
	bool b_showTuginstruction;
	bool b_crouching;
	bool b_inspection;
	bool b_elevatorIdle;
	bool b_IsIntugofwar;

	float f_interactionTimer;
	float f_LogisticinteractionTimer;
	float f_CustomerinteractionTimer;
	float f_moveDoorFront;
	float f_moveDoorBack;
	float f_trolleyrotation;
	float f_handrotationleftandright;
	float f_handtranslation;
	float f_diffX;
	float f_diffZ;
	float f_charactersrotation;
	float f_elevatorDoorY;
	float f_elevatorY;
	float f_itemYrotation;
	float f_itemXrotation;
	float f_ATMMoney;
	float f_soundTimer;
	float f_easterLimiter;
	float f_easterLimiter2;
	float f_easterTimer;
	float f_cagedPos;
	float f_diffY;

	CEmptyItem emptyItem;
	CPlayer * ptrplayer;
	CItem * ptrItem;
	CItem * ptrClass;
	CItem * ptrInvSelect;
	CNpc * ptrNPC;
	
	int i_getCounter;
	int i_total_items_to_find;
	int i_sampleItems;
	int i_menuHandle;
	int i_drunkmanAct;
	int i_CashierAct;
	int i_selectionPointing;
	int i_inventoryPointing;
	string s_money;
	string s_position;
	string s_fps;
	string s_camera_target;
	string s_item_name;
	string s_item_price;
	string s_easter_counter;
	string s_easter_count;
	string s_atm_balance;
	
	
	CContainer* ptrContainer;
	vector<CContainer*> myContainerList; //Shelf vector
	vector<CItem*> myStockList;	//Supermarket stock vector
	vector<CItem*> myTreasureList; //Treasure item vector
	vector<CItem*> myCheckList; //Check list for items
	vector<CNpc*> myNPCList;
	

	//Sound Buffers
	sf::Music music;
	sf::Music music2;
	sf::Music sound;
	sf::Music easter;
public:
	SceneSP();
	~SceneSP();
	double timer;
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	/*==============================
				Get Quit
	==============================*/
	bool getQuit();
	//Camera3 camera;
	Camera3 camera;
	 
	//render skybox
	void RenderSkyBox();

	MS modelStack, viewStack, projectionStack;
	
	Light lights[2];
	void RenderMesh(Mesh *mesh, bool enableLight);
};


#endif

