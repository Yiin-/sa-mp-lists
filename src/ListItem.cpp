#include "ListItem.h"

std::stack<int> unusedListItemIds;
std::map<int, ListItem *> gListItems;

void ListItem::setList(std::string list) {
	this->list = list;
}

std::string ListItem::getList() {
	return this->list;
}

void ListItem::setData(std::string key, int value) {
	this->listItem[key] = value;
}

int ListItem::getData(std::string key) {
	return this->listItem[key];
}

int ListItem::getId() {
	return this->uniqueId;
}

ListItem::ListItem() {
	if (unusedListItemIds.empty()) {
		static int uniqueId = 1;
		this->uniqueId = uniqueId++;
	}
	else {
		this->uniqueId = unusedListItemIds.top();
		unusedListItemIds.pop();
	}
}

ListItem::~ListItem() {
	this->listItem.clear();
	unusedListItemIds.emplace(this->uniqueId);
}