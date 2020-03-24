#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

void check_args(int arg_count, char *a[]);
void create_map(int disks_count);
void draw_map();
void check_available_moves();
void move_disk(int from, int to, int num_of_disks_tower_from, int num_of_disks_tower_to);
void choose_option();
void clear_option_arr();
bool win();

const int default_num_of_disks = 3;
int num_of_disks = default_num_of_disks;
int moves_counter = 0;

int num_of_disks_on_each_tower[3] = { default_num_of_disks, 0, 0 };

int arr[3][7];
int option[6];

int main(int argc, char** argv)
{
    check_args(argc, argv);
    create_map(num_of_disks);
    while(!win()) {
        draw_map();
        check_available_moves();
        std::cout << "\nMoves: " << moves_counter;
        choose_option();
    }
    draw_map();

    std::cout << "\n\nYeah, congratulations, you WON!\n"
              << "Score: " << moves_counter-1 << " moves\n";

    return 0;
}

void check_args(int arg_count, char *a[]) {
    int arg_content;
    if (arg_count > 1) {
        arg_content = atoi(a[1]);
        if (arg_content > default_num_of_disks && arg_content < 8) {
            num_of_disks = arg_content;
            num_of_disks_on_each_tower[0] = num_of_disks;
        }
    }
}

void create_map(int disks_count) {
    int map_val = 2; // the number of blocks for one disk must be even to make the whole structure symmetrical
    for(int i = 0; i < num_of_disks; i++){
        for(int j = 0; j < disks_count;j++) {
            arr[i][j] = i == 0 ? map_val : 0;
            map_val += 2;
        }
    }
}

void draw_map() {
    int longest_disk = num_of_disks*2;
    int current;
    int padding;

    for(int i = 0; i < num_of_disks; i++) {
        std::cout << std::string(2, ' '); // Distance between left frame and first tower
        for(int j = 0;j < 3; j++) {
            current = arr[j][i];
            padding = (longest_disk-current)/2;
            std::cout << std::string(padding, ' '); // Padding from the left of the disk
            for(int b = 0; b < arr[j][i];b++)
                std::cout << "#";
            std::cout << std::string(padding, ' '); // Padding from the right of the disk
            std::cout << std::string(2, ' '); // // Padding between disks
        }
        std::cout << "\n";
    }
    std::cout << std::string(2, ' ')
              << std::string(longest_disk, '-')
              << std::string(2, ' ')
              << std::string(longest_disk, '-')
              << std::string(2, ' ')
              << std::string(longest_disk, '-');
}

void check_available_moves(){
    int top_el_tower[] = {
        arr[0][num_of_disks - num_of_disks_on_each_tower[0]],
        arr[1][num_of_disks - num_of_disks_on_each_tower[1]],
        arr[2][num_of_disks - num_of_disks_on_each_tower[2]]
    };

    std::cout << "\n";

    int arr_index = 1;

    for(int i = 0; i < 3; i++)
        for(int j =0; j < 3;j++) {
            if((top_el_tower[i] < top_el_tower[j] || top_el_tower[j] == 0) && top_el_tower[i] != 0){
                std::cout << arr_index << ") " << i+1 << " -> " << j+1 << "\n";
                option[arr_index] = std::stoi(std::to_string(i+1) + std::to_string(j+1));
                arr_index++;
            }
        }
    std::cout << "\n" << 0 << ") Exit\n";
    option[0] = 9; // Exit game
}

void move_disk(int from, int to, int num_of_disks_tower_from, int num_of_disks_tower_to) {
    arr[to-1][num_of_disks - num_of_disks_tower_to-1] = arr[from-1][num_of_disks - num_of_disks_tower_from];
    arr[from-1][num_of_disks - num_of_disks_tower_from] = 0;
    num_of_disks_on_each_tower[from-1] -= 1;
    num_of_disks_on_each_tower[to-1] += 1;
    moves_counter++;
}

void choose_option() {
    int key;
    std::cout << "\n";
    do {
        std::cout << "Option: ";
        std::cin >> key;
        if(std::cin.fail()){ // If user inputs char/string instead of integer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while(std::cin.fail() || key > 10 || (option[key] == 0));

    if(option[key] == 9) {
        std::cout << "\nHave a nice day :D\n";
        exit(1);
    }

    int from = option[key] / 10;
    int to = option[key] % 10;
    std::cout << std::string((num_of_disks*2*3) + 6, '~') << "\n";
    move_disk(from, to, num_of_disks_on_each_tower[from-1], num_of_disks_on_each_tower[to-1]);
    clear_option_arr();
}

void clear_option_arr() {
    for(int i = 0; i < 7; i++) {
        option[i] = 0;
    }
}

bool win() {
    bool win = true;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < num_of_disks; j++) {
            if (arr[i][j] != 0)
                win = false;
        }
    }
    return win;
}

