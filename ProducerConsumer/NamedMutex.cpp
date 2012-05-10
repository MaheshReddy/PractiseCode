#include"NamedMutex.h"
#include<stdio.h>
#include<iostream>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR;

bool check_create(const char *path,int flags);
bool test_if_exists(char *dir, char *file);

using namespace std;

/** 
  Only available constructor for NamedMutex. It does following things.
  1. checks if locks dir "lcks_path" exists if not creates it.
  2. checks if master_file of "lcks_path" exists if not create it.
  3. Sets the sem_name to the name of the semaphore.
  4. By default the lock is configured to be Multi-Process lock.
  */
NamedMutex::NamedMutex(const char* name){
	strcpy(lcks_path,LCKS_DIR);
	sprintf(master_file,"%s/%s",lcks_path,MSTR_FILE);
	locked = 0;
	lkType=false;
	lock_type = F_SETLKW;
	check_create(lcks_path,CRT_DIR);
	check_create(master_file,CRT_FIL);
	snprintf(sem_name,MAXPATHLEN,"%s",name);
}

/**
  Tries to acquire the lock on the master file of the lcks_path. Any program modifying the directory needs to grab this lock first
  first.
  */
int NamedMutex::lock_master(){
    struct flock flk = {F_WRLCK, SEEK_SET,   0,      0,     0 };
	if (isLlType()){
		flk.l_pid = (unsigned long)pthread_self();
	}
	else
		flk.l_pid = getpid();
	int r=0;
	if ((fd_master = open(master_file,O_WRONLY)) < 0){
		perror("NamedMutex::lock_master::open");
		return -1;
	}
	if ((r=fcntl(fd_master,F_SETLKW,&flk))<0){
		perror("NamedMutex::lock_master::fcntl");
		return -1;
	}
	//close(fd);
	return 0;
}
/**
  Releases the Master lock.
  */

int NamedMutex::unlock_master(){
    struct flock flk = {F_UNLCK, SEEK_SET,   0,      0,     0 };
	if (isLlType()){
		flk.l_pid = (unsigned long)pthread_self();
	}
	else
		flk.l_pid = getpid();
	int r=0;
	if (fd_master < 0){
		perror("NamedMutex::unlock_handle::open");
		return -1;
	}
	if ((r=fcntl(fd_master,F_SETLK,&flk))<0){
		perror("NamedMutex::unlock_handle::fcntl");
		return -1;
	}
	close(fd_master);
	return 0;
}

/**
  Checks in the handle is already been locked or not. If not just returns else calls unlock_handle unlock the handle.
  */
void NamedMutex::unlock(){
	if (!locked){
		return;
	}
	int r =0;
	if ((r=unlock_handle())<0)
		return ;
	locked=0;
	return;
}
/**
  Tries to acquire lock on the handle. If it fails then checks if the error was "EAGAIN", if yes then sleeps of 'timeout_secs' and tries to grab the lock again. If it fials returns as an error.
  */
void NamedMutex::lock(int timeout_secs){
	if (locked) // Already locked so retrun
		return;
	int r=0;
	lock_type = F_SETLK;
	if ((r=lock_master())<0)
		return;
	if ((r=set_handle())<0){
		unlock_master();
		return;
	}
	if ((r=unlock_master())<0)
		return;
	if((r = lock_handle())<0){ // If we couldn't get the lock sleep for timeout_secs and try again.
		if (errno == EAGAIN){
			sleep(timeout_secs);
			if ((r = lock_handle())<0){ // This time print error and return;
				perror("NamedMutex::lock::Timeout");
				return;
			}
		}
	}
	locked=1;
}

/** lock first tries to find a suitable handle for this instance, then creates a link for named semaphore, tries to acquire lock on the
  file, blocks till it acquires the lock.
  */
void NamedMutex::lock(){ 
	// Now before I create a new handle I need to lock the master since I don't want any one else to pick up the same
	// unique name for creating the handle.
	if (locked) // Already locked so retrun
		return;
	int r=0;
	lock_type = F_SETLKW;
	if ((r=lock_master())<0)
		return;
	if ((r=set_handle())<0){
		unlock_master();
		return;
	}
	if ((r=unlock_master())<0)
		return;
	if ((r = lock_handle())<0)
		return;
	locked=1;
}

int NamedMutex::unlock_handle(){
	//struct flock flk;// = { 0,0,0,F_UNLCK,SEEK_SET};
    struct flock flk = {F_UNLCK, SEEK_SET,   0,      0,     0 };
	//FLOCK_INIT(flk,F_UNLCK);
	if (isLlType()){
		flk.l_pid = (unsigned long)pthread_self();
	}
	else
		flk.l_pid = getpid();
	//flk.l_pid = getpid();
	int r=0;
	if (fd_handle < 0){
		perror("NamedMutex::unlock_handle::open");
		return -1;
	}
	if ((r=fcntl(fd_handle,F_SETLK,&flk))<0){
		perror("NamedMutex::unlock_handle::fcntl");
		return -1;
	}
	close(fd_handle);
	// I need to grab the master lock before unlinking it since I am modifying the directory
	lock_master();
	if ((r=unlink(handle))<0){
		perror("NamedMutex::unlock_handle::unlink");
		unlock_master();
		return -1;
	}
	unlock_master();
	return 0;
}

/**
  Tries to acquire the lock on the handle. It uses fcntl to lock the file. which blocks if it doesn't receive the lock.
  */
int NamedMutex::lock_handle(){
	//struct flock flk ;//= { 0,0,0,F_WRLCK,SEEK_SET};
    struct flock flk = {F_WRLCK, SEEK_SET,   0,      0,     0 };
	//FLOCK_INIT(flk,F_WRLCK);
	if (isLlType()){
		flk.l_pid = (unsigned long)pthread_self();
	}
	else
		flk.l_pid = getpid();
	//flk.l_pid = getpid();
	int r=0;
	if ((fd_handle = open(handle,O_WRONLY)) < 0){
		perror("NamedMutex::lock_handle::open");
		return -1;
	}
	if ((r=fcntl(fd_handle,lock_type,&flk))<0){
		perror("NamedMutex::lock_handle::fcntl");
		return -1;
	}
	//close(fd);
	return 0;
}

/**
   set_handle searches the lcks_path directory for the locks created using "sem_name" as root.
   if there exists a file It then tries to build an unique file name and link
   
  */

int NamedMutex::set_handle(){
	DIR * lcks_dir = opendir(lcks_path);
	int r=0;
	if (lcks_dir == NULL){
		perror("opendir");
		return -1;
	}
	struct dirent * lcks_ent = NULL;
	int no_ent = 0;
	while ((lcks_ent=readdir(lcks_dir))){
		if ( !strncmp(lcks_ent->d_name,sem_name,strlen(sem_name))){ 
			// Now I need to make sure of name is not substring of d_name
			int len = strlen(sem_name);
			if (lcks_ent->d_name[len] != '_' && lcks_ent->d_name[len] !='\0')
				continue;
			// Now I have a match, so I just create a new handl and link it with it.
			char uniq_name[MAXPATHLEN];
			do{
				snprintf(uniq_name,MAXPATHLEN,"%s_%ld",sem_name,(random() % MAX_LCKS));
			}while(test_if_exists(lcks_path,uniq_name));
			snprintf(handle,MAXPATHLEN,"%s/%s",lcks_path,uniq_name);
			char path_diren[MAXPATHLEN];
			sprintf(path_diren,"%s/%s",lcks_path,lcks_ent->d_name);
			if ((r = link(path_diren,handle))<0){
				perror("NamedMutex::set_handle::link");
				unlock_master();
					return -1;
			}
			no_ent++;
			break;
		}
	}
	if (!no_ent){ // means there is no lock file for this root file so create one
		snprintf(handle,MAXPATHLEN,"%s/%s",lcks_path,sem_name);
		//int fd = open(handle,O_CREAT|O_EXCL,mode);
		int fd = open(handle,O_CREAT|O_EXCL,mode);
		if (fd < 0){
			perror("NamedMutex::set_handle::open");
			return -1;
		}
		close(fd);
	}
	closedir(lcks_dir);
	return 0;
}

bool test_if_exists(char *dir, char *file){
	if ( dir == NULL or file == NULL)
		return false;
	int len = strlen(file);
	DIR *dirp = opendir(dir);
	struct dirent *dp;
	while ((dp = readdir(dirp)) != NULL){
		//if (dp->d_reclen == len && !strcmp(dp->d_name, file)) {
		if (!strcmp(dp->d_name, file)) {
			(void)closedir(dirp);
			return true;
		}
    }
	(void)closedir(dirp);
	return false;	
}


/**
  First checks if the current path exists , if it doesn't exits creates it and returns.
  */
bool check_create(const char *path,int flags){
	if (path == NULL)
		return -1;
	if (flags & CRT_DIR){
		int r =0 ;
		if ((r=mkdir(path,mode))<0){
			if (EEXIST == errno){
				return true;
			}
			else{
				perror("mkdir");
				return false;
			}
		}
	}
	else {
		int fd =-1; 
		if((fd=open(path,O_CREAT|O_EXCL|O_RDONLY,mode))<0){
			if (EEXIST == errno){
				return true;
			}
			else {
				perror("open");
				return false;
			}
			close(fd);
		}
	}
	return true;
}
