

class GoTester : public Component
{
private:
	Input* InputManager = nullptr;
public :
	GoTester(Input* IM);


	void update();
};

