#ifndef STUDENT_H
#define student_h
#include<QString>
#include<QDebug>
class student
{
   private:
      int xuehao;
      QString name;
      int score1;
      int score2;
public:
      student(){}
      void set (int xh,QString xm,int fs1,int fs2)
      {
        xuehao=xh;
        name=xm;
        score1=fs1;
        score2=fs2;
      }
      void printtable()
      {
          qDebug()<<xuehao<<name<<score1<<score2;

      }
      bool static name_sort(const student &m1,const student &m2){
          if(m1.name>m2.name)
              return 1;
          else
              return 0;

      }
      bool static score1_sort(const student &m1,const student &m2){
          if(m1.score1>m2.score2)
              return 1;
          else
              return 0;


      }
      bool static score2_sort(const student &m1,const student &m2){
          if(m1.score2>m2.score2)
              return 1;
          else
              return 0;
      }

}


#endif // STUDENT_H
