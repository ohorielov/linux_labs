// lab_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "table.h" 
#include "letters_list.h" 
#include "functions.h" 

//#define input "../non_compressed_text.txt"
//#define outpit "../compressed_text.txt"


using namespace std;

int main()
{
    string text = open_and_read_file();
    letters_list lista;
    for (int i = 0; i < text.size(); i++) {
        lista.add_node(text[i]);
    }
    cout << "letter list:" << endl;
    lista.print_list();
    lista.sort_list();
    cout << "sorted letter list:";
    lista.print_list();
    node* lol = lista.transform(lista.head);
    cout << "print huffman tree" << endl;
    print_tree(lol, 0);
    h_table table;
    table.fill_table(lol, "");
    cout << "print huffman table" << endl;
    table.print_table();
    create_and_write_file(text, table);
    decoded_text(table);



}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
