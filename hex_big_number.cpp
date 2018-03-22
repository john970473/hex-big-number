//compile environment : dev C++
#include <iostream>
#include <stdint.h>
#include <sstream>
#include <string.h>
#include <stdlib.h>
using namespace std;
#define MAX 300

void read_from_string(int* big, char* str) //hex input convert to int 
{
    int i=0, len=strlen(str);
    memset(big, 0, sizeof(int)*MAX);
    for(i=len-1; i>=0; --i){
        if(str[i]>='0' && str[i]<='9')
            big[len - i - 1] = str[i] - '0';
        else
            big[len - i - 1] = str[i] - 'a' + 10;
    }

}

void big_print(int *big) //print big number and convert from int to hex
{
    int i=MAX-1;
    for(i=MAX-1;i>0 && big[i]==0; --i);
    while(i>=0){
        if(big[i]==10)
            cout << 'a';
        else if (big[i]==11)
            cout << 'b';
        else if (big[i]==12)
            cout << 'c';
        else if (big[i]==13)
            cout << 'd';
        else if (big[i]==14)
            cout << 'e';
        else if (big[i]==15)
            cout << 'f';
        else
            cout<<big[i];
        --i;
    }
    cout << endl;
}

void big_assign(int *a, int *b) // b is assigned to a
{
    memset(a, 0, sizeof(int)*MAX);
    int i;
    for (i=MAX-1 ; i>=0 ; i--)
        a[i] = b[i];
}
int big_compare(int *a, int *b) // if a>b return positive number , if a=b return 0 , if a<b return negative number
{
    int i=MAX-1;
    while(i>0 && a[i]==b[i]) --i;
    return a[i]-b[i];
}

void big_add(int *rst, int *a, int *b) // rst = a + b
{
    memset(rst, 0, sizeof(int)*MAX);
    int i, sum, carry;
    for(carry=i=0; i<MAX; ++i){
        rst[i] = a[i] + b[i] + carry;
        carry = rst[i] / 16;
        rst[i]%=16;
    }
}

bool big_sub(int *rst, int *a, int *b) // rst = a-b return sign = 0 , if a<b => rst = b-a and return sign = 1
{
    memset(rst, 0, sizeof(int)*MAX);
    int i, borrow;
    bool sign=0;
	
    if (big_compare(a,b)>=0){ // a<b
        for(borrow=i=0; i<MAX; ++i) {
            rst[i] = a[i]-b[i]-borrow; // sub borrow number last time
            if(rst[i]<0) {
                borrow=1, rst[i]+=16; // rst < 0 => need to borrow
            } else {
                borrow=0; 
            }
        }

    }
    else { // a<b  
        for(borrow=i=0; i<MAX; ++i) {
            rst[i] = b[i]-a[i]-borrow; 
            if(rst[i]<0) {
                borrow=1, rst[i]+=16; 
            } else {
                borrow=0; 
            }
        }
        sign=1;
    }
    return sign;
}

void big_mul(int *rst, int *a, int *b) //rst = a*b
{
    int i, j, carry;
    memset(rst, 0, sizeof(int)*MAX); 
    for(i=0; i<MAX; ++i) {
        if(a[i]==0) continue;
        for(j=0; i+j<MAX; ++j)
            rst[i+j]+= a[i]*b[j];
    }
    
    for(carry=i=0; i<MAX; ++i) { // if rst[i] >= 16 , need to add a carry
        rst[i]+=carry;
        carry = rst[i] / 16;
        rst[i] %= 16;
    }
}

void big_div(int *div, int *rst, int *a, int *b) // a/b = div ... rst
{
    int sub[MAX];
    int i=0, j, carry;
    memset(div, 0, sizeof(int)*MAX);
    memset(rst, 0, sizeof(int)*MAX);
    while(!big_sub(rst, a, b)){ //keep doing rst = a-b , a = rst , div + 1
        big_assign(a,rst); 
        div[0]++; 
        for(i=0 ; i<MAX ; i++){ // carry 
            if(div[i] == 16){
                div[i] = 0;
                div[i+1] += 1;
            }
        }
    }

}
int main(){

    char *str1 = new char[300](); // input a 
    char *str2 = new char[300](); // input b
    int a[MAX],b[MAX],add[MAX],sub[MAX],mul[MAX],div[MAX],rem[MAX];
    cout << "a= ";
    cin >> str1;
    cout << "b= ";
    cin >> str2;

    read_from_string(a,str1);
    read_from_string(b,str2);

    cout << "a+b= ";
    big_add(add,a,b);
    big_print(add);

    cout << "a-b= ";
    if(big_sub(sub,a,b)) // if a<b , add a sign '-'
        cout << '-';
    big_print(sub);

    cout << "a*b= ";
    big_mul(mul,a,b);
    big_print(mul);

    cout << "a/b= ";
    big_div(div, rem ,a, b);
    big_print(div);

    cout << "a%b= ";
    big_div(div, rem ,a, b);
    big_print(a);



    return 0;
}
