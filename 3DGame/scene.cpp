/*==============================================================================

   �V�[���Ǘ� [scene.cpp]
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
   �萔��`
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �\���̐錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
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
   �������֐�
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
   �I������������֐�
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
   �X�V����������֐�
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
   �`�揈��������֐�
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
   �V�[���J�ڂ�v������֐�
------------------------------------------------------------------------------*/
void SetScene(SCENE index)
{
	//�J�ڐ�V�[����ݒ肷��
	g_SceneNextIndex = index;
}

/*------------------------------------------------------------------------------
   �J�ڂ�v��������ꍇ�ɃV�[����؂�ւ���֐�
------------------------------------------------------------------------------*/
void CheckScene(void)
{
	//���݂̃V�[���ƑJ�ڐ�V�[��������Ă�����
	if( g_SceneIndex != g_SceneNextIndex )
	{
		//���݂̃V�[�����I��������
		UninitScene();
		
		//�J�ڐ�V�[���̏������������s��
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