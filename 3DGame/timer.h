#ifndef TIMER_H_
#define TIMER_H_

#include "Texture.h"
#include "sprite.h"
#include "fade.h"

#define MINPOS (330)
#define SECPOS (165)
#define COLONPOSX (55)
#define COLONPOSY (25)
#define DIGITWORDDIS (15)
class Timer
{
private:
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	D3DXVECTOR2 textCoord     = { 0.0f, 0.0f };
	D3DXVECTOR2 textCoordSize = { 1.0f, 1.0f };
	int digitalWordTextNo	  = LoadTexture("data/TEXTURE/digitalWord.png");
	int colonTextNo			  = LoadTexture("data/TEXTURE/colon.png");
	int minute   = 100;
	int sec      = 100;
	int millisec = 100;
public:
	Timer(D3DXVECTOR3 pos_, D3DXVECTOR2 size_, int min_, int sec_, int millisec_)
		:pos(pos_), size(size_), minute(min_), sec(sec_), millisec(millisec_) {}
	~Timer(){}

	void Update()
	{
		millisec--;
		if (millisec < 0)
		{
			millisec = 59;
			sec--;
			if (sec < 0)
			{
				sec = 59;
				minute--;
				if (minute < 0)
				{
					minute   = 0;
					sec      = 0;
					millisec = 0;
					if (minute <= 0 && sec <= 0 && millisec <= 0)
					{
						SceneTransition(SCENE_RESULT);
					}
				}
			}
		}
	}

	void Draw()
	{
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(digitalWordTextNo));

		// 桁数分処理する
		int millisec_timer_ = millisec;

		for (int i = 0; i < 2; i++)
		{
			int n = millisec_timer_ % 10;

			millisec_timer_ /= 10;

			DrawSpriteColorRotate(digitalWordTextNo,
				pos.x + ((size.x - DIGITWORDDIS) / 2.0f * (2 - 1 - i)), pos.y,
				size.x, size.y,
				0.0f + 0.2f * (n % 5), 0.0f + 0.5f * (n / 5),
				0.2f, 0.5f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0);
		}

		int sec_timer_ = sec;

		for (int i = 0; i < 2; i++)
		{
			int n = sec_timer_ % 10;

			sec_timer_ /= 10;

			DrawSpriteColorRotate(digitalWordTextNo,
				pos.x  - SECPOS + ((size.x - DIGITWORDDIS) / 2.0f * (2 - 1 - i)), pos.y,
				size.x, size.y,
				0.0f + 0.2f * (n % 5), 0.0f + 0.5f * (n / 5),
				0.2f, 0.5f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0);
		}

		int min_timer_ = minute;

		for (int i = 0; i < 2; i++)
		{
			int n = min_timer_ % 10;

			min_timer_ /= 10;

			DrawSpriteColorRotate(digitalWordTextNo,
				pos.x - MINPOS + ((size.x - DIGITWORDDIS) / 2.0f * (2 - 1 - i)), pos.y,
				size.x, size.y,
				0.0f + 0.2f * (n % 5), 0.0f + 0.5f * (n / 5),
				0.2f, 0.5f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				0);
		}

		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(colonTextNo));

		DrawSpriteColorRotate(colonTextNo,
			pos.x - SECPOS - COLONPOSX, pos.y - COLONPOSY,
			size.x / 2, size.y / 2,
			0.0f, 0.0f,
			1.0f, 1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			0);

		DrawSpriteColorRotate(colonTextNo,
			pos.x - COLONPOSX, pos.y - COLONPOSY,
			size.x / 2, size.y / 2,
			0.0f, 0.0f,
			1.0f, 1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			0);
	}
};

#endif//TIMER_H_
