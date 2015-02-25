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

using std::vector;
using std::string;

class SceneSP: public Scene
{
private:
	
	/*=======================================
				Collision Functions
	=======================================*/
	void checkPickUpItem();
	void checkSupermarketCollision();
	void checkShelfCollision();
	void checkFreezerCollision();
	void checkCashierCollision();
	void checkElevatorCollision();
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
	void RenderItem(); // Take in a CContainer location and populate it's contents
	void RenderCashierTables();
	void RenderInventory();
	void RenderFence();
	void RenderElevator();
	void RenderCharacters();
	void RenderCharacter(CNpc* npc);
	void RenderHand();
	void RenderMainMenu();
	/*=======================================
				All update functions
	=======================================*/
	void UpdateTrolley(double dt);
	void UpdateDoor(double dt);
	void UpdateUI(double dt);
	void UpdateSamples();
	void UpdateElevator(double dt);
	void UpdateMenu();
	void UpdatePlaying(double dt);
	void UpdateTugofwar(double dt);
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
	float interactionTimer;
	float moveDoorFront;
	float moveDoorBack;
	float trolleyrotation;
	float handrotationleftandright;
	float diffX;
	float diffZ;
	float charactersrotation;
	float elevatorDoorY;
	float elevatorY;
	bool elevatorDoorOpening;
	bool elevatorSecondFloor;
	
	bool win;
	bool lose;
	bool showTuginstruction;
	int i_sampleItems;
	int i_menuHandle;
	bool elevatorIdle;
	bool IsIntugofwar;
	string s_money;
	string s_position;
	string s_fps;
	string s_camera_target;
	CPlayer * ptrplayer;
	CItem * ptrItem;
	CItem * ptrClass;
	CNpc * ptrNPC;
	int selectionPointing;
	CContainer* ptrContainer;
	vector<CContainer*> myContainerList; //Shelf vector
	vector<CItem*> myStockList;	//Supermarket stock vector
	vector<CItem*> myTrolleyList; //Trolley item vector
	vector<CNpc*> myNPCList;
	struct Transformations
	{
		float translateX;
		float translateY;
		float translateZ;
		float rotateA;
	};

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

