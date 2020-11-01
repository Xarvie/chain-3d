
#ifndef INC_3D5_PACKTOOL_H
#define INC_3D5_PACKTOOL_H


#include <iostream>
#include "Archives.h"
#include "ScanFile.h"

int packResource() {
    Archives a;
    std::set<HashCode> hashset;
    int ii = 0;
    {
        std::cout << "create data.0 file" << std::endl;
        if(a.createDataFile("../data.0")){
            std::cout << "error: createDatafile: data.0" << std::endl;
            return -1;
        }

        std::cout << "open ../data.0" << std::endl;
        a.openDataFile("../data.0");

        ScanFile scan;
        std::set<string> filePathSet;
        int ac = 2;
        char av0[] = "a.exe";
        char av1[] = "../resources";
        char *av[] = {av0, av1};
        scan.formatDir(ac, av, filePathSet);
        string fileOrFolderPath;
        int i = 0;
        for (auto it = filePathSet.begin(); it != filePathSet.end(); it++) {
            std::string str = *it;
            std::replace(str.begin(), str.end(), '\\', '/');
            str = str.substr(str.find("/resources/") + sizeof("/resources/")-1);
            std::cout << str << " start" << std::endl;
            std::vector<char> data = readFile(it->c_str());
//            if (data.size() == 0) {
//                std::cout << str << " error readFile" << std::endl;
//            }
//            if(str == std::string("/Users/xarvie/CLionProjects/untitled3/a/resourcefile1.txt"))
//            {
//                std::cout << std::endl;
//            }
            std::cout << str << " read" << std::endl;
            if (a.createFile(str.c_str(), data.data(), data.size()) < 0) {
                std::cout << str << " error createFile" << std::endl;
            }


//            i++;
//            if(i>1)
//            {
//
//
//            fseek(a.f, a.headMap[a.stringHash("/Users/xarvie/CLionProjects/untitled3/a/boom.png")].head.pos, SEEK_SET);
//            char aa[] = {0,0,0};
//            int ret = fread(aa,1,1,a.f);
//
//            std::cout << "pos"<< a.headMap[a.stringHash("/Users/xarvie/CLionProjects/untitled3/a/boom.png")].head.pos
//            <<" value: " << (int)aa[0]
//            << " rawdata[0]: " << (int)data[0]
//            << std::endl;
//            }
            //auto data2 = a.readFile(str.c_str());
            hashset.insert(a.stringHash(str.c_str()));
            ii++;
        }

    }
//    std::cout << a.headMap.size() << "-" << a.headList.size() << "-" <<a.headLayout.dataFileMaxSize<< a.headLayout.version<<a.headLayout.fileNum << "-" << a.fileMaxNum << "-"
//              << a.dataFileHeadMaxSize
//              << std::endl;
//    for (auto E:a.headList) {
//        std::cout << "E-" << E.head.id << E.head.size << E.head.pos << std::endl;
//    }
//    return 0;
//    a.close();
    a.headList.clear();
    a.headMap.clear();
    a.headParse();

//    std::cout << a.headMap.size() << "-" << a.headList.size() << "-" <<a.headLayout.dataFileMaxSize<< a.headLayout.version<<a.headLayout.fileNum << "-" << a.fileMaxNum << "-"
//              << a.dataFileHeadMaxSize
//              << std::endl;
//    for (auto E:a.headList) {
//        std::cout << "E-" << E.head.id << E.head.size << E.head.pos << std::endl;
//    }
    {
//        std::cout << "create data.0 file" << std::endl;
        //a.createDataFile("../data.0");

        int errorNum = 0;
        std::cout << "open ../data.0" << std::endl;
        a.openDataFile("../data.0");

        ScanFile scan;
        std::set<string> filePathSet;
        int ac = 2;
        char av1[] = "a.exe";
        char av2[] = "../resources";
        char *av[] = {av1, av2};
        scan.formatDir(ac, av, filePathSet);
        string fileOrFolderPath;


        for (auto it = filePathSet.begin(); it != filePathSet.end(); it++) {
            std::string str = *it;
            std::replace(str.begin(), str.end(), '\\', '/');
            str = str.substr(str.find("/resources/") + sizeof("/resources/")-1);
            std::cout << str << " start" << std::endl;
            std::vector<char> data = readFile(it->c_str());
            std::cout << str << " read" << std::endl;
            //a.createFile(str.c_str(), data.data(), data.size());
            auto data2 = a.readFile(str.c_str());

            for (size_t i = 0; i < data.size(); i++) {
                if (data[i] != data2[i]) {
                    std::cout << str << " check error" << "pos" << i << std::endl;
                    errorNum++;
                    break;
                } else {
                    std::cout << str << " check ok" << std::endl;
                    break;
                }
            }

            //std::cout << str << std::endl;
        }


        std::cout << hashset.size() << "-" << ii << "eNum::" << errorNum << std::endl;
    }
    exit(0);
    return 0;
}


#endif //INC_3D5_PACKTOOL_H
