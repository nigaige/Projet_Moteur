
class Component
{
protected:
	bool active = false;
	
	GameObject* gameobject_ = new GameObject();
	Transform* transform_ =nullptr;
public:
	//TODO GAMEOBJECT OWNER
	Component(bool isActive = true);
	~Component();
	void gameObject(GameObject* go);
	GameObject* gameObject();
	void transform(Transform* trans);
	Transform* transform();
	void setActive(bool a = true) { active = a; };
	virtual void update() {};
};

