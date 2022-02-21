#pragma once

#include "stage.h"
#include "title.h"
// 登録シーン一覧
enum SCENE
{
	SCENE_NONE,		//シーン処理なし
	SCENE_TITLE,	//タイトル
	SCENE_CHARACTERSELECTMENU,
	SCENE_GAME,		//ゲーム
	SCENE_RESULT,	//リザルト
	SCENE_GAMEOVER,
	SCENE_GAMECLEAR,
	SCENE_MAX		//最後だとわかる奴をいれる
};

void InitScene(SCENE index);
void UninitScene(void);
void UpdateScene(void);
void DrawScene(void);

void SetScene(SCENE index);
void CheckScene(void);
void SetStage(STAGE stage);
void SetCharacter(CHARACTER character);
Title* GetTitle();
STAGE  GetStage();