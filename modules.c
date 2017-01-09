#define _GNU_SOURCE // Give me asprintf
#include <dirent.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "modules.h"

int _bf_load_module(const char *filename){
    void *dlhandle;
    int (*mod_entry)(void);
    dlhandle = dlopen(filename, RTLD_LAZY | RTLD_GLOBAL); 
    if (!dlhandle){
        perror(dlerror());
    }
    mod_entry = dlsym(dlhandle, "bf_mod_load");
    return mod_entry();
}

int bf_load_mods(const char *directory){
    struct dirent *dirent;
    DIR *dir = opendir(directory);
    if (dir) {
        while (dirent = readdir(dir)) {
            if (dirent->d_type == DT_REG){
                char *fullpath;
                asprintf(&fullpath, "%s/%s", directory, dirent->d_name);
                _bf_load_module(fullpath);
                free(fullpath);
            }
        }
        closedir(dir);
    }
}

