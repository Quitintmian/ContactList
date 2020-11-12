#include <iostream>
#include <malloc.h>
#include <string.h>
#include <fstream>
using namespace std;

//����һ��ͨ������ʵ�ֵ�ͨѶ¼,���������2020��10��27��11��43��27.

struct Contact
{
    char name[20];
    char sex[20];
    int age;
    int phoneNumber;
    char address[20];
};

typedef struct ContactManager
{
    struct Contact contact_data;
    struct ContactManager *next;
    int Size;
} * ContactNode, Node;

void printContactInfo(Contact *p);
void Init(ContactNode &manager);
void showMenu();
void exitSys();
void addContact(ContactNode &manager);
void showContactList(ContactNode manager);
void delContactByName(ContactNode &manager);
ContactNode isExist(ContactNode manager);
void findContactByName(ContactNode manager);
void updateContactByName(ContactNode &manager);
void ClearManager(ContactNode &manager);
void savefile(ContactNode manager);
void readfile(ContactNode &manager);
//�����ǹ���ʵ�ֵĺ�������

void showMenu()
{
    cout << "****************************************" << endl;
    cout << "**************1�������ϵ��**************" << endl;
    cout << "**************2����ʾ��ϵ��**************" << endl;
    cout << "**************3��ɾ����ϵ��**************" << endl;
    cout << "**************4��������ϵ��**************" << endl;
    cout << "**************5���޸���ϵ��**************" << endl;
    cout << "**************6�������ϵ��**************" << endl;
    cout << "**************0�������ļ����˳�ϵͳ****************" << endl;
    cout << "****************************************" << endl;
    cout << "------> ��ѡ����������������ţ�" << endl;
}

void exitSys()
{
    cout << "��ӭ�´�ʹ�ã��ټ���" << endl;
    system("pause");
    exit(0);
}

void Init(ContactNode &manager) //��ʼ������
{
    manager = (Node *)malloc(sizeof(Node));
    manager->next = NULL;
}

void printContactInfo(Contact *p)
{
    cout << "������" << p->name << "   �Ա�" << p->sex << "   ���䣺" << p->age << "   ��ϵ�绰��" << p->phoneNumber << "   ��ͥ��ַ��" << p->address << endl;
} //�����������Ļ���

void addContact(ContactNode &manager)//ͷ�巨
{
    ContactNode s = (Node *)malloc(sizeof(Node)); //����һƬ�ڵ�ռ�,����sizeof����ΪContactNode��������Ϊstruct ContactManager��û����
    cout << "��������ϵ�˵�������";
    cin >> s->contact_data.name;
    cout << "��������ϵ�˵��Ա�";
    cin >> s->contact_data.sex;
    cout << "��������ϵ�˵����䣺";
    cin >> s->contact_data.age;
    cout << "��������ϵ�˺��룺";
    cin >> s->contact_data.phoneNumber;
    cout << "��������ϵ�˵ĵ�ַ��";
    cin >> s->contact_data.address;
    s->next = manager->next;
    manager->next = s; //��ɽڵ������
    manager->Size++;
    system("pause");
    system("cls");
}

void showContactList(ContactNode manager)
{
    if (manager->Size == 0)
    {
        cout << "û����ϵ�ˣ�" << endl;
        system("pause");
        system("cls");
        return;
    }
    ContactNode p = manager->next;
    for (int i = 0; i < manager->Size; i++)
    {
        printContactInfo(&p->contact_data);
        p = p->next;
    }
    system("pause");
    system("cls");
}

ContactNode isExist(ContactNode manager, char *name)
{
    ContactNode p = manager->next;
    ContactNode pre = manager; //��������ָ�룬����ɾ�������
    for (int i = 0; i < manager->Size && strcmp(p->contact_data.name, name); i++)
    {
        p = p->next;
        pre = pre->next;
    }
    if (p == NULL)
    {
        return NULL;
    }
    return pre;
}

void delContactByName(ContactNode &manager)
{
    cout << "������Ҫɾ������ϵ�˵�������";
    char name[20];
    cin >> name;
    ContactNode pos = isExist(manager, name); //�ж���ϵ�����������Ƿ���ڣ������ڲ���������ǰ��ָ�룬�������򷵻�NULL
    if (pos == NULL)
    {
        cout << "��ϵ�˲����ڣ�" << endl;
        system("pause");
        system("cls");
        return;
    }
    else
    {
        ContactNode d = pos->next; //dΪ��ɾ���ڵ�
        pos->next = pos->next->next;
        free(d);
        cout << "ɾ����ɣ�" << endl;
        manager->Size--;
        system("pause");
        system("cls");
    }
}

void findContactByName(ContactNode manager)
{
    cout << "������Ҫ���ҵ���ϵ�˵�������";
    char name[20];
    cin >> name;
    ContactNode pos = isExist(manager, name);
    if (pos == NULL)
    {
        cout << "��ϵ�˲����ڣ�" << endl;
        system("pause");
        system("cls");
        return;
    }
    else
    {
        printContactInfo(&pos->next->contact_data);
        system("pause");
        system("cls");
    }
}

void updateContactByName(ContactNode &manager)
{
    cout << "��������Ҫ�޸ĵ���ϵ�˵�������";
    char name[20];
    cin >> name;
    ContactNode pos = isExist(manager, name);
    if (pos == NULL)
    {
        cout << "��ϵ�˲����ڣ�" << endl;
        system("pause");
        system("cls");
        return;
    }
    else
    {
        cout << "��������ϵ�˵�������";
        cin >> pos->next->contact_data.name;
        cout << "��������ϵ�˵��Ա�";
        cin >> pos->next->contact_data.sex;
        cout << "��������ϵ�˵����䣺";
        cin >> pos->next->contact_data.age;
        cout << "��������ϵ�˺��룺";
        cin >> pos->next->contact_data.phoneNumber;
        cout << "��������ϵ�˵ĵ�ַ��";
        cin >> pos->next->contact_data.address;
        cout << "�޸���ɣ�" << endl;
        system("pause");
        system("cls");
    }
}

void ClearManager(ContactNode &manager) //���ͷ�ͷ�ڵ㣬ֻ�ͷź�̵����нڵ�
{
    ContactNode p = manager->next;
    ContactNode pre = p;
    while (p != NULL)
    {
        p = p->next;
        free(pre); //�ͷ�
        pre = p;
    }
    free(pre);
    manager->Size = 0;
    manager->next = NULL;
    cout << "��ϵ������գ�" << endl;
    system("pause");
    system("cls");
}

//�����ļ�����
void savefile(ContactNode manager)
{
    ofstream ofs;
    ofs.open("userfile.txt", ios::out);

    ContactNode fp = manager->next;
    for (int i = 0; i < manager->Size; i++)
    {
        ofs << fp->contact_data.name << " "
            << fp->contact_data.sex << " "
            << fp->contact_data.age << " "
            << fp->contact_data.phoneNumber << " "
            << fp->contact_data.address << endl; //�Կո�Ϊ�ֽ�����ֱ��ȡ
        fp = fp->next;
    }

    ofs.close();
}

//��������ʱ�ĳ�ʼ����������Ҫ���ļ��ж�ȡ�ļ��������浽�ڴ���
void readfile(ContactNode &manager)
{
    ifstream ifs;
    ifs.open("userfile.txt", ios::in);

    //1.�ļ�������
    if (!ifs.is_open())
    {
        cout << "�ļ������ڣ�" << endl;
        Init(manager);
        manager->Size = 0; //��ʼ������
        ifs.close();
        return;
    }
    //2.��ȷ��ʼ��
    char name[20];
    char sex[20];
    int age;
    int phoneNumber;
    char address[20];

    Init(manager);
    manager->Size = 0;

    while (ifs >> name && ifs >> sex && ifs >> age && ifs >> phoneNumber && ifs >> address){
        ContactNode s = (Node *)malloc(sizeof(Node));

        strcpy(s->contact_data.name,name);
        strcpy(s->contact_data.sex,sex);
        s->contact_data.age=age;
        s->contact_data.phoneNumber=phoneNumber;
        strcpy(s->contact_data.address,address);
        s->next = manager->next;
        manager->next = s; //��ɽڵ������
        manager->Size++;
    }
    ifs.close();
    cout<<"�ļ���ʼ���ɹ�!"<<endl;
}

int main()
{
    ContactNode m;
    readfile(m);
    int select = 0;
    while (1)
    {
        showMenu();
        cin >> select;
        switch (select)
        {
        case 1:
            addContact(m);
            break;
        case 2:
            showContactList(m);
            break;
        case 3:
            delContactByName(m);
            break;
        case 4:
            findContactByName(m);
            break;
        case 5:
            updateContactByName(m);
            break;
        case 6:
            ClearManager(m);
            break;
        case 0:
            savefile(m);
            exitSys();
            break;
        }
    }
}