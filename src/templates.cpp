#include <iostream>

template<typename T>
class Array
{
  private:
    T* ptr;
    int size;

  public:
    Array(T arr[], int s);
    void print();
};

template<typename T>
Array<T>::Array(T arr[], int s)
{
    ptr = new T[s];
    size = s;
    for (int i = 0; i < size; i++)
        ptr[i] = arr[i];
}

template<typename T>
void Array<T>::print()
{
    for (int i = 0; i < size; i++)
        std::cout << " " << *(ptr + i);
    std::cout << '\n';
}

template<class T, class U>
struct A
{
    T x;
    U y;

  public:
    A()
    {
        std::cout << "Constructor called" << '\n';
    }
};

int main()
{
    float arr[5] = {1, 2, 3, 4, 5};
    Array<float> a(arr, 5);
    a.print();

    A<char, char> c;
    A<int, double> b;
    return 0;
}

template<typename A, typename B>
void set()
{
}