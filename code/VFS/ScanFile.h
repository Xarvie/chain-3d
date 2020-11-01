//
// Created by xarvie on 2020/10/8.
//

#ifndef INC_3D4_SCANFILE_H
#define INC_3D4_SCANFILE_H

#include <set>
#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <errno.h>

#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#include <io.h>
#else

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#endif


using namespace std;

class ScanFile {
public:
#ifdef _WIN32
    #define SPL "\\"
#define SPLC '\\'
#else
#define SPL "/"
#define SPLC '/'
#endif
    static void pushFiles(string fileName, void *param) {
        if (param) {
            std::set<string> *pathSet = (std::set<string> *) param;
            pathSet->insert(fileName);
        }
    }

    void formatDir(int ac, char *arg[], std::set<string> &pathSet) {
#ifdef _WIN32
        char * tmpPwd = getcwd(NULL, 256);
        string pwd(tmpPwd);
        ::free(tmpPwd);

        for (int i = 0; i<ac; i++)
        {
            DWORD dwAttr = GetFileAttributes(arg[i]);
            if (dwAttr == INVALID_FILE_ATTRIBUTES)
                continue;
            if (dwAttr & FILE_ATTRIBUTE_DIRECTORY)
            {
                string s = arg[i];
                size_t len = strlen(arg[i]);
                if (len>1 && arg[i][len - 1] == SPLC)
                    arg[i][len - 1] = 0;
                ergodicFolder(arg[i], NULL, NULL, pushFiles, &pathSet);
            }
            else
            {
                pathSet.insert(arg[i]);
            }
        }
        if (ac < 2)
        {
            ergodicFolder(pwd, NULL, NULL, pushFiles, &pathSet);
        }
#else
        char *tmpPwd = getcwd(NULL, 100);
        string pwd(tmpPwd);
        free(tmpPwd);
        struct stat st;
        for (int i = 0; i < ac; i++) {
            if (0 == lstat(arg[i], &st)) {
                if (S_ISDIR(st.st_mode)) {
                    string s = arg[i];

                    size_t len = strlen(arg[i]);
                    if (len > 1 && arg[i][len - 1] == SPLC)
                        arg[i][len - 1] = 0;
                    //cout << arg[i] << "  " << len << endl;

                    ergodicFolder(arg[i], NULL, NULL, ScanFile::pushFiles, &pathSet);

                } else {
                    pathSet.insert(arg[i]);
                }
            }
        }

        if (ac < 2) {
            ergodicFolder(pwd, NULL, NULL, ScanFile::pushFiles, &pathSet);
        }
#endif
    }

    void ergodicFolder(string folderPath, void(*dirFunc)(string dir, void *param), void *folderParam,
                       void(*fileFunc)(string file, void *param), void *fileParam) {
#ifdef _WIN32

        _finddata_t fileData;
        string strfind = folderPath + "\\*";

        intptr_t handle = _findfirst(strfind.c_str(), &fileData);
        if (handle == -1L)
        {
            cerr << "文件打开失败" << errno << endl;
            exit(-1);
        }
        do
        {
            if (fileData.attrib & _A_SUBDIR)
            {
                if ((strcmp(fileData.name, ".") != 0) && (strcmp(fileData.name, "..") != 0))
                {
                    string newPath = folderPath + "\\" + fileData.name;
                    if (dirFunc) dirFunc(newPath, folderParam);
                    ergodicFolder(newPath, dirFunc, folderParam, fileFunc, fileParam);
                }
            }
            else
            {
                string filename = (folderPath + "\\" + fileData.name);
                if (fileFunc) fileFunc(filename, fileParam);
            }
        } while (!_findnext(handle, &fileData));
        _findclose(handle);

#else
        DIR *dp;
        struct dirent *entry;
        struct stat statBuf;
        if ((dp = opendir(folderPath.c_str())) == NULL) {
            char *tmpPwd = getcwd(NULL, 100);
            string pwd(tmpPwd);
            free(tmpPwd);
            fprintf(stderr, "cannot open directory: %s\n%s\n", folderPath.c_str(), pwd.c_str());
            return;
        }

        while (NULL != (entry = readdir(dp))) {
            string tmpdir = folderPath + SPL + entry->d_name;
            if (lstat(tmpdir.c_str(), &statBuf) == 0) {
                if (S_ISDIR(statBuf.st_mode)) {
                    if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
                        continue;
                    if (dirFunc)
                        dirFunc(tmpdir, folderParam);
                    ergodicFolder(tmpdir, dirFunc, folderParam, fileFunc, fileParam);
                } else {
                    string filename = folderPath + SPL + entry->d_name;
                    if (fileFunc)
                        fileFunc(filename, fileParam);
                }
            }
        }

        closedir(dp);
#endif
    }

};


#endif //INC_3D4_SCANFILE_H
