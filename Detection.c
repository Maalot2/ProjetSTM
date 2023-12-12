//
// Created by maaloton 12/12/2023.
//

#include "Detection.h"

/*Critère :
* frelon -> f0 entre 110Hz et 135Hz -> SNR <2.2
* abeille -> f0 entre 148Hz et 182Hz -> SNR > 3
* mouche -> f0 entre 190Hz et 210Hz -> SNR > 3
* */
//retour : 1 = frelon, 2 = abeille, 3 = mouche , -1 = Non trouvé
int detection(int *IndicePic, float *freqAll, float *AmpALL){
    int i=0;
    float f0=0;
    float N0=0;
    while(IndicePic[i+1]!=-1){
        f0+=freqAll[IndicePic[i+1]]-freqAll[IndicePic[i]];
        i++;
    }
    f0=f0/(float)i;
    i=0;
    while(IndicePic[i+1]!=-1){
        N0+=AmpALL[IndicePic[i+1]]-AmpALL[IndicePic[i]];
        i++;
    }
    N0/=(float)i;

//ENTRE 1000 ET 2000HZ
    i=0;
    int cpt=0,j=0,k=0;
    float maxAmp=0,bruit=0,SNR=0,N1=0;
    while((float)i*f0<=1000)i++;
    while((float)i*f0>=1000 && (float)i*f0<=2000){
        while(freqAll[j]<=(float)i*f0-2 )j++;
        maxAmp = AmpALL[j-1] > AmpALL[j] ? (AmpALL[j-1] > AmpALL[j+1] ? AmpALL[j-1] : AmpALL[j+1]) : (AmpALL[j] > AmpALL[j+1] ? AmpALL[j] : AmpALL[j+1]);
        while(freqAll[k]<=(i-0.5)*f0-2 )k++;
        bruit = AmpALL[k-1] < AmpALL[k] ? (AmpALL[k-1] < AmpALL[k+1] ? AmpALL[k-1] : AmpALL[k+1]) : (AmpALL[k] < AmpALL[k+1] ? AmpALL[k] : AmpALL[k+1]);
        SNR+=maxAmp/bruit;
        N1+=maxAmp;
        i++;
        cpt++;

    }
    N1/=(float)cpt;
    SNR/=(float)cpt;

    if(f0>=110 && f0<=135 && SNR < 2.2) return 1;       //frelon
    else if(f0>=148 && f0 <=182 && SNR > 3 ) return 2;  //abeille
    else if (f0 >=190 && f0 <= 210 && SNR > 3) return 3;//mouche
    else return -1;

}