#pragma once
#include "main.h"

#include <map>
#include <stack>

extern std::stack<int> unusedListItemIds;

class ListItem {
	std::map<std::string, int> listItem;
	int uniqueId;
public:
	std::string list;
	void setList(std::string);
	std::string getList();
	void setData(std::string key, int value);
	int getData(std::string key);
	int getId();
	ListItem();
	~ListItem();
};

extern std::map<int, ListItem *> gListItems;