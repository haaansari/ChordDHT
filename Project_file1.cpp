#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<fstream>
#include"md5.h"
using namespace std;


int HashFunc(string adress, int bitsystem) {
    long double ID, sum = 0;
    int i = 0;
    long double indet = pow(2,bitsystem);
    while (adress[i] != '\0')
    {
        sum = sum + int(adress[i]);
        i++;
    }
    ID = fmod(sum, indet);
    return ID;
}
class doublyNode
{
public:
    int key;
    int data;
    doublyNode* next;
    doublyNode* previous;

    doublyNode()
    {
        key = 0;
        data = 0;
        next = NULL;
        previous = NULL;
    }
    doublyNode(int k, int d)
    {
        key = k;
        data = d;
    }
};

class doublyList
{

public:
    doublyNode* head;

    doublyList()
    {
        head = NULL;
    }
    doublyList(doublyNode* n)
    {
        head = n;
    }



    doublyNode* nodeexistsalready(int k) {
        doublyNode* temp = NULL;
        doublyNode* ptr = head;

        while (ptr != NULL) {
            if (ptr->key == k) {
                temp = ptr;
            }
            ptr = ptr->next;
        }

        return temp;
    }


    void appendNodeinlist(int k, int shortcut) {
        doublyNode* n = new doublyNode;
        n->key = k;
        n->data = shortcut;
        if (nodeexistsalready(n->key) != NULL) {
            cout << "Node exist" << endl;
        }
        else
        {
            if (head == NULL) {
                head = n;
            }
            else
            {
                doublyNode* ptr = head;
                while (ptr->next != NULL)
                {
                    ptr = ptr->next;
                }
                ptr->next = n;
                n->previous = ptr;
            }
        }
    }


    void prependNodeinlist(doublyNode* n) {
        if (nodeexistsalready(n->key) != NULL) {
            cout << "Node exist" << endl;
        }
        else
        {
            if (head == NULL)
            {
                head = n;

            }
            else
            {
                head->previous = n;
                n->next = head;
                head = n;

            }

        }
    }


    void insertnodeinlist(int k, doublyNode* n)
    {
        doublyNode* ptr = nodeexistsalready(k);
        if (ptr == NULL) {
            cout << "Node alredy exist" << endl;
        }
        else
        {
            if (nodeexistsalready(n->key) != NULL)
            {
                cout << "Node exists" << endl;
            }
            else
            {
                doublyNode* temp = ptr->next;

                if (temp == NULL) {
                    ptr->next = n;
                    n->previous = ptr;

                }


                else
                {
                    n->next = temp;
                    temp->previous = n;
                    n->previous = ptr;
                    ptr->next = n;



                }

            }
        }
    }


    void deletenodeinlist(int k) {
        doublyNode* ptr = nodeexistsalready(k);
        if (ptr == NULL) {
            cout << "No node " << endl;
        }
        else
        {

            if (head->key == k) {
                head = head->next;

            }
            else
            {
                doublyNode* temp1 = ptr->next;
                doublyNode* temp2 = ptr->previous;

                if (temp1 == NULL) {

                    temp2->next = NULL;

                }


                else {
                    temp2->next = temp1;
                    temp1->previous = temp2;

                }
            }
        }
    }

    void display()
    {
        int ID;
        if (head == NULL)
        {
            cout << "There exits no node";
        }
        else
        {
            doublyNode* temp = head;
            ID = temp->key;
            cout << endl << "The routing table of " << ID << endl;
            while (temp != NULL)
            {
                cout << "(" << temp->key << "," << temp->data << ")\n ";
                temp = temp->next;
            }
        }
    }

};


struct avl {
    avl* l;
    string file_path = " ";
    int linenumber = 0;
    string key = " ";
    int ht;
    avl* r;

};

class avl_tree
{
public:
    int inc_ln = 0;
    struct avl* avl_root;
    avl_tree() {
        this->avl_root = NULL;

    }

    int height(struct avl* ptr) {

        if (ptr->l && ptr->r) {
            if (ptr->l->ht < ptr->r->ht)
                return ptr->r->ht + 1;
            else return  ptr->l->ht + 1;
        }
        else if (ptr->l && ptr->r == NULL) {
            return ptr->l->ht + 1;
        }
        else if (ptr->l == NULL && ptr->r) {
            return ptr->r->ht + 1;
        }
        return 0;

    }

    int balancing(struct avl* new_node) {
        if (new_node->l && new_node->r) {
            return new_node->l->ht - new_node->r->ht;
        }
        else if (new_node->l && new_node->r == NULL) {
            return new_node->l->ht;
        }
        else if (new_node->l == NULL && new_node->r) {
            return new_node->r->ht;
        }
    }

    struct avl* leftleftrotat(struct avl* new_node) {
        struct avl* parent;
        struct avl* temp;
        parent = new_node;
        temp = parent->l;

        parent->l = temp->r;
        temp->r = parent;

        return temp;
    }


    struct avl* rightrightrotat(struct avl* new_node) {
        struct avl* parent;
        struct avl* temp;
        parent = new_node;
        temp = parent->r;

        parent->r = temp->l;
        temp->l = parent;

        return temp;
    }


    struct avl* rightleftrotat(struct avl* new_node) {
        struct avl* parent;
        struct avl* temp;
        struct avl* temp1;
        parent = new_node;
        temp = parent->r;
        temp1 = parent->r->l;

        parent->r = temp1->l;
        temp->l = temp1->r;
        temp1->l = parent;
        temp1->r = temp;

        return temp1;
    }

    struct avl* leftrightrotat(struct avl* new_node) {
        struct avl* parent;
        struct avl* temp;
        struct avl* temp1;
        parent = new_node;
        temp = parent->l;
        temp1 = parent->l->r;

        parent->l = temp1->r;
        temp->r = temp1->l;
        temp1->r = parent;
        temp1->l = temp;

        return temp1;
    }



    struct avl* insert(string k, string p, avl* temp) {
        inc_ln++;
        if (temp == NULL) {
            struct avl* new_node;
            new_node = new struct avl;
            new_node->linenumber = inc_ln;
            new_node->file_path = p;
            new_node->key = k;
            temp = new_node;
            temp->l = temp->r = NULL;
            temp->ht = 1;
            return temp;
        }
        else {
            if (k < temp->key)
                temp->l = insert(k, p, temp->l);
            else
                temp->r = insert(k, p, temp->r);
        }

        temp->ht = height(temp);

        if (balancing(temp) == 2 && balancing(temp->l) == 1) {
            temp = leftleftrotat(temp);
        }
        else if (balancing(temp) == -2 && balancing(temp->r) == -1) {
            temp = rightrightrotat(temp);
        }
        else if (balancing(temp) == -2 && balancing(temp->r) == 1) {
            temp = rightleftrotat(temp);
        }
        else if (balancing(temp) == 2 && balancing(temp->l) == -1) {
            temp = leftrightrotat(temp);
        }

        return temp;

    }
    void showBAt(avl* p, int l) {
        int i;
        if (p != NULL) {
            showBAt(p->r, l + 1);
            cout << " ";
            if (p == avl_root)
                cout << "Root -> ";
            for (i = 0; i < l && p != avl_root; i++)
                cout << " ";
            cout << p->file_path;
            showBAt(p->l, l + 1);
        }
    }

    avl* searchnode(string k) {
        if (avl_root == NULL) {
            return avl_root;
        }
        else {
            avl* temp = avl_root;
            while (temp != NULL) {
                if (k == temp->key) {
                    return temp;
                }
                else if (k < temp->key)
                {
                    temp = temp->l;
                }
                else {
                    temp = temp->r;
                }
            }
            return NULL;
        }
    }


    struct avl* func1(struct avl* p) {
        while (p->r != NULL)
            p = p->r;
        return p;
    }

    struct avl* func2(struct avl* p) {
        while (p->l != NULL)
            p = p->l;

        return p;
    }


    struct avl* deleteavlNode(struct avl* ptr, string data, string str) {

        string line;
        if (ptr->l == NULL && ptr->r == NULL) {
            if (ptr == this->avl_root)
                this->avl_root = NULL;
            delete ptr;
            return NULL;
        }

        struct avl* temp;
        struct avl* q;
        if (ptr->key < data) {
            ptr->r = deleteavlNode(ptr->r, data, str);
        }
        else if (ptr->key > data) {
            ptr->l = deleteavlNode(ptr->l, data, str);
        }
        else {
            if (ptr->l != NULL) {
                q = func1(ptr->l);
                ptr->key = q->key;
                ptr->l = deleteavlNode(ptr->l, q->key, str);
            }
            else {
                q = func2(ptr->r);
                ptr->key = q->key;
                ptr->r = deleteavlNode(ptr->r, q->key, str);
            }
        }

        if (balancing(ptr) == 2 && balancing(ptr->l) == 1) { ptr = leftleftrotat(ptr); }
        else if (balancing(ptr) == 2 && balancing(ptr->l) == -1) { ptr = leftrightrotat(ptr); }
        else if (balancing(ptr) == 2 && balancing(ptr->l) == 0) { ptr = leftleftrotat(ptr); }
        else if (balancing(ptr) == -2 && balancing(ptr->r) == -1) { ptr = rightrightrotat(ptr); }
        else if (balancing(ptr) == -2 && balancing(ptr->r) == 1) { ptr = rightleftrotat(ptr); }
        else if (balancing(ptr) == -2 && balancing(ptr->r) == 0) { ptr = leftleftrotat(ptr); }


        return ptr;
        ifstream obj(str);
        obj.open(str);
        //ofstream obj1(str);

        while (getline(obj, line))
        {

            line.replace(line.find(data), data.length(), "");
            //obj >> line;

        }
    }





    void inorder(avl* t)
    {

        if (t == NULL)
            return;

        inorder(t->l);
        cout << t->key << "->" << "(" << t->file_path << "," << t->linenumber << ")" << endl;

        inorder(t->r);
    }

};


class circularNode {
public:
    int key;
    int data;
    circularNode* next;
    doublyList object;
    avl_tree avl_object;
    circularNode() {
        key = 0;
        data = 0;
        next = NULL;
    }
    circularNode(int k, int d, doublyList obj, avl_tree avl_obj)
    {
        key = k;
        data = d;
        object = obj;
        avl_object = avl_obj;
        next = NULL;
    }
};

class CircularList {
public:
    circularNode* head;

    CircularList()
    {
        head = NULL;
    }


    circularNode* nodeexistsalready(int k) {

        circularNode* temp = NULL;
        circularNode* ptr = head;

        if (ptr == NULL) {
            return temp;
        }
        else {
            do {
                if (ptr->key == k) {
                    temp = ptr;
                }
                ptr = ptr->next;

            } while (ptr != head);
            return temp;
        }
    }


    void appendNode(int k) {
        circularNode* new_node = new circularNode;
        new_node->key = k;
        string s1, s2, s3, s4;
        s3 = ".txt";
        s2 = "project";
        s1 = to_string(k);
        s4 = s2 + s1 + s3;
        if (nodeexistsalready(new_node->key) != NULL) {

            cout << "Node already exist";
            cout << endl;
        }
        else
        {
            if (head == NULL) {
                head = new_node;
                new_node->next = head;

            }
            else
            {
                circularNode* ptr = head;
                while (ptr->next != head) {
                    ptr = ptr->next;
                }
                ptr->next = new_node;
                new_node->next = head;

            }

        }
        ofstream obj1(s4);
        obj1.close();
        // obj.open("dfgdfvc.txt");
        //obj1 << "Writing to your file" << endl;
    }

    void prependNode(circularNode* new_node)
    {
        if (nodeexistsalready(new_node->key) != NULL)
        {
            cout << "Node aleady exist" << endl;
        }
        else
        {
            if (head == NULL) {
                head = new_node;
                new_node->next = head;

            }
            else
            {
                circularNode* ptr = head;
                while (ptr->next != head)
                {
                    ptr = ptr->next;
                }

                ptr->next = new_node;
                new_node->next = head;
                head = new_node;

            }

        }
    }


    void insertnode(int k) {
        circularNode* new_node = new circularNode;
        circularNode* ptr = nodeexistsalready(k);
        if (ptr == NULL)
        {
            cout << "No node exists" << endl;
        }
        else
        {
            if (nodeexistsalready(new_node->key) != NULL) {
                cout << "Node already exist" << endl;
            }
            else
            {
                if (ptr->next == head) {
                    new_node->next = head;
                    ptr->next = new_node;
                    new_node->object;

                }
                else
                {
                    new_node->next = ptr->next;
                    ptr->next = new_node;

                }

            }
        }
    }


    //void deletenode(int k)
    //{
    //    circularNode* ptr = nodeexistsalready(k);
    //    if (ptr == NULL)
    //    {
    //        cout << "No node exist" << endl;
    //    }
    //    else
    //    {
    //        if (ptr == head) {
    //            if (head->next == NULL)
    //            {
    //                head = NULL;

    //            }
    //            else
    //            {
    //                circularNode* ptr1 = head;
    //                while (ptr1->next != head)
    //                {
    //                    ptr1 = ptr1->next;
    //                }
    //                ptr1->next = head->next;
    //                head = head->next;

    //            }
    //        }
    //        else
    //        {
    //            circularNode* temp = NULL;
    //            circularNode* previous = head;
    //            circularNode* temp1 = head->next;
    //            while (temp1 != NULL)
    //            {
    //                if (temp1->key == k)
    //                {
    //                    temp = temp1;
    //                    temp1 = NULL;
    //                }
    //                else
    //                {
    //                    previous = previous->next;
    //                    temp1 = temp1->next;
    //                }
    //            }

    //            previous->next = temp->next;

    //        }
    //    }
    //}

    void updateNodeByKey(string k, string new_data, int mac_ID, int bit_size) {
        string path;
        int ln = 1;
        avl s;
        string s1, s2, s3, s4;
        s3 = ".txt";
        s2 = "project";
        s1 = to_string(mac_ID);
        s4 = s2 + s1 + s3;
        circularNode* ptr = nodeexistsalready(mac_ID);
        circularNode* NEW = nodeexistsalready(mac_ID);
        int hashID = HashFunc(k, (pow(2, bit_size) - 1));
        doublyNode* rout = ptr->object.nodeexistsalready(1);
        if (hashID = mac_ID)
        {
            ptr = NEW;
        }
        else {
            if (hashID > mac_ID && hashID <= rout->data)
            {
                ptr = nodeexistsalready(rout->data);
            }
            while (NEW->next != head)
            {
                NEW = NEW->next;
            }
            if (hashID <= NEW->key)
            {
                while (rout->data < hashID)
                {
                    rout = rout->next;
                }
                if (rout->data == hashID)
                {
                    ptr = nodeexistsalready(rout->data);
                }
                else
                {
                    rout = rout->previous;
                    ptr = nodeexistsalready(rout->data);
                    while (ptr->data < hashID)
                    {
                        ptr = ptr->next;
                    }

                }
            }
            else
            {
                ptr = head;
            }
        }
        if (ptr != NULL) {
            //ptr -> data = new_data;
            fstream input(s4, ios::app);
            if (input.is_open())
            {
                input << new_data;
                input << endl;
            }
            // avl_tree obj1;
            ptr->avl_object.avl_root = ptr->avl_object.insert(k, s4, ptr->avl_object.avl_root);
            input.close();
            cout << "Node Data Updated Successfully" << endl;
        }
        else {
            cout << "Node Doesn't exist with key value : " << k << endl;
        }

    }

    void routingtable(int ID, int bit_size) {
        circularNode* ptr = nodeexistsalready(ID);
        circularNode* NEW = nodeexistsalready(ID);
        int i2 = 0;
        long double inc, shortcut = 0;
        for (int i = 1; i <= bit_size; i++)
        {
            //i2 = i-1;
            inc = pow(2, i - 1);
            shortcut = ID + inc;

            if (shortcut > pow(2, bit_size))
            {
                shortcut = shortcut - (pow(2, bit_size));
            }

            NEW = head;
            do
            {

                if (NEW->key >= shortcut)
                {
                    shortcut = NEW->key;
                    break;
                }
                NEW = NEW->next;
            } while (NEW != head);
            while (NEW->next != head)
            {
                NEW = NEW->next;
            }

            if ((shortcut > NEW->key) && (shortcut <= pow(2, bit_size)))
            {
                shortcut = head->key;
            }
            ptr->object.appendNodeinlist(i, shortcut);
        }
        ptr->object.display();
    }
};




int main()
{
    CircularList obj;
    int bit_system, option, no_machine = 0;
    int flag = 0;
    string data_key = " ";
    int input_machineID = 0;
    avl* ob1 = new avl;
    circularNode* object = new circularNode;
    string input = "0";
    string machine_address;
    string md5_result;
    cout << "Enter the bit size of DHT" << endl;
    cin >> bit_system;
    cout << "Enter the number of machines";
    cin >> no_machine;
    int* machine_ID = new int[no_machine];
    cout << "Do you want to specify ID's Machine manually or by using hash function" << endl;
    cout << "Enter 0 for Manual inserton" << endl;
    cout << "Enter 1 for Hash function" << endl;
    cin >> option;
    if (option == 0)
    {
        for (int i = 0; i < no_machine; i++)
        {
            cout << "Enter the machine ID";
            cin >> machine_ID[i];
            obj.appendNode(machine_ID[i]);
        }
    }
    else
    {
        for (int i = 0; i < no_machine; i++)
        {
            cout << "Enter the machine Address";
            cin >> machine_address;
            md5_result = md5(machine_address);
            machine_ID[i] = HashFunc(md5_result, bit_system);
            obj.appendNode(machine_ID[i]);
        }

    }
    
    for (int i = 0; i < no_machine; i++)
    {
        obj.routingtable(machine_ID[i], bit_system);
    }

    while (flag == 0)
    {
        cout << "Enter The Machine ID through which you want to enter data";
        cin >> input_machineID;
        while (data_key != "-1")
        {
            cout << "Enter the key(Enter -1 to exit) ";
            cin >> data_key;
            if (data_key == "-1")
            {
                break;
            }
            cout << "Enter the data";
            cin.ignore();
            getline(cin, input);
            if (data_key != "-1")
            {
                obj.updateNodeByKey(data_key, input, input_machineID, bit_system);
            }
        }
        cout << "Do want to exit or enter data from another machine(1 to exit and  to enter data ): ";
        cin >> flag;
    }
    int display;
    cout << "The IDs of given machines are:\n";
    for (int i = 0; i < no_machine; i++)
    {
        cout << machine_ID[i]<<endl;
    }
    cout << "Enter the machine of which data you want to be displayed: ";
    cin >> display;
        object = obj.nodeexistsalready(display);

        ob1 = object->avl_object.avl_root;
        //cout << machine_ID[0];
        object->avl_object.inorder(ob1);
        //cout << "md5 of 'grape': " << md5("grape") << endl;
        string s1, s2, s3, s4;
        s3 = ".txt";
        s2 = "project";
        s1 = to_string(machine_ID[0]);
        s4 = s2 + s1 + s3;
        cin.ignore();
        cout << "Which node do you want to delete,enter key" << endl;
        string delete_key;
        getline(cin, delete_key);
        ob1->key = delete_key;
        object->avl_object.deleteavlNode(ob1, delete_key, s4);
        object->avl_object.inorder(ob1);

    return 0;
}