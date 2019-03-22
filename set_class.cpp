#include <iostream>
using namespace std;
class Tset{
public:
    Tset(const char* str = "");
    Tset operator +(Tset); //連集
    Tset operator *(Tset); //交集
    Tset operator -(Tset); //差集
    bool operator >=(Tset); //包含
    void print(string);
private:
    char var[256];
};

Tset::Tset(const char* str) {
    for (int i = 0 ; i < 256 ; i++) var[i] = '0';
    int index = 0;
    while (str[index] != '\0'){
        var[int(str[index])] = '1';
        index += 1;
    }
}

Tset Tset::operator +(Tset Set) {
    Tset temp;
    for(int i = 0; i < 256 ; i++) {
        if(var[i] == '1' || Set.var[i] == '1') temp.var[i] = '1';
        else temp.var[i] = '0';
    }
    return temp;
}

Tset Tset::operator *(Tset Set) {
    Tset temp;
    for(int i = 0; i < 256 ; i++) {
        if(var[i] == Set.var[i] && var[i] == '1') temp.var[i] = '1';
        else temp.var[i] = '0';
    }
    return temp;
}

Tset Tset::operator -(Tset Set) {
    Tset temp1;
    Tset temp2;
    for(int i = 0; i < 256 ; i++) {
        if(Set.var[i] == '1') temp1.var[i] = '0';
        else temp1.var[i] = '1';
    }
    temp2 = (*this) * temp1;
    return temp2;
}

bool Tset::operator >=(Tset Set) {
    Tset temp;
    temp = (*this) * Set;
    int count = 0;
    for(int i = 0 ; i<256 ; i++){
        if(temp.var[i] == Set.var[i]) count += 1;
    }
    if (count == 256) return true;
    else return false;
}

void Tset::print(string X) {
    cout << X;
    cout << ": {";
    for (int i = 0 ; i < 256 ; i++) if (var[i] == '1') cout << char(i);
    cout << "}" << endl;
}

//屬於
void in (char &x, Tset Set, string Set_Name){
    char* s;
    s = new char[2];
    s[0] = x;
    s[1] = '\0';
    Tset temp(s);
    if (Set >= temp) cout << '\'' << x << '\'' << " is in " << Set_Name << endl;
    else cout << '\'' << x << '\'' << " is not in " << Set_Name << endl;
    delete [] s;
}

int main(){
    int run_time = 0;
    cin >> run_time;
    for(int i = 0 ; i < run_time ; i++){
        char * strA; char * strB; char x;
        strA = new char[256];
        strB = new char[256];
        cin >> strA;
        cin >> strB;
        cin >> x;
        cout << "Test Case " << i + 1 << endl;
        Tset A(strA);
        Tset B(strB);
        Tset C; Tset D;
        C = A + B;
        D = A * B;
        A.print("A");
        B.print("B");
        C.print("A+B");
        D.print("A*B");
        (A - B).print("A-B");
        (B - A).print("B-A");
        if(A >= B) cout << "A contains B" << endl;
        else cout << "A dose not contains B" << endl;
        if(B >= A) cout << "B contains A" << endl;
        else cout << "B dose not contains A" << endl;
        in(x, A, "A");
        in(x, B, "B");
        delete [] strA;
        delete [] strB;
    }

}