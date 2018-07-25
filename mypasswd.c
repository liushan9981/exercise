//
// Created by liushan on 18-7-25.
//

#include <stdio.h>
#include <pwd.h>
#include <shadow.h>


void passwd_test(void)
{
    char * username = "liushan";
    struct passwd * ps_ptr;
    struct spwd * sp_ptr;

    ps_ptr = getpwnam(username);
    printf("%d %s %s %s\n", ps_ptr->pw_uid, ps_ptr->pw_name, ps_ptr->pw_dir, ps_ptr->pw_shell);

    ps_ptr = getpwuid(87);
    printf("%d %s %s %s\n", ps_ptr->pw_uid, ps_ptr->pw_name, ps_ptr->pw_dir, ps_ptr->pw_shell);
    printf("---------------\n");
    // 确保读取文件的位置定位到文件的开始处
    setpwent();
    while ( (ps_ptr = getpwent() ) != NULL)
    {
        printf("%d %s %s %s\n", ps_ptr->pw_uid, ps_ptr->pw_name, ps_ptr->pw_dir, ps_ptr->pw_shell);
    }
    // 关闭打开的文件
    endpwent();

    sp_ptr = getspnam(username);
    printf("%s    %s\n", sp_ptr->sp_namp, sp_ptr->sp_pwdp);

    printf("---------------\n");
    setspent();
    while ( (sp_ptr = getspent() ) != NULL)
        printf("%s    %s    %ld\n", sp_ptr->sp_namp, sp_ptr->sp_pwdp, sp_ptr->sp_lstchg);
    endspent();

}