//
// Created by liushan on 18-7-25.
//

#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>


void myuname(void)
{
    struct utsname name_ptr;
    char name[64];

    uname(&name_ptr);
    gethostname(name, 64);

    printf("%s    %s    %s    %s    %s\n",
           name_ptr.sysname, name_ptr.nodename, name_ptr.release, name_ptr.version, name_ptr.machine);
    printf("%s\n", name);

}