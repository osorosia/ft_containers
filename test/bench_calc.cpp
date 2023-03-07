#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#define END            "\033[0m"
#define BOLD           "\033[1m"
#define BLACK          "\033[30m"
#define RED            "\033[31m"
#define GREEN          "\033[32m"
#define YELLOW         "\033[33m"
#define BLUE           "\033[34m"
#define MAGENTA        "\033[35m"
#define CYAN           "\033[36m"
#define WHITE          "\033[37m"
#define UNDERLINE      "\033[4m"
#define BOLD_UNDERLINE "\033[1;4m"

using namespace std;

int main() {
    ifstream ft_ifs("./ft_bench.log");
    ifstream std_ifs("./std_bench.log");

    string ft_line;
    string std_line;

    for (long row = 0;; row++) {
        if (!getline(ft_ifs, ft_line))
            break;
        if (!getline(std_ifs, std_line))
            break;

        // 奇数行はテストケース名
        if (row % 2 == 0) {
            cout << YELLOW << left << setw(24) << ft_line << END << " ";
        }
        // 奇数行はクロック数
        else {
            double ft_clock  = stod(ft_line);
            double std_clock = stod(std_line);
            double amp       = ft_clock / std_clock;
            if (amp > 20)
                cout << RED;
            cout << amp << END << endl;
        }
    }
}