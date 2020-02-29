#include <iostream>
#include <cstdlib>

void create_map(int num_of_disks);
void check_args(int arg_count, char *a[]);

int num_of_disks = 3;

int main(int argc, char** argv)
{
    check_args(argc, argv);

    int arr[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    for(int i = 0; i < 3; i++) {
        for(int j = 0;j < 3; j++) {
            std::cout << arr[j][i] << "\t";
        }
        std::cout << std::endl;
    }

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
