#include <common.h>
#include <command.h>
#include <ansi.h>
#include <menu.h>
#include <watchdog.h>
#include <malloc.h>
#include <linux/string.h>

static int do_my_cmd(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
    char *load_addr = NULL;
    char *img_name = NULL;
    char command[100];
    int errno;

    if (argc == 2)
    {
        img_name = argv[1];     //image name
        load_addr = "0x10000000"; // a well known addr which can be use
    }
    else if (argc == 3)
    {
        img_name = argv[1];
        load_addr = argv[2];
    }
    else
    {
        printf("%s", "Usage:\n\tbootfish arg1<Enter>\n\targ1: the image filename of barrelfish in the remote tftp server.");
    }

    //construct tftp commad
    errno = sprintf(command, "load mmc 0:1 %s %s", load_addr, img_name);
    if (errno == -1){
        printf("sprintf error!\n");
        return -1;
    }
    run_command(command, 0);

    //construct bootelf commad
    errno = sprintf(command, "bootefi %s", load_addr);
    if (errno == -1){
        printf("sprintf error!\n");
        return -1;
    }
    run_command(command, 0);

    /* never arrive here!*/
    return 0;
}

U_BOOT_CMD(
    bootfish, 2, 1, do_my_cmd,
    "Very fast way to boot barrelfish",
    "Usage:\n\tbootfish arg1<Enter>\n\targ1: the image filename of barrelfish in sd card.");
