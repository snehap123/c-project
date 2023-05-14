#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

struct Book {
    char title[50];
    char author[50];
    int id;
    int borrowed;
};

struct Library {
    struct Book books[MAX_BOOKS];
    int num_books;
};

void add_book(struct Library *lib, char title[], char author[], int id) {
    if (lib->num_books >= MAX_BOOKS) {
        printf("Error: library is full.\n");
        return;
    }
    struct Book new_book;
    strcpy(new_book.title, title);
    strcpy(new_book.author, author);
    new_book.id = id;
    new_book.borrowed = 0;
    lib->books[lib->num_books] = new_book;
    lib->num_books++;
    printf("Book added successfully.\n");
}

void print_books(struct Library *lib) {
    printf("ID\tTitle\tAuthor\tStatus\n");
    for (int i = 0; i < lib->num_books; i++) {
        printf("%d\t%s\t%s\t%s\n", lib->books[i].id, lib->books[i].title, lib->books[i].author,
            lib->books[i].borrowed ? "Borrowed" : "Available");
    }
}

int find_book_index(struct Library *lib, int id) {
    for (int i = 0; i < lib->num_books; i++) {
        if (lib->books[i].id == id) {
            return i;
        }
    }
    return -1;
}

void borrow_book(struct Library *lib, int id) {
    int index = find_book_index(lib, id);
    if (index == -1) {
        printf("Error: book not found.\n");
        return;
    }
    if (lib->books[index].borrowed) {
        printf("Error: book is already borrowed.\n");
        return;
    }
    lib->books[index].borrowed = 1;
    printf("Book borrowed successfully.\n");
}

void return_book(struct Library *lib, int id) {
    int index = find_book_index(lib, id);
    if (index == -1) {
        printf("Error: book not found.\n");
        return;
    }
    if (!lib->books[index].borrowed) {
        printf("Error: book is not borrowed.\n");
        return;
    }
    lib->books[index].borrowed = 0;
    printf("Book returned successfully.\n");
}

int main() {
    struct Library lib = {0};

    add_book(&lib, "The Great Gatsby", "F. Scott Fitzgerald", 1);
    add_book(&lib, "To Kill a Mockingbird", "Harper Lee", 2);
    add_book(&lib, "1984", "George Orwell", 3);

    print_books(&lib);

    borrow_book(&lib, 1);
    borrow_book(&lib, 2);
    print_books(&lib);

    return_book(&lib, 1);
    print_books(&lib);

    return 0;
}
