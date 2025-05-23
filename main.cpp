#include "pasien.h"
#include <cstdlib>

using namespace std;

int main()
{
    listPenyakit Lpen;
    listRelation Lrel;
    listPasien Lpas;

    createListPenyakit(Lpen);
    createListRelation(Lrel);
    createListPasien(Lpas);

    //Create Dataset Penyakit
    infotypePenyakit X;

    X.namaPenyakit = "Tipes";
    X.kodeicdx = "A01.0";
    X.idPenyakit = 101;

    adrPenyakit newPenyakit = createElemenPenyakit(X);
    insertLastPenyakit(Lpen, newPenyakit);

    X.namaPenyakit = "Autis";
    X.kodeicdx = "F84.0";
    X.idPenyakit = 102;

    newPenyakit = createElemenPenyakit(X);
    insertLastPenyakit(Lpen, newPenyakit);

    X.namaPenyakit = "Influenza";
    X.kodeicdx = "J10.0";
    X.idPenyakit = 103;

    newPenyakit = createElemenPenyakit(X);
    insertLastPenyakit(Lpen, newPenyakit);

    X.namaPenyakit = "DBD";
    X.kodeicdx = "A91";
    X.idPenyakit = 104;

    newPenyakit = createElemenPenyakit(X);
    insertLastPenyakit(Lpen, newPenyakit);

    X.namaPenyakit = "Malaria";
    X.kodeicdx = "B54";
    X.idPenyakit = 105;

    newPenyakit = createElemenPenyakit(X);
    insertLastPenyakit(Lpen, newPenyakit);

    X.namaPenyakit = "Hipomania";
    X.kodeicdx = "F30.0";
    X.idPenyakit = 106;

    newPenyakit = createElemenPenyakit(X);
    insertLastPenyakit(Lpen, newPenyakit);

     X.namaPenyakit = "Hipertensi";
    X.kodeicdx = "I10";
    X.idPenyakit = 107;

    newPenyakit = createElemenPenyakit(X);
    insertLastPenyakit(Lpen, newPenyakit);
    //End

    //Create Dataset Pasien
    infotypePasien Y;

    adrPasien newPasien;

    Y.namaPasien = "KingNadhif";
    Y.usia = 40;
    Y.jenisKelamin = "L";
    Y.NIK = "327321001";

    newPasien = createElemenPasien(Y);
    insertLastPasien(Lpas, newPasien);

    Y.namaPasien = "Nolan";
    Y.usia = 21;
    Y.jenisKelamin = "L";
    Y.NIK = "327321002";

    newPasien = createElemenPasien(Y);
    insertLastPasien(Lpas, newPasien);

    Y.namaPasien = "Juliana";
    Y.usia = 19;
    Y.jenisKelamin = "P";
    Y.NIK = "327321003";

    newPasien = createElemenPasien(Y);
    insertLastPasien(Lpas, newPasien);

    Y.namaPasien = "Supriana";
    Y.usia = 15;
    Y.jenisKelamin = "P";
    Y.NIK = "327321004";

    newPasien = createElemenPasien(Y);
    insertLastPasien(Lpas, newPasien);

     Y.namaPasien = "Bobby";
    Y.usia = 31;
    Y.jenisKelamin = "L";
    Y.NIK = "327321005";

    newPasien = createElemenPasien(Y);
    insertLastPasien(Lpas, newPasien);
    //End

    //Connect Dataset Penyakit and Pasien
    connectRelation(Lpen,Lpas,"Influenza","327321001");
    connectRelation(Lpen,Lpas,"Influenza","327321002");
    connectRelation(Lpen,Lpas,"Influenza","327321003");
    connectRelation(Lpen,Lpas,"DBD","327321001");
    connectRelation(Lpen,Lpas,"DBD","327321004");
    connectRelation(Lpen,Lpas,"Tipes","327321001");
    connectRelation(Lpen,Lpas,"Tipes","327321002");
    connectRelation(Lpen,Lpas,"Tipes","327321004");
    connectRelation(Lpen,Lpas,"Autis","327321001");
    connectRelation(Lpen,Lpas,"Autis","327321002");
    connectRelation(Lpen,Lpas,"Autis","327321003");
    connectRelation(Lpen,Lpas,"Hipomania","327321001");
    cout << endl;
    system("cls");
    //End

    Menu(Lpen, Lpas, Lrel);

    return 0;
}
