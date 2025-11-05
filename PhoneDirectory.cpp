#include <iostream>
#include <string>
using namespace std;

struct Contact {
    string name;
    string phone;
    Contact* left;
    Contact* right;
};

// Function to create a new contact node
Contact* createContact(string name, string phone) {
    Contact* newNode = new Contact;
    newNode->name = name;
    newNode->phone = phone;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Function to insert a contact in BST
Contact* insert(Contact* root, string name, string phone) {
    if (root == nullptr)
        return createContact(name, phone);

    if (name < root->name)
        root->left = insert(root->left, name, phone);
    else if (name > root->name)
        root->right = insert(root->right, name, phone);
    else
        cout << "Contact with this name already exists!\n";

    return root;
}

// Function to search for a contact by name
Contact* search(Contact* root, string name) {
    if (root == nullptr || root->name == name)
        return root;

    if (name < root->name)
        return search(root->left, name);
    else
        return search(root->right, name);
}

// Find node with minimum value (used for deletion)
Contact* findMin(Contact* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

// Function to delete a contact
Contact* remove(Contact* root, string name) {
    if (root == nullptr)
        return nullptr;

    if (name < root->name)
        root->left = remove(root->left, name);
    else if (name > root->name)
        root->right = remove(root->right, name);
    else {
        // Case 1: No child
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        }
        // Case 2: One child
        else if (!root->left) {
            Contact* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) {
            Contact* temp = root->left;
            delete root;
            return temp;
        }
        // Case 3: Two children
        else {
            Contact* temp = findMin(root->right);
            root->name = temp->name;
            root->phone = temp->phone;
            root->right = remove(root->right, temp->name);
        }
    }
    return root;
}

// Inorder traversal to display contacts alphabetically
void inorder(Contact* root) {
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << "Name: " << root->name << " | Phone: " << root->phone << endl;
    inorder(root->right);
}

int main() {
    Contact* root = nullptr;
    int choice;
    string name, phone;

    do {
        cout << "\n===== PHONE DIRECTORY MENU =====\n";
        cout << "1. Add Contact\n";
        cout << "2. Search Contact\n";
        cout << "3. Delete Contact\n";
        cout << "4. Display All Contacts\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter phone number: ";
                getline(cin, phone);
                root = insert(root, name, phone);
                cout << "Contact added successfully!\n";
                break;

            case 2: {
                cout << "Enter name to search: ";
                getline(cin, name);
                Contact* found = search(root, name);
                if (found)
                    cout << "Found! " << found->name << " -> " << found->phone << endl;
                else
                    cout << "Contact not found!\n";
                break;
            }

            case 3:
                cout << "Enter name to delete: ";
                getline(cin, name);
                root = remove(root, name);
                cout << "Contact deleted (if it existed).\n";
                break;

            case 4:
                cout << "\n--- Phone Directory (Alphabetical Order) ---\n";
                inorder(root);
                cout << "-------------------------------------------\n";
                break;

            case 5:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
