#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <time.h>

using namespace std;

class Log
{

private:
    Log(){
        ofstream fout("C:\\Dropbox\\Log.txt", ios_base::app);
        fout << "\n\n\n";
        time_t t;
        t = time(0);
        fout << "Logger's work start at ";
        fout << ctime(&t);
        fout.close();
    }

    static Log* logger;

public:
    static Log* getInstanse(){
        if (!logger){
            logger = new Log();
        }

        return logger;
    }

    template<typename T>
    void write(T argv){
        ofstream fout("C:\\Dropbox\\Log.txt", ios_base::app);
        fout << argv;
        fout.close();
    }

    template<typename T>
    void writeln(T argv){
        ofstream fout("C:\\Dropbox\\Log.txt", ios_base::app);
        fout << argv;
        fout << "\n";
        fout.close();
    }
};

Log* Log::logger = 0;


#endif // LOG_H
