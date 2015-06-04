#pragma once
#include "main.h"
#include "ListItem.h"

#include <map>
#include <vector>

class Lists {
	std::map<std::string, std::vector<ListItem *>> lists;
public:
	void AddItemToList(std::string listKey, ListItem * listItem);
	void RemoveItemFromList(std::string listKey, ListItem * listItem);
	int CountItemsInList(std::string listKey);
	int GetAt(std::string listKey, int idx);
};
extern Lists gLists;