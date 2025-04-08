#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <string>
#include <sstream>

// Dołączamy nasze własne struktury
#include "lista_wiazana_jednokierunkowa.h"
#include "tablica_dynamiczna.h"

int main() {
    //Wczytywanie danych z pliku tekstowego
    std::ifstream file("C://clion//dane_projekt_1//cmake-build-debug//dane.txt"); // ścieżka do pliku z danymi
    std::vector<int> all_data; //wektor dane z pliku
    int number;

    // Odczytujemy liczby z pliku i wrzucamy do all_data
    while (file >> number) {
        all_data.push_back(number);
    }

    //plik CSV na wyniki benchmarków
    std::ofstream out("benchmark_results.csv"); //plik do zapisu
    out << "Rozmiar,Struktura,Operacja,Proba,Czas_us\n"; // nagłówki

    // Lista rozmiarów danych do testów
    std::vector<int> sizes = {5000,10000,20000,30000,40000,50000,60000,70000,80000,90000,100000};

    // Generator liczb losowych do losowych indeksów i wartości
    std::random_device rd; //entropia
    std::mt19937 gen(rd()); // silnik generatora liczb losowych

    // Pętla po rozmiarach danych
    for (int size : sizes) {
        // Przygotowanie datasetu
        std::vector<int> dataset(all_data.begin(), all_data.begin() + size);

        // Generujemy 1000 losowych indeksów i wartości
        std::uniform_int_distribution<> index_dist(0, size - 1); // zakres indeksów
        std::uniform_int_distribution<> value_dist(0, 10000);    // zakres losowych wartości

        std::vector<int> losowe_indeksy(1000), losowe_wartosci(1000);

        for (int i = 0; i < 1000; ++i) {
            losowe_indeksy[i] = index_dist(gen);
            losowe_wartosci[i] = value_dist(gen);
        }

        // 5 prób każdej operacji
        for (int proba = 1; proba <= 5; ++proba) {

            //Operacja 1: addToBeginning
            LinkedList llist1(size);
            DynamicArray darr1;
            for (int val : dataset) { llist1.addToEnd(val); darr1.addToEnd(val); }

            auto t1 = std::chrono::high_resolution_clock::now();
            llist1.addToBeginning(123);
            auto t2 = std::chrono::high_resolution_clock::now();
            out << size << ",LinkedList,addToBeginning," << proba << "," << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << "\n";

            t1 = std::chrono::high_resolution_clock::now();
            darr1.addToBeginning(123);
            t2 = std::chrono::high_resolution_clock::now();
            out << size << ",DynamicArray,addToBeginning," << proba << "," << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << "\n";

            //Operacja 2: addToEnd
            LinkedList llist2(size);
            DynamicArray darr2;
            for (int val : dataset) { llist2.addToEnd(val); darr2.addToEnd(val); }

            t1 = std::chrono::high_resolution_clock::now();
            llist2.addToEnd(123);
            t2 = std::chrono::high_resolution_clock::now();
            out << size << ",LinkedList,addToEnd," << proba << "," << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << "\n";

            t1 = std::chrono::high_resolution_clock::now();
            darr2.addToEnd(123);
            t2 = std::chrono::high_resolution_clock::now();
            out << size << ",DynamicArray,addToEnd," << proba << "," << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << "\n";

            //Operacja 3: addAtIndex (1000 razy)
            LinkedList llist3(size);
            DynamicArray darr3;
            for (int val : dataset) { llist3.addToEnd(val); darr3.addToEnd(val); }

            t1 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 1000; ++i)
                llist3.addAtIndex(losowe_indeksy[i] % size, losowe_wartosci[i]);
            t2 = std::chrono::high_resolution_clock::now();
            out << size << ",LinkedList,addAtIndex," << proba << "," << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << "\n";

            t1 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 1000; ++i)
                darr3.addAtIndex(losowe_indeksy[i] % size, losowe_wartosci[i]);
            t2 = std::chrono::high_resolution_clock::now();
            out << size << ",DynamicArray,addAtIndex," << proba << "," << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << "\n";

            //Operacja 4: removeFromBeginning
            LinkedList llist4(size);
            DynamicArray darr4;
            for (int val : dataset) { llist4.addToEnd(val); darr4.addToEnd(val); }

            t1 = std::chrono::high_resolution_clock::now();
            llist4.removeFromBeginning();
            t2 = std::chrono::high_resolution_clock::now();
            out << size << ",LinkedList,removeFromBeginning," << proba << "," << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << "\n";

            t1 = std::chrono::high_resolution_clock::now();
            darr4.removeFromBeginning();
            t2 = std::chrono::high_resolution_clock::now();
            out << size << ",DynamicArray,removeFromBeginning," << proba << "," << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << "\n";

            //Operacja 5: removeFromEnd
            LinkedList llist5(size);
            DynamicArray darr5;
            for (int val : dataset) { llist5.addToEnd(val); darr5.addToEnd(val); }

            t1 = std::chrono::high_resolution_clock::now();
            llist5.removeFromEnd();
            t2 = std::chrono::high_resolution_clock::now();
            out << size << ",LinkedList,removeFromEnd," << proba << "," << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << "\n";

            t1 = std::chrono::high_resolution_clock::now();
            darr5.removeFromEnd();
            t2 = std::chrono::high_resolution_clock::now();
            out << size << ",DynamicArray,removeFromEnd," << proba << "," << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << "\n";

            //Operacja 6: removeAtIndex (1000 razy)
            LinkedList llist6(size + 1000);
            DynamicArray darr6;
            for (int val : dataset) { llist6.addToEnd(val); darr6.addToEnd(val); }
            for (int i = 0; i < 1000; ++i) {
                llist6.addAtIndex(losowe_indeksy[i] % size, losowe_wartosci[i]);
                darr6.addAtIndex(losowe_indeksy[i] % size, losowe_wartosci[i]);
            }

            t1 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 1000; ++i)
                llist6.removeAtIndex(losowe_indeksy[i] % size);
            t2 = std::chrono::high_resolution_clock::now();
            out << size << ",LinkedList,removeAtIndex," << proba << "," << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << "\n";

            t1 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 1000; ++i)
                darr6.removeAtIndex(losowe_indeksy[i] % size);
            t2 = std::chrono::high_resolution_clock::now();
            out << size << ",DynamicArray,removeAtIndex," << proba << "," << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << "\n";

            //Operacja 7: search (1000 razy)
            LinkedList llist7(size);
            DynamicArray darr7;
            for (int val : dataset) { llist7.addToEnd(val); darr7.addToEnd(val); }

            t1 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 1000; ++i)
                llist7.search(losowe_wartosci[i]);
            t2 = std::chrono::high_resolution_clock::now();
            out << size << ",LinkedList,search," << proba << "," << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << "\n";

            t1 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 1000; ++i)
                darr7.search(losowe_wartosci[i]);
            t2 = std::chrono::high_resolution_clock::now();
            out << size << ",DynamicArray,search," << proba << "," << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << "\n";
        }
    }

    out.close();
    return 0;
}
