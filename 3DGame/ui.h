#ifndef UI_H_
#define UI_H_

class Timer;
class StaminaBar;
class HpBar;
class Character;
class Stage;

class UI
{
private:
	Timer*		timer;
	StaminaBar* staminaBar;
	HpBar*      hpBar;

public:
	 UI(Stage* stage);
	~UI(){}

	void Draw();
	void Update(Character* character);
};

#endif//UI_H_