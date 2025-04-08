
#ifndef LISTA_WIAZANA_JEDNOKIERUNKOWA_H
#define LISTA_WIAZANA_JEDNOKIERUNKOWA_H

// Struktura węzła listy
struct Node {
    int data;       // Przechowywana liczba
    Node* next;     // Wskaźnik na kolejny węzeł

    // Konstruktor przypisujący wartość i ustawiający wskaźnik na nullptr
    Node(int value) : data(value), next(nullptr) {}
};

// Klasa listy jednokierunkowej
class LinkedList {
private:
    Node* head;     // Wskaźnik na pierwszy element listy
    Node* tail;     // Wskaźnik na ostatni element listy
    int size;       // Ilość elementów w liście
    int capacity;   // Aktualna maksymalna pojemność (to srednio potrzebne ale zrobilem przez przypadek tak jak dla listy)

    // Funkcja pomocnicza powiększająca pojemność listy
    void resize() {
        capacity *= 2;
    }

public:
    // Konstruktor - ustawia wskaźniki na nullptr i ustawia początkową pojemność
    LinkedList(int initialCapacity = 4) : head(nullptr), tail(nullptr), size(0), capacity(initialCapacity) {}

    // Destruktor - usuwa wszystkie elementy z listy
    ~LinkedList() {
        while (head) {
            removeFromBeginning(); // Czyści po jednym węźle
        }
    }

    // Dodanie elementu na początek listy
    void addToBeginning(int value) {
        if (size == capacity) resize(); // Powiększamy listę jeśli pełna
        Node* newNode = new Node(value); // Nowy węzeł z wartością
        newNode->next = head; // Nowy węzeł wskazuje na stary head
        head = newNode;       // Nowy head to ten nowy węzeł
        if (!tail) tail = newNode; // Jeśli lista była pusta, tail = head
        ++size;
    }

    // Dodanie elementu na koniec listy
    void addToEnd(int value) {
        if (size == capacity) resize();
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode; // Jeśli lista pusta
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }

    // Dodanie elementu na konkretny indeks
    void addAtIndex(int index, int value) {
        if (index <= 0) {
            addToBeginning(value); // Jeśli indeks <= 0, dodaj na początek
            return;
        }
        if (size == capacity) resize();
        Node* current = head;
        for (int i = 0; current && i < index - 1; ++i)
            current = current->next; // Szukamy miejsca do wstawienia

        if (!current) {
            addToEnd(value); // Jeśli poza zakresem, dodaj na koniec
            return;
        }

        Node* newNode = new Node(value);
        newNode->next = current->next;
        current->next = newNode;
        if (!newNode->next) tail = newNode;
        ++size;
    }

    // Usunięcie elementu z początku listy
    void removeFromBeginning() {
        if (!head) return; // Jeśli lista pusta
        Node* temp = head;
        head = head->next;
        delete temp; // Usuwamy stary head
        --size;
        if (!head) tail = nullptr; // Jeśli lista stała się pusta
    }

    // Usunięcie elementu z końca listy
    void removeFromEnd() {
        if (!head) return;
        if (head == tail) { // Tylko jeden element
            delete head;
            head = tail = nullptr;
            size = 0;
            return;
        }
        Node* current = head;
        while (current->next != tail)
            current = current->next; // Szukamy przedostatniego

        delete tail;
        tail = current;
        tail->next = nullptr;
        --size;
    }

    // Usunięcie elementu z konkretnego indeksu
    void removeAtIndex(int index) {
        if (index < 0 || !head) return;
        if (index == 0) {
            removeFromBeginning();
            return;
        }

        Node* current = head;
        for (int i = 0; current->next && i < index - 1; ++i)
            current = current->next;

        Node* target = current->next;
        if (!target) return;
        current->next = target->next;
        if (target == tail) tail = current;
        delete target;
        --size;
    }

    // Szukanie wartości w liście
    bool search(int value) {
        Node* current = head;
        while (current) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }
};
#endif //LISTA_WIAZANA_JEDNOKIERUNKOWA_H
