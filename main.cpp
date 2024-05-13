#include <iostream>
#include "Array.h"
int main() {
    try {
        Array<int> arr(10); 

        arr += 1;
        arr += 3;
        arr += 2;
        arr += 5;
        arr += 4;

        for (int i = 0; i < arr.GetSize(); ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << '\n';

        arr.Sort();
        for (int i = 0; i < arr.GetSize(); ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << '\n';

        int index = arr.BinarySearch(3);
        std::cout << "L-am gasit e aici uite-l: " << index << '\n';

        arr.Insert(2, 10);  
        for (int i = 0; i < arr.GetSize(); ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << '\n';

        arr.Delete(2);  
        for (int i = 0; i < arr.GetSize(); ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << '\n';
        arr.Insert(20, 5);
    }
    catch (const std::exception& e) {
        std::cout << "A aparut o eroare: " << e.what() << '\n';
    }

    return 0;
}
