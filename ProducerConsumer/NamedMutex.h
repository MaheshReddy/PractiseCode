#ifndef NAMED_MUTEX
#define NAMED_MUTEX

#define CRT_DIR 0x1
#define CRT_FIL 0x2

#define MAX_LCKS 20000

#define MAXPATHLEN 1024

#define LCKS_DIR "/tmp/namedsems"

#define MSTR_FILE "master_lck"

#define MAXNAMELEN 30

using namespace std;
class NamedMutex{
	private:
	// Whenever the process tries to lock, an unique handle is created. All the handles of a NamedMutex are linked.
	char handle[MAXPATHLEN];
	char sem_name[MAXPATHLEN];
	// The directory to store files used for locking
	char lcks_path[MAXPATHLEN];
	// The master file used to synchronize access to lcks_path directory.
	char master_file[MAXPATHLEN];
	// Flag indicating if the lock is acquired or not.
	bool locked;
	// If lkType is set then it is a multi-thread lock else by default its multi-process lock
	bool lkType;
	int fd_handle;
	int fd_master;
	int lock_type;
	int set_handle();
	int lock_handle();
	int unlock_handle();
	int lock_master();
	int unlock_master();
	public:
	NamedMutex(const char* name);
	void lock(void);
	void lock(int time_out);
	void unlock();
	bool isLocked(){return locked;};
	void setlkType() {lkType = true; };
	bool isLlType(){return lkType;};
};
#endif
