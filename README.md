# sa-mp-lists

> Šis plugin'as suteikia galimybę kurti sąrašus, kuriuose laikomas informacijos objektas, kuriame laikoma informacija. :D

#### Ką tai reiškia ir kaip tai naudoti?

Kaip pavizdį padarysiu žaidėjų parduodamų mašinų aukciono sąrašą.

Sukurti informacijos objektą yra itin paprasta:

```
new parduodamaMasina = CreateListItem();
```

Pats objektas susikuria tuščias, ir jokios informacijos jame nebūna, todėl būtų visai ne pro šalį jos įrašyti:

```
SetListItemInfo(parduodamaMasina, "pardavėjas", playerid);
SetListItemInfo(parduodamaMasina, "pradinė kaina", 5000);
SetListItemInfo(parduodamaMasina, "didžiausias siūlymas", 0);
SetListItemInfo(parduodamaMasina, "daugiausiai pasiūlęs žaidėjas", INVALID_PLAYER_ID);
SetListItemInfo(parduodamaMasina, "pradžios laikas", gettime());
SetListItemInfo(parduodamaMasina, "trukmė", 60*60*3); // 3 valandos
```

Kai surašome norima informaciją (arba prieš surašant, nėra skirtumo), parduodamos mašinos informacijos objektą galime pridėti į norimą sąrašą: 

```
AddItemToList("mašinų aukcionas", parduodamaMasina);
```

Sąrašų kurti nereikia, jie susikuria automatiškai jeigu dar nebuvo sukurti panaudojus funkciją `AddItemToList`. Tiek sąrašo pavadinimui, tiek parduodamos mašinos informacijos pavadinimui galima naudoti betkokius simbolius, įskaitant ir lietuviškas raides bei tarpus.

Išspausdinti visų sąraše esančių informacijos objektų informaciją galima šitaip:

```
for(new i, j = CountItemsInList("mašinų aukcionas"); i < j; i++) {
    new masinosInfo = GetItemFromList("mašinų aukcionas", i);

    printf("Pardavėjo ID: %i", GetListItemInfo(masinosInfo, "pardavėjas");

    new id = GetListItemInfo(masinosInfo, "daugiausiai pasiūlęs žaidėjas");
    if(id != INVALID_PLAYER_ID) {
        printf("Daugiausiai pasiūlė žaidėjas kurio ID yra %i", id);
        printf("Jo statoma suma yra %i", GetListItemInfo(masinosInfo, "didžiausias siūlymas"));
    }
    else {
        printf("Joks žaidėjas dar nepasiūlė jokio statymo už šio pardavėjo mašiną.");
    }
}
```