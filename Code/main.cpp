#include "Swap.h"

int main(int argc, char **argv){
    
    Swap myswap(10,20);
    myswap.printInfo();
    myswap.run();
    myswap.printInfo();


    std::cout << "_cplusplus:" << __cplusplus << std::endl;  // decide c++ standard
    std::cout << "_cplusplus:" << __cplusplus << std::endl;
    std::cout << "_cplusplus:" << __cplusplus << std::endl;
    return 0;
}