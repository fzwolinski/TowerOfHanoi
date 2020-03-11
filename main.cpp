#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>


void check_args(int arg_count, char *a[]);
void create_map(int disks_count);
void draw_map();
void check_available_moves();
void move_disk(int from, int to, int num_of_disks_tower_from, int num_of_disks_tower_to);
void choose_option();
void clear_option_arr();

const int default_num_of_disks = 5;
int num_of_disks = default_num_of_disks;

int num_of_disks_on_each_tower[3] = { default_num_of_disks, 0, 0 };
int arr[3][7];
std::string option[6];

int main(int argc, char** argv)
{
    check_args(argc, argv);
    create_map(num_of_disks);
    draw_map();
    check_available_moves();
    choose_option();

    return 0;
}

void check_args(int arg_count, char *a[]) {
    int arg_content;
    if (arg_count > 1) {
        arg_content = atoi(a[1]);
        if (*a[1] > 3 && *a[1] < 8) {
            num_of_disks = arg_content;
        }
    }
}

void create_map(int disks_count) {
    int map_val = 2; // the number of blocks for one disk must be even to make the whole structure symmetrical
    /*
   ##
  ####
 ######
########

    {2, 4, 6, 8, 10, 0 , 0},
    {0, 0, 0, 8, 10, 0 , 0},
    {0, 4, 6, 8, 10, 0 , 0},

    */
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < disks_count;j++) {
            arr[i][j] = i == 0 ? map_val : 0;
            map_val += 2;
        }
    }
}

void draw_map() {
    int how_many_spaces = num_of_disks;
    int next;
    int next_should_have;

    for(int i = 0; i < num_of_disks; i++) {
        for(int j = 0;j < 3; j++) {
            next = arr[j][i];
            next_should_have = (i+1)*2;
            if (next_should_have != next ) {
                std::cout << std::string((next_should_have-next)/2, ' ');
            }

            std::cout << std::string(how_many_spaces, ' ');

            for(int b = 0; b < arr[j][i];b++)
                std::cout << "#";
            if (arr[j][i] == 0)     // In case there is no disk at this place
                std::cout << "\t";

            std::cout << " \t";

        }
        how_many_spaces = how_many_spaces != 0 ? how_many_spaces-1 : 0;
        std::cout << std::endl;
    }
    //std::cout << "-----";

}

void check_available_moves(){
    int top_el_tower_1 = arr[0][num_of_disks - num_of_disks_on_each_tower[0]];
    int top_el_tower_2 = arr[1][num_of_disks - num_of_disks_on_each_tower[1]];
    int top_el_tower_3 = arr[2][num_of_disks - num_of_disks_on_each_tower[2]];

    std::cout << "\n";

    // Check moves for Tower 1
    if (top_el_tower_1 > top_el_tower_2) {
        std::cout << "1) 1 -> 2\n";
        option[1] = "12";
    }
    if (top_el_tower_1 > top_el_tower_3) {
        std::cout << "2) 1 -> 3\n";
        option[2] = "13";
    }

    // Check moves for Tower 2
    if (top_el_tower_2 > top_el_tower_1) {
        std::cout << "3) 2 -> 1\n";
        option[3] = "21";
    }
    if (top_el_tower_2 > top_el_tower_3) {
        std::cout << "4) 2 -> 3\n";
        option[4] = "23";
    }

    // Check moves for Tower 3
    if (top_el_tower_3 > top_el_tower_1) {
        std::cout << "5) 3 -> 1\n";
        option[5] = "31";
    }
    if (top_el_tower_3 > top_el_tower_2) {
        std::cout << "6) 3 -> 2\n";
        option[6] = "32";
    }
}

void move_disk(int from, int to, int num_of_disks_tower_from, int num_of_disks_tower_to) {
    arr[to-1][num_of_disks - num_of_disks_tower_to-1] = arr[from-1][num_of_disks - num_of_disks_tower_from];
    arr[from-1][num_of_disks - num_of_disks_tower_from] = 0;
    num_of_disks_on_each_tower[from-1] -= 1;
    num_of_disks_on_each_tower[to-1] += 1;

    std::cout << "\n\n";

    draw_map();

    //check_available_moves();
}

void choose_option() {
    char key;

    do {
        std::cout << "\nOption: ";
        std::cin >> key;
    } while((option[key - '0'] == ""));

    int from = option[key - '0'][0] - '0';
    int to = option[key - '0'][1] - '0';
    move_disk(from, to, num_of_disks_on_each_tower[from-1], num_of_disks_on_each_tower[to-1]);
    clear_option_arr();
}

void clear_option_arr() {
    for(int i = 0; i < 7; i++) {
        option[i].clear();
    }
}



