#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Product {
    string name;
    int quantity;
    double price;
};

void addProductToFile(const Product& product) {
    ofstream file("orders.txt", ios::app);
    if (file.is_open()) {
        file << product.name << "|" << product.quantity << "|" << product.price << endl;
        file.close();
    }
    else {
        cout << "������ ��� �������� ����� ��� ����������.\n";
    }
}

void addProduct() {
    Product product;
    while (true) {
        cout << "\n������� �������� ������ (��� ������� Enter ��� ����������): ";
        getline(cin, product.name);

        if (product.name.empty()) {
            break; // ��������� ����������, ���� ������� ������ ������
        }

        cout << "������� ���������� ������ ������: ";
        cin >> product.quantity;
        cout << "������� ���� �� ������� ������: ";
        cin >> product.price;
        cin.ignore(); // ������� ����� �����

        addProductToFile(product);
        cout << "����� �������� � ����.\n";
    }
}

void searchProductByName() {
    string name;
    cout << "\n������� �������� ������ ��� ������: ";
    getline(cin, name);

    ifstream file("orders.txt");
    if (file.is_open()) {
        string line;
        bool found = false;
        while (getline(file, line)) {
            size_t pos = line.find('|');
            string productName = line.substr(0, pos);
            if (productName == name) {
                cout << "����� ������: " << line << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "����� � ����� ��������� �� ������.\n";
        }
        file.close();
    }
    else {
        cout << "������ ��� �������� ����� ��� ������.\n";
    }
}

bool compareByName(const Product& a, const Product& b) {
    return a.name < b.name;
}

bool compareByQuantity(const Product& a, const Product& b) {
    return a.quantity < b.quantity;
}

bool compareByPrice(const Product& a, const Product& b) {
    return a.price < b.price;
}

void sortProducts() {
    vector<Product> products;
    ifstream file("orders.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);

            Product product;
            product.name = line.substr(0, pos1);
            product.quantity = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            product.price = stod(line.substr(pos2 + 1));

            products.push_back(product);
        }
        file.close();

        int choice;
        cout << "\n�������� �������� ����������:\n";
        cout << "1. �� �������� ������\n";
        cout << "2. �� ���������� ������\n";
        cout << "3. �� ���� �� �������\n";
        cout << "��� �����: ";
        cin >> choice;
        cin.ignore(); // ������� ����� �����

        switch (choice) {
        case 1:
            sort(products.begin(), products.end(), compareByName);
            break;
        case 2:
            sort(products.begin(), products.end(), compareByQuantity);
            break;
        case 3:
            sort(products.begin(), products.end(), compareByPrice);
            break;
        default:
            cout << "�������� �����.\n";
            return;
        }

        ofstream fileOut("orders.txt");
        if (fileOut.is_open()) {
            for (const auto& product : products) {
                fileOut << product.name << "|" << product.quantity << "|" << product.price << endl;
            }
            fileOut.close();
            cout << "������ �������������.\n";
        }
        else {
            cout << "������ ��� �������� ����� ��� ������ ��������������� ������.\n";
        }
    }
    else {
        cout << "������ ��� �������� ����� ��� ����������.\n";
    }
}

void displayProducts() {
    ifstream file("orders.txt");
    if (file.is_open()) {
        string line;
        cout << "\n������ �������:\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cout << "������ ��� �������� ����� ��� ������ ������.\n";
    }
}

void filterProductsByPrice() {
    double maxPrice;
    cout << "\n������� ������������ ���� ��� ���������� �������: ";
    cin >> maxPrice;
    cin.ignore(); // ������� ����� �����

    ifstream file("orders.txt");
    if (file.is_open()) {
        string line;
        cout << "\n������ � ����� �� " << maxPrice << ":\n";
        while (getline(file, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            double price = stod(line.substr(pos2 + 1));
            if (price <= maxPrice) {
                cout << line << endl;
            }
        }
        file.close();
    }
    else {
        cout << "������ ��� �������� ����� ��� ����������.\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    do {
        cout << "\n����:\n";
        cout << "1. �������� �����\n";
        cout << "2. ����� ������ �� ��������\n";
        cout << "3. ���������� �������\n";
        cout << "4. ����� ���� �������\n";
        cout << "5. ���������� ������� �� ����\n";
        cout << "0. ��������� ���������\n";
        cout << "��� �����: ";
        cin >> choice;
        cin.ignore(); // ������� ����� �����

        switch (choice) {
        case 1:
            addProduct();
            break;
        case 2:
            searchProductByName();
            break;
        case 3:
            sortProducts();
            break;
        case 4:
            displayProducts();
            break;
        case 5:
            filterProductsByPrice();
            break;
        case 0:
            cout << "��������� ���������.\n";
            break;
        default:
            cout << "�������� �����. ���������� �����.\n";
        }
    } while (choice != 0);

    return 0;
}