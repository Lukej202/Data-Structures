#include <iostream>
using namespace std;

int fib(int n);

int main(){
    int num;
    cin >> num;
    cout << fib(num) << endl;
}

int fib(int n){
    if(n == 0){
        return 0;
    }else if(n == 1){
        return 1;
    }else{
        return fib(n-2) + fib(n-1);
    }
}
