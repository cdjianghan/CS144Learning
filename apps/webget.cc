#include "socket.hh"
#include "util.hh"

#include <cstdlib>
#include <iostream>

using namespace std;

void get_URL(const string &host, const string &path) {
    // Your code here.

    // You will need to connect to the "http" service on
    // the computer whose name is in the "host" string,
    // then request the URL path given in the "path" string.

    // Then you'll need to print out everything the server sends back,
    // (not just one call to read() -- everything) until you reach
    // the "eof" (end of file).

    //(+)
    //close-----关闭本进程的socket id，但链接还是开着的，用这个socket id的其它进程还能用这个链接，能读或写这个socket id
    //shutdown--则破坏了socket 链接，读的时候可能侦探到EOF结束符，写的时候可能会收到一个SIGPIPE信号，这个信号可能直到
    //socket buffer被填充了才收到，shutdown还有一个关闭方式的参数，0 不能再读，1不能再写，2 读写都不能。
    // Your code here.
    TCPSocket sk;
    sk.connect(Address(host,"http"));
    sk.write("GET "+path+" HTTP/1.1\r\nHOST: "+host+"\r\n\r\n");
    string response;
    while (sk.eof()==false)
    {
        response = sk.read();
        cout<<response;
    }
    sk.close();
}

int main(int argc, char *argv[]) {
    try {
        if (argc <= 0) {
            abort();  // For sticklers: don't try to access argv[0] if argc <= 0.
        }

        // The program takes two command-line arguments: the hostname and "path" part of the URL.
        // Print the usage message unless there are these two arguments (plus the program name
        // itself, so arg count = 3 in total).
        if (argc != 3) {
            cerr << "Usage: " << argv[0] << " HOST PATH\n";
            cerr << "\tExample: " << argv[0] << " stanford.edu /class/cs144\n";
            return EXIT_FAILURE;
        }

        // Get the command-line arguments.
        const string host = argv[1];
        const string path = argv[2];
        // Call the student-written function.
        get_URL(host, path);
    } catch (const exception &e) {
        cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
