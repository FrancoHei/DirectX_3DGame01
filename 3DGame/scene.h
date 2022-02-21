#pragma once

#include "stage.h"
#include "title.h"
// �o�^�V�[���ꗗ
enum SCENE
{
	SCENE_NONE,		//�V�[�������Ȃ�
	SCENE_TITLE,	//�^�C�g��
	SCENE_CHARACTERSELECTMENU,
	SCENE_GAME,		//�Q�[��
	SCENE_RESULT,	//���U���g
	SCENE_GAMEOVER,
	SCENE_GAMECLEAR,
	SCENE_MAX		//�Ōゾ�Ƃ킩��z�������
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