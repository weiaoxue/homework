//
//  main.cpp
//  DataProcess
//
//  Created by 魏傲雪 on 2018/7/9.
//  Copyright © 2018年 魏傲雪. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
using namespace std;
const int N = 538;

class Info {
    int rank;
    int book_every_mon[13];  // the number of borrowed books every month
    int book_every_type[50];  // the number of borrowed books every type
    int library_every_mon[13];  // the number of going to library every month
    int library_every_hour[30];  // the number of going to library every hour
    double consume_every_pos[10];  // the money consumed every position
    double consume_every_mon[13];  // the money consumed every month
    double consume_every_hour[30];  // the money consumed every hour
    bool if_print_mon[3][13] = {
        0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
        0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1
    };
    bool if_print_hour[24] = {
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0
    };
    
public:
    Info() {
        memset(book_every_mon, 0,sizeof(book_every_mon));
        memset(book_every_type, 0,sizeof(book_every_type));
        memset(library_every_mon, 0,sizeof(library_every_mon));
        memset(library_every_hour, 0,sizeof(library_every_hour));
        memset(consume_every_pos, 0,sizeof(consume_every_pos));
        memset(consume_every_mon, 0,sizeof(consume_every_mon));
        memset(consume_every_hour, 0,sizeof(consume_every_hour));
    }
    
    void SetRank(int rank) {
        this->rank = rank;
    }
    
    void AddBookMon(int mon) {
        book_every_mon[mon]++;
    }
    
    void AddBookType(int type) {
        book_every_type[type]++;
    }
    
    void AddLibMon(int mon) {
        library_every_mon[mon]++;
    }
    
    void AddLibHour(int hour) {
        library_every_hour[hour]++;
    }
    
    void AddConsumePos(int pos, double money) {
        consume_every_pos[pos] += money;
    }
    
    void AddConsumeMon(int mon, double money) {
        consume_every_mon[mon] += money;
    }
    
    void AddConsumeHour(int hour, double money) {
        consume_every_hour[hour] += money;
    }
    
    void Print(fstream &f, int sem) {
        for (int i = 1; i <= 12; ++i)
            if (if_print_mon[sem][i])
                f << book_every_mon[i] << ",";
        for (int i = 1; i <= 42; ++i)
            f << book_every_type[i] << ",";
        for (int i = 1; i <= 12; ++i)
            if (if_print_mon[sem][i])
                f << library_every_mon[i] << ",";
        for (int i = 0; i < 24; ++i)
            if (if_print_hour[i])
                f << library_every_hour[i] << ",";
        for (int i = 1; i <= 7; ++i)
            f << consume_every_pos[i] << ",";
        for (int i = 1; i <= 12; ++i)
            if (if_print_mon[sem][i])
                f << consume_every_mon[i] << ",";
        for (int i = 0; i < 24; ++i)
            f << consume_every_hour[i] << ",";
    }
    
    void PrintRank(fstream &f) {
        f << rank;
    }
};

class Student {
    Info info[3];
    
public:
    Student() {}
    
    void SetRank(int sem, int rank) {
        info[sem - 1].SetRank(rank);
    }
    
    void AddBookMon(int sem, int mon) {
        info[sem - 1].AddBookMon(mon);
    }
    
    void AddBookType(int sem, int type) {
        info[sem - 1].AddBookType(type);
    }
    
    void AddLibMon(int sem, int mon) {
        info[sem - 1].AddLibMon(mon);
    }
    
    void AddLibHour(int sem, int hour) {
        info[sem - 1].AddLibHour(hour);
    }
    
    void AddConsumePos(int sem, int pos, double money) {
        info[sem - 1].AddConsumePos(pos, money);
    }
    
    void AddConsumeMon(int sem, int mon, double money) {
        info[sem - 1].AddConsumeMon(mon, money);
    }
    
    void AddConsumeHour(int sem, int hour, double money) {
        info[sem - 1].AddConsumeHour(hour, money);
    }
    
    void Print(fstream &f) {
        for (int i = 0; i < 3; ++i) {
            info[i].Print(f, i);
        }
        for (int i = 0; i < 3; ++i) {
            info[i].PrintRank(f);
            if (i == 2) f << endl;
            else f << ",";
        }
    }
};

Student student[600];
map<string, int> Type, Pos;
map<int, int> BookType;

int main(int argc, const char * argv[]) {
    char header[100], type[10], pos[10];
    int line, cnt,sem, id, rank, bookid, date, tim;
    double money;
    
    fstream f("train/grade.txt", ios::in);
    f.getline(header, 100);
    line = 0;
    while (f >> sem >> id >> rank) {
        line++;
        student[id].SetRank(sem, rank);
    }
    f.close();
    cout << "grade.txt line = " << line << endl;
    
    f.open("type.txt", ios::in);
    f.getline(header, 100);
    line = cnt = 0;
    Type.clear();
    BookType.clear();
    while (f >> bookid >> type) {
        line++;
        if (!Type[type]) Type[type] = ++cnt;
        if (!BookType[bookid]) BookType[bookid] = Type[type];
    }
    f.close();
    cout << "type.txt line = " << line << endl;
    line = 0;
    map<string, int>::iterator it = Type.begin();
    while (it != Type.end()) {
        cout << it->first << endl;
        line++;
        it++;
    }
    cout << "type num = " << line << endl;
    
    f.open("train/book.txt", ios::in);
    f.getline(header, 100);
    line = 0;
    while (f >> sem >> id >> bookid >> date) {
        line++;
        student[id].AddBookMon(sem, date / 100);
        student[id].AddBookType(sem, BookType[bookid]);
    }
    f.close();
    cout << "book.txtline = " << line << endl;
    
    f.open("train/guard.txt", ios::in);
    f.getline(header, 100);
    line = 0;
    while (f >> sem >> id >> date >> tim) {
        line++;
        student[id].AddLibMon(sem, date / 100);
        student[id].AddLibHour(sem, tim / 10000);
    }
    f.close();
    cout << "guard.txt line = " << line << endl;
    
    f.open("train/consumption.txt", ios::in);
    f.getline(header, 100);
    line = cnt = 0;
    Pos.clear();
    while (f >> sem >> id >> pos >> date >> tim >> money) {
        line++;
        if (!Pos[pos]) {
            Pos[pos] = ++cnt;
            cout << pos << endl;
        }
        if (money > 10000) {
            puts("hhh");
            continue;
        }
        student[id].AddConsumePos(sem, Pos[pos], money);
        student[id].AddConsumeMon(sem, date / 100, money);
        student[id].AddConsumeHour(sem, tim / 10000, money);
    }
    f.close();
    cout << "position num = " << cnt << endl;
    cout << "consumption.txt line = " << line << endl;
    
//    for (int i = 1; i <= 12; ++i) {
//        int cnt1 = 0, cnt2 = 0;
//        for (int j = 1; j <= N; ++j) {
//            if (student[j].info[0].book_every_mon[i] != 0) cnt1++;
//            if (student[j].info[1].book_every_mon[i] != 0) cnt2++;
//        }
//        cout << "book_every_mon " << i << ": cnt1 = " << cnt1 << ", cnt2 = " << cnt2 << endl;
//    }
//
//    for (int i = 1; i <= 42; ++i) {
//        int cnt1 = 0, cnt2 = 0;
//        for (int j = 1; j <= N; ++j) {
//            if (student[j].info[0].book_every_type[i] != 0) cnt1++;
//            if (student[j].info[1].book_every_type[i] != 0) cnt2++;
//        }
//        cout << "book_every_type " << i << ": cnt1 = " << cnt1 << ", cnt2 = " << cnt2 << endl;
//    }
//
//    for (int i = 1; i <= 12; ++i) {
//        int cnt1 = 0, cnt2 = 0;
//        for (int j = 1; j <= N; ++j) {
//            if (student[j].info[0].library_every_mon[i] != 0) cnt1++;
//            if (student[j].info[1].library_every_mon[i] != 0) cnt2++;
//        }
//        cout << "library_every_mon " << i << ": cnt1 = " << cnt1 << ", cnt2 = " << cnt2 << endl;
//    }
//
//    for (int i = 0; i < 24; ++i) {
//        int cnt1 = 0, cnt2 = 0;
//        for (int j = 1; j <= N; ++j) {
//            if (student[j].info[0].library_every_hour[i] != 0) cnt1++;
//            if (student[j].info[1].library_every_hour[i] != 0) cnt2++;
//        }
//        cout << "library_every_hour " << i << ": cnt1 = " << cnt1 << ", cnt2 = " << cnt2 << endl;
//    }
//
//    for (int i = 1; i <= 7; ++i) {
//        int cnt1 = 0, cnt2 = 0;
//        for (int j = 1; j <= N; ++j) {
//            if (student[j].info[0].consume_every_pos[i] != 0) cnt1++;
//            if (student[j].info[1].consume_every_pos[i] != 0) cnt2++;
//        }
//        cout << "consume_every_pos " << i << ": cnt1 = " << cnt1 << ", cnt2 = " << cnt2 << endl;
//    }
//
//    for (int i = 1; i <= 12; ++i) {
//        int cnt1 = 0, cnt2 = 0;
//        for (int j = 1; j <= N; ++j) {
//            if (student[j].info[0].consume_every_mon[i] != 0) cnt1++;
//            if (student[j].info[1].consume_every_mon[i] != 0) cnt2++;
//        }
//        cout << "consume_every_mon " << i << ": cnt1 = " << cnt1 << ", cnt2 = " << cnt2 << endl;
//    }
//
//    for (int i = 0; i < 24; ++i) {
//        int cnt1 = 0, cnt2 = 0;
//        for (int j = 1; j <= N; ++j) {
//            if (student[j].info[0].consume_every_hour[i] != 0) cnt1++;
//            if (student[j].info[1].consume_every_hour[i] != 0) cnt2++;
//        }
//        cout << "consume_every_hour " << i << ": cnt1 = " << cnt1 << ", cnt2 = " << cnt2 << endl;
//    }
    
    f.open("train.csv", ios::out);
    f << "id,sem1_book_every_mon1,sem1_book_every_mon9,sem1_book_every_mon10,sem1_book_every_mon11,sem1_book_every_mon12,sem1_book_every_type1,sem1_book_every_type2,sem1_book_every_type3,sem1_book_every_type4,sem1_book_every_type5,sem1_book_every_type6,sem1_book_every_type7,sem1_book_every_type8,sem1_book_every_type9,sem1_book_every_type10,sem1_book_every_type11,sem1_book_every_type12,sem1_book_every_type13,sem1_book_every_type14,sem1_book_every_type15,sem1_book_every_type16,sem1_book_every_type17,sem1_book_every_type18,sem1_book_every_type19,sem1_book_every_type20,sem1_book_every_type21,sem1_book_every_type22,sem1_book_every_type23,sem1_book_every_type24,sem1_book_every_type25,sem1_book_every_type26,sem1_book_every_type27,sem1_book_every_type28,sem1_book_every_type29,sem1_book_every_type30,sem1_book_every_type31,sem1_book_every_type32,sem1_book_every_type33,sem1_book_every_type34,sem1_book_every_type35,sem1_book_every_type36,sem1_book_every_type37,sem1_book_every_type38,sem1_book_every_type39,sem1_book_every_type40,sem1_book_every_type41,sem1_book_every_type42,sem1_library_every_mon1,sem1_library_every_mon9,sem1_library_every_mon10,sem1_library_every_mon11,sem1_library_every_mon12,sem1_library_every_hour7,sem1_library_every_hour8,sem1_library_every_hour9,sem1_library_every_hour10,sem1_library_every_hour11,sem1_library_every_hour12,sem1_library_every_hour13,sem1_library_every_hour14,sem1_library_every_hour15,sem1_library_every_hour16,sem1_library_every_hour17,sem1_library_every_hour18,sem1_library_every_hour19,sem1_library_every_hour20,sem1_library_every_hour21,sem1_library_every_hour22,sem1_consume_every_pos_shitang,sem1_consume_every_pos_jiaotong,sem1_consume_every_pos_chaoshi,sem1_consume_every_pos_sushe,sem1_consume_every_pos_jiaoshi,sem1_consume_every_pos_tushuguan,sem1_consume_every_pos_dayin,sem1_consume_every_mon1,sem1_consume_every_mon9,sem1_consume_every_mon10,sem1_consume_every_mon11,sem1_consume_every_mon12,sem1_consume_every_hour0,sem1_consume_every_hour1,sem1_consume_every_hour2,sem1_consume_every_hour3,sem1_consume_every_hour4,sem1_consume_every_hour5,sem1_consume_every_hour6,sem1_consume_every_hour7,sem1_consume_every_hour8,sem1_consume_every_hour9,sem1_consume_every_hour10,sem1_consume_every_hour11,sem1_consume_every_hour12,sem1_consume_every_hour13,sem1_consume_every_hour14,sem1_consume_every_hour15,sem1_consume_every_hour16,sem1_consume_every_hour17,sem1_consume_every_hour18,sem1_consume_every_hour19,sem1_consume_every_hour20,sem1_consume_every_hour21,sem1_consume_every_hour22,sem1_consume_every_hour23,sem2_book_every_mon2,sem2_book_every_mon3,sem2_book_every_mon4,sem2_book_every_mon5,sem2_book_every_mon6,sem2_book_every_mon7,sem2_book_every_type1,sem2_book_every_type2,sem2_book_every_type3,sem2_book_every_type4,sem2_book_every_type5,sem2_book_every_type6,sem2_book_every_type7,sem2_book_every_type8,sem2_book_every_type9,sem2_book_every_type10,sem2_book_every_type11,sem2_book_every_type12,sem2_book_every_type13,sem2_book_every_type14,sem2_book_every_type15,sem2_book_every_type16,sem2_book_every_type17,sem2_book_every_type18,sem2_book_every_type19,sem2_book_every_type20,sem2_book_every_type21,sem2_book_every_type22,sem2_book_every_type23,sem2_book_every_type24,sem2_book_every_type25,sem2_book_every_type26,sem2_book_every_type27,sem2_book_every_type28,sem2_book_every_type29,sem2_book_every_type30,sem2_book_every_type31,sem2_book_every_type32,sem2_book_every_type33,sem2_book_every_type34,sem2_book_every_type35,sem2_book_every_type36,sem2_book_every_type37,sem2_book_every_type38,sem2_book_every_type39,sem2_book_every_type40,sem2_book_every_type41,sem2_book_every_type42,sem2_library_every_mon2,sem2_library_every_mon3,sem2_library_every_mon4,sem2_library_every_mon5,sem2_library_every_mon6,sem2_library_every_mon7,sem2_library_every_hour7,sem2_library_every_hour8,sem2_library_every_hour9,sem2_library_every_hour10,sem2_library_every_hour11,sem2_library_every_hour12,sem2_library_every_hour13,sem2_library_every_hour14,sem2_library_every_hour15,sem2_library_every_hour16,sem2_library_every_hour17,sem2_library_every_hour18,sem2_library_every_hour19,sem2_library_every_hour20,sem2_library_every_hour21,sem2_library_every_hour22,sem2_consume_every_pos_shitang,sem2_consume_every_pos_jiaotong,sem2_consume_every_pos_chaoshi,sem2_consume_every_pos_sushe,sem2_consume_every_pos_jiaoshi,sem2_consume_every_pos_tushuguan,sem2_consume_every_pos_dayin,sem2_consume_every_mon2,sem2_consume_every_mon3,sem2_consume_every_mon4,sem2_consume_every_mon5,sem2_consume_every_mon6,sem2_consume_every_mon7,sem2_consume_every_hour0,sem2_consume_every_hour1,sem2_consume_every_hour2,sem2_consume_every_hour3,sem2_consume_every_hour4,sem2_consume_every_hour5,sem2_consume_every_hour6,sem2_consume_every_hour7,sem2_consume_every_hour8,sem2_consume_every_hour9,sem2_consume_every_hour10,sem2_consume_every_hour11,sem2_consume_every_hour12,sem2_consume_every_hour13,sem2_consume_every_hour14,sem2_consume_every_hour15,sem2_consume_every_hour16,sem2_consume_every_hour17,sem2_consume_every_hour18,sem2_consume_every_hour19,sem2_consume_every_hour20,sem2_consume_every_hour21,sem2_consume_every_hour22,sem2_consume_every_hour23,sem3_book_every_mon1,sem3_book_every_mon9,sem3_book_every_mon10,sem3_book_every_mon11,sem3_book_every_mon12,sem3_book_every_type1,sem3_book_every_type2,sem3_book_every_type3,sem3_book_every_type4,sem3_book_every_type5,sem3_book_every_type6,sem3_book_every_type7,sem3_book_every_type8,sem3_book_every_type9,sem3_book_every_type10,sem3_book_every_type11,sem3_book_every_type12,sem3_book_every_type13,sem3_book_every_type14,sem3_book_every_type15,sem3_book_every_type16,sem3_book_every_type17,sem3_book_every_type18,sem3_book_every_type19,sem3_book_every_type20,sem3_book_every_type21,sem3_book_every_type22,sem3_book_every_type23,sem3_book_every_type24,sem3_book_every_type25,sem3_book_every_type26,sem3_book_every_type27,sem3_book_every_type28,sem3_book_every_type29,sem3_book_every_type30,sem3_book_every_type31,sem3_book_every_type32,sem3_book_every_type33,sem3_book_every_type34,sem3_book_every_type35,sem3_book_every_type36,sem3_book_every_type37,sem3_book_every_type38,sem3_book_every_type39,sem3_book_every_type40,sem3_book_every_type41,sem3_book_every_type42,sem3_library_every_mon1,sem3_library_every_mon9,sem3_library_every_mon10,sem3_library_every_mon11,sem3_library_every_mon12,sem3_library_every_hour7,sem3_library_every_hour8,sem3_library_every_hour9,sem3_library_every_hour10,sem3_library_every_hour11,sem3_library_every_hour12,sem3_library_every_hour13,sem3_library_every_hour14,sem3_library_every_hour15,sem3_library_every_hour16,sem3_library_every_hour17,sem3_library_every_hour18,sem3_library_every_hour19,sem3_library_every_hour20,sem3_library_every_hour21,sem3_library_every_hour22,sem3_consume_every_pos_shitang,sem3_consume_every_pos_jiaotong,sem3_consume_every_pos_chaoshi,sem3_consume_every_pos_sushe,sem3_consume_every_pos_jiaoshi,sem3_consume_every_pos_tushuguan,sem3_consume_every_pos_dayin,sem3_consume_every_mon1,sem3_consume_every_mon9,sem3_consume_every_mon10,sem3_consume_every_mon11,sem3_consume_every_mon12,sem3_consume_every_hour0,sem3_consume_every_hour1,sem3_consume_every_hour2,sem3_consume_every_hour3,sem3_consume_every_hour4,sem3_consume_every_hour5,sem3_consume_every_hour6,sem3_consume_every_hour7,sem3_consume_every_hour8,sem3_consume_every_hour9,sem3_consume_every_hour10,sem3_consume_every_hour11,sem3_consume_every_hour12,sem3_consume_every_hour13,sem3_consume_every_hour14,sem3_consume_every_hour15,sem3_consume_every_hour16,sem3_consume_every_hour17,sem3_consume_every_hour18,sem3_consume_every_hour19,sem3_consume_every_hour20,sem3_consume_every_hour21,sem3_consume_every_hour22,sem3_consume_every_hour23,sem1_rank,sem2_rank,sem3_rank" << endl;
    for (int i = 1; i <= N; ++i) {
        f << i << ",";
        student[i].Print(f);
    }
    f.close();
    
    return 0;
}
