//Interface contact between Game and GameSence

#pragma once
class ISence
{
public:
	//được Game gọi
	virtual void UpdateRender(int t) = 0;
	virtual void ProcessInput() = 0;
	virtual void OnKeyDown(int keyCode) = 0;
	virtual void OnKeyUp(int keyCode) = 0;
	virtual void Load() = 0;

	virtual bool IsDead() = 0;
};

