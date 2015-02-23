#ifndef _DEFINE_ITEM_H
#define _DEFINE_ITEM_H

#include "BeansCan.h"
#include "BrownCan.h"
#include "CerealBox1.h"
#include "CerealBox2.h"
#include "CerealBox3.h"
#include "CerealBox4.h"
#include "CerealBox5.h"
#include "EasterEgg1.h"
#include "EasterEgg2.h"
#include "EasterEgg3.h"
#include "MelonCan.h"
#include "PeasCan.h"
#include "SardineCan.h"
#include "TomatoCan.h"
#include "VargaCan.h"
#include "BranCan.h"
#include "GluWaterCan.h"
#include "HumanCan.h"
#include "MtnDewCan.h"
#include "RedMonsterCan.h"
#include "RootBeerFloatsCan.h"
#include "SodaCan.h"
#include "SodaFestCan.h"

static float interactionDistanceZ = 4.0f;
static float interactionDistanceX = 1.0f;
static float interactionDistanceYMax = 4.7f;
static float interactionDistanceYMin = 4.0f;
static float interactionTimerLimiter = 0.5f;

//Render item X position offset
static float RenderItemTopRowXOffSet = 2.0f;
static float RenderItemMiddleRowXOffSet = 2.0f;
static float RenderItemBottomRowXOffSet = 2.0f;

//Render item Y position offset
static float RenderItemTopRowYOffSet = 5.05f;
static float RenderItemMiddleRowYOffSet = 2.95f;
static float RenderItemBottomRowYOffSet = 1.4f;

#endif