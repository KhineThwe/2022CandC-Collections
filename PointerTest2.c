//
// Created by khine on 11/22/2022.
//
#include "stdio.h"
void swap(int *d1,int *d2);
int main(){
    int data1 =10;
    int data2 =20;
    swap(&data1,&data2);//pass by reference
    printf("Data 1: %d\nData 2: %d",data1,data2);

    return 0;
}
void swap(int *d1,int *d2){
    int temp;
    temp = *d1;
    *d1 = *d2;
    *d2 = temp;
}

