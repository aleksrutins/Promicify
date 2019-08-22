#include <promicify.h>
#include <string>
#include <stdio.h>
using namespace Promicify;
using namespace std;

string readall(FILE *fp) {
    string buf;
    char ch = getc(fp);
    while(!(ch == EOF)) {
        buf += ch;
    }
    return buf;
}

string meth(Promise<string>::Resolve res, Promise<string>::Reject rej) {
        FILE *f;
        if(!(f = fopen("tst.txt", "r"))) {
            exit(1);
        }
        string contents = readall(f);
        res(contents);
}
int main() {
    Promise<string> prom = Promise<string>(&meth).then<void>([&](string val) {
        puts(val.c_str());
    });
    return 0;
}