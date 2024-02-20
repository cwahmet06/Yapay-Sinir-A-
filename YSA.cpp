#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include <stdlib.h>
#include <iostream>

#define MAXCHAR 1000

using namespace std;

float input[8];

float y;

int idx = 0;

float yüzde = 0;

double test1, test2, test3, test4, test5, test6, test7, test8;

double hata;    

double b0 = 0, b1 = 0, b2 = 0, b3 = 0, b4 = 0, b5 = 0, b6 = 0, b7 = 0, b8 = 0;

double öğrenmeHızı = 0.01; 

double  e = 2.71828;

int sayac = 0;

int egitim_dongu = 0;

double pred;

int epoch;

float islem(float* in)
{
    float toplam = 0;


    for (int i = 0; i < 8; i++)


    toplam += in[i];


    return toplam;


}



int main() {

    FILE* fp, *fp2;

    char satır[MAXCHAR];

    char satir2[MAXCHAR];

    char* girdi;

    std::cout << "***********************************************" << endl;
    std::cout << "Egitim / Test yuzde oraninin giriniz(Egitim %): "; 
    cin >> yüzde;
    std::cout << "***********************************************\n" << endl;

    int cast = (1030*yüzde) / 100;

    fp2 = fopen("SOURCES\\targets.csv", "r");
    if (!fp2)
    return -1;

    std::cout << "***********************************************" << endl;
    printf("Targets CSV Okunuyor..\n");
    std::cout << "***********************************************\n" << endl;

    fp = fopen("SOURCES\\inputs.csv", "r");
    if (!fp)
    return -1;

    fgets(satır, MAXCHAR, fp);

    std::cout << "Satir: " << satır << endl; 

    std::cout << "***********************************************" << endl;
    std::cout << "Inputs CSV Okunuyor.." << endl;
    std::cout << "***********************************************\n" << endl;

    fgets(satır, MAXCHAR, fp2);
    std::cout << "Satir: " << satır << endl; 
    std::cout << "***********************************************\n";
    std::cout << "Egitim sureci baslatiliyor..\n";
    std::cout << "***********************************************\n\n";
    std::cout << "***********************************************\n";
    std::cout << "Kac Epoch isteniyor(x8): ";

    cin >> epoch;

    std::cout << "***********************************************" << endl;
    std::cout << "Ogrenme hizini giriniz( Baslangic degeri: 0.01): ";
    cin >> öğrenmeHızı;
    std::cout << "***********************************************" << endl;


    int döngü = epoch * 8;




    while (feof(fp) != true)    
    {
        sayac++;
        if (sayac >= cast)
        {
            break;
        }

        fgets(satır, MAXCHAR, fp);
        std::cout << "Satir: "<<satır<<endl;
        girdi = strtok(satır, ",");

        while (girdi != NULL)
        {
            std::cout <<"Girdi: "<< girdi<< endl; 
            input[idx++] = atof(girdi);
            girdi = strtok(NULL, ",");
        }

        fgets(satir2, MAXCHAR, fp2);
        std::cout << "Satir: " << satir2 << endl;
        girdi = strtok(satir2, ",");

        while (girdi != NULL)
        {
            std::cout << "Girdi: " << girdi << endl; 
            y = atof(girdi);
            girdi = strtok(NULL, ",");
        }

   



        
        if (egitim_dongu < döngü) 
        {   
            egitim_dongu++;

            double p = -(b0 + b1 * input[0] + b2 * input[1] + b3 * input[2] + b4 * input[3] + b5 * input[4] + b6 * input[5] + b7 * input[6] + b8 * input[7]);  
            double pred = 1 / (1 + pow(e, p)); //SİGMOİD AF. uygulayarak nihai tahminin hesaplanması
            hata = y - pred;  
            b0 = b0 - öğrenmeHızı * hata * pred * (1 - pred) * 1.0;     
            b1 = b1 + öğrenmeHızı * hata * pred * (1 - pred) * input[0];
            b2 = b2 + öğrenmeHızı * hata * pred * (1 - pred) * input[1];
            b3 = b3 + öğrenmeHızı * hata * pred * (1 - pred) * input[2];
            b4 = b4 + öğrenmeHızı * hata * pred * (1 - pred) * input[3];
            b5 = b5 + öğrenmeHızı * hata * pred * (1 - pred) * input[4];
            b6 = b6 + öğrenmeHızı * hata * pred * (1 - pred) * input[5];
            b7 = b7 + öğrenmeHızı * hata * pred * (1 - pred) * input[6];
            b8 = b8 + öğrenmeHızı * hata * pred * (1 - pred) * input[7];
        } 

        idx = 0;
    }


    while (feof(fp) != true) 
    {

        fgets(satır, MAXCHAR, fp);
        std::cout << "Satir: " << satır << endl;
        girdi = strtok(satır, ",");

        while (girdi != NULL)
        {
            std::cout << "Girdi: " << girdi << endl;
            input[idx++] = atof(girdi);
            girdi = strtok(NULL, ",");
        }

        pred = b0 + b1 * input[0] + b2 * input[1] + b3 * input[2] + b4 * input[3] + b5 * input[4] + b6 * input[5] + b7 * input[6] + b8 * input[7];  

        idx = 0;

    }

    // SİSTEMİN TESTİ

    std::cout << "\n***********************************************\n";
    std::cout << "Test sureci baslatiliyor..\n";
    std::cout << "***********************************************\n" << endl;
    std::cout << "B0=" << b0 << " " << "B1=" << b1 << " " << "B2=" << b2 << " " << "B3=" << b3 << " " << "B4=" << b4 << " " << "B5=" << b5 << " " << "B6=" << b6 << " " << "B7=" << b7 << " " << "B8=" << b8 << " " << " Hata= %" << hata << endl;// her adımdan sonra değerleri yazdırma
    std::cout << "\nModel tarafindan tahmin edilen deger= " << pred << endl;
    
}

