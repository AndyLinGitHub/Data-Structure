#include <iostream>
void magic_square(int n){
    int** ptr = NULL;
    ptr = new int* [n];
    for(int i = 0 ; i < n ; i++){
        ptr[i] = new int [n];
    }
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n ; j++){
            ptr[i][j] = 0;
        }
    }
    ptr[0][n/2] = 1;
    int x1 = 0; int y1 = n/2;
    int x2 = 0; int y2 = 0;
    for (int i = 1; i < n * n ;i++){
        if (x1 - 1 >= 0) x2 = x1 - 1;
        else x2 = x1 - 1 + n;
        if (y1 - 1 >= 0) y2 = y1 - 1;
        else y2 = y1 - 1 + n;
        if (ptr[x2][y2] == 0) {ptr[x2][y2] = i + 1;x1 = x2 ; y1 = y2;}
        else {
            if (x1 + 1 < n) {ptr[x1 + 1][y1] = i + 1;x1 = x1 + 1;}
            else {ptr[x1 + 1 - n][y1] = i + 1;x1 = x1 + 1 - n;}
        }

    }
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n ; j++){
            if (j != n - 1) std:: cout << ptr[i][j] << " ";
            else std:: cout << ptr[i][j] << std:: endl;
        }
    }
    std:: cout << std:: endl;

    int sum = 0;
    for(int i = 0; i < n ; i++){
        for(int j = 0; j < n ; j++){
            if (j != n - 1) sum += ptr[i][j];
            else {sum += ptr[i][j];
                  std:: cout << sum << std:: endl;
                  sum = 0;
            }
        }
    }
    std:: cout << std:: endl;
    for (int i = 0; i < n ; i++) delete [] ptr[i];
    delete [] ptr;
}
int main() {
    magic_square(1);
    magic_square(3);
    magic_square(5);
    magic_square(7);
    magic_square(9);
    magic_square(11);
    return 0;
}
