#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Employee {
    std::string surname;
    std::string initials;
    std::string position;
    int yearOfHire;
    double salary;
    bool isDeleted;  

    Employee() : isDeleted(false) {}
};

class HashTable {
private:
    std::vector<Employee> table;
    size_t size;
    size_t count;

    unsigned int HashFunction(const std::string& key) {
        unsigned int hash = 0;
        for (char ch : key) {
            hash = 31 * hash + ch;
        }
        return hash % size;
    }

    int Probe(int hashValue) {
        return (hashValue + 1) % size;
    }

public:
    HashTable(size_t size) : size(size), count(0) {
        table.resize(size);
    }

    bool AddEmployee(const Employee& employee) {
        if (count >= size) {
            std::cerr << "Hash table is full.\n";
            return false;
        }

        unsigned int hashValue = HashFunction(employee.surname);
        while (!table[hashValue].surname.empty() && !table[hashValue].isDeleted) {
            hashValue = Probe(hashValue);
        }
        table[hashValue] = employee;
        table[hashValue].isDeleted = false;
        count++;
        return true;
    }

    bool RemoveEmployee(const std::string& surname) {
        unsigned int hashValue = HashFunction(surname);
        for (size_t i = 0; i < size; ++i) {
            if (table[hashValue].surname == surname && !table[hashValue].isDeleted) {
                table[hashValue].isDeleted = true;
                count--;
                return true;
            }
            hashValue = Probe(hashValue);
        }
        return false;
    }

    Employee* FindEmployee(const std::string& surname) {
        unsigned int hashValue = HashFunction(surname);
        for (size_t i = 0; i < size; ++i) {
            if (table[hashValue].surname == surname && !table[hashValue].isDeleted) {
                return &table[hashValue];
            }
            if (table[hashValue].surname.empty()) {
                return nullptr;
            }
            hashValue = Probe(hashValue);
        }
        return nullptr;
    }

    void SaveToFile(const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Could not open file for writing.\n";
            return;
        }

        for (const auto& employee : table) {
            if (!employee.surname.empty() && !employee.isDeleted) {
                file.write((char*)&employee, sizeof(Employee));
            }
        }

        file.close();
    }

    void LoadFromFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Could not open file for reading.\n";
            return;
        }

        Employee employee;
        while (file.read((char*)&employee, sizeof(Employee))) {
            AddEmployee(employee);
        }

        file.close();
    }
};

void DisplayMenu() {
    std::cout << "Menu:\n";
    std::cout << "1. Add Employee\n";
    std::cout << "2. Remove Employee\n";
    std::cout << "3. Edit Employee\n";
    std::cout << "4. Display Employee\n";
    std::cout << "5. Save to File\n";
    std::cout << "6. Load from File\n";
    std::cout << "7. Exit\n";
}

void AddEmployee(HashTable& hashTable) {
    Employee employee;
    std::cout << "Enter surname: ";
    std::cin >> employee.surname;
    std::cout << "Enter initials: ";
    std::cin >> employee.initials;
    std::cout << "Enter position: ";
    std::cin >> employee.position;
    std::cout << "Enter year of hire: ";
    std::cin >> employee.yearOfHire;
    std::cout << "Enter salary: ";
    std::cin >> employee.salary;
    if (hashTable.AddEmployee(employee)) {
        std::cout << "Employee added successfully.\n";
    }
}

void RemoveEmployee(HashTable& hashTable) {
    std::string surname;
    std::cout << "Enter surname to remove: ";
    std::cin >> surname;
    if (hashTable.RemoveEmployee(surname)) {
        std::cout << "Employee removed successfully.\n";
    }
    else {
        std::cout << "Employee not found.\n";
    }
}

void EditEmployee(HashTable& hashTable) {
    std::string surname;
    std::cout << "Enter surname to edit: ";
    std::cin >> surname;
    Employee* employee = hashTable.FindEmployee(surname);
    if (employee) {
        std::cout << "Enter new initials: ";
        std::cin >> employee->initials;
        std::cout << "Enter new position: ";
        std::cin >> employee->position;
        std::cout << "Enter new year of hire: ";
        std::cin >> employee->yearOfHire;
        std::cout << "Enter new salary: ";
        std::cin >> employee->salary;
        std::cout << "Employee updated successfully.\n";
    }
    else {
        std::cout << "Employee not found.\n";
    }
}

void DisplayEmployee(HashTable& hashTable) {
    std::string surname;
    std::cout << "Enter surname to display: ";
    std::cin >> surname;
    Employee* employee = hashTable.FindEmployee(surname);
    if (employee) {
        std::cout << "Surname: " << employee->surname << "\n";
        std::cout << "Initials: " << employee->initials << "\n";
        std::cout << "Position: " << employee->position << "\n";
        std::cout << "Year of Hire: " << employee->yearOfHire << "\n";
        std::cout << "Salary: " << employee->salary << "\n";
    }
    else {
        std::cout << "Employee not found.\n";
    }
}

void SaveToFile(HashTable& hashTable) {
    std::string filename;
    std::cout << "Enter filename to save: ";
    std::cin >> filename;
    hashTable.SaveToFile(filename);
}

void LoadFromFile(HashTable& hashTable) {
    std::string filename;
    std::cout << "Enter filename to load: ";
    std::cin >> filename;
    hashTable.LoadFromFile(filename);
}

int main() {
    HashTable hashTable(10);
    int choice;

    do {
        DisplayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            AddEmployee(hashTable);
            break;
        case 2:
            RemoveEmployee(hashTable);
            break;
        case 3:
            EditEmployee(hashTable);
            break;
        case 4:
            DisplayEmployee(hashTable);
            break;
        case 5:
            SaveToFile(hashTable);
            break;
        case 6:
            LoadFromFile(hashTable);
            break;
        case 7:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
