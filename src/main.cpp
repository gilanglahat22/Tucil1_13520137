/* NAMA      : MUHAMMAD GILANG RAMADHAN             */
/* NIM       : 13520137                             */
/* KELAS     : K-2                                  */ 
/* DESKRIPSI : TUGAS KECIL 1 STRATEGI ALGORITMA     */

// PENYELESAIAN WORD SEARCH PUZZLE DENGAN ALGORITMA BRUTE FORCE

#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

/* Menginisialisasikan Variabel Global */
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
long long banyak_pengecekan = 0;
vector<vector<int> > vecX;
vector<vector<int> > vecY;
vector<vector<int> > Penunjuk_arah;
vector<string>tampung_kata;
vector<vector<char> >tampung_char;
bool file_berhasil_dibuka = true;
// Menginisialisasikan arah gerak (x,y) yang berguna untuk pengecekan 8 arah 
int moveX[] = { -1, -1, -1, 1, 1, 1, 0, 0 };
int moveY[] = { -1, 0, 1, -1, 0, 1, -1, 1 };

// Procedure untuk memasukkan data isi file txt ke vektor
void convertTXT(){
    // Membuka File Inputan

    ifstream ifs;
    ifs.open("../test/stars.txt");

    if (ifs.is_open()){

        // Membaca Line

        string line;

        // Memasukkan karakter-karakter yang membentuk matriks dari file txt ke vektor yang menampung char-char tersebut dalam bentuk matriks
        while( getline( ifs, line ) )
        {
            vector<char> temp;
            if (!line.empty()){
                int indeks = 0;
                while (indeks < line.length()){
                    if (line[indeks] != ' '){
                        temp.push_back(line[indeks]);
                    }
                    indeks++;
                }
                tampung_char.push_back(temp);
            }
            else{
                break;
            }
        }

        // Memasukkan dan menampung karakter yang ingin dicari
        // Ke dalam container berupa vektor
        while( getline( ifs, line ) ){
            tampung_kata.push_back(line);
        }
    }
    else{
        cout << "File tidak bisa dibuka";
        file_berhasil_dibuka = false;
    }
    ifs.close();
}

// Fungsi pencarian karakter pada kata yang ingin dicari pada delapan arah pencarian di puzzle
bool Search_8_Direction(string word, vector<vector<char> >tampung_char, int row, int col, int moveX, int moveY)
{
    // Inisialisasikan RD sebagai penunjuk baris dan CD sebagai penunjuk kolom yang akan bergerak sesuai dengan moveX dan moveY
    int j = 1, RD = row + moveY, CD = col + moveX;
    
    // Jika RD dan CD tidak overbound dan setiap huruf ke j cocok
    while ((j < word.length()) && (RD < tampung_char.size() && CD < tampung_char[0].size() && RD >= 0 && CD >= 0) && (word[j] == tampung_char[RD][CD]))
    {
        // Jika cocok, bergerak lagi
        CD += moveX;
        RD += moveY;
        j++;
        banyak_pengecekan++;
    }

    // Jika semua karakter cocok, maka nilai dari j harus sama dengan panjang dari kata yang ingin dicari
    if (j == word.length()){
        return true;
    }
}

// Fungsi untuk mengecek apakah indeks ke indeks_row = vecY dan dan indeks_col = vecX 
// Jika benar akan mengembalikan sesuai dengan arahnya yaitu 1,2,3,..,8
// Jika salah maka akan mengembalikan 0 
int Check_Indeks(vector<vector<int> > vecX, vector<vector<int> > vecY, int indeks_row, int indeks_col){
    for (int k = 0; k < vecX.size(); k++){
        for (int L = 0; L < vecX[k].size(); L++){
            if ((indeks_row == vecY[k][L]) & (indeks_col == vecX[k][L])){
                return Penunjuk_arah[k][L];
            }
        }
    }
    return 0;
}

// Procedure untuk memasukkan setiap koordinat dari setiap karakter 
// Ke dalam vektor of vektor
void Simpan_koordinat(vector<vector<char> >tampung_char, string word){
    for (int row = 0; row < tampung_char.size(); row++){
        for (int col = 0; col < tampung_char[row].size(); col++){
            if (word[0] == tampung_char[row][col])
            {
                for (int arah = 0; arah < 8; arah++)
                {
                    // Jika digit ke-2 sampai digit terakhir dari huruf yang akan diperiksa di puzzle ditemukan, 
                    // Maka masukkan koordinat-koordinat huruf tersebut pada puzzle 
                    // Dengan cara memasukkan masing-masing absis dan ordinat tersebut ke dalam tempX dan tempY 
                    // kemudian masukkan ke dalam vecX dan VecY
                    if (Search_8_Direction(word, tampung_char, row, col, moveX[arah], moveY[arah])){
                        vector<int> tempPenunjukArah;
                        vector<int> tempX;
                        vector<int> tempY;
                        for (int i = 0; i < word.length(); i++){
                            tempX.push_back(col + (i * moveX[arah]));
                            tempY.push_back(row + (i * moveY[arah]));

                            // Menyimpan arah dari setiap titik
                            if (moveX[arah] == -1 & moveY[arah] == -1){
                                tempPenunjukArah.push_back(1);
                            }
                            else if (moveX[arah] == -1 & moveY[arah] == 1){
                                tempPenunjukArah.push_back(2);
                            }
                            else if (moveX[arah] == 1 & moveY[arah] == -1){
                                tempPenunjukArah.push_back(3);
                            }
                            else if (moveX[arah] == 1 & moveY[arah] == 1){
                                tempPenunjukArah.push_back(4);
                            }
                            else if (moveX[arah] == 0 & moveY[arah] == -1){
                                tempPenunjukArah.push_back(5);
                            }
                            else if (moveX[arah] == -1 & moveY[arah] == 0){
                                tempPenunjukArah.push_back(6);
                            }
                            else if (moveX[arah] == 0 & moveY[arah] == 1){
                                tempPenunjukArah.push_back(7);
                            }
                            else if (moveX[arah] == 1 & moveY[arah] == 0){
                                tempPenunjukArah.push_back(8);
                            }
                        }
                        vecX.push_back(tempX);
                        vecY.push_back(tempY);
                        Penunjuk_arah.push_back(tempPenunjukArah);
                    } 
                }
            }
            banyak_pengecekan++;
        }
    }
}

// Procedure untuk menampikan Solusi berbentuk matriks ke layar
void PrintSolusi(){
    for (int i = 0; i < tampung_char.size(); i++){
        for (int j = 0; j < tampung_char[i].size(); j++){
            // Mewarnai karakter dengan warna tertentu
            // Sesuai dengan arahnya
            if (Check_Indeks(vecX, vecY, i, j) == 1){
                SetConsoleTextAttribute(h, 1);
                cout << tampung_char[i][j] << " ";
            }
            else if (Check_Indeks(vecX, vecY, i, j) == 2){
                SetConsoleTextAttribute(h, 2);
                cout << tampung_char[i][j] << " ";
            }
            else if (Check_Indeks(vecX, vecY, i, j) == 3){
                SetConsoleTextAttribute(h, 4);
                cout << tampung_char[i][j] << " ";
            }
            else if (Check_Indeks(vecX, vecY, i, j) == 4){
                SetConsoleTextAttribute(h, 5);
                cout << tampung_char[i][j] << " ";
            }
            else if (Check_Indeks(vecX, vecY, i, j) == 5){
                SetConsoleTextAttribute(h, 6);
                cout << tampung_char[i][j] << " ";
            }
            else if (Check_Indeks(vecX, vecY, i, j) == 6){
                SetConsoleTextAttribute(h, 9);
                cout << tampung_char[i][j] << " ";
            }
            else if (Check_Indeks(vecX, vecY, i, j) == 7){
                SetConsoleTextAttribute(h, 3);
                cout << tampung_char[i][j] << " ";
            }
            else if (Check_Indeks(vecX, vecY, i, j) == 8){
                SetConsoleTextAttribute(h, 13);
                cout << tampung_char[i][j] << " ";
            }
            else if (Check_Indeks(vecX, vecY, i, j) == 0){
                // Jika tidak warnai putih pada setiap karakter yang akan diprint
                SetConsoleTextAttribute(h, 7);
                cout << tampung_char[i][j] << " ";
            }
        }
        cout << endl;
    }
    SetConsoleTextAttribute(h, 7);
}

// Procedure untuk solusi dalam bentuk koordinat kata yang ingin dicari
void solve(){
    for (int i = 0; i < tampung_kata.size(); i++){
        // Memasukkan setiap koordinat dari setiap karakter ke dalam vektor of vektor
        Simpan_koordinat(tampung_char, tampung_kata[i]);
    }
}

// Main Program
int main()
{
    convertTXT();
    if (file_berhasil_dibuka){
        // Waktu eksekusi dimulai
        clock_t start, end;
        start = clock();
        
        // Proses melakukan brute force
        solve();

        // Menampilkan solusi
        PrintSolusi();

        cout << endl;

        // Waktu eksekusi selesai
        end = clock();
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        // Menampilkan waktu eksekusi program
        cout << "Waktu Eksekusi Program : " << fixed << time_taken * 1000 << setprecision(5); 
        cout << " ms " << endl;

        // Menampilkan jumlah pengecekan kata pada program
        cout << "Jumlah Total pengecekan Huruf : " << banyak_pengecekan << endl;
    }
    return 0;
}
