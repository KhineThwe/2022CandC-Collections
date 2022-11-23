//
// Created by khine on 11/21/2022.
//

#include "stdio.h"
int main(){
    int i,data[10],total =0;
    printf("Enter 10 number: ");
    for(i=0;i<10;i++){
        scanf("%d",data+i);
        //&data[i]
        //data --> array , i ---> index
        total += *(data+i);
        //total += data[i]
    }

    printf("Total Number = %d ",total);
    for(int x=0;x<10;x++){
        printf("Data at index = %d: memaddr = %X\n",data[x],&data[x]);
    }
    return 0;
}
//Pointer store address of another variable
//pointer hard exercise 1 ခုအကြွေးမှတ်ရန်
