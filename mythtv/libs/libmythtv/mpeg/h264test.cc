
#include <H264Parser.h>
#include <cstring>
#include <cerrno>

#include <fstream>
#include <iostream>


using namespace std;

const int BUF_SZ = 188 * 1000;

int main (int argc, char *argv[])
{
    H264Parser      parser;
    ifstream        input;
    uint8_t         buffer[BUF_SZ];

    int             p1, p2, sz, cnt, total;
    int             frame_cnt = 0;

    if (argc < 2)
    {
        cout << "Expecting filename as argument.\n";
        return 1;
    }

    input.open(argv[1]);
    if (!input.is_open())
    {
        cerr << "Failed to open '" << argv[1] << "':\n"
             << strerror(errno) << '\n';
        return -2;
    }

    p1 = p2 = 0;
    total = 0;
    sz = BUF_SZ;

    for (;;)
    {
        input.read(reinterpret_cast<char *>(&buffer[p1]), sz);
        if ((p2 = input.gcount()) == 0)
            break;

        cnt = parser.addBytes(buffer, p1 + p2, total);

        cout << "Total=" << total;
        if (parser.stateChanged())
        {
            if (parser.onFrameStart() &&
                parser.FieldType() != H264Parser::FIELD_BOTTOM)
            {
                ++frame_cnt;
                cout << " onKeyFrameStart = " << parser.onKeyFrameStart();
            }
            else if (parser.onFrameStart())
                cout << " onFrameStart";
        }
        cout << endl;

        total += cnt;

        p1 = BUF_SZ - cnt;
        memmove(buffer, &buffer[cnt], p1);
        sz = BUF_SZ - p1;
    }

    cout << "\n" << frame_cnt << " Frames.\n";

    return 0;
}
