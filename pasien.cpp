#include "pasien.h"

//Create list penyakit
void createListPenyakit(listPenyakit &Lpen) {
	Lpen.first = NULL;
}

//Create list relation
void createListRelation(listRelation &Lrel) {
    Lrel.first = NULL;
}

//Create list pasien
void createListPasien(listPasien &Lpas) {
	Lpas.first = NULL;
}

//Create elemen penyakit
adrPenyakit createElemenPenyakit(infotypePenyakit X) {
	adrPenyakit p = new elmPenyakit;
	p->info.namaPenyakit = X.namaPenyakit;
	p->info.kodeicdx = X.kodeicdx;
	p->info.idPenyakit = X.idPenyakit;
	p->next = NULL;
	p->nextRelation = NULL;
	return p;
}

//Create elemen pasien
adrPasien createElemenPasien(infotypePasien X) {
	adrPasien p = new elmPasien;
	p->info.namaPasien = X.namaPasien;
	p->info.usia = X.usia;
	p->info.jenisKelamin = X.jenisKelamin;
	p->info.NIK = X.NIK;
	p->next = NULL;
	return p;
}

//Create elemen relation
adrRelation createElemenRelation() {
    adrRelation rel = new elmRelation;
    rel->nextPasien = NULL;
    rel->next = NULL;
    return rel;
}

//Insert first penyakit
void insertFirstPenyakit(listPenyakit &Lpen, adrPenyakit p) {
    p->next = Lpen.first;
    Lpen.first = p;
}

//Insert last penyakit
void insertLastPenyakit(listPenyakit &Lpen, adrPenyakit p) {
    if (Lpen.first == NULL) {
        p->next = Lpen.first;
        Lpen.first = p;
    } else {
        adrPenyakit q = Lpen.first;
        while (q->next != NULL) {
            q = q->next;
        }
        q->next = p;
    }
}

//Insert first pasien
void insertFirstPasien(listPasien &Lpas, adrPasien p) {
    p->next = Lpas.first;
    Lpas.first = p;
}

//Insert last pasien
void insertLastPasien(listPasien &Lpas, adrPasien p) {
    if (Lpas.first == NULL) {
        p->next = Lpas.first;
        Lpas.first = p;
    } else {
        adrPasien q = Lpas.first;
        while (q->next != NULL) {
            q = q->next;
        }
        q->next = p;
    }
}

//Delete first penyakit
void deleteFirstPenyakit(listPenyakit &Lpen, adrPenyakit &p) {
    if (Lpen.first != NULL) {
        p = Lpen.first;
        Lpen.first = p->next;
        p->next == NULL;
    } else {
        cout << "List penyakit kosong." << endl;
    }
}

//Delete after penyakit
void deleteAfterPenyakit(listPenyakit &Lpen, adrPenyakit &p) {
    adrPenyakit prec = Lpen.first;
    while (prec->next != p) {
        prec = prec->next;
    }
    prec->next = p->next;
    p->next = NULL;
}

//Delete last penyakit
void deleteLastPenyakit(listPenyakit &Lpen, adrPenyakit &p) {
    if (Lpen.first != NULL) {
        if (Lpen.first->next == NULL) {
            p = Lpen.first;
            Lpen.first == NULL;
        } else {
            adrPenyakit prec = Lpen.first;
            while (prec->next->next != NULL) {
                prec = prec->next;
            }
            p = prec->next;
            prec->next = NULL;
        }
    } else {
        cout << "List penyakit kosong." << endl;
    }
}

//Delete relation yang berhubungan dengan penyakit yang akan dihapus
void deleteRelationPenyakit(listRelation &Lrel, adrPenyakit &p) {
    adrRelation rel = Lrel.first;
    adrRelation prevRel = NULL;

    while (rel != NULL) {
        if (rel == p->nextRelation) {
            if (prevRel == NULL) {
                //Relasi di awal list
                Lrel.first = rel->next;
            } else {
                //Relasi di tengah/akhir list
                prevRel->next = rel->next;
            }
            delete rel;
            break;
        }
        prevRel = rel;
        rel = rel->next;
    }
}

//Delete elemen penyakit dari list penyakit
void deletePenyakit(listPenyakit &Lpen, listRelation &Lrel, string namaPenyakit) {
    adrPenyakit deletedPenyakit = findPenyakit(Lpen, namaPenyakit);

    if (deletedPenyakit != NULL) {
        deleteRelationPenyakit(Lrel, deletedPenyakit);

        if (deletedPenyakit->next == NULL) {
            //deletedPenyakit di akhir list
            deleteLastPenyakit(Lpen, deletedPenyakit);
        } else if (Lpen.first == deletedPenyakit) {
            //deletedPenyakit di awal list
            deleteFirstPenyakit(Lpen, deletedPenyakit);
        } else {
            //deletedPenyakit di tengah list
            deleteAfterPenyakit(Lpen, deletedPenyakit);
        }
        cout << "Penyakit dengan nama " << namaPenyakit << " berhasil dihapus." << endl;
    } else {
        cout << "Penyakit tidak ditemukan." << endl;
    }
}

//Delete elemen pasien dari list pasien
void deleteElmPasien(listPasien &Lpas, adrPasien &p) {
    if (p != NULL) {
        if (Lpas.first == p) {
            //Pasien berada di awal list
            Lpas.first = p->next;
            delete p;
        } else {
            adrPasien prec = Lpas.first;
            //Pasien berada di tengah/akhir list
            while (prec->next != p && prec->next != NULL) {
                prec = prec->next;
            }
            if (prec->next == p) {
                prec->next = p->next;
                delete p;
            }
        }
    }
}

//Delete pasien dan relasi yang berhubungan dengan pasien
void deletePasien(listPenyakit &Lpen, listPasien &Lpas, listRelation &Lrel, string NIK) {
    adrPasien deletedPasien = findPasien(Lpas, NIK);

    if (deletedPasien != NULL) {
        adrPenyakit pen = Lpen.first;
        while (pen != NULL) {
            adrRelation prevRel = NULL;
            adrRelation rel = pen->nextRelation;

            while (rel != NULL) {
                if (rel->nextPasien == deletedPasien) {
                    if (prevRel == NULL) {
                        //Relasi di awal list
                        pen->nextRelation = rel->next;
                    } else {
                        //Relasi di tengah/akhir list
                        prevRel->next = rel->next;
                    }
                    delete rel;
                    break;
                }
                prevRel = rel;
                rel = rel->next;
            }
            pen = pen->next;
        }
        deleteElmPasien(Lpas, deletedPasien);
        cout << "Pasien dengan NIK: " << NIK << " berhasil dihapus." << endl;
    } else {
        cout << "Pasien tidak ditemukan." << endl;
    }
}

void deletePenyakitFromPasien(listPenyakit &Lpen, listRelation &Lrel, listPasien &Lpas, string NIK, string namaPenyakit) {
    adrPasien cariPasien= findPasien(Lpas, NIK);
    adrPenyakit cariPenyakit = findPenyakit(Lpen, namaPenyakit);

    if (cariPenyakit != NULL && cariPasien != NULL) {
        adrRelation prevRel = NULL;
        adrRelation rel = cariPenyakit->nextRelation;

        while (rel != NULL) {
                if (rel->nextPasien == cariPasien) {
                    if (prevRel == NULL) {
                        //Relasi di awal list
                        cariPenyakit->nextRelation = rel->next;
                    } else {
                        //Relasi di tengah/akhir list
                        prevRel->next = rel->next;
                    }
                    break;
                }
                prevRel = rel;
                rel = rel->next;
            }
    } else {
        if (cariPenyakit == NULL && cariPasien != NULL) {
            cout << "Penyakit tidak ditemukan." << endl;
        } else if (cariPasien == NULL && cariPenyakit != NULL) {
            cout << "Pasien tidak ditemukan." << endl;
        } else {
            cout << "Pasien dan penyakit tidak ditemukan." << endl;
        }
    }
}

//Show list penyakit
void showPenyakit(listPenyakit Lpen) {
    adrPenyakit p = Lpen.first;

    cout << "=========================== LIST PENYAKIT ==========================" << endl;
    while (p != NULL) {
        cout << "Nama Penyakit : " << p->info.namaPenyakit << " || Kode ICDX : " << p->info.kodeicdx << " || ID Penyakit : " << p->info.idPenyakit << endl;
        p = p->next;
    }
    if (Lpen.first == NULL) {
        cout << "List Penyakit Kosong" << endl;
    }
    cout << "====================================================================" << endl;
    cout << endl;
}

//Show list pasien
void showPasien(listPasien Lpas) {
    adrPasien p = Lpas.first;

    cout << "============================ LIST PASIEN ===========================" << endl;
    while (p != NULL) {
        cout << "Nama Pasien : " << p->info.namaPasien << " || Usia : " << p->info.usia << " || Jenis Kelamin : " << p->info.jenisKelamin << " || NIK : " << p->info.NIK << endl;
        p = p->next;
    }
    if (Lpas.first == NULL) {
        cout << "List Pasien Kosong" << endl;
    }
    cout << "====================================================================" << endl;
    cout << endl;
}

//Find penyakit
adrPenyakit findPenyakit(listPenyakit Lpen, string namaPenyakit) {
    adrPenyakit p = Lpen.first;
    while (p != NULL) {
        if (p->info.namaPenyakit == namaPenyakit) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

//Find penyakit(advanced)
adrPenyakit findPenyakitAdvanced(listPenyakit Lpen, infotypePenyakit X) {
    adrPenyakit p = Lpen.first;
    while (p != NULL) {
        if (p->info.namaPenyakit == X.namaPenyakit || p->info.kodeicdx == X.kodeicdx || p->info.idPenyakit == X.idPenyakit) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

//Find pasien
adrPasien findPasien(listPasien Lpas, string NIK) {
    adrPasien p = Lpas.first;
    while (p != NULL) {
        if (p->info.NIK== NIK) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

//Connect relation
void connectRelation(listPenyakit Lpen, listPasien Lpas, string namaPenyakit, string NIK) {
    adrPenyakit cariPenyakit = findPenyakit(Lpen, namaPenyakit);
    adrPasien cariPasien = findPasien(Lpas, NIK);

    if (cariPenyakit != NULL && cariPasien != NULL) {
        adrRelation newRelation = createElemenRelation();
        newRelation->nextPasien = cariPasien;

        //Connecting
        if (cariPenyakit->nextRelation == NULL) {
            cariPenyakit->nextRelation = newRelation;
        } else {
            newRelation->next = cariPenyakit->nextRelation;
            cariPenyakit->nextRelation = newRelation;
        }

        cout << "Pasien berhasil terhubung dengan penyakit." << endl;

    } else {
        if (cariPenyakit == NULL && cariPasien != NULL) {
            cout << "Penyakit tidak ditemukan." << endl;
        } else if (cariPasien == NULL && cariPenyakit != NULL) {
            cout << "Pasien tidak ditemukan." << endl;
        } else {
            cout << "Pasien dan penyakit tidak ditemukan." << endl;
        }
    }
}

//Show all
void showAll(listPenyakit Lpen, listPasien Lpas, listRelation Lrel){
    adrPenyakit pen = Lpen.first;

    cout << "============================ LIST RELASI ===========================" << endl;
    cout << endl;

    while (pen != NULL) {
        cout << "Nama Penyakit : " << pen->info.namaPenyakit << " || Kode ICD-X : " << pen->info.kodeicdx << " || ID Penyakit : " << pen->info.idPenyakit << endl;
        cout << "====================================================================" << endl;

        adrRelation rel = pen->nextRelation;
        if (rel == NULL){
            cout << "Tidak Ada Pasien yang Terjangkit!" << endl;
        }
        while (rel != NULL) {
            cout << "Nama Pasien : " << rel->nextPasien->info.namaPasien << " || Usia : " << rel->nextPasien->info.usia << " || Jenis Kelamin : " << rel->nextPasien->info.jenisKelamin << " || NIK : " << rel->nextPasien->info.NIK << endl;
            rel = rel->next;
        }
        pen = pen->next;
        cout << endl;
    }
}

//Show Pasien Penyakit
void showPasienTerjangkit(listPenyakit Lpen, listPasien Lpas, string namaPenyakit){
    adrPenyakit srcPenyakit = findPenyakit(Lpen, namaPenyakit);

    if (srcPenyakit != NULL){

        cout << "Nama Penyakit : " << srcPenyakit->info.namaPenyakit << endl;
        cout << "========================= PASIEN TERJANGKIT =======================" << endl;

        adrRelation srcRelation = srcPenyakit->nextRelation;

        if (srcRelation == NULL) {
            cout << "Tidak ada pasien yang terjangkit." << endl;
        }
        while (srcRelation != NULL){

            cout << "Nama Pasien : " << srcRelation->nextPasien->info.namaPasien << " || Usia : " << srcRelation->nextPasien->info.usia << " || Jenis Kelamin : " << srcRelation->nextPasien->info.jenisKelamin << " || NIK : " << srcRelation->nextPasien->info.NIK;
            cout << endl;

            srcRelation = srcRelation->next;
        }
    } else {
        cout << "Penyakit tidak ditemukan." << endl;
    }
}

//Show Penyakit Pasien
void showPenyakitPasien(listPenyakit Lpen, listPasien Lpas, string NIK){
    adrPasien srcPasien = findPasien(Lpas, NIK);

    if (srcPasien != NULL){

        cout << "Nama Pasien : " << srcPasien->info.namaPasien << endl;
        cout << "======================= PENYAKIT YANG DIMILIKI =====================" << endl;

        adrPenyakit srcPenyakit = Lpen.first;
        bool sick = false;
        while (srcPenyakit != NULL){
            adrRelation srcRelation = srcPenyakit->nextRelation;

            while (srcRelation != NULL){
                if (srcRelation->nextPasien == srcPasien){
                    cout << "Nama Penyakit : " << srcPenyakit->info.namaPenyakit << " || Kode ICD-X : " << srcPenyakit->info.kodeicdx << " || ID Penyakit : " << srcPenyakit->info.idPenyakit << endl;
                    sick  = true;
                    break;
                }
                srcRelation = srcRelation->next;
            }

            srcPenyakit = srcPenyakit->next;
        }
        if (!sick) {
            cout << "Belum ada peyakit yang terdaftar pada pasien tersebut." << endl;
        }
    } else {
        cout << "Data pasien tersebut tidak ditemukan." << endl;
    }

}

//Count Child on Specific Parent
int countChild(listPenyakit Lpen, string namaPenyakit){
    adrPenyakit srcPenyakit = findPenyakit(Lpen, namaPenyakit);
    int jmlChild = 0;

    if (srcPenyakit != NULL){
        adrRelation srcRelation = srcPenyakit->nextRelation;
        while (srcRelation != NULL){
            jmlChild++;
            srcRelation = srcRelation->next;
        }
    }
    return jmlChild;
}

//Count Parent
int countParent(listPenyakit Lpen){
    adrPenyakit srcPenyakit = Lpen.first;

    int jmlPenyakit = 0;
    while (srcPenyakit != NULL){
        jmlPenyakit++;
        srcPenyakit = srcPenyakit->next;
    }
    return jmlPenyakit;
}

//Show Most Penyakit
void showMostPenyakit(listPenyakit Lpen){
    adrPenyakit srcPenyakit = Lpen.first;

    int i = 0, parent = 0;

    parent = countParent(Lpen);
    int child[parent];

    //Input jmlChild ke dalam array
    while (i < parent){
        child[i] = countChild(Lpen, srcPenyakit->info.namaPenyakit);
        i++;
        srcPenyakit = srcPenyakit->next;
    }

    int temp[parent];

    i = 0;
    while (i < parent){
        temp[i] = child[i];
        i++;
    }

    //Compute the size of array
    int l = sizeof(child) / sizeof(child[0]);

    //Sort the array in descending order
    sort(child, child + parent, greater<int>());

    i = 0;
    int k = 0;

    srcPenyakit = Lpen.first;
    int n;

    if (parent < 5) {
           n = parent;
    } else {
        n = 5;
    }

    cout << "======================= 5 PENYAKIT PALING BANYAK =====================" << endl;
     while (i < n) {
            if (i == 0) {
                while (child[i] != temp[k]) {
                    k++;
                    srcPenyakit = srcPenyakit->next;
                }
                cout << "Nama Penyakit : " << srcPenyakit->info.namaPenyakit << " || Kode ICDX : " << srcPenyakit->info.kodeicdx << " || ID Penyakit : " << srcPenyakit->info.idPenyakit << " || Jumlah Pengidap : " << child[i] << endl;
                i++;
            } else {
                if (child[i] == child[i-1]) {
                    k++;
                    srcPenyakit = srcPenyakit->next;
                    while (child[i] != temp[k]) {
                        k++;
                        srcPenyakit = srcPenyakit->next;
                    }
                     cout << "Nama Penyakit : " << srcPenyakit->info.namaPenyakit << " || Kode ICDX : " << srcPenyakit->info.kodeicdx << " || ID Penyakit : " << srcPenyakit->info.idPenyakit << " || Jumlah Pengidap : " << child[i] << endl;
                    i++;
                } else {
                    k = 0;
                    srcPenyakit = Lpen.first;
                    while (child[i] != temp[k]) {
                        k++;
                        srcPenyakit = srcPenyakit->next;
                    }
                     cout << "Nama Penyakit : " << srcPenyakit->info.namaPenyakit << " || Kode ICDX : " << srcPenyakit->info.kodeicdx << " || ID Penyakit : " << srcPenyakit->info.idPenyakit << " || Jumlah Pengidap : " << child[i] << endl;
                    i++;
                }
            }
        }
        cout << endl;
}

//Menu
void Menu(listPenyakit Lpen, listPasien Lpas, listRelation Lrel){
    int inputNum;

    do {
        //UI Menu
        int consoleWidth = 0; // Adjust this to match your console width

        std::string menu[] = {
        "================================= MENU ================================",
        "|               1. Input data Penyakit                                |",
        "|               2. Input data Pasien                                  |",
        "|               3. Connect Relasi Penyakit dan Pasien                 |",
        "|               4. Show Data Penyakit                                 |",
        "|               5. Show Data Pasien                                   |",
        "|               6. Show Data Penyakit beserta Pasien                  |",
        "|               7. Show Pasien dari Penyakit Tertentu                 |",
        "|               8. Show Penyakit yang dimiliki Pasien Tertentu        |",
        "|               9. Show 5 Penyakit Terbanyak                          |",
        "|              10. Jumlah Pasien pada Penyakit Tertentu               |",
        "|              11. Jumlah Penyakit yang Ada                           |",
        "|              12. Delete data Penyakit                               |",
        "|              13. Delete data Pasien                                 |",
        "|              14. Delete Penyakit dari Pasien Tertentu               |",
        "|               0. Exit                                               |",
        "======================================================================="
        };

        for (const auto& line : menu) {
            std::cout << std::setw((consoleWidth + line.length()) / 2) << line << std::endl;
        }

        cout << "Masukkan Angka untuk Memilih Fitur yang Anda Inginkan (0-14) : ";
        cin >> inputNum;
        cout << endl;

            switch (inputNum){
                case 1 :
                    {
                    //createListPenyakit(Lpen);

                    infotypePenyakit InputPenyakit;

                    cout << "Masukkan Nama Penyakit : ";
                    cin >> InputPenyakit.namaPenyakit;
                    cout << "Masukkan Kode ICDX : ";
                    cin >> InputPenyakit.kodeicdx;
                    cout << "Masukkan ID Penyakit : ";
                    cin >> InputPenyakit.idPenyakit;

                    adrPenyakit cek = findPenyakitAdvanced(Lpen, InputPenyakit);

                    if (cek == NULL){
                        adrPenyakit newPenyakit = createElemenPenyakit(InputPenyakit);
                        insertLastPenyakit(Lpen, newPenyakit);
                        cout << "Data Penyakit Berhasil Ditambahkan!" << endl;
                    } else {
                        cout << "Data Penyakit Tersebut Sudah Ada!" << endl;
                    }
                        break;
                    }

                case 2 :
                    {
                    //createListPasien(Lpas);

                    infotypePasien InputPasien;

                    cout << "Masukkan Nama Pasien : ";
                    cin >> InputPasien.namaPasien;
                    cout << "Masukkan Usia Pasien : ";
                    cin >> InputPasien.usia;
                    cout << "Masukkan Jenis Kelamin(L/P) : ";
                    cin >> InputPasien.jenisKelamin;
                    cout << "Masukkan NIK Pasien : ";
                    cin >> InputPasien.NIK;

                    adrPasien cek = findPasien(Lpas, InputPasien.NIK);

                    if (cek == NULL){
                        adrPasien newPasien = createElemenPasien(InputPasien);
                        insertLastPasien(Lpas, newPasien);
                        cout << "Data Pasien Berhasil Ditambahkan!" << endl;
                    } else {
                        cout << "Data Dengan NIK Tersebut Sudah Ada!" << endl;
                    }
                        break;
                    }
                case 3 :
                    {
                    string namaPenyakit, NIK;

                    showPenyakit(Lpen);
                    cout << "Pilih Penyakit : ";
                    cin >> namaPenyakit;
                    cout << endl;

                    showPasien(Lpas);
                    cout << "Pilih Pasien berdasarkan NIK : ";
                    cin >> NIK;
                    cout << endl;

                    connectRelation(Lpen, Lpas, namaPenyakit, NIK);
                    break;
                    }
                case 4 :
                    {
                        showPenyakit(Lpen);
                        cout << endl;
                        break;
                    }
                case 5 :
                    {
                        showPasien(Lpas);
                        cout << endl;
                        break;
                    }
                case 6 :
                    {
                        showAll(Lpen, Lpas, Lrel);
                        cout << endl;
                        break;
                    }
                case 7 :
                    {
                        string namaPenyakit;

                        showPenyakit(Lpen);
                        cout << "Masukkan Nama Penyakit yang Ingin Anda Cari : ";
                        cin >> namaPenyakit;

                        showPasienTerjangkit(Lpen, Lpas, namaPenyakit);
                        cout << endl;
                        break;
                    }
                case 8 :
                    {
                        string NIK;

                        showPasien(Lpas);
                        cout << "Masukkan NIK Pasien yang Ingin Anda Cari : ";
                        cin >> NIK;

                        showPenyakitPasien(Lpen, Lpas, NIK);
                        cout << endl;
                        break;
                    }
                case 9 :
                    {
                        showMostPenyakit(Lpen);
                        cout << endl;
                        break;
                    }
                case 10 :
                    {
                        string namaPenyakit;

                        showPenyakit(Lpen);
                        cout << "Masukkan Nama Penyakit : ";
                        cin >> namaPenyakit;
                        cout << "Jumlah Pasien Pada Penyakit " << namaPenyakit << " : "<< countChild(Lpen, namaPenyakit) << endl;
                        break;
                    }
                case 11 :
                    {

                        cout << "Jumlah Penyakit Di Lingkungan Sekitar : " << countParent(Lpen) << endl;
                        cout << endl;
                        break;
                    }
                case 12 :
                    {
                        string namaPenyakit;

                        showPenyakit(Lpen);
                        cout << "Masukkan Nama Penyakit yang Ingin Anda Hapus : ";
                        cin >> namaPenyakit;
                        cout << endl;
                        deletePenyakit(Lpen, Lrel, namaPenyakit);
                        cout << endl;
                        break;
                    }
                case 13 :
                    {
                        string NIK;

                        showPasien(Lpas);
                        cout << "Masukkan NIK Pasien yang Ingin Anda Hapus : ";
                        cin >> NIK;
                        cout << endl;
                        deletePasien(Lpen, Lpas, Lrel, NIK);
                        cout << endl;
                        break;
                    }
                case 14 :
                    {
                        string NIK, namaPenyakit;

                        showAll(Lpen, Lpas, Lrel);

                        cout << "Masukkan NIK Pasien : ";
                        cin >> NIK;
                        cout << "Masukkan Nama Penyakit : ";
                        cin >> namaPenyakit;

                        deletePenyakitFromPasien(Lpen, Lrel, Lpas, NIK, namaPenyakit);
                        cout << endl;
                        break;
                    }
                case 0 :
                    {
                        cout << "Keluar Dari Program." << endl;
                        cout << "Terima Kasih!" << endl;
                        cout << endl;
                        break;
                    }
                default :
                    {
                        // Cat
                        cout << " /\\     /\\       /\\     /\\  " << endl;
                        cout << "{  `---'  }     {  `---'  }" << endl;
                        cout << "{  O   O  }     {  -   -  }" << endl;
                        cout << "~~>  V  <~~     ~~>  ^  <~~ "<< endl;
                        cout << " \\ \\___/ /       \\ \\___/ / " << endl;
                        cout << "  \\_____/         \\_____/" << endl;

                        cout << endl;
                        cout << "Invalid Input. Tolong Masukkan Angka (0-14)." << endl;
                        cout << endl;
                    }
            }

        } while (inputNum != 0);
}

