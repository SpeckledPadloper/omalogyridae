#include <unistd.h>

int main ()
{
    write(2, "test to error\n", 14);
}