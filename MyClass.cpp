#include "MyClass.h"

MySingletonClass* MySingletonClass::sharedInstance = nullptr;

MySingletonClass& MySingletonClass::GetInstance()
{
	if (sharedInstance == nullptr)
	{
		sharedInstance = new MySingletonClass();
	}
	return *sharedInstance;
}