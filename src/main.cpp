#include <iostream>
#include "http.h"

/**
 * @brief main function
 *
 * This is the main function of the program.
 * In this function, an object of the class http is created,
 * which starts the RUN function, which waits for connections in an endless loop and processes them.
 *
 * @return 0
 */
int main()
{
    http http1;

    http1.RUN();

    return 0;
}