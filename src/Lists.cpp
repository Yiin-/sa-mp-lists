#include "Lists.h"

Lists gLists;

void Lists::AddItemToList(std::string listKey, ListItem * listItem) {
	listItem->setList(listKey);
	lists[listKey].push_back(listItem);
}

void Lists::RemoveItemFromList(std::string listKey, ListItem * listItem) {
	gListItems.erase(listItem->getId());
	
	auto iter = lists[listKey].end();
	for (auto i = lists[listKey].begin(); i != lists[listKey].end(); ++i) {
		if ((*i)->getId() == listItem->getId()) {
			iter = i;
		}
	}
	if (iter != lists[listKey].end()) {
		lists[listKey].erase(iter);
	}
	delete listItem;
}

int Lists::CountItemsInList(std::string listKey) {
	return lists[listKey].size();
}

int Lists::GetAt(std::string listKey, int idx) {
	if (idx < 0 || idx >= lists[listKey].size()) {
		return -2;
	}
	return lists[listKey].at(idx)->getId();
}