//
// Copyright (c) 2011 Nutanix Inc. All rights reserved.
//
// The problem is to implement a file cache in C that implements the defined
// interface given below for struct 'file_cache'. The typical usage is for a
// client to call 'file_cache_pin_files()' to pin a bunch of files in the cache
// and then either read or write to their in-memory contents in the cache.
// Writing to a cache entry makes that entry 'dirty'. Before a dirty entry can
// be evicted from the cache, it must be unpinned and has to be cleaned by
// writing the corresponding data to disk.
//
// All files are assumed to have size 10KB. If a file doesn't exist to begin
// with, it should be created and filled with zeros - the size should be 10KB.
//
// 'file_cache' should be a thread-safe object that can be simultaneously
// accessed by multiple threads. If you are not comfortable with concurrent
// programming, then it may be single-threaded (see alternative in the
// file_cache_pin_files() comment). To implement the problem in its entirety
// may require use of third party libraries and headers. For the sake of
// convenience, it is permissible (although not preferred) to substitute
// external functions with stub implementations, but in doing so, please be
// clear what the intended behavior and side effects would be.
//
// Do not be overly concerned about portability. Pick your platform of choice
// (Nutanix develops on Linux) and be consistent.
//
// The problem is expected to take no longer than four hours (it is not
// necessary to work for that complete time). We'd rather see a stable and
// clean solution that implements a subset of the functionality than a
// complete but buggy one. There is no strict threshold on the time limit, so
// if you need a extra time to organize and improve the readability of your
// solution, please do so.
//
// If you have any questions, please email both brian@nutanix.com and
// bnc@nutanix.com. If no reply is received in a timely manner, please make a
// judgement call and state your assumptions in the code or response email.

#ifndef _NUTANIX_FILE_CACHE_H_
#define _NUTANIX_FILE_CACHE_H_

struct file_cache;

// Constructor. 'max_cache_entries' is the maximum number of files that can
// be cached at any time. If a background flusher thread is implemented, then
// 'dirty_time_secs' is the duration after which an unpinned, dirty file will
// be cleaned (flushed to disk) by a background thread.
file_cache *file_cache_construct(int max_cache_entries, int dirty_time_secs);

// Destructor. Flushes all dirty buffers and stops the background thread (if
// implemented).
void file_cache_destroy(file_cache *cache);

// Pins the given files in array 'files' with size 'num_files' in the cache.
// If any of these files are not already cached, they are first read from the
// local filesystem. If the cache is full, then some existing cache entries may
// be evicted. If no entries can be evicted (e.g., if they are all pinned, or
// dirty), then this method will block until a suitable number of cache
// entries becomes available. It is fine if more than one thread pins the
// same file, however the file should not become unpinned until both pins
// have been removed from the file.
//
// Correct usage of file_cache_pin_files() is assumed to be the caller's
// responsibility, and therefore deadlock avoidance doesn't need to be handled.
// The caller is assumed to pin all the files it wants using one
// file_cache_pin_files() call and not call multiple file_cache_pin_files()
// calls without unpinning those files in the interim.
//
// If you are not comfortable with multi-threaded programming or
// synchronization, this function may be modified to return a boolean if
// the requested files cannot be pinned due to the cache being full. However,
// note that entries in 'files' may already be pinned and therefore even a
// full cache may add additional pins to files.
void file_cache_pin_files(file_cache *cache,
                          const char **files,
                          int num_files);

// Unpin one or more files that were previously pinned. It is ok to unpin
// only a subset of the files that were previously pinned using
// file_cache_pin_files(). It is undefined behavior to unpin a file that wasn't
// pinned.
void file_cache_unpin_files(file_cache *cache,
                            const char **files,
                            int num_files);

// Provide read-only access to a pinned file's data in the cache.
//
// It is undefined behavior if the file is not pinned, or to access the buffer
// when the file isn't pinned.
const char *file_cache_file_data(file_cache *cache, const char *file);

// Provide write access to a pinned file's data in the cache. This call marks
// the file's data as 'dirty'. The caller may update the contents of the file
// by writing to the memory pointed by the returned value.
//
// It is undefined behavior if the file is not pinned, or to access the buffer
// when the file is not pinned.
char *file_cache_mutable_file_data(file_cache *cache, const char *file);

// Mark a file for deletion from the local filesystem. It may or may not be
// pinned. If it is pinned, then the deletion is delayed until after the file
// is unpinned.
void file_cache_delete_file(file_cache *cache, const char *file);

#endif  // _NUTANIX_FILE_CACHE_H_
