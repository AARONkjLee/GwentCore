#ifndef __collectionInstance_H__ 
#define __collectionInstance_H__ 
#include "cardCollections.h"

class collectionInstance {
public:
	collectionInstance() {}
	~collectionInstance() {}
	static collectionInstance* getInstance();
	CardCollection collection;
};
 
#endif __collectionInstance_H__ 
