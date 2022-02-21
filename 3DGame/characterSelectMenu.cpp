#include "characterSelectMenu.h"
#include "image.h"
#include "Texture.h"
#include "blueSlime_Button.h"
#include "yellowSlime_Button.h"
#include "greenSlime_Button.h"
#include "input.h"
#include "constant.h"

#define SLIMEIMAGEPOSX				    250.0f
#define SLIMEIMAGEPOSY				    200.0f
#define SLIMEIMAGESIZEX					400.0f
#define SLIMEIMAGESIZEY					400.0f

#define BLUESLIMEBUTTONPOSX				300.0f
#define BLUESLIMEBUTTONPOSY				SCREEN_HEIGHT - 300.0f
#define YELLOWSLIMEBUTTONPOSX			450.0f
#define YELLOWSLIMEBUTTONPOSY			SCREEN_HEIGHT - 300.0f
#define GREENSLIMEBUTTONPOSX			600.0f
#define GREENSLIMEBUTTONPOSY			SCREEN_HEIGHT - 300.0f

#define BUTTONSIZEX						150.0f
#define BUTTONSIZEY						150.0f

#define STATUSEPOSX						1350.0f
#define STATUSEPOSY						200.0f
#define STATUSSIZEX                     50.0f
#define STATUSSIZEY                     20.0f
#define STATUSDISX                      50.0f
#define STATUSDISY                      85.0f

CharacterSelectMenu::CharacterSelectMenu()
{
	blue_Slime   = new Image({ SLIMEIMAGEPOSX, SLIMEIMAGEPOSY }, { SLIMEIMAGESIZEX, SLIMEIMAGESIZEY }, LoadTexture("data/TEXTURE/blue_slime.png"));
	green_Slime  = new Image({ SLIMEIMAGEPOSX, SLIMEIMAGEPOSY }, { SLIMEIMAGESIZEX, SLIMEIMAGESIZEY }, LoadTexture("data/TEXTURE/green_slime.png"));
	yellow_Slime = new Image({ SLIMEIMAGEPOSX, SLIMEIMAGEPOSY }, { SLIMEIMAGESIZEX, SLIMEIMAGESIZEY }, LoadTexture("data/TEXTURE/yellow_slime.png"));

	blueSlimeButton   = new BlueSlime_Button({ BLUESLIMEBUTTONPOSX ,BLUESLIMEBUTTONPOSY });
	blueSlimeButton   ->SetSize({ BUTTONSIZEX ,BUTTONSIZEY });
	yellowSlimeButton = new YellowSlime_Button({ YELLOWSLIMEBUTTONPOSX ,YELLOWSLIMEBUTTONPOSY });
	yellowSlimeButton ->SetSize({ BUTTONSIZEX ,BUTTONSIZEY });
	greenSlimeButton  = new GreenSlime_Button({ GREENSLIMEBUTTONPOSX ,GREENSLIMEBUTTONPOSY });
	greenSlimeButton  ->SetSize({ BUTTONSIZEX ,BUTTONSIZEY });
}

CharacterSelectMenu::~CharacterSelectMenu()
{

}

void CharacterSelectMenu::Update()
{
	if(choice == 0)
	{
		for (int h = 0; h < 5; h++)
		{
			for (int w = 0; w < 5; w++)
			{
				if( h == 0)
				{
					if(w < CHARACTER01_ACC__)
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_2TextNo);
					}else
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_3TextNo);
					}
				}else
				if( h == 1)
				{
					if(w < CHARACTER01_MAXVEL__)
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_2TextNo);
					}else
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_3TextNo);
					}
				}else
				if( h == 2)
				{
					if(w < CHARACTER01_JUMPPOWER__)
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_2TextNo);
					}else
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_3TextNo);
					}
				}else
				if( h == 3)
				{
					if(w < CHARACTER01_STAMINIA__)
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_2TextNo);
					}else
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_3TextNo);
					}
				}else
				if( h == 4)
				{
					if(w < CHARACTER01_HP__)
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_2TextNo);
					}else
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_3TextNo);
					}
				}
			}
		}
	}else
	if(choice == 1)
	{
		for (int h = 0; h < 5; h++)
		{
			for (int w = 0; w < 5; w++)
			{
				if( h == 0)
				{
					if(w < CHARACTER03_ACC__)
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_2TextNo);
					}else
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_3TextNo);
					}
				}else
				if( h == 1)
				{
					if(w < CHARACTER03_MAXVEL__)
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_2TextNo);
					}else
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_3TextNo);
					}
				}else
				if( h == 2)
				{
					if(w < CHARACTER03_JUMPPOWER__)
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_2TextNo);
					}else
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_3TextNo);
					}
				}else
				if( h == 3)
				{
					if(w < CHARACTER03_STAMINIA__)
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_2TextNo);
					}else
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_3TextNo);
					}
				}else
				if( h == 4)
				{
					if(w < CHARACTER03_HP__)
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_2TextNo);
					}else
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_3TextNo);
					}
				}
			}
		}
	}else
	if(choice == 2)
	{
		for (int h = 0; h < 5; h++)
		{
			for (int w = 0; w < 5; w++)
			{
				if( h == 0)
				{
					if(w < CHARACTER02_ACC__)
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_2TextNo);
					}else
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_3TextNo);
					}
				}else
				if( h == 1)
				{
					if(w < CHARACTER02_MAXVEL__)
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_2TextNo);
					}else
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_3TextNo);
					}
				}else
				if( h == 2)
				{
					if(w < CHARACTER02_JUMPPOWER__)
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_2TextNo);
					}else
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_3TextNo);
					}
				}else
				if( h == 3)
				{
					if(w < CHARACTER02_STAMINIA__)
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_2TextNo);
					}else
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_3TextNo);
					}
				}else
				if( h == 4)
				{
					if(w < CHARACTER02_HP__)
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_2TextNo);
					}else
					{
						status[h][w] = new Image({ STATUSEPOSX + STATUSDISX * w, STATUSEPOSY + STATUSDISY * h }, { STATUSSIZEX, STATUSSIZEY }, status_3TextNo);
					}
				}
			}
		}
	}




	if (choice == 0)
	{
		blueSlimeButton  ->Update(true);
		yellowSlimeButton->Update(false);
		greenSlimeButton ->Update(false);
	}else
	if (choice == 1)
	{
		blueSlimeButton  ->Update(false);
		yellowSlimeButton->Update(true);
		greenSlimeButton ->Update(false);
	}else
	if (choice == 2)
	{
		blueSlimeButton  ->Update(false);
		yellowSlimeButton->Update(false);
		greenSlimeButton ->Update(true);
	}

	if (GetKeyboardTrigger(DIK_RIGHT) && GetFadeState() == FADE_NONE)
	{
		if(choice < 2)
		{
			choice++;
		}

	}else
	if (GetKeyboardTrigger(DIK_LEFT) && GetFadeState() == FADE_NONE)
	{
		if (choice > 0)
		{
			choice--;
		}
	}

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		if(choice == 0)
		{
			SetCharacter(CHARACTER01);
			SceneTransition(SCENE_GAME);
		}else
		if(choice == 1)
		{
			SetCharacter(CHARACTER03);
			SceneTransition(SCENE_GAME);
		}else
		if(choice == 2)
		{
			SetCharacter(CHARACTER02);
			SceneTransition(SCENE_GAME);
		}
	}
}

void CharacterSelectMenu::Draw()
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(textureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(stateBaseTextNo, SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f - 400.0f, 700.0f, 800.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(statusTextNo,    SCREEN_WIDTH / 2.0f + 30.0f, SCREEN_HEIGHT / 2.0f - 360.0f, 300.0f, 400.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	if (choice == 0)
	{
		if (blue_Slime)
			blue_Slime->Draw();
	}else
	if (choice == 1)
	{
		if (yellow_Slime)
			yellow_Slime->Draw();
	}else
	if (choice == 2)
	{
		if (green_Slime)
			green_Slime->Draw();
	}
	
	if (blueSlimeButton)
		blueSlimeButton  ->Draw();
	if (yellowSlimeButton)
		yellowSlimeButton->Draw();
	if (greenSlimeButton)
		greenSlimeButton ->Draw();

	for (int h = 0; h < 5; h++)
	{
		for (int w = 0; w < 5; w++)
		{
			status[h][w]->Draw();
		}
	}

}	
