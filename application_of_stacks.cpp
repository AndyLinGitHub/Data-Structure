#include <iostream>
#include <iomanip>
using namespace std;
//Goal：Test if a knight can visit each positon of a chess board
class step{
    friend void FullKnight(int);
private:
    int Xpos;
    int Ypos;
    int MovDirect;
public:
    step(int x, int y, int d){
        Xpos = x;
        Ypos = y;
        MovDirect = d;
    }
    step(){
        Xpos = 0;
        Ypos = 0;
        MovDirect = 0;
    }
};

template <class T>
class Stack{
    friend void FullKnight(int);
private:
    T* stack;
    int top;
    int capacity;
public:
    Stack(int stackCapacity = 100);
    bool IsEmpty() const;
    T& Top() const;
    void Push(const T& item);
    void Pop();
};

template <class T>
Stack<T>:: Stack (int stackCapacity){
    capacity = stackCapacity;
    stack = new T[capacity];
    top = -1;
}

template <class T>
inline bool Stack<T>::IsEmpty() const {
    return top == -1;
}

template  <class T>
inline T& Stack<T>::Top() const {
    if(IsEmpty()) throw "Stack is Empty";
    return stack[top];
}

template <class T>
void Stack<T>::Push(const T& x) {
    if (top == capacity - 1) throw "Stack Overflows";
    stack[++top] = x;
}

template <class T>
void Stack<T>::Pop() {
    if(IsEmpty()) throw "Stack is Empty. Cannot delete.";
    stack[top--].~T();

}

int CheckDirect(int** &ptr, int &x, int &y, int &n, int &direct){
    switch (direct){
        case 1:
            if (x - 2 >=0 && y + 1 < n && ptr[x - 2][y + 1] == 0) return true;
            else return false;
        case 2:
            if (x - 1 >=0 && y + 2 < n && ptr[x - 1][y + 2] == 0) return true;
            else return false;
        case 3:
            if (x + 1 < n && y + 2 < n && ptr[x + 1][y + 2] == 0) return true;
            else return false;
        case 4:
            if (x + 2 < n && y + 1 < n && ptr[x + 2][y + 1] == 0) return true;
            else return false;
        case 5:
            if (x + 2 < n && y - 1 >= 0 && ptr[x + 2][y - 1] == 0) return true;
            else return false;
        case 6:
            if (x + 1 < n && y - 2 >= 0 && ptr[x + 1][y - 2] == 0) return true;
            else return false;
        case 7:
            if (x - 1 >=0 && y - 2 >=0 && ptr[x - 1][y - 2] == 0) return true;
            else return false;
        case 8:
            if (x - 2 >=0 && y - 1 >=0 && ptr[x - 2][y - 1] == 0) return true;
            else return false;
        default:
            return false;
    }
}

void PosMove(int &x, int &y, int &n){
    switch (n){
        case 1:
            x = x - 2; y = y + 1; break;
        case 2:
            x = x - 1; y = y + 2; break;
        case 3:
            x = x + 1; y = y + 2; break;
        case 4:
            x = x + 2; y = y + 1; break;
        case 5:
            x = x + 2; y = y - 1; break;
        case 6:
            x = x + 1; y = y - 2; break;
        case 7:
            x = x - 1; y = y - 2; break;
        case 8:
            x = x - 2; y = y - 1; break;
        default:
            break;
    }
}

void FullKnight(int n) {
    cout << "n = " << n << endl;
    Stack<step> s;
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
    while (step_count < n*n) {
        if (CheckDirect(board, x, y, n, direct)) {
            s.Push(step(x, y, direct));
            PosMove(x, y, direct);
            direct = 1;
            step_count++;
            board[x][y] = step_count;
            //cout << "step count = " << step_count << endl;
            //cout << "x : " << x << " y : " << y << endl;
        }
        else direct += 1;
        if(step_count == 1 && direct == 9) break;
        //cout << "Direct" << direct << endl;
        if (direct >= 9){
            board[x][y] = 0;
            x = s.Top().Xpos;
            y = s.Top().Ypos;
            direct = s.Top().MovDirect + 1;
            s.Pop();
            step_count -= 1;
            //cout << "step count = " << step_count << endl;
            //cout << "x : " << x << " y : " << y << endl;
        }
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
