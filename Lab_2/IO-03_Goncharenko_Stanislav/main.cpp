#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

/// @brief Класс, через который реализовываем бинарное дерево
class Node
{
public:
    char chr;
    int count;
    Node *left, *right;

    Node(char chr, int count)
    {
        this->chr = chr;
        this->count = count;
        left = right = nullptr;
    }

    Node(Node *first, Node *second)
    {
        if (first->count >= second->count) {
            this->left = first;
            this->right = second;
        } else {
            this->left = second;
            this->right = first;
        }
        this->count = second->count + first->count;
        this->chr = NULL;
    }
};

/// @brief Генерирует хеш-таблицу (символ: код) шифрования из дерева
/// @param node Корень дерева
/// @param code Строка, использующая для генерации кодов (должна быть пустой)
/// @param mp масив (map<...>), куда надо сохранить
void makeCoderMap(Node *node, string &code, map<char, string> &mp)
{
    if (node->chr != NULL)
    {
        //cout <<  "Значение кода " << code << " значение символа " << node->chr << "   ";
        //cout << (node->left ? 1 : 0) << " " << (node->right ? 1 : 0) << " " << node->right << endl;
        mp[node->chr] = code;
        return;
    }

    code += "0";
    makeCoderMap(node->left, code, mp);
    code.resize(code.length()-1);
    code += "1";
    makeCoderMap(node->right, code, mp);
    code.resize(code.length()-1);
}


/// @brief Генерирует дерево из таблицы частот
/// @param arrFreq таблица частот
/// @return Корень дерева
Node *generateTree(unsigned int *arrFreq)
{
    // Создаём вектор из нодов символов, которые встречались хотя бы раз
    vector<Node*> nodes;
    for (int i = 0; i < 256; i++)
    {
        if (arrFreq[i] != 0)
        {
            nodes.push_back(new Node(i, arrFreq[i]));
        }
    }

    // Сотритуем по возрастанию частоты (для удобной генерации дерева)
    sort(nodes.begin(), nodes.end(), [](Node *a, Node *b){ return a->count > b->count; });

    // Создаём дерево 
    while (nodes.size() != 1)
    {
        Node *nod = new Node(nodes[nodes.size()-1], nodes[nodes.size()-2]);
        nodes.pop_back();
        nodes.pop_back();
        
        // Размещаем новый нод сразу в позицию, что бы весь вектор был отсортирован по убыванию
        int ins = nodes.size();
        for (int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i]->count < nod->count)
            {
                ins = i;
                break;
            }
        }
        nodes.insert(nodes.begin()+ins, nod);
    }

    return nodes[0];
}


/// @brief Читает файл и создаёт масив частот 
/// @param fileName Название файла
/// @param arrFreq массив, в который записываем таблицу частот
void makeArrFrequencies(string fileName, unsigned int *arrFreq)
{
    ifstream fileRead(fileName, ios::binary);

    for (int i = 0; i < 256; i++) arrFreq[i] = 0;
    char buf;
    
    while (fileRead.get(buf))
    {   
        arrFreq[(unsigned char)buf]++;
    }

    if (fileRead.eof())
        cout << "Успешное чтение файла\n";
    else if (fileRead.bad())
        cout << "Ошибка при чтении файла\n";
    else if (fileRead.fail())
        cout << "Ошибка формата файла\n";
    fileRead.close();
}


/// @brief Читает и зашифровывает текст
/// @param fileName название файла
/// @param heshTab хеш-таблица (символ: код), по которому зашифровываем текст
/// @return пара с вектор, с зашифроваными байтами, и количеством битов в коде
pair<vector<unsigned char>, int>* readAndCompresFile(string fileName, map<char, string> heshTab)
{
    ifstream fileRead(fileName);
    char buf;
    string bitData = "";
     while (fileRead.get(buf))
    {
        bitData += heshTab[buf];
    }
    fileRead.close();

    // Массив в котором временно храним закодированные чары
    vector<unsigned char> savedChars;

    int bitSize = bitData.length();
    unsigned char mask, out;

    // Кодируем большую часть байтов
    while (bitData.length() >= 8)
    {
        out = 0;
        mask = 128;
        for (int i = 0; i < 8; i++)
        {
            if (bitData[i] == '1') { out += mask; }
            mask = mask >> 1;
        }
        bitData = bitData.substr(8, bitData.length()-8);

        savedChars.push_back(out);
    }
    cout << endl;
    
    // Кодируем последний байт
    out = 0;
    mask = 128;
    for (int i = 0; i < bitData.length(); i++)
    {
        if (bitData[i] == '1') { out += mask; }
        mask = mask >> 1;
    }
    savedChars.push_back(out);

    return new pair<vector<unsigned char>, int>(savedChars, bitSize);
}

/// @brief Создаём и записываем закодированный файл
/// @param fileName название файла
/// @param arrFreq массив частот
/// @param comprChars зашифрованные символы (char-ы)
/// @param bitSize размер зашифрованного кода (количество бит в коде)
void writeCompresedFile(string fileName, unsigned int *arrFreq, vector<unsigned char> comprChars, int bitSize)
{
    ofstream fileWrite("compressed_text.txt", ios::binary);

    // Запись шапки
    for (int i = 0; i < 256; i++)
    {
        fileWrite << arrFreq[i] << " ";
    }
    fileWrite << bitSize << '\n';

    // Запись кода
    for (int i = 0; i < comprChars.size(); i++)
    {
        fileWrite << comprChars[i];
    }

    fileWrite.close();
}

string readAndDecompresFile(string fileName)
{
    ifstream file(fileName, ios::binary);
    unsigned int arrFreq[256];  // таблица частот
    int bitSize;                // размер шифра

    // Читает шапку файла
    for (int i = 0; i < 256; i++)
    {
        file >> arrFreq[(unsigned char) i];
    }
    file >> bitSize;

    // Генерируем дерево
    Node *root = generateTree(arrFreq);

    unsigned char mask;
    char in;
    unsigned char buffer;
    Node *checking = root;
    string out;

    // Читаем символ "\n", который являеться концом шапки
    file.get(in);

    // Читаем и декодируем оставшийся файл
    for (int i = 0; i < bitSize; i++)
    {
        if (i % 8 == 0) { // Читаем новый байт каждых 8 битов
            file.get(in); 
            buffer = (unsigned char) in;
            mask = 128; // Обновляем маску
        }

        if ((buffer & mask) > 0) {
            checking = checking->right;
        } else {
            checking = checking->left;
        }
        mask = mask >> 1;

        if (checking->chr != NULL)
        {
            out += checking->chr;
            checking = root;
        }
    }

    return out;
}

int main() 
{
    // Таблица частот
    unsigned int charCounter[256];

    // Вызываем функцию, которая сгенерирует таблицу частот читая файл
    makeArrFrequencies("non_compressed_text.txt", charCounter);

    // Корень дерева
    Node *root = generateTree(charCounter);

    // Хеш-таблица
    map<char, string> coder;
    string st = ""; // Для коректного запуска рекурсии
    
    // Генерируем хеш-таблицу из дерева
    makeCoderMap(root, st, coder);

    // Читаем файл, зашифровываем текст, зашифрованый текст и его размер переносим в буфер
    pair<vector<unsigned char>, int> *pairOut = readAndCompresFile("non_compressed_text.txt", coder);

    // Сохраняем из буфера нужные переменные
    
    // Вектор из зашифрованных символов
    vector<unsigned char> savedChars = pairOut->first;
    // Общая длина шифра (в битах)
    int bitSize = pairOut->second;

    // Освобождаем буфер
    free(pairOut);

    // Записываем зашифрованный текст в файл
    writeCompresedFile("compressed_text.txt", charCounter, savedChars, bitSize);

    // Читаем зашифрованный файл и декодируем его
    string decodedText = readAndDecompresFile("compressed_text.txt");
    
    // Читаем файл оригинальный файл
    ifstream file("non_compressed_text.txt", ios::binary);
    char buf;
    string origText = "";
    while(file.get(buf))
    {
        origText += buf;
    }
    file.close();

    // Сравниваем текст из оригинального файла и декодированного
    if (decodedText == origText)
        cout << "\nТекст совпадает\n";
    else
        cout << "\nТекст отличаеться\n";
}