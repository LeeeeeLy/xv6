#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
    int pid, value;

    pid = atoi(argv[1]);
    value = atoi(argv[2]);

    setp(pid, value);
    exit();
}