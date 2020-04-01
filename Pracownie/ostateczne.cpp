#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <float.h> 
#include <algorithm>
#include <iostream>

using namespace std;

//pomysły
//zmienic na longlong
//cos zrobic z tym brutem
//zmienic tego fora na while zeby bral pod uwage aktualne minimum
//w podziale na p i l mozesie nie miescic

struct Punkt{
    int x;
    int y;
};
double MIN = FLT_MAX;
Punkt X[500000];
Punkt Y[500000];
Punkt minT[3];

int porownajY(const void* p1, const void* p2)
{
   if((*(Punkt*)p1).y<(*(Punkt*)p2).y) return -1;
   if((*(Punkt*)p1).y>(*(Punkt*)p2).y) return 1;
   else {
    if((*(Punkt*)p1).x<(*(Punkt*)p2).x) return -1;
    if((*(Punkt*)p1).x>(*(Punkt*)p2).x) return 1;
    else return 0;
   };
}

int porownajX(const void* p1, const void* p2)
{
   if((*(Punkt*)p1).x<(*(Punkt*)p2).x) return -1;
   if((*(Punkt*)p1).x>(*(Punkt*)p2).x) return 1;
   else {
    if((*(Punkt*)p1).y<(*(Punkt*)p2).y) return -1;
    if((*(Punkt*)p1).y>(*(Punkt*)p2).y) return 1;
    else return 0;
   };
}

double odleglosc (Punkt a, Punkt b){
   return sqrt((double)((long long)(a.x-b.x)*(long long)(a.x-b.x) + (long long)(a.y-b.y)*(long long)(a.y-b.y)));
}

double obwod (Punkt a, Punkt b, Punkt c){
    return odleglosc(a, b)+odleglosc(b, c)+odleglosc(c, a);
}

//brut poprawiony

double brute(int l, int r){

    for(int i = l; i<r; i++){
        for(int j = i+1; j<r; j++){
            for(int k=j+1; k<r; k++){
                if(obwod(X[i], X[j], X[k])<MIN){
                    MIN = obwod(X[i], X[j], X[k]);
                    minT[0]= X[i];
                    minT[1]= X[j];
                    minT[2]= X[k];
                }
            }
        }
    }
    return MIN;
}


double pasek (Punkt pasek[], int size, double currmin){
    double min = currmin;
    double marg = currmin/2;
    for (int i=0; i<size; i++){
        for (int j=i+1; j<size && (pasek[j].y - pasek[i].y )< marg; j++){
            for (int k=j+1; k<size && (pasek[k].y-pasek[i].y) < marg; k++){
                    
                    if(obwod(pasek[i], pasek[j], pasek[k])<min){
                    min = obwod(pasek[i], pasek[j], pasek[k]);
                    minT[0]=pasek[i];
                    minT[1]=pasek[j];
                    minT[2]=pasek[k];
                    }
            }
        }
    }
    return min;
}
//glowna poprawiona

double glowna(int l, int r){ 

    int n = r - l; 
    if (n<=7) return brute(l, r);

    int mid = l+n/2;
    Punkt midPoint=X[mid];

    double minl = glowna(l, mid);
    if(brute(l, mid)==minl){

        printf("%s", "okL \n");
    }
    else printf("%s", "nieok!L \n");
    double minr = glowna(mid, r);
        if(brute(mid, r)==minr){

        printf("%s", "okR \n");
    }
    else printf("%s", "nieok!R \n");
    double d = (minl<minr? minl : minr); //dobra, czyli chyba wywala sie na pasku!!!

    Punkt p[n];  
    int j = 0;
    for(int i = l; i<r; i++){
        if(abs(Y[i].x - midPoint.x)<(d/2))
        {
            p[j]=Y[i];
            j++;
        }
    }
    printf("Z D %f\n", d);
    double result = pasek(p, j, d);
    printf("Z PASKA %f\n", result);
    d = (d<result? d : result);
    printf("Z OBWODU %f\n", obwod(minT[0], minT[1], minT[2]));
    return d;
}

double pre(int n){

    qsort(X, n, sizeof(Punkt), porownajX);
    qsort(Y, n, sizeof(Punkt), porownajY);    
    return glowna(0, n);
}


int main()
{
    ios_base::sync_with_stdio(false);
    int ile_punktow;
    scanf("%d", &ile_punktow);
    for(int i=0; i<ile_punktow; i++)
    {
        Punkt temp;
        int tx, ty;
        scanf("%d %d", &tx, &ty);
        temp.x=tx;
        temp.y=ty;
        X[i]=temp;
        Y[i]=temp;
    };
    printf("%f \n", pre(ile_punktow));
    printf("%f \n", obwod(minT[0], minT[1], minT[2]));
    // printf("%s","ALGO: \n");
    // printf("%d %d \n %d %d \n %d %d \n",minT[0].x, minT[0].y, minT[1].x, minT[1].y, minT[2].x, minT[2].y);

    printf("%s","BRUT: \n");
    printf("%f", brute(0, ile_punktow));
    // brute(0, ile_punktow);
    // printf("%d %d \n %d %d \n %d %d \n",minT[0].x, minT[0].y, minT[1].x, minT[1].y, minT[2].x, minT[2].y);



    return 0;

}