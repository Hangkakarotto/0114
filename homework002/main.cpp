#include <QDebug>
#include <QList>
#include <QTextStream>
#include <QString>
#include <QFile>
namespace SK {
enum SortKind{
    col01    =   0x00000001<<0,         //!< 第1列
    col02    =   0x00000001<<1,         //!< 第2列
    col03    =   0x00000001<<2,         //!< 第3列
    col04    =   0x00000001<<3,         //!< 第4列
    col05    =   0x00000001<<4,         //!< 第5列
    col06    =   0x00000001<<5,         //!< 第6列
    col07    =   0x00000001<<6,         //!< 第7列
    col08    =   0x00000001<<7,         //!< 第8列
    col09    =   0x00000001<<8,         //!< 第9列
    col10    =   0x00000001<<9,         //!< 第10列
    col11    =   0x00000001<<10,        //!< 第11列
    col12    =   0x00000001<<11,        //!< 第12列
    col13    =   0x00000001<<12,        //!< 第13列
    col14    =   0x00000001<<13,        //!< 第14列
    col15    =   0x00000001<<14,        //!< 第15列
    col16    =   0x00000001<<15,        //!< 第16列
    col17    =   0x00000001<<16,        //!< 第17列
    col18    =   0x00000001<<17,        //!< 第18列
    col19    =   0x00000001<<18,        //!< 第19列
    col20    =   0x00000001<<19,        //!< 第20列
    col21    =   0x00000001<<20,        //!< 第21列
    col22    =   0x00000001<<21,        //!< 第22列
    col23    =   0x00000001<<22,        //!< 第23列
    col24    =   0x00000001<<23,        //!< 第24列
    col25    =   0x00000001<<24,        //!< 第25列
    col26    =   0x00000001<<25,        //!< 第26列
    col27    =   0x00000001<<26,        //!< 第27列
    col28    =   0x00000001<<27,        //!< 第28列
    col29    =   0x00000001<<28,        //!< 第29列
    col30    =   0x00000001<<29,        //!< 第30列
    col31    =   0x00000001<<30,        //!< 第31列
    col32    =   0x00000001<<31,        //!< 第32列
};
}

typedef struct
{
    QStringList stu;

} stuData;

QDebug operator<< (QDebug d, const stuData &data)
{
   QDebugStateSaver saver(d);
   for(int i=0;i<data.stu.size();i++)
    {
        d.noquote().nospace()<<data.stu.at(i)<<"\t";
    }
       return d;
}

class myCmp//比较类，用于std::sort第三参数
{
public:
    myCmp(int selectedColumn)
    {
        currentColumn = selectedColumn;
    }
    bool operator() (const stuData& d1,const stuData& d2);
private:
    int currentColumn;
};
#define rather(m)  (d1.stu.at(m)>=d2.stu.at(m))? 1:0

bool myCmp::operator()(const stuData &d1, const stuData &d2)
{
    bool result = false;
        quint32 sortedColumn = 0x00000001<<currentColumn;
        switch (sortedColumn)
        {
            case SK::col01: result=rather(1);break;
            case SK::col02: result=rather(2);break;
            case SK::col03: result=rather(3);break;
            case SK::col04: result=rather(4);break;
            case SK::col05: result=rather(5);break;
            case SK::col06: result=rather(6);break;
            case SK::col07: result=rather(7);break;
            case SK::col08: result=rather(8);break;
            case SK::col09: result=rather(9);break;
            case SK::col10: result=rather(10);break;
            case SK::col11: result=rather(11);break;
            case SK::col12: result=rather(12);break;
            case SK::col13: result=rather(13);break;
            case SK::col14: result=rather(14);break;
            case SK::col15: result=rather(15);break;
            case SK::col16: result=rather(16);break;

            default:break;

        }
        return result;
}


class ScoreSorter
{
public:
    ScoreSorter(QString dataFile);
    void readFile();
    void doSort();
private:
    QString data_file;
    QList<stuData> data;
    stuData tablelist;
    void print_file(int col);
};

ScoreSorter::ScoreSorter(QString dataFile)
{
    data_file=dataFile;
}

void ScoreSorter::readFile()
{
    QFile file(data_file);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<QString("failing to open the file:%1").arg(data_file);
    }

    QString title(file.readLine());
    tablelist.stu= title.split(" ", QString::SkipEmptyParts);
    if((tablelist.stu).last() == "\n") tablelist.stu.removeLast();
    stuData gooddata;
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        gooddata.stu = str.split(" ", QString::SkipEmptyParts);
        if((gooddata.stu).last() == "\n")
        {
            gooddata.stu.removeLast();
        }
        if(gooddata.stu.size()==0) continue;
        this->data.append(gooddata);
    }
    file.close();
}

void ScoreSorter::doSort()
{
    for(int i=1;i<tablelist.stu.size();i++)
    {
        myCmp cmp(i-1);
        std::sort(data.begin() , data.end() ,cmp );
        qDebug()<<"排序后输出，当前排序第"<<i+1<<"列:";
        qDebug() << "   "<<(tablelist)<<"\t";
        for(int i=0;i<data.size();i++)
        {
            qDebug()<<data.at(i)<<"\t";
        }
        qDebug()<<"\n";
        this->print_file(i+1);
    }
}

void ScoreSorter::print_file(int col)
{
    QFile file("sorted_"+data_file);
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream<<QString("排序后输出，当前排序第")<<col<<QString("列:");
    stream<<"\t";
    for(int j=0;j<tablelist.stu.size();j++)
        stream<<tablelist.stu.at(j)<<"\t";
    stream<<"------------------------------------------------";
    for(int i=0;i<data.size();i++)
    {
        for(int j=0;j<tablelist.stu.size();j++)
            stream<<data.at(i).stu.at(j)<<"\t";
        stream<<"\r\n";
    }
    stream<<"-------------------------------------------------";
    file.close();
}

int main()
{
    QString datafile = "data.txt";
    QFile f("sorted_"+datafile);
    if (f.exists())
    {
        f.remove();
    }
    ScoreSorter s(datafile);
    s.readFile();
    s.doSort();
    return 0;
}
