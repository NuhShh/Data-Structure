#ifndef PASIEN_H_INCLUDED
#define PASIEN_H_INCLUDED

#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef struct penyakit infotypePenyakit;
typedef struct pasien infotypePasien;
typedef struct elmPenyakit *adrPenyakit;
typedef struct elmPasien *adrPasien;
typedef struct elmRelation *adrRelation;


//Infotype Penyakit
struct penyakit {
    string namaPenyakit;
    string kodeicdx;
    int idPenyakit;
};

//Elemen Penyakit
struct elmPenyakit {
    infotypePenyakit info;
    adrPenyakit next;
    adrRelation nextRelation;
};

//Infotype Pasien
struct pasien {
    string namaPasien;
    int usia;
    string jenisKelamin;
    string NIK;
};

//Elemen Pasien
struct elmPasien {
    infotypePasien info;
    adrPasien next;
};

//List Penyakit
struct listPenyakit {
    adrPenyakit first;
};

//List Pasien
struct listPasien {
    adrPasien first;
};

//Elemen Relasi
struct elmRelation {
    adrRelation next;
    adrPasien nextPasien;
};

//List Relasi
struct listRelation {
	adrRelation first;
};

//Procedure Create List
void createListPenyakit(listPenyakit &Lpen);
void createListRelation(listRelation &Lpen);
void createListPasien(listPasien &Lpas);

//Function Create Elemen
adrPenyakit createElemenPenyakit(infotypePenyakit X);
adrPasien createElemenPasien(infotypePasien X);
adrRelation createElemenRelation();

//Procedure Insert
void insertFirstPenyakit(listPenyakit &Lpen, adrPenyakit p);
void insertLastPenyakit(listPenyakit &Lpen, adrPenyakit p);
void insertFirstPasien(listPasien &Lpas, adrPasien p);
void insertLastPasien(listPasien &Lpas, adrPasien p);

//Procedure Delete Penyakit
void deleteFirstPenyakit(listPenyakit &Lpen, adrPenyakit &p);
void deleteAfterPenyakit(listPenyakit &Lpen, adrPenyakit &p);
void deleteLastPenyakit(listPenyakit &Lpen, adrPenyakit &p);
void deleteRelationPenyakit(listRelation &Lrel, adrPenyakit &p);
void deletePenyakit(listPenyakit &Lpen, listRelation &Lrel, string namaPenyakit);

//Procedure Delete Pasien
void deleteElmPasien(listPasien &Lpas, adrPasien &p);
void deletePasien(listPenyakit &Lpen, listPasien &Lpas, listRelation &Lrel, string NIK);
void deletePenyakitFromPasien(listPenyakit &Lpen, listRelation &Lrel, listPasien &Lpas, string NIK, string namaPenyakit);

//Procedure Show List
void showPenyakit(listPenyakit Lpen);
void showPasien(listPasien Lpas);
void showAll(listPenyakit Lpen, listPasien Lpas, listRelation Lrel);
void showPasienTerjangkit(listPenyakit Lpen, listPasien Lpas, string namaPenyakit);
void showPenyakitPasien(listPenyakit Lpen, listPasien Lpas, string NIK);
void showMostPenyakit(listPenyakit Lpen);

//Count
int countChild(listPenyakit Lpen, string namaPenyakit);
int countParent(listPenyakit Lpen);

//Function Find
adrPenyakit findPenyakit(listPenyakit Lpen, string namaPenyakit);
adrPasien findPasien(listPasien Lpas, string NIK);
adrPenyakit findPenyakitAdvanced(listPenyakit Lpen, infotypePenyakit X);

//Connect Relation
void connectRelation(listPenyakit Lpen, listPasien Lpas, string namaPenyakit, string NIK);

//Menu
void Menu(listPenyakit Lpen, listPasien Lpas, listRelation Lrel);

#endif // PASIEN_H_INCLUDED
