#include <iostream>
#include <cstdlib>
#include <string>

void check_args(int arg_count, char *a[]);
void create_map(int disks_count);
void draw_map();

int num_of_disks = 3;
int arr[3][7];


int main(int argc, char** argv)
{
    check_args(argc, argv);
    create_map(num_of_disks);
    draw_map();

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


