struct StudentNode {
    Student data;
    struct StudentNode* next;
    int Number_In_List;
};


class StudentList {
private:
    StudentNode* myHead;
    int countStudent = 0;

public:
    // Конструктор
    StudentList() : myHead(nullptr), countStudent(0) {}

    // Деструктор
    ~StudentList() {
        while (myHead != nullptr) {
            StudentNode* temp = myHead;
            myHead = myHead->next;
            delete temp;
        }
    }
    int getCountStudent() { return countStudent; }
    StudentNode* getMyHead() { return myHead; }
    
    void addStudent(Student* data) {
        StudentNode* newNode = new StudentNode{ *data, nullptr, getCountStudent()+1};
        //cout << endl;
        
        if (myHead == nullptr) {
            myHead = newNode;
        }
        else {
            StudentNode* current = myHead;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        countStudent++;
    }

    bool IsCompareArrays(char array1[], char array2[]) {
        return strcmp(array1, array2) == 0;
    }

    bool IsListEmpty() {
        return countStudent == 0;
    }

    void deleteStudent(char Id[]) {
        if (myHead == nullptr) return;

        if (this->IsCompareArrays(myHead->data.getID(), Id)) {
            StudentNode* temp = myHead;
            myHead = myHead->next;
            delete temp;
            countStudent--;
            return;
        }

        StudentNode* current = myHead;
        while (current->next != nullptr && this->IsCompareArrays(current->next->data.getID(), Id)!=true) {
            current = current->next;
        }

        if (current->next != nullptr) {
            StudentNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
            countStudent--;
        }
    }

    StudentNode* FindStudetnByID(char ID[]) {
        int i = 0;
        StudentNode* current = myHead;
        while (i < this->countStudent) {
            if (this->IsCompareArrays(current->data.getID(), ID)){
                return current;
            }
            i++;
            current = current->next;
        }
        return nullptr;
    };
};

