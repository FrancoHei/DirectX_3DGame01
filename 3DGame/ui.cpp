#include "ui.h"
#include "timer.h"
#include "staminaBar.h"
#include "hpBar.h"
#include "character.h"
#include "stage.h"

UI::UI(Stage* stage)
{
	timer	   = new Timer	   (D3DXVECTOR3{ 1050.0f, 100.0f, 0.0f }, D3DXVECTOR2{ 150.0f, 150.0f }, stage->GetMin(), stage->GetSec(), stage->GetMilliSec());
	hpBar	   = new HpBar	   ({ 20.0f,20.0f,0.0f }, { 500.0f, 70.0f });
	staminaBar = new StaminaBar({ 20.0f,90.0f,0.0f }, { 500.0f, 70.0f });
}

void UI::Update(Character* character)
{
	if (timer)
		timer->Update();
	if (hpBar)
		hpBar->Update(character);
	if (staminaBar)
		staminaBar->Update(character);
}

void UI::Draw()
{
	if (timer)
		timer->Draw();
	if (hpBar)
		hpBar->Draw();
	if (staminaBar)
		staminaBar->Draw();
}
