/*==============================================================================

   シーン管理 [scene.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "scene.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "stage.h"
#include "characterSelectMenu.h"
#include "gameClear.h"
#include "gameOver.h"
/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
static SCENE g_SceneIndex					= SCENE_NONE;
static SCENE g_SceneNextIndex				= g_SceneIndex;
Game*        g_Game							= nullptr;
CharacterSelectMenu* g_CharacterSelectMenu	= nullptr;
Title*       g_Title						= nullptr;
GameClear*   g_GameClear					= nullptr;
GameOver*    g_GameOver						= nullptr;
STAGE        g_Stage						= STAGE01;
CHARACTER    g_Character				    = CHARACTER01;

/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitScene(SCENE index)
{
	g_SceneIndex = g_SceneNextIndex = index;

	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		if(!g_Title)
			g_Title = new Title();
		break;

	case SCENE_CHARACTERSELECTMENU:
		g_CharacterSelectMenu = new CharacterSelectMenu();
		break;

	case SCENE_GAME:
		g_Game = new Game(g_Stage, g_Character);
		break;

	case SCENE_GAMECLEAR:
		g_GameClear = new GameClear();
		break;

	case SCENE_GAMEOVER:
		g_GameOver = new GameOver();
		break;

	case SCENE_RESULT:
		InitResult();
		break;
	}
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitScene(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		break;

	case SCENE_CHARACTERSELECTMENU:
		delete g_CharacterSelectMenu;
		break;

	case SCENE_GAME:
		delete g_Game;
		break;

	case SCENE_GAMECLEAR:
		delete g_GameClear;
		break;

	case SCENE_GAMEOVER:
		delete g_GameOver;
		break;

	case SCENE_RESULT:
		UninitResult();
		break;
	}
}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdateScene(void)
{
	switch( g_SceneIndex ) 
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		g_Title->Update();
		break;

	case SCENE_CHARACTERSELECTMENU:
		g_CharacterSelectMenu->Update();
		break;

	case SCENE_GAME:
		g_Game->Update();
		break;

	case SCENE_GAMECLEAR:
		g_GameClear->Update();
		break;

	case SCENE_GAMEOVER:
		g_GameOver->Update();
		break;

	case SCENE_RESULT:
		UpdateResult();
		break;
	}

	UpdateFade();
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawScene(void)
{
	switch( g_SceneIndex )
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE:
		g_Title->Draw();
		break;

	case SCENE_CHARACTERSELECTMENU:
		g_CharacterSelectMenu->Draw();
		break;

	case SCENE_GAME:
		g_Game->Draw();
		break;

	case SCENE_GAMECLEAR:
		g_GameClear->Draw();
		break;

	case SCENE_GAMEOVER:
		g_GameOver->Draw();
		break;

	case SCENE_RESULT:
		DrawResult();
		break;
	}

	DrawFade();
}

/*------------------------------------------------------------------------------
   シーン遷移を要求する関数
------------------------------------------------------------------------------*/
void SetScene(SCENE index)
{
	//遷移先シーンを設定する
	g_SceneNextIndex = index;
}

/*------------------------------------------------------------------------------
   遷移を要求がある場合にシーンを切り替える関数
------------------------------------------------------------------------------*/
void CheckScene(void)
{
	//現在のシーンと遷移先シーンが違っていたら
	if( g_SceneIndex != g_SceneNextIndex )
	{
		//現在のシーンを終了させる
		UninitScene();
		
		//遷移先シーンの初期化処理を行う
		InitScene(g_SceneNextIndex);
	}
}

void SetStage(STAGE stage)
{
	g_Stage = stage;
}

void SetCharacter(CHARACTER character)
{
	g_Character = character;
}

STAGE GetStage()
{
	return g_Stage;
}

Title* GetTitle()
{
	return g_Title;
}