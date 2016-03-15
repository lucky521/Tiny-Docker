#define _GNU_SOURCE
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
} while (0)

char* const bash_args[] = {
    "/bin/sh",
    NULL
};

static int              /* Start function for cloned child */
childFunc(void *arg)
{
	struct utsname uts;
	char *child_name = "lu-container";
	int pid = getpid();
	char command_buffer[100];

	// configuration
	int cpu_per = 20000;
	char *memory_set = "500M";

	printf("#######################################################\n");
	printf("Welcome to container world!\n");

	// re-mount
	system("mount -t proc proc ./lu-container-root/proc");
	system("mount -t tmpfs cgroup_root ./lu-container-root/sys/fs/cgroup");
	// cpu cgroup
	system("mkdir ./lu-container-root/sys/fs/cgroup/cpu");
	system("mount -t cgroup cpu -ocpu ./lu-container-root/sys/fs/cgroup/cpu");
	system("test -d ./lu-container-root/sys/fs/cgroup/cpu/lu-container | mkdir -p ./lu-container-root/sys/fs/cgroup/cpu/lu-container");
	memset(command_buffer, 0, 100);
	sprintf(command_buffer, "echo %d >> ./lu-container-root/sys/fs/cgroup/cpu/lu-container/tasks", pid);
	system(command_buffer);
	memset(command_buffer, 0, 100);
	sprintf(command_buffer, "echo %d > ./lu-container-root/sys/fs/cgroup/cpu/lu-container/cpu.cfs_quota_us", cpu_per);
	system(command_buffer);
	// memory cgroup
	system("mkdir ./lu-container-root/sys/fs/cgroup/memory");
	system("mount -t cgroup -omemory memory ./lu-container-root/sys/fs/cgroup/memory");
	system("test -d ./lu-container-root/sys/fs/cgroup/memory/lu-container | mkdir -p ./lu-container-root/sys/fs/cgroup/memory/lu-container");
	memset(command_buffer, 0, 100);
	sprintf(command_buffer, "echo %d >> ./lu-container-root/sys/fs/cgroup/memory/lu-container/tasks", pid);
	system(command_buffer);
	memset(command_buffer, 0, 100);
	sprintf(command_buffer, "echo %s > ./lu-container-root/sys/fs/cgroup/memory/lu-container/memory.limit_in_bytes", memory_set);
	system(command_buffer);

	//chroot
	if( chdir("./lu-container-root") != 0  || chroot("./") != 0 || chdir("/") != 0)
		perror("chroot error");

	/* Change hostname in UTS namespace of child */
	if (sethostname(child_name, strlen(child_name)) == -1)
		errExit("sethostname");
	/* Retrieve and display hostname */
	if (uname(&uts) == -1)
		errExit("uname");
	printf("uts.nodename in child:  %s\n", uts.nodename);


	// run target process
	system("./test-program/hello");
//	system("./test-program/deadloop_1");
	execv(bash_args[0], bash_args); //change current process to bash

	/*
	printf("getpid = %d\n", getpid());
	printf("Shell command: \n");
	system("hostname");
	system("whoami");
	system("pwd");
	system("ls");
	system("ps -elf");
	*/

	/* Keep the namespace open for a while, by sleeping.
	   This allows some experimentation--for example, another
	   process might join the namespace. */
	sleep(10);
	return 0;           /* Child terminates now */
}

#define STACK_SIZE (1024 * 1024)    /* Stack size for cloned child */

int
main(int argc, char *argv[])
{
	char *stack;                    /* Start of stack buffer */
	char *stackTop;                 /* End of stack buffer */
	pid_t pid;
	struct utsname uts;

	/* Display hostname in parent's UTS namespace. This will be
	   different from hostname in child's UTS namespace. */
	if (uname(&uts) == -1)
		errExit("uname");
	printf("uts.nodename in parent: %s\n", uts.nodename);

	/* Allocate stack for child */
	stack = malloc(STACK_SIZE);
	if (stack == NULL)
		errExit("malloc");
	stackTop = stack + STACK_SIZE;  /* Assume stack grows downward */

	/* Create child that has its own UTS namespace;
	   child commences execution in childFunc() */
	pid = clone(childFunc, stackTop, CLONE_NEWUTS | CLONE_NEWPID | CLONE_NEWNS | SIGCHLD, NULL);
	if (pid == -1)
		errExit("clone");
	printf("clone() returned %ld\n", (long) pid);

	/* Parent falls through to here */
	sleep(1);           /* Give child time to change its hostname */

	if (waitpid(pid, NULL, 0) == -1)    /* Wait for child */
		errExit("waitpid");
	printf("child has terminated\n");
	printf("You leave container world.\n");
	printf("#######################################################\n");
	
	// clean job
	system("umount  ./lu-container-root/sys/fs/cgroup");

	exit(EXIT_SUCCESS);
}

