#include"Employee.h"
bool InitDatatype() {
    Type = (datatype*)malloc(sizeof(datatype));
    datatype* temporary = Type;
    strcpy(temporary->type, "ְ������");
    value[KEY++] = "ְ������";

    temporary->next = new datatype; // �����µ��ڴ�
    temporary->next = NULL;
    temporary->type[0] = '\0'; // ���ַ�����Ϊ��

    strcpy(temporary->type, "��������");
    value[KEY++] = "��������";

    temporary->next = new datatype; // �����µ��ڴ�
    temporary = temporary->next;
    temporary->next = NULL;
    temporary->type[0] = '\0'; // ���ַ�����Ϊ��

    strcpy(temporary->type, "ְ��");
    value[KEY++] = "ְ��";

    temporary->next = new datatype; // �����µ��ڴ�
    temporary = temporary->next;
    temporary->next = NULL;
    temporary->type[0] = '\0'; // ���ַ�����Ϊ��

    strcpy(temporary->type, "������");
    value[KEY++] = "������";

    temporary->next = new datatype; // �����µ��ڴ�
    temporary = temporary->next;
    temporary->next = NULL;
    temporary->type[0] = '\0'; // ���ַ�����Ϊ��

    strcpy(temporary->type, "��ϵ�绰");
    value[KEY++] = "��ϵ�绰";

    temporary->next = new datatype; // �����µ��ڴ�
    temporary = temporary->next;
    temporary->next = NULL;
    temporary->type[0] = '\0'; // ���ַ�����Ϊ��

    strcpy(temporary->type, "΢�ź�");
    value[KEY++] = "΢�ź�";

	/*
    temporary->next = new datatype; // �����µ��ڴ�
	temporary = temporary->next;
	temporary->next = NULL;
	temporary->type[0] = '\0'; // ���ַ�����Ϊ��

	strcpy(temporary->type, "XXXXX");
	value[KEY++] = "XXXXX";
    */
    temporary->next = NULL; // ���һ���ڵ��nextӦ����ΪNULL

    return true;
}


bool InitEmployee_list(employee_list& A)//��ͷ�ڵ�Ķ�ά����
{
    A = new employee_list_node;
    if (A) {
        // ʹ�� strncpy ���ַ������Ƶ� NO �ֶ���
        strncpy(A->NO, "-999999999", MAX_NO_SIZE);
        A->data = NULL; // ��ʼ�����ݳ�ԱΪ NULL
        A->next = NULL; // ��ʼ����һ���ڵ�Ϊ NULL
        return true;
    }
    return false; // �ڴ����ʧ��ʱ���� false
}
bool Empolyee_Data_Storage(employee_list& A)
{
    char temp[20];
    employee_list_node* x = A;
    while (x->next != NULL)
    {
        x = x->next;
    }
    employee_list_node* s = new employee_list_node;
    if (s == NULL)
        return false;
    s->next = NULL;
    s->data = NULL;
    x->next = s;
    x = s;
    begin:
    printf("�������ְԱ%dλ���:\n", MAX_NO_SIZE-1);
    cin>>temp;
    if (strlen(temp) != MAX_NO_SIZE-1)
    {
        cout << "��ų��Ȳ��������������룡" << endl;
        goto begin;
    }
    strcpy(x->NO , temp);
    x->data = new employee_data_node;
    if (x->data == NULL)
        return false;
    employee_data_node* y = x->data;
    for (int i = 0;i < KEY;i++)
    {
        y->key = i;
        cout << "�������ְԱ��" << value[i] << "��" << endl;
        cin >> y->data;
        if (i == 1)
        {
            if(department==NULL)
            department = new department_name_node;
            department_name_node* a = department;
            if (!DepartmentNum)
            {
                a->name = y->data;
                a->Address.ADDRESS = x;
                a->Address.next = NULL;
                a->next = NULL;
                DepartmentNum++;
            }
            else
            {
                while (y->data != a->name && a->next != NULL)
                {
                    a = a->next;
                }
                if (y->data == a->name)
                {
                    address* b = &(a->Address);
                    while (b->next != NULL)
                    {
                        b = b->next;
                    }
                    b->next = new address;;
                    if (b->next == NULL)
                        return false;
                    b = b->next;
                    b->next = NULL;
                    b->ADDRESS = x;
                }
                else
                {
                    department_name_node* c = new department_name_node;
                    if (c == NULL)
                        return false;
                    a->next = c;
                    a = c;
                    a->name = y->data;
                    a->Address.ADDRESS = x;
                    a->Address.next = NULL;
                    a->next = NULL;
                    DepartmentNum++;
                }
            }

        }
        if (i < KEY-1)
        {
            y->next = new employee_data_node;
            if (y->next == NULL)
                return false;
            y = y->next;
        }
        else
            y->next = NULL;
    }
    Count++;
    return true;
}
void Print_Sheet(employee_list& A)
{
    employee_list_node* x = A->next;
    for (int i = 0;i < Count;i++)
    {
        
        cout << x->NO << "  ";
        employee_data_node* y = x->data;
        for (int j = 0;j < KEY;j++)
        {
            cout << left << setw(11) << y->data << "  ";
            y = y->next;
        }
        x = x->next;
        cout << endl;
    }
}
void Print_TotalSalary_By_Department()
{
    if (department != NULL)
    {
        department_name_node* a = department;
        for (int i = 0;i < DepartmentNum;i++)
        {
            int sum = 0;
            int result;
            address* b = &(a->Address);
            while (b->next != NULL)
            {
                auto [p, ec] = from_chars(b->ADDRESS->data->next->next->next->data.c_str(), b->ADDRESS->data->next->next->next->data.c_str() + b->ADDRESS->data->next->next->next->data.length(), result);//C++17�µĿ⺯��
                sum += result;
                b = b->next;
            }
            auto [p, ec] = from_chars(b->ADDRESS->data->next->next->next->data.c_str(), b->ADDRESS->data->next->next->next->data.c_str() + b->ADDRESS->data->next->next->next->data.length(), result);//C++17�µĿ⺯��
            sum += result;
            cout << a->name << "  " << "\033[31;1m" << "total" << "\033[0m" << "  " << sum << endl;
            a = a->next;
        }
    }
    else
    {
        cout << "��Ա����" << endl;
    }
}

void Print_Sheet_By_Department()
{
    if (department != NULL)
    {
        department_name_node* a = department;
        for (int i = 0;i < DepartmentNum;i++)
        {
            cout << "\033[31;1m" << a->name << "��" << "\033[0m" << endl;
            for (address* j = &(a->Address);j != NULL;j = j->next)
            {
                cout << j->ADDRESS->NO << "  ";
                employee_data_node* y = j->ADDRESS->data;
                for (int k = 0;k < KEY;k++)
                {
                    cout << left << setw(11) << y->data << "  ";
                    y = y->next;
                }
                cout << endl;
            }
            a = a->next;
            cout << endl;
        }
    }
    else
    {
        cout << "��Ա��" << endl;
    }
}
void Delete_Field(employee_list& A)
{
    char deleteNO[MAX_NO_SIZE];
    employee_list x = A->next;
    employee_list y = A;
    cout << "������Ҫɾ����ְԱ���: ";
    cin >> deleteNO;
    while (x!= NULL)
    {
        if (strcmp(x->NO, deleteNO) == 0)
        {
            break;
        }
        x = x->next;
        y = y->next;
    }
    if (x != NULL && strcmp(x->NO, deleteNO) == 0)
    {
        department_name temp = department;//��ʱ���Žṹ�����
        department_name temp2 = department;
        while (temp != NULL)
        {
            if (temp->name == x->data->next->data)
            {
                address* T = &(temp->Address);
                address* T1 = &(temp->Address);
                while (1)
                {
                    if (T->ADDRESS == x)
                        break;
                    else
                    {
                        T = T->next;
                        if (T != (&(temp->Address))->next)
                        {
                            T1 = T1->next;
                        }
                    }
                        
                }
                if (temp == department&& T == &(temp->Address))//��һ�е�һ��
                {
                    if (T->next == NULL)
                    {
                        department = department->next;
                        delete temp;
                    }
                    else
                    {
                        department->Address = *(department->Address.next);
                        delete T->next;
                    }
                    DepartmentNum--;
                    break;
                }
                else if(temp == department && T != &(temp->Address))//��һ�е�N��
                {
                    T1->next = T->next;
                    delete T;
                    break;
                }
                else if (temp != department && T == &(temp->Address))//��N�е�һ��
                {
                    if (T->next == NULL)
                    {
                        temp2->next = temp->next;
                        delete temp;
                    }
                    else
                    {
                        temp->Address = *(temp->Address.next);
                        delete T->next;
                    }
                    DepartmentNum--;
                    break;
                }
                else if (temp != department && T != &(temp->Address))
                {
                    T1->next = T->next;
                    delete T;
                    break;
                }
            }
            temp = temp->next;
            if (temp != department->next)
            {
                temp2 = temp2->next;
            }
        }
        y->next = x->next;
        delete x;
        Count--;
        cout << "ɾ���ɹ���" << endl;
    }
    else 
    {
        cout << "���޴���" << endl;
    }
}

//void ChangeSalary_By_Job(employee_list&A)
//{
//    string job;
//    string salary;
//    cout << "������ְ�ƣ�" << endl;
//    cin >> job;
//    employee_list_node*  x= A->next;
//    Job* c= new Job ;
//    Job* d = c;
//    d->jOb = NULL;
//    d->next = NULL;
//    while (x != NULL)
//    {
//        employee_data_node* y = x->data;
//        for (;y->key != 2;y = y->next);
//        if (y->data == job)
//        {
//            d->jOb = y;
//            d->next = new Job;
//            d = d->next;
//        }
//        d->jOb = NULL;
//        d->next = NULL;
//        x = x->next;
//    }
//    if (c->next == NULL)
//    {
//        cout << "δ�鵽�д˸�λ����Ա��" << endl;
//        return;
//    }
//    else
//    {
//        cout << "������ø�λ������Ĺ��ʣ�" << endl;
//        cin >> salary;
//        d = c;
//        while (d != NULL)
//        {
//            employee_data_node* joB = d->jOb;
//            while (joB->key != 3)
//            {
//                joB = joB->next;
//            }
//            joB->data = salary;
//            d = d->next;
//        }
//        delete c;
//        cout << "������ɣ�������Ĺ���Ϊ: " << salary << endl;
//    }
//}
void ChangeSalary_By_Job(employee_list& A) 
{
    string job;
    string salary;

    cout << "������ְ�ƣ�" << endl;
    cin >> job;

    employee_list_node* x = A->next;
    Job* c = new Job;
    c->jOb = NULL;
    Job* d = new Job;
    c->next = d;
    d->jOb = NULL;
    d->next = NULL;

    while (x != NULL) 
    {
        employee_data_node* y = x->data;
        while (y != NULL && y->key != 2) 
        {
            y = y->next;
        }

        if (y != NULL && y->data == job) 
        {
            d->jOb = x->data;
            d->next = new Job;
            d = d->next;
        }

        d->jOb = NULL;
        d->next = NULL;
        x = x->next;
    }

    if (c->next->jOb==NULL) 
    {
        cout << "δ�鵽�д˸�λ����Ա��" << endl;
        delete c;
        return;
    }
    else 
    {
        cout << "������ø�λ������Ĺ��ʣ�" << endl;
        cin >> salary;
        d = c->next;
        while (d->jOb!= NULL) 
        {
            employee_data_node* joB = d->jOb;
            while (joB->key != 3) {
                joB = joB->next;
            }
            joB->data = salary;
            d = d->next;
        }
        delete c;
        cout << "������ɣ�������Ĺ���Ϊ: " << salary << endl;
    }
}


void Sort_Sheet(employee_list_node* head)
{
    employee_list_node* pre,* cur, *next, *end;//preǰһ�� cur��ǰ�� next��һ�� end����ѭ������(�Ż�ð��)
    end = NULL;
    if (!head || !head->next)
        return;
    while (head->next != end)
    {
        //��ʼ������ָ�� ; �ж��Ƿ񵽴����λ�� ; ����ָ�뼯�����
        for (pre = head, cur = pre->next, next = cur->next; next != end; pre = pre->next, cur = cur->next, next = next->next)
        {
            if (strcmp(cur->NO ,next->NO)>0) //��С����
            {
                pre->next = next;
                cur->next = next->next;
                next->next = cur;

                //��ʱnext��ǰһ�cur���һ��  ����next cur
                employee_list_node* temp = cur; cur = next; next = temp;
            }
        }

        //һ��ѭ������ ���һ���Ѿ��ź� end��ǰһ�� (ð��ԭ��)
        end = cur;
    }
}
void Excel_Dealing(employee_list_node* head)
{
    const char* originalFileName = "Personnel Information System.xlsx";
    remove(originalFileName);
    libxl::Book* book = xlCreateXMLBook();
    if (book) 
    {
        // ���һ��������
        libxl::Sheet* sheet = book->addSheet(L"Sheet1");
        sheet->writeStr(2, 0, L"���");
        for (int i = 0;i < KEY;i++)
        {
            const char* pCStrKey = value[i].c_str();
            int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
            wchar_t* pWCStrKey = new wchar_t[pSize];
            MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
            sheet->writeStr(2, i+1, pWCStrKey);
        }
        // д�����ݵ���Ԫ��
        for (int i = 0;i < Count;i++)
        {
            string temp;
            temp = head->next->NO;
            const char* pCStrKey = temp.c_str();
            int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
            wchar_t* pWCStrKey = new wchar_t[pSize];
            MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
            sheet->writeStr(i+3, 0, pWCStrKey);
            employee_data_node* y = head->next->data;
            for (int j = 0;j < KEY;j++)
            {
                const char* pCStrKey1 = y->data.c_str();
                int pSize1 = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey1, strlen(pCStrKey1) + 1, NULL, 0);
                wchar_t* pWCStrKey1 = new wchar_t[pSize1];
                MultiByteToWideChar(CP_OEMCP, 0, pCStrKey1, strlen(pCStrKey1) + 1, pWCStrKey1, pSize1);
                sheet->writeStr(i + 3, j+1, pWCStrKey1);
                y = y->next;
            }
            head = head->next;
        }

        // ����Excel�ļ�
        if (book->save(L"Personnel Information System.xlsx")) 
        {
            std::cout << "Excel�ļ�����ɹ�!" << std::endl;
        }
        else 
        {
            std::cerr << "����Excel�ļ�ʧ��!" << std::endl;
        }

        // �ͷ���Դ
        book->release();
    }
    else 
    {
        std::cerr << "����Excel�ĵ�ʧ��!" << std::endl;
    }
}



