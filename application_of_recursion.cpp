#include <iostream>
#include <iomanip>
using namespace std;
bool MoveOn(int** &ptr, int &x, int &y, int &n, int &direct){
    switch (direct){
        case 1:
            if (x - 2 >=0 && y + 1 < n && ptr[x - 2][y + 1] == 0) {x = x - 2; y = y + 1; direct = 1;return true;}
        case 2:
            if (x - 1 >=0 && y + 2 < n && ptr[x - 1][y + 2] == 0) {x = x - 1; y = y + 2; direct = 2;return true;}
        case 3:
            if (x + 1 < n && y + 2 < n && ptr[x + 1][y + 2] == 0) {x = x + 1; y = y + 2; direct = 3;return true;}
        case 4:
            if (x + 2 < n && y + 1 < n && ptr[x + 2][y + 1] == 0) {x = x + 2; y = y + 1; direct = 4;return true;}
        case 5:
            if (x + 2 < n && y - 1 >= 0 && ptr[x + 2][y - 1] == 0) {x = x + 2; y = y - 1; direct = 5;return true;}
        case 6:
            if (x + 1 < n && y - 2 >= 0 && ptr[x + 1][y - 2] == 0) {x = x + 1; y = y - 2; direct = 6;return true;}
        case 7:
            if (x - 1 >=0 && y - 2 >=0 && ptr[x - 1][y - 2] == 0) {x = x - 1; y = y - 2; direct = 7;return true;}
        case 8:
            if (x - 2 >=0 && y - 1 >=0 && ptr[x - 2][y - 1] == 0) {x = x - 2; y = y - 1; direct = 8;return true;}
        default:
            return false;
    }
}

int Find_Come_Direct(int i, int j,int x, int y){
    if (i == x - 2 && j == y + 1) return  1;
    if (i == x - 1 && j == y + 2) return  2;
    if (i == x + 1 && j == y + 2) return  3;
    if (i == x + 2 && j == y + 1) return  4;
    if (i == x + 2 && j == y - 1) return  5;
    if (i == x + 1 && j == y - 2) return  6;
    if (i == x - 1 && j == y - 2) return  7;
    if (i == x - 2 && j == y - 1) return  8;
    else return 9;
}
void MoveBack(int &step_count, int &n, int** &board, int &x, int &y,int &direct){
    step_count -= 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == step_count) {x = i; y = j;}
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == step_count + 1) {board[i][j] = 0; direct = (Find_Come_Direct(i,j,x,y) + 1);}
        }
    }

    //cout << "x: " << x << " y: " << y << " direct: " << direct << endl;

}

inline bool Step(int &step_count, int &n, int** &board, int &x, int &y , int &direct){
    if(step_count == n*n) {board[x][y] = n*n; return false;}
    else{
        if(MoveOn(board, x, y, n, direct))  {
            step_count += 1;
            board[x][y] = step_count;
            direct = 1 ;
            //cout << "StepCount:" << step_count << endl;
            Step(step_count,n,board,x,y,direct);
            return true;
        }
        else
        {
            if (step_count != 1) {MoveBack(step_count, n, board, x, y, direct); return true;}
            else return false;
            //cout << "StepCount:" << step_count << endl;
        }

    }
}
void FullKnight(int n) {
    int **board;
    int x = 0, y = 0;
    int direct = 1;
    int step_count = 1;
    board = new int *[n];
    for (int i = 0; i < n; i++) board[i] = new int[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) board[i][j] = 0;
    }

    board[x][y] = 1;
    cout << "n = " << n << endl;
    while(step_count < n*n){
        //cout << "StepCount:" << step_count << endl;
        if (Step(step_count,n,board,x,y ,direct)) continue;
        else break;
    }
    if(step_count == n*n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j != n - 1) cout << setfill('0') << setw(2) << board[i][j] << " ";
            else cout << setfill('0') << setw(2) << board[i][j] << endl;
        }
    }
    }
    else cout << "no solution" << endl;

    for(int i = 0;i < n;i++) delete [] board[i];
    delete [] board;
}

int main(){
    FullKnight(1);
    FullKnight(2);
    FullKnight(3);
    FullKnight(4);
    FullKnight(5);
    FullKnight(6);
    FullKnight(7);
    FullKnight(8);

    return 0;
}
