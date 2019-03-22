#include <iostream>
#include <math.h>
using namespace std;

inline void PrintMatrix(double** &M, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j != n - 1) cout << M[i][j] << "  ";
            else cout << M[i][j] << endl;
        }
    }
}
int main(){
   int n = 0;
   cin >> n;
   //cout << n << endl;
   double** A;
   double** B;
   double** C;
   double** D;
   double** E;
   A = new double* [n];
   B = new double* [n];
   C = new double* [n];
   D = new double* [n];
   E = new double* [n];
   for (int i = 0; i < n; i++){
       A[i] = new double[n];
       B[i] = new double[n];
       C[i] = new double[n];
       D[i] = new double[n];
       E[i] = new double[n];
   }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
            D[i][j] = A[i][j];
            if(i == j) B[i][j] = E[i][j] = 1;
            else B[i][j] = E[i][j] = 0;
            C[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++){
        for(int k = 1; k < n - i; k++) {
            double mul = (A[i + k][i]/A[i][i]);
            for (int j = 0; j < n; j++) {
                A[i + k][j] -= A[i][j] * mul;
                B[i + k][j] -= B[i][j] * mul;
            }
        }
    }

    for (int i = n -1; i >= 0; i--){
        double mul = A[i][i];
        for (int j = 0; j < n; j++) {
            A[i][j] /= mul;
            B[i][j] /= mul;
        }
        for(int k = 1; k < i + 1; k++){
            mul = (A[i - k][i]/A[i][i]);
            for (int j = 0; j < n; j++) {
                A[i - k][j] -= A[i][j] * mul;
                B[i - k][j] -= B[i][j] * mul;
            }
        }
    }

    double error = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) C[i][j] += D[i][k] * B[k][j];
            if (abs(C[i][j] - E[i][j]) >= error) error = abs(C[i][j] - E[i][j]);

        }
    }

    cout << error << endl;

    //PrintMatrix(A,n);
    //cout << endl;
    //PrintMatrix(B,n);
    //cout << endl;

    for (int i = 0; i < n; i++){
        delete [] A[i];
        delete [] B[i];
        delete [] C[i];
        delete [] D[i];
        delete [] E[i];
    }
    delete [] A;
    delete [] B;
    delete [] C;
    delete [] D;
    delete [] E;

    return 0 ;
}