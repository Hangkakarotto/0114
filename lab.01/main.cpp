#include <QCoreApplication>
#include <QDebug>
#include <QVector>
#include"student.h"
using namespace std;

int main()
{
    QVector<student> a(3);
    a[0].set(1403130209,"鲁智深",80,72);
    a[1].set(1403140101,"林冲",82,76);
    a[2].set(1403140102,"宋江",76,85);
    a[3].set(1403140103,"武松",88,80);
    qDebug()<<"未排序：";
    qDebug()<<"学号"<<"\t"<<"\t"<<"姓名"<<"\t"<<"\t"<<"课程1"<<"\t"<<"课程2";
    a[0].printtable();
    a[1].printtable();
    a[2].printtable();
    a[3].printtable();
    qDebug()<<"按照姓名排序：";
    std::sort(a.begin(),a.end(),student::name_sort);
    a[0].printtable();
    a[1].printtable();
    a[2].printtable();
    a[3].printtable();
    qDebug()<<"按课程1排序：";
    std::sort(a.begin(),a.end(),student::score1_sort);
    a[0].printtable();
    a[1].printtable();
    a[2].printtable();
    a[3].printtable();
    qDebug()<<"按课程2排序：";
    std::sort(a.begin(),a.end(),student::score2_sort);
    a[0].printtable();
    a[1].printtable();
    a[2].printtable();
    a[3].printtable();

    return 0;
}
