#ifndef _SCENESP_H
#define _SCENESP_H

#include "Scene.h"
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
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_TYPE,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		U_LIGHT1_POSITION,
		U_LIGHT1_TYPE,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		U_NUMLIGHTS,
		//add these enum in UNIFORM_TYPE before U_TOTAL
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_TEXT,	
		GEO_FRONT,
		GEO_BOTTOM,
		GEO_BACK,
		GEO_TOP,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_SUPERMARKET,
		GEO_SHELF,
		GEO_CASHIER,
		GEO_DOOR,
		GEO_SAMPLESTAND,
		GEO_CAN_SARDINE,
		GEO_CAN_PEAS,
		GEO_CAN_BROWN,
		GEO_CAN_TOMATO,
		GEO_CAN_BEANS,
		GEO_CAN_MELON,
		GEO_CAN_VARGA,
		GEO_CEREAL_1,
		GEO_CEREAL_2,
		GEO_CEREAL_3,
		GEO_CEREAL_4,
		GEO_CEREAL_5,
		GEO_EASTEREGG_1,
		GEO_EASTEREGG_2,
		GEO_EASTEREGG_3,
		NUM_GEOMETRY,
	};
	enum ROW_TYPE
	{
		ROW_TOP,
		ROW_MIDDLE,
		ROW_BOTTOM,
		NUM_ROW,
	};

	void checkCollision();
	/*=======================================
				All Render Functions
	=======================================*/
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderSupermarket();
	void RenderShelves();
	void RenderShelves(CContainer* container);
	void RenderDoors();
	void RenderSamplestand();
	void RenderUI();
	void RenderItem(); // Take in a CContainer location and populate it's contents
	void RenderCashierTables();

	/*=======================================
				All update functions
	=======================================*/
	void UpdateDoor(double dt);
	void UpdateUI(double dt);
	/*=======================================
				All Init functions
	=======================================*/
	void DeclareLightParameters();
	void DeclareGLEnable();
	void DefineItem(CContainer* container, CItem item, int row);
	void initGeoType();
	void initCharacter();
	void initItems();
	void initShelves();


	/*========================================
			Declare variables here
	=========================================*/
	
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	CCharacter * ptrplayer;
	CItem sardineCan;
	CItem peasCan;
	CItem brownCan;
	CItem tomatoCan;
	CItem beansCan;
	CItem melonCan;
	CItem vargaCan;
	CItem cerealBox1;
	CItem cerealBox2;
	CItem cerealBox3;
	CItem cerealBox4;
	CItem cerealBox5;
	CItem easterEgg1;
	CItem easterEgg2;
	CItem easterEgg3;
	CContainer shelfSardineCan;
	bool toggleLight;
	bool toggleDoorFront;
	bool toggleDoorBack;
	float world_size;
	float moveDoorFront;
	float moveDoorBack;
	string s_money;
	string s_position;
	string s_fps;
	string s_camera_target;
	vector<CItem*> myItemList;
	CItem * ptrItem;
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

