#include "collectionInstance.h" 


static collectionInstance* C_ins = nullptr;
collectionInstance * collectionInstance::getInstance()
{
	if (!C_ins) {
		C_ins = new (std::nothrow) collectionInstance;
	}
	return C_ins;
}
