#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <iomanip>

using std::cout, std::cin, std::endl, std::string,
std::cerr, std::vector , std::setw , std::setfill ,std::internal ;
namespace FS = std::filesystem ;

bool exit_s = false;
bool change = false;

void command() {
    string command;
    cin >> command;

    if (command == "/exit")
      {
            exit(0);
        }
    else if (command == "/change") {
        system("cls");
        change = true;
        return;
    }
}

class Music {
private:
    string m_name;
    int m_number;

public:
    Music() = default;
    Music(int number, const string& name) : m_number(number), m_name(name) {}

    void play() const {
        cout<<setfill('-');
        cout<<setw(101)<<"\n";
        cout << m_name <<" is playing" << endl;
        PlaySound(m_name.c_str(), NULL, SND_FILENAME | SND_ASYNC);
        command();
    }

    string get_name() const { return m_name; }
    int get_number() const { return m_number; }
};

void open_file(const string& folder_path, vector<Music>& ms) {
    int index = 0;

    for (const auto& f : FS::directory_iterator(folder_path)) {
        if (f.is_regular_file()) {
            string filename = f.path().filename().string();
            if (filename.length() > 4 && filename.substr(filename.length() - 4) == ".wav") {
                ms.emplace_back(++index, filename);
                cout <<"\n"<<setw(30)<< index << "-" << filename << endl;
            }
        }
    }
}

int main() {

    vector<Music> ms;
    string folder_path;
    cout<<setfill('~')<<setw(70)<<"Hello it is a music player for wav"<<setw(40)<<"\n";
    cout<<setw(60)<<"Enter your music folder's address  :  "<<setfill(' ')<<setw(40);
    if(!change)
    {
    getline(cin, folder_path);
    open_file(folder_path, ms);
    }
    change = false;
    cout<<setw(40)<<"Enter a number to play music  :  ";
    int choice;
    cin>>choice;
    while(!change){
        ms.at(choice-1).play();
    }
    return main();
}
