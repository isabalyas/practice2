#include <iostream>
#include <fstream>
#include <cctype>
#include "gronsfeld.h"

using namespace std;

void process_data(vector<unsigned char> &data, const string &key, bool encrypt)
{
    if (key.empty()){
        cerr << "Ошибка: Ключ не может быть пустым." << endl;
        return;
    }

    vector<int> numeric_key;
    for (char c : key)
    {
        if (isdigit(c)){
            numeric_key.push_back(c - '0');
        }
        else{
            cerr << "Ошибка: Ключ должен состоять только из цифр." << endl;
            return;
        }
    }
    if (numeric_key.empty()){
        return;
    }

    for (size_t i = 0; i < data.size(); ++i)
    {
        int shift = numeric_key[i % numeric_key.size()];
        if (!encrypt){
            shift = -shift;
        }
        data[i] = static_cast<unsigned char>((data[i] + shift + 256) % 256);
    }
}

void encrypt_file(const string &input_path, const string &output_path, const string &key)
{
    ifstream input_file(input_path, ios::binary);
    if (!input_file){
        cerr << "Ошибка: Не удалось открыть входной файл: " << input_path << endl;
        return;
    }
    vector<unsigned char> buffer(istreambuf_iterator<char>(input_file), {});
    input_file.close();

    process_data(buffer, key, true);

    ofstream output_file(output_path, ios::binary);
    if (!output_file){
        cerr << "Ошибка: Не удалось создать выходной файл: " << output_path << endl;
        return;
    }
    output_file.write(reinterpret_cast<const char *>(buffer.data()), buffer.size());
    output_file.close();
    cout << "Файл успешно зашифрован: " << output_path << endl;
}

void decrypt_file(const string &input_path, const string &output_path, const string &key)
{
    ifstream input_file(input_path, ios::binary);
    if (!input_file){
        cerr << "Ошибка: Не удалось открыть входной файл: " << input_path << endl;
        return;
    }
    vector<unsigned char> buffer(istreambuf_iterator<char>(input_file), {});
    input_file.close();
    process_data(buffer, key, false);
    ofstream output_file(output_path, ios::binary);
    if (!output_file){
        cerr << "Ошибка: Не удалось создать выходной файл: " << output_path << endl;
        return;
    }

    output_file.write(reinterpret_cast<const char *>(buffer.data()), buffer.size());
    output_file.close();

    cout << "Файл успешно дешифрован: " << output_path << endl;
}
