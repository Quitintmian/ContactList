#include <iostream>
#include <malloc.h>
#include <string.h>
#include <fstream>
using namespace std;

//这是一个通过链表实现的通讯录,最终完成与2020年10月27日11：43：27.

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
//以上是功能实现的函数申明

void showMenu()
{
    cout << "****************************************" << endl;
    cout << "**************1、添加联系人**************" << endl;
    cout << "**************2、显示联系人**************" << endl;
    cout << "**************3、删除联系人**************" << endl;
    cout << "**************4、查找联系人**************" << endl;
    cout << "**************5、修改联系人**************" << endl;
    cout << "**************6、清空联系人**************" << endl;
    cout << "**************0、保存文件并退出系统****************" << endl;
    cout << "****************************************" << endl;
    cout << "------> 请选择操作项并输入操作项编号：" << endl;
}

void exitSys()
{
    cout << "欢迎下次使用，再见！" << endl;
    system("pause");
    exit(0);
}

void Init(ContactNode &manager) //初始化链表
{
    manager = (Node *)malloc(sizeof(Node));
    manager->next = NULL;
}

void printContactInfo(Contact *p)
{
    cout << "姓名：" << p->name << "   性别：" << p->sex << "   年龄：" << p->age << "   联系电话：" << p->phoneNumber << "   家庭地址：" << p->address << endl;
} //该输出用于屏幕输出

void addContact(ContactNode &manager)//头插法
{
    ContactNode s = (Node *)malloc(sizeof(Node)); //申请一片节点空间,而且sizeof后不能为ContactNode，若设置为struct ContactManager则没问题
    cout << "请输入联系人的姓名：";
    cin >> s->contact_data.name;
    cout << "请输入联系人的性别：";
    cin >> s->contact_data.sex;
    cout << "请输入联系人的年龄：";
    cin >> s->contact_data.age;
    cout << "请输入联系人号码：";
    cin >> s->contact_data.phoneNumber;
    cout << "请输入联系人的地址：";
    cin >> s->contact_data.address;
    s->next = manager->next;
    manager->next = s; //完成节点的连接
    manager->Size++;
    system("pause");
    system("cls");
}

void showContactList(ContactNode manager)
{
    if (manager->Size == 0)
    {
        cout << "没有联系人！" << endl;
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
    ContactNode pre = manager; //设置两个指针，便于删除与插入
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
    cout << "请输入要删除的联系人的姓名：";
    char name[20];
    cin >> name;
    ContactNode pos = isExist(manager, name); //判断联系人在链表中是否存在，若存在并返回它的前继指针，不存在则返回NULL
    if (pos == NULL)
    {
        cout << "联系人不存在！" << endl;
        system("pause");
        system("cls");
        return;
    }
    else
    {
        ContactNode d = pos->next; //d为待删除节点
        pos->next = pos->next->next;
        free(d);
        cout << "删除完成！" << endl;
        manager->Size--;
        system("pause");
        system("cls");
    }
}

void findContactByName(ContactNode manager)
{
    cout << "请输入要查找的联系人的姓名：";
    char name[20];
    cin >> name;
    ContactNode pos = isExist(manager, name);
    if (pos == NULL)
    {
        cout << "联系人不存在！" << endl;
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
    cout << "请输入你要修改的联系人的姓名：";
    char name[20];
    cin >> name;
    ContactNode pos = isExist(manager, name);
    if (pos == NULL)
    {
        cout << "联系人不存在！" << endl;
        system("pause");
        system("cls");
        return;
    }
    else
    {
        cout << "请输入联系人的姓名：";
        cin >> pos->next->contact_data.name;
        cout << "请输入联系人的性别：";
        cin >> pos->next->contact_data.sex;
        cout << "请输入联系人的年龄：";
        cin >> pos->next->contact_data.age;
        cout << "请输入联系人号码：";
        cin >> pos->next->contact_data.phoneNumber;
        cout << "请输入联系人的地址：";
        cin >> pos->next->contact_data.address;
        cout << "修改完成！" << endl;
        system("pause");
        system("cls");
    }
}

void ClearManager(ContactNode &manager) //不释放头节点，只释放后继的所有节点
{
    ContactNode p = manager->next;
    ContactNode pre = p;
    while (p != NULL)
    {
        p = p->next;
        free(pre); //释放
        pre = p;
    }
    free(pre);
    manager->Size = 0;
    manager->next = NULL;
    cout << "联系人已清空！" << endl;
    system("pause");
    system("cls");
}

//保存文件部分
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
            << fp->contact_data.address << endl; //以空格为分界符，分别读取
        fp = fp->next;
    }

    ofs.close();
}

//程序启动时的初始化操作，需要从文件中读取文件，并保存到内存中
void readfile(ContactNode &manager)
{
    ifstream ifs;
    ifs.open("userfile.txt", ios::in);

    //1.文件不存在
    if (!ifs.is_open())
    {
        cout << "文件不存在！" << endl;
        Init(manager);
        manager->Size = 0; //初始化链表
        ifs.close();
        return;
    }
    //2.正确初始化
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
        manager->next = s; //完成节点的连接
        manager->Size++;
    }
    ifs.close();
    cout<<"文件初始化成功!"<<endl;
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