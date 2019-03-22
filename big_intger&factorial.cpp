#include <iostream>
#include <math.h>
using namespace std;
class big_integer{
    private:
        int num_array[100] = {};
    public:
        big_integer(int);
        big_integer operator*(big_integer);
        void print(){
            int count = 0;
            for (int i = 99; i >= 0; i--) {
                if (num_array[i] != 0) count += 1;
                if (count != 0) cout << num_array[i];
            }
        }
};
big_integer:: big_integer(int n) {
    for (double i = 0; i < 100; i++) {
        num_array[int(i)] = n % int(pow(10, i + 1)) / int(pow(10, i));
    }
}
big_integer big_integer:: operator*(big_integer n){
    int k = 0;
    big_integer temp = *this;
    for (int i = 0; i < 100; i++) {
        k += int(n.num_array[i] * pow(10,i));
    }
    for (int i = 0; i < 100; i++) {
        temp.num_array[i] = temp.num_array[i] * k;
        //cout << temp.num_array[i] << endl;
    }
    //cout << endl;
    for (int i = 0; i < 99; i++) {
        temp.num_array[i + 1] = (temp.num_array[i] / 10) +  temp.num_array[i + 1];
        temp.num_array[i] = temp.num_array[i] % 10;
    }
    /*for (int i = 0; i < 100; i++) {
        cout << temp.num_array[i] << endl;
    }
    cout << endl;*/
    return temp;
}
big_integer fact(int n){
    big_integer one(1);
    big_integer value(n);
    if (n == 1) return one;
    else return   fact(n - 1) * value;
}
int main() {
    int N;
    cin >> N;
    fact(N).print();
    //cout << endl;
    return 0;
}