#include <iostream>
#include <math.h>
using namespace std;

template <class T> class Chain;

class Polynomial;

class Term;

template <class T> class ChainNode{
    friend class Chain <T>;
public:
    ChainNode(T element, ChainNode* next = 0)
    :data(element)
    {
        link = next;
    }
    T data;
    ChainNode<T>* link;
};

template <class T> class Chain{
    friend class Polynomial;
public:
    Chain(){
        first = 0;
        last = 0;
    }
    void InsertBack(const T& e);
    void InsertFront(const T& e);
    void InsertBetween(ChainNode<T>* x, const T& e);

private:
    ChainNode <T>* first;
    ChainNode <T>* last;
};

template<class T> void Chain<T>::InsertBack(const T &e) {
    if (first) {
        last -> link = new ChainNode<T>(e);
        last = last -> link;
    }
    else first = last = new ChainNode<T>(e);
}

template<class T> void Chain<T>::InsertFront(const T &e) {
    if (first) {
        first = new ChainNode<T>(e, first);
    }
    else first = last = new ChainNode<T>(e);
}

template<class T> void Chain<T>::InsertBetween(ChainNode<T>* x, const T &e) {
    if (first) {
        x -> link = new ChainNode<T>(e, x-> link);
    }
    else first = last = new ChainNode<T>(e);
}

class Term{
public:
    int coef;
    int exp;
    Term(int c, int e){
        coef = c;
        exp = e;
    }
};

class Polynomial{
public:
    Polynomial(){
        //cout << "Add a Polynomial" << endl;
    }
    void AddTerm(int c, int e){
        Term tempTerm(c, e);
        ChainNode <Term>* tempPtr = poly.first;
        if (tempPtr != NULL) {
            while (true) {
                if (tempPtr->data.exp == e) {
                    tempPtr->data.coef += c;
                    break;
                }
                if(e > poly.first -> data.exp) {
                    poly.InsertFront(tempTerm);
                    break;
                }
                if (tempPtr->link != NULL){
                    if (tempPtr->data.exp > e && tempPtr->link->data.exp < e) {
                        poly.InsertBetween(tempPtr, tempTerm);
                        break;
                    }
                }
                if (tempPtr == poly.last) {
                    poly.InsertBack(tempTerm);
                    break;
                }
                tempPtr = tempPtr->link;
            }
        }
        else poly.InsertBack(tempTerm);


    }
    void PrintPoly(){
        if (poly.first) {
            ChainNode<Term> *tempPtr = poly.first;
            while (true) {
                if (tempPtr->data.coef != 0)
                    cout << (tempPtr->data.coef) << " " << (tempPtr->data.exp) << endl;
                if (tempPtr->data.coef == 0 && tempPtr->data.exp == 0)
                    cout << (tempPtr->data.coef) << " " << (tempPtr->data.exp) << endl;
                if (tempPtr == poly.last) break;
                tempPtr = tempPtr->link;
            }
        }
        else cout << "End!!" << endl;
    }

    Polynomial operator + (Polynomial P) {
        Polynomial tempPoly;
        Term tempTerm(0, -1);
        ChainNode<Term> tempNode(tempTerm);
        ChainNode<Term> *tempLeftPtr = this->poly.first;
        ChainNode<Term> *tempRightPtr = P.poly.first;
        if (!(this->poly.first) && (P.poly.first))
            return P;
        else if ((this->poly.first) && !(P.poly.first))
            return *this;
        else if (!(this->poly.first) && !(P.poly.first))
            return tempPoly;
        else {
            while (true) {
                if (tempLeftPtr->data.exp == tempRightPtr->data.exp) {
                    tempPoly.AddTerm(tempLeftPtr->data.coef + tempRightPtr->data.coef, tempRightPtr->data.exp);
                    if (tempLeftPtr != this->poly.last) tempLeftPtr = tempLeftPtr->link;
                    else tempLeftPtr = &tempNode;
                    if (tempRightPtr != P.poly.last) tempRightPtr = tempRightPtr->link;
                    else tempRightPtr = &tempNode;
                } else if (tempLeftPtr->data.exp > tempRightPtr->data.exp) {
                    tempPoly.AddTerm(tempLeftPtr->data.coef, tempLeftPtr->data.exp);
                    if (tempLeftPtr != this->poly.last) tempLeftPtr = tempLeftPtr->link;
                    else tempLeftPtr = &tempNode;
                } else {
                    tempPoly.AddTerm(tempRightPtr->data.coef, tempRightPtr->data.exp);
                    if (tempLeftPtr != P.poly.last) tempRightPtr = tempRightPtr->link;
                    else tempRightPtr = &tempNode;
                }
                if (tempLeftPtr == tempRightPtr) break;
            }
            return tempPoly;
        }
    }

    Polynomial operator * (Polynomial P){
        Polynomial tempPoly;
        ChainNode<Term> *tempLeftPtr = this->poly.first;
        ChainNode<Term> *tempRightPtr = P.poly.first;
        int c, e;
        if (!(this->poly.first) || !(P.poly.first)) {
            tempPoly.AddTerm(0, 0);
            return tempPoly;
        }
        while(true) {
            tempRightPtr = P.poly.first;
            while (true) {
                c = (tempLeftPtr->data.coef * tempRightPtr->data.coef);
                e = (tempLeftPtr->data.exp + tempRightPtr->data.exp);
                tempPoly.AddTerm(c, e);
                if (tempRightPtr == P.poly.last) break;
                tempRightPtr = tempRightPtr->link;
            }
            if (tempLeftPtr == this -> poly.last) break;
            tempLeftPtr = tempLeftPtr->link;
        }
        return tempPoly;
    }

private:
    Chain<Term> poly;
};
int main(){
    int n;
    int c;
    int e;
    int counter = 0;
    int timer = 1;
    while (true) {
        counter = 0;
        Polynomial A;
        Polynomial B;
        cin >> n;
        if (n == 0) counter += 1;
        for (int i = 0; i < n; i++) {
            cin >> c >> e;
            A.AddTerm(c, e);
        }
        cin >> n;
        if (n == 0) counter += 1;
        for (int i = 0; i < n; i++) {
            cin >> c >> e;
            B.AddTerm(c, e);
        }
        if (counter == 2) break;
        cout << "Case:" << timer << endl;
        cout << "ADD" << endl;
        (A + B).PrintPoly();
        cout << "MULTIPLY" << endl;
        (A * B).PrintPoly();
        timer += 1;
    }
    return 0;
}
