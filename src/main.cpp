#include "main.h"
#include "ListItem.h"
#include "Lists.h"

#include "amx/amx.h"
#include "plugincommon.h"

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit() {

  return true;
}

char * AmxGetString(AMX* amx, cell * params, int index) {
	// Get the length
	int iLength = 0;
	cell *pAddress = NULL;
	amx_GetAddr(amx, params[index], &pAddress); 
    amx_StrLen(pAddress, &iLength);
	// Make sure the length is valid
	if(!iLength)
		return NULL;
	
	// Make room for the string end
	iLength++;
	// Allocate the string
	char *ret = new char [iLength];
	// Get the string
	amx_GetString(ret, pAddress, 0, iLength);
	return ret;
}

// listKey[], listItemId
cell AMX_NATIVE_CALL  AddItemToList(AMX* amx, cell* params)
{
	char * listKey = AmxGetString(amx, params, 1);
	if (listKey == NULL) {
		return NULL;
	}

	if ((int)params[2]) {
		ListItem * listItem = gListItems[((int)params[2])];
		if (listItem != NULL && listItem->getList().empty()) {
			gLists.AddItemToList(listKey, listItem);
			return 1;
		}
	}
	return 0;
}

// listKey[], listItemId
cell AMX_NATIVE_CALL  RemoveItemFromList(AMX* amx, cell* params)
{
	char * listKey = AmxGetString(amx, params, 1);
	if (listKey == NULL) {
		return 0;
	}

	if ((int)params[2]) {
		ListItem * listItem = gListItems[((int)params[2])];
		if (listItem != NULL) {
			gLists.RemoveItemFromList(listKey, listItem);
			return 1;
		}
	}
	return 0;
}

// listKey[], listItemId
cell AMX_NATIVE_CALL  IsItemInList(AMX* amx, cell* params) {
	char * listKey = AmxGetString(amx, params, 1);
	std::string sListKey(listKey);

	if (listKey == NULL) {
		return 0;
	}

	if ((int)params[2]) {
		ListItem * listItem = gListItems[((int)params[2])];
		if (listItem) {
			return listItem->getList() == listKey;
		}
	}
	return 0;
}

//
cell AMX_NATIVE_CALL  CreateListItem(AMX* amx, cell* params)
{
	ListItem * listItem = new ListItem();
	if(listItem == NULL) return NULL;

	gListItems.insert(std::make_pair(listItem->getId(), listItem));

	return listItem->getId();
}

// listItemId, key[], value
cell AMX_NATIVE_CALL  SetListItemInfo(AMX* amx, cell* params)
{
	if ((int)params[1]) {
		char * key = AmxGetString(amx, params, 2);
		if (key) {
			ListItem * listItem = gListItems[((int)params[1])];
			if (listItem) {
				listItem->setData(key, (int)params[3]);
				return 1;
			}
		}
	}
	return 0;
}

// listItemId, key[]
cell AMX_NATIVE_CALL  GetListItemInfo(AMX* amx, cell* params)
{
	if ((int)params[1]) {
		char * key = AmxGetString(amx, params, 2);
		if (key) {
			ListItem * listItem = gListItems[((int)params[1])];
			if (listItem) {
				return listItem->getData(key);
			}
		}
	}
	return 0;
}

// listKey[]
cell AMX_NATIVE_CALL  CountItemsInList(AMX* amx, cell* params) {
	char * listKey = AmxGetString(amx, params, 1);
	if (listKey == NULL) return 0;
	return gLists.CountItemsInList(listKey);
}

// listKey[], idx
cell AMX_NATIVE_CALL  GetItemFromList(AMX* amx, cell* params) {
	char * listKey = AmxGetString(amx, params, 1);
	if (listKey == NULL) return -1;
	return gLists.GetAt(listKey, (int)params[2]);
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "CreateListItem", CreateListItem }, //
	{ "AddItemToList", AddItemToList }, //
	{ "RemoveItemFromList", RemoveItemFromList }, //
	{ "SetListItemInfo", SetListItemInfo }, //
	{ "GetListItemInfo", GetListItemInfo }, //
	{ "IsItemInList", IsItemInList }, //
	{ "CountItemsInList", CountItemsInList }, //
	{ "GetItemFromList", GetItemFromList }, //
	{ 0, 0 }
};


PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
  return SUPPORTS_AMX_NATIVES;
}

extern void *pAMXFunctions;

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
  pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
  return true;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, PluginNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return true;
}