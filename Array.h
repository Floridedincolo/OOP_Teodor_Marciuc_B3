#pragma once
#include<iostream>
#include<exception>
using namespace std;
class exceptie1 : public exception
{
    virtual const char* what() const throw()
    {
        return "Index out of bounds";
    }
};
class exceptie2 : public exception
{
    virtual const char* what() const throw() {
        return "Not enough memory allocated";
    }
};
class Compare
{
public:
    virtual int CompareElements(void* e1, void* e2) = 0;
};
template<class T>
class ArrayIterator
{
private:
    int Current;
public:
    ArrayIterator();
    ArrayIterator& operator ++ ();
    ArrayIterator& operator -- ();
    bool operator== (ArrayIterator<T>&);
    bool operator!=(ArrayIterator<T>&);
    T* GetElement();
};
template<class T>
class Array
{
private:
    T* List; // lista cu pointeri la obiecte de tipul T*
    int Capacity; // dimensiunea listei de pointeri
    int Size; // cate elemente sunt in lista
public:
    Array(); // Lista nu e alocata, Capacity si Size = 0
    ~Array(); // destructor
    Array(int capacity); // Lista e alocata cu 'capacity' elemente
    Array(const Array<T>& otherArray); // constructor de copiere

    T& operator[] (int index); // arunca exceptie daca index este out of range

    const Array<T>& operator+=(const T& newElem); // adauga un element de tipul T la sfarsitul listei si returneaza this
    const Array<T>& Insert(int index, const T& newElem); // adauga un element pe pozitia index, retureaza this. Daca index e invalid arunca o exceptie
    const Array<T>& Insert(int index, const Array<T> otherArray); // adauga o lista pe pozitia index, retureaza this. Daca index e invalid arunca o exceptie
    const Array<T>& Delete(int index); // sterge un element de pe pozitia index, returneaza this. Daca index e invalid arunca o exceptie

    bool operator==(const Array<T>& otherArray);

    void Sort(); // sorteaza folosind comparatia intre elementele din T
    void Sort(int(*compare)(const T&, const T&)); // sorteaza folosind o functie de comparatie
    void Sort(Compare* comparator); // sorteaza folosind un obiect de comparatie

    // functii de cautare - returneaza pozitia elementului sau -1 daca nu exista
    int BinarySearch(const T& elem); // cauta un element folosind binary search in Array
    int BinarySearch(const T& elem, int(*compare)(const T&, const T&));//  cauta un element folosind binary search si o functie de comparatie
    int BinarySearch(const T& elem, Compare* comparator);//  cauta un element folosind binary search si un comparator

    int Find(const T& elem); // cauta un element in Array
    int Find(const T& elem, int(*compare)(const T&, const T&));//  cauta un element folosind o functie de comparatie
    int Find(const T& elem, Compare* comparator);//  cauta un element folosind un comparator

    int GetSize();
    int GetCapacity();

    ArrayIterator<T> GetBeginIterator();
    ArrayIterator<T> GetEndIterator();
};

template<class T>
inline ArrayIterator<T>::ArrayIterator()
{
    this->Current = 0;
}

template<class T>
inline ArrayIterator<T>& ArrayIterator<T>::operator++()
{
    this->Current++;
    return (*this);
}

template<class T>
inline ArrayIterator<T>& ArrayIterator<T>::operator--()
{
    this->Current--;
    return (*this);
}

template<class T>
inline bool ArrayIterator<T>::operator==(ArrayIterator<T>& other)
{
    return this->Current==other.Current;
}

template<class T>
inline bool ArrayIterator<T>::operator!=(ArrayIterator<T>& other)
{
    return !(*this == other);
}

template<class T>
inline T* ArrayIterator<T>::GetElement()
{
    return this->Current;
}

template<class T>
inline Array<T>::Array()
{
    List = nullptr;
    Capacity = 0;
    Size = 0;
}

template<class T>
inline Array<T>::~Array()
{
    delete List;
}

template<class T>
inline Array<T>::Array(int capacity)
{
    List = new T[capacity];
    this->Capacity = capacity;
    this->Size = 0;
}

template<class T>
inline Array<T>::Array(const Array<T>& otherArray)
{
    this->Size = otherArray->Size;
    this->Capacity = otherArray->Capacity;
    this->List = otherArray->List;
}

template<class T>
inline T& Array<T>::operator[](int index)
{
    if (index < 0 or index >= this->Size)
       throw exceptie1();
    else {
        return this->List[index];
    }
}

template<class T>
inline const Array<T>& Array<T>::operator+=(const T& newElem)
{
    if (this->Size < this->Capacity)
    {
        this->List[this->Size] = newElem;
        this->Size++;
    }
    else throw exceptie2();
    //this->Size++;
}

template<class T>
inline const Array<T>& Array<T>::Insert(int index, const T& newElem)
{
    if (index < 0 or index >= this->Size)
       throw exceptie1();
    if (this->Size >= this->Capacity)
        throw exceptie2();
    for (int i = this->Size; i > index; i--)
    {
        this->List[i] = this->List[i - 1];
    }
    this->List[index] = newElem;
    this->Size++;
}

template<class T>
inline const Array<T>& Array<T>::Insert(int index, const Array<T> otherArray)
{
    if (index < 0 or index >=this->Size)
       throw exceptie1();
    if (index + otherArray->Size >= this->Capacity())
        throw exceptie2();
    for (int i = this->Size-1+otherArray.Size(); i > index; i--)
    {
        this->List[i] = this->List[i -otherArray.Size()];
    }
    for (int i = index; i < index + otherArray.Size(); i++)
        List[i] = otherArray->List[i - index];
    this->Size+=otherArray.Size();
}
template<class T>
inline const Array<T>& Array<T>::Delete(int index)
{
    if (index < 0 or index >= this->Size)
       throw exceptie1();
    for (int i = index; i < this->Size; i++)
    {
        this->List[i] = this->List[i + 1];
    }
    this->Size--;
}
template<class T>
inline bool Array<T>::operator==(const Array<T>& otherArray)
{
    this->Size = otherArray->Size;
    this->Capacity = otherArray->Capacity;
    this->List = new T[this->Size];
    for (int i = 0; i < this->Size; i++)
        this->List[i] = otherArray[i];
}
template<class T>
inline void Array<T>::Sort()
{
    for (int i = 0; i < this->Size; i++)
        for (int j = i + 1; j < this->Size; j++)
            if (this->List[i] > this->List[j])
                std::swap(this->List[i], this->List[j]);
}

template<class T>
inline void Array<T>::Sort(int(*compare)(const T&, const T&))
{
    for (int i = 0; i < this->Size; i++)
        for (int j = i + 1; j < this->Size; j++)
            if (compare(this->List[i] , this->List[j]))
                swap(this->List[i], this->List[j]);
}
template<class T>
inline void Array<T>::Sort(Compare* comparator)
{
    for (int i = 0; i < this->Size; i++)
        for (int j = i + 1; j < this->Size; j++)
            if (comparator->CompareElements(this->List[i], this->List[j]))
                swap(this->List[i], this->List[j]);
}

template<class T>
inline int Array<T>::BinarySearch(const T& elem)
{
    int st = 0, dr = this->Size;
    while (st < dr) {
        int mid = (st + dr) / 2;
        if (elem > this->List[mid])
            st = mid + 1;
        else if (elem < this->List[mid])
            dr = mid - 1;
        else return mid;
    }
    if(this->List[st]==elem) return st;
    return -1;
}

template<class T>
inline int Array<T>::BinarySearch(const T& elem, int(*compare)(const T&, const T&))
{
    int st = 0, dr = this->Size;
    while (st < dr) {
        int mid = (st + dr) / 2;
        if (compare(this->List[mid],elem)==1)
            st = mid + 1;
        else if (compare(elem, this->List[mid])==1)
            dr = mid - 1;
        else return mid;
    }
    if (this->List[st] == elem) return st;
    return -1;
}
template<class T>
inline int Array<T>::BinarySearch(const T& elem, Compare* comparator)
{
    int st = 0, dr = this->Size;
    while (st < dr) {
        int mid = (st + dr) / 2;
        if (comparator->CompareElements(this->List[mid], elem)==1)
            st = mid + 1;
        else if (comparator->CompareElements(elem < this->List[mid])==1)
            dr = mid - 1;
        else return mid;
    }
    if (this->List[st] == elem) return st;
    return -1;
}

template<class T>
inline int Array<T>::Find(const T& elem)
{
    for (int i = 0; i < this->Size; i++)
        if (this->List[i] == elem)
            return i;
    return -1;
}

template<class T>
inline int Array<T>::Find(const T& elem, int(*compare)(const T&, const T&))
{
    for (int i = 0; i < this->Size; i++)
        if (compare(this->List[i], elem)==0)
            return i;
    return -1;
}

template<class T>
inline int Array<T>::Find(const T& elem, Compare* comparator)
{
    for (int i = 0; i < this->Size; i++)
        if (comparator->CompareElements(this->List[i],elem)==0)
            return i;
    return -1;
}

template<class T>
inline int Array<T>::GetSize()
{
    return this->Size;
}

template<class T>
inline int Array<T>::GetCapacity()
{
    return this->Capacity;
}
template<class T>
inline ArrayIterator<T> Array<T>::GetBeginIterator()
{
    return ArrayIterator<T>(List);
}
template<class T>
inline ArrayIterator<T> Array<T>::GetEndIterator()
{
    return ArrayIterator<T>(List + Size);
}
