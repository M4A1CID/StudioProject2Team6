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
#include "Character.h"
#include "Container.h"
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
	void checkCollision();
	void checkSupermarketCollision();
	void checkShelfCollision();
	/*=======================================
				All Render Functions
	=======================================*/
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderTGA(Mesh* mesh,float size, float x , float y);
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

	/*=======================================
				All update functions
	=======================================*/
	void UpdateTrolley(double dt);
	void UpdateDoor(double dt);
	void UpdateUI(double dt);
	void UpdateSamples(double dt);
	/*=======================================
				All Init functions
	=======================================*/
	void DeclareLightParameters();
	void DeclareGLEnable();
	void DefineItem(CContainer* container, CItem item, int row);
	void initGeoType();
	void initCharacter();
	void initNPC();
	void initItems();
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
	float world_size;
	float moveDoorFront;
	float moveDoorBack;
	float trolleyrotation;
	int i_sampleItems;
	string s_money;
	string s_position;
	string s_fps;
	string s_camera_target;
	vector<CItem*> myItemList;
	CCharacter * ptrplayer;
	CItem * ptrItem;
	CItem * ptrClass;
	CContainer* ptrContainer;
	vector<CContainer*> myContainerList;
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
	void RenderMesh(Mesh *mesh, bool enableLight);
};


#endif

