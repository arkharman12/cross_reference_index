//Final Build

/*******To compile: g++ main.cpp -> ./a.out
//(OR) 
// make main -> make run -> make clean(to clear the files)
*******/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

struct line {
    int number;
    line * next;
};

void makeList(line * &temporary, int number) {
    line * n = new line;
    n -> number = number;
    n -> next = NULL;
    if (temporary == NULL) {
        temporary = n;
    } else {
        line * t = temporary;
        while (t -> next != NULL) {
            t = t -> next;
        }
        t -> next = n;
    } // end if
} //end makeList

struct node {
    string word;
    line *lines;
    node *left;
    node *right;
}; // end node

class BST {
    private:
    node * head;
    int count;

    public:
    BST();
    int size();
    void insert(string value, int number);
    void insert(node * & temporary, string value, int number);
    node * search(node * temporary, string value);
    void display();
    void display(node * root);
}; //end BST

BST::BST() {
    head = NULL;
    count = 0;
}

int BST::size() {
    return count;
}

void BST::insert(node * &temporary, string value, int number) {
    if (temporary == NULL) {
        node * newOne = new node;
        newOne -> word = value;
        newOne -> left = NULL;
        newOne -> right = NULL;
        newOne -> lines = NULL;
        makeList(newOne -> lines, number);
        temporary = newOne;
        return;
    } else {
        if (temporary -> word <= value) {
            insert(temporary -> right, value, number);
        } else {
            insert(temporary -> left, value, number);
        } // end nested if
    } // end if
} // end BST::insert

void BST::insert(string value, int number) {
    if (head == NULL) {
        node * newOne = new node;
        newOne -> word = value;
        newOne -> left = NULL;
        newOne -> right = NULL;
        newOne -> lines = NULL;
        makeList(newOne -> lines, number);
        head = newOne;
        count++;
        return;
    } else {
        node * f = search(head, value);
        if (f != NULL) {
            makeList(f -> lines, number);
        } else {
            insert(head, value, number);
            count++;
        } // end nested if
        return;
    } // end if
} // end BST::insert

node * BST::search(node * temporary, string value) {
    if (temporary == NULL) {
        return NULL;
    } else {
        if (temporary -> word == value) {
            return temporary;
        } else {
            node * l = search(temporary -> left, value);
            node * r = search(temporary -> right, value);
            if (l != NULL) {
                return l;
            } else if (r != NULL) {
                return r;
            } else {
                return NULL;
            } // end double nested if
        } // end nested if
    } // end if
}

void BST::display(node * root) {
    if (root == NULL) {
        return;
    } else {
        display(root -> left);
        cout << setw(10) << root -> word << " " << setw(10);
        line * t = root -> lines;
        while (t != NULL) {
            cout << t -> number << " ";
            t = t -> next;
        } // end while
        cout << endl;
        display(root -> right);
    } // end if
}

void BST::display() {
    if (count == 0) {
        cout << "\nFile is Empty, Try Again!" << endl;
    } else {
        cout << setw(10) << "Word" << setw(10) << "     Line numbers" << endl;
        display(head);
        cout << endl;
    } // end if 
}

// Driver code
int main() {
    BST tree = BST();
    ifstream in;
    string fName;
    cout << "\nEnter File Name: ";
    cin >> fName; 
    in .open(fName.c_str());
    if (in .is_open()) {
        int lineCount = 0;
        while (! in .eof()) {
            lineCount++;
            string temporary;
            getline(in, temporary);
            stringstream ss;
            ss << temporary;
            string t = "";
            while (ss >> t) {
                if (t.size() > 10) {
                    t = t.substr(0, 10);
                } // end nested if
                char lineEnd = t[t.size() - 1];
                if (lineEnd == ',' || lineEnd == '.' || lineEnd == '.') {
                    t = t.substr(0, t.size() - 1);
                } // end nested if 
                tree.insert(t, lineCount);
            } // end while loop
        }
        tree.display(); // display the final result
    } // end if 
    return 0;
} // end main
