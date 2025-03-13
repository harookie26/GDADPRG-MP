#pragma once

class MySingletonClass
{
public:
	static MySingletonClass& GetInstance();

private:
	MySingletonClass() {};
	MySingletonClass(MySingletonClass const&) {};
	MySingletonClass& operator=(MySingletonClass const&) {};
	static MySingletonClass* sharedInstance;
};