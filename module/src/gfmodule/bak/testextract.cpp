
#include <stdio.h>
#include <string>
#include "geoshape.h"
#include "GFimg.h"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
using namespace boost::filesystem;
std::vector<std::string> vector_files;

void printUsage()
{
        printf("Usage: \n  testdis <your_path> <save_path>\n <your_path> mean the directory where you save the Gao Fen image!\n <save_path> mean the directory where you want to save the result!\n<year> mean the year you want to extract\n  ");

}
int main(int argc, char * argv[])
{
    if(argc<4)
    {
        printf("need input the directory\n");printUsage();
        return 0;
    }
    if(argc>4)
    {
        printf("Do not input more than two dicectory\n");
    }
    std::string year= argv[3];
    std::string full_path = argv[1];
    std::string savepath = std::string(argv[2]);
    std::string saveback = savepath + "backgroud.txt";
    std::string savefile = savepath + "saved.txt";
    if(is_directory(full_path) && is_directory(argv[2]))
    {
        printf("begin.....\n");
    }else
    {
        printf("the fist or second input is not a directory");
    }
    directory_iterator end;
  for(directory_iterator pos(full_path);pos !=end; ++pos){
    boost::filesystem::path path_(*pos);
    if(is_regular(path_)){
        std::string s= path_.string();
      vector_files.push_back(s);
    }
  }
  std::string filename = " ";
  std::string xmlfile = " ";
  std::string rpbfile = " ";
    for(int i=0; i < vector_files.size(); i++)
    {
        if(vector_files[i].find(".tiff") != std::string::npos)
        {    
            filename = vector_files[i];
             printf("filename:%s\n", vector_files[i].c_str());
        }
            else if(vector_files[i].find(".rpb") != std::string::npos)
            {
                rpbfile = vector_files[i];
                printf("rpbfile:%s\n", vector_files[i].c_str());
            }
                else if(vector_files[i].find(".xml") != std::string::npos)
                {
                    xmlfile = vector_files[i];
                    printf("xmlfile:%s\n", vector_files[i].c_str());
                }
    }
    printf("filename:%s\n", filename.c_str());
    printf("rpbfile:%s\n", rpbfile.c_str());
    printf("xmlfile:%s\n", xmlfile.c_str());
   if(filename.compare(" ")==0 || xmlfile.compare(" ") ==0 || rpbfile.compare(" ")==0)
   {
    printf("There are not .tiff, or .rpb, or .xml file in your directory!\n");
    exit(1);
   } 

//////////////////////////////////////////
  //  std::string filename = "/home/yang/workspace/gf/data/GF1_WFV2_E113.4_N29.3_20151020_L1A0001116845/GF1_WFV2_E113.4_N29.3_20151020_L1A0001116845.tiff";
//    std::string xmlfile = "/home/yang/workspace/gf/data/GF1_WFV2_E113.4_N29.3_20151020_L1A0001116845/GF1_WFV2_E113.4_N29.3_20151020_L1A0001116845.xml";
  //  std::string rpbfile = "/home/yang/workspace/gf/data/GF1_WFV2_E113.4_N29.3_20151020_L1A0001116845/GF1_WFV2_E113.4_N29.3_20151020_L1A0001116845.rpb";
   std::string geofile; 
//    if (Year.compare("2014"))
//    {  
//        geofile = "/home/yang/workspace/gf/data/2014.txt";
//    }else
        geofile = "/home/yang/workspace/gf/data/2015.txt";

 //   std::string savefile = "/home/yang/workspace/gf/data/2014save.txt";
//    std::string saveimg = "/home/yang/workspace/gf/data/savedimg.tiff"; 
    GFimg * gf = new GFimg(filename, 1, xmlfile,rpbfile);
    gf->getCorner();
    gf->init();
    gf->generate_Lat_Long();
   gf->readGeoinfo(geofile);
   gf->doextract(savefile);
   gf->extractAll(saveback);
   delete gf; gf = NULL; 
}
