#include <iostream>
using namespace std;

void swap(int &a, int &n){
    int temp;
    temp=a;
    a = n;
    n = temp;
}

int main(){
    int a;
    int b;
    cout << "Selectionnez a :";
    cin >> a;
    cout << "Selectionnez b :";
    cin >> b;
    swap(a,b);
    cout << "Maintenant a="<<a<< "et b="<<b<< endl;
    return 0;
}