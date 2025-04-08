
#ifndef TABLICA_DYNAMICZNA_H
#define TABLICA_DYNAMICZNA_H
// Klasa dynamicznej tablicy
class DynamicArray {
private:
    int* data;       // Wskaźnik na dane tablicy
    int capacity;    // Aktualna maksymalna pojemność
    int size;        // Liczba aktualnych elementów

    // Zwiększa rozmiar tablicy
    void resize(int newCapacity) {
        int* newData = new int[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i]; // Przepisujemy dane
        }
        delete[] data; // Usuwamy starą tablicę
        data = newData;
        capacity = newCapacity;
    }

public:
    // Konstruktor domyślny
    DynamicArray() : data(new int[2]), capacity(2), size(0) {}

    // Destruktor
    ~DynamicArray() {
        delete[] data;
    }

    // Dodanie na koniec
    void addToEnd(int value) {
        if (size == capacity) resize(capacity * 2);
        data[size++] = value;
    }

    // Dodanie na początek
    void addToBeginning(int value) {
        if (size == capacity) resize(capacity * 2);
        for (int i = size; i > 0; --i) data[i] = data[i - 1];
        data[0] = value;
        ++size;
    }

    // Dodanie na indeks
    void addAtIndex(int index, int value) {
        if (index < 0) index = 0;
        if (index > size) index = size;
        if (size == capacity) resize(capacity * 2);
        for (int i = size; i > index; --i) data[i] = data[i - 1];
        data[index] = value;
        ++size;
    }

    // Usunięcie z początku
    void removeFromBeginning() {
        if (size == 0) return;
        for (int i = 0; i < size - 1; ++i) data[i] = data[i + 1];
        --size;
    }

    // Usunięcie z końca
    void removeFromEnd() {
        if (size == 0) return;
        --size;
    }

    // Usunięcie z indeksu
    void removeAtIndex(int index) {
        if (index < 0 || index >= size) return;
        for (int i = index; i < size - 1; ++i) data[i] = data[i + 1];
        --size;
    }

    // Szukanie elementu
    bool search(int value) {
        for (int i = 0; i < size; ++i)
            if (data[i] == value) return true;
        return false;
    }
};
#endif //TABLICA_DYNAMICZNA_H
