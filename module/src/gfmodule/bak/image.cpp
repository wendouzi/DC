#include "image.h"
#include "cpl_conv.h"
#include "myassert.h"
image::image(const I_Size * isize)
{
    data=NULL;
    size = isize;
}
image::~image()
{
    
}

void image::i_read(const char * filename)
{
}

void image::i_free()
{
}

void image::i_malloc()
{}

void image::i_write(const char * szPath, const char * filename, const char * format)
{}

MODimage::~MODimage()
{
    if(data!=NULL)
        i_free();
    size = NULL;
    desc = NULL;
}
void image::CPLMalloctest()
{

}

void MODimage::CPLMalloctest()
{
	printf("\nbegin to test CPLMalloc...\n");
	writebuf= (float *)malloc(sizeof(float)*size->YSize* size->XSize* size->NBand); // 用于缓存单波段数据
    //writebuf = new float[160];
	if(writebuf == NULL)
    {
        printf("\nMODimage CPLMalloctest CPLMalloc error\n\n");
        return;
    }
	free(writebuf);
	printf("\ntest end...\n");
}

void MODimage::i_write(const char * szPath, const char * filename, const char * pszFormat)
{
    printf("begin MODimage::i_write....\n");
    assert(filename != NULL);
    assert(szPath != NULL);
    std::string abfile = std::string(szPath)+std::string(filename);
    GDALAllRegister();
    GDALDriver * poDriver;
    char ** papszMetadata;
    writebuf = (float *)malloc(sizeof(float)*size->YSize* size->XSize* size->NBand);
    if(writebuf == NULL)
    {
        printf("MODimage i_write CPLMalloc error\n");
        return;
    }
    poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
    if( poDriver == NULL )
    {
        printf("%s is not supported.\n", pszFormat);
        return;
    }
    char **papszOptions = NULL; 
    GDALDataset *WriteDataSet = poDriver->Create(abfile.c_str(), size->XSize,size->YSize,size->NBand,GDT_Float32,papszOptions);

 //       printf("size->XSize:%d, size->YSize : %d\n", size->XSize, size->YSize);
    // 输出第一波段数据
    int poBandMap[9]={1,2,3,4,5,6,7,8,9};
    for(int b = 0 ; b < size->NBand; b++)
    {
   //     int b =0;
    for(int i = 0 ; i < size->XSize; i++)
    {
        for(int j =0 ; j < size->YSize ; j++)
        {
          //  data[i][j][0]=
            writebuf[b*size->XSize*size->YSize+i*size->YSize+j] = data[i][j][b];
        //    pMemData[i] = data[i][j][b];
        }
    }
    } // for (band) 

        if(WriteDataSet->RasterIO(GF_Write,0,0,size->XSize,size->YSize,writebuf,size->XSize,size->YSize,GDT_Float32,size->NBand,poBandMap,0,0,0)==CE_Failure)
        {
            printf("MODimage:: i_write failed.\n");
      //      break;
        }
    free(writebuf);
    delete WriteDataSet;
    printf("finished MODimage::i_write...\n");
}

float image::rad2rrs(float a,float b, float c,float rad)
{
    float y = a*rad-b;
    float acr = y/(1+c*y);
    return acr/3.141593;
}

void MODimage::i_malloc()
{
    printf("MODimage i_malloc...\n");
    data= (float***)malloc(sizeof(float**)*(size->XSize)); 
        for (int i = 0 ; i < size->XSize ; i++)
        {
            data[i] = (float**)malloc(sizeof(float*)*(size->YSize));
            for (int j = 0 ; j < size->YSize ; j++)
            {
                  data[i][j]= (float *)malloc(sizeof(float)*size->NBand); 
            }
        }

    printf("MODimage i_malloc end\n");
}
void MODimage::i_read(const char * filename)
{
    assert(filename!=NULL);
    {

        // 读取影像数据的DN值，将其转化为radiance，并赋值给data.        
    GDALDataset  *poDataset;
    char **papszOpenOptions = NULL;
    uint16_t * pMemData = (uint16_t *)CPLMalloc(sizeof(uint16_t)*MOD1.XSize*MOD1.YSize); // 用于缓存单波段数据
    printf("reading MODimage data.......\n");
    GDALAllRegister();
    poDataset = (GDALDataset *)GDALOpenEx( filename, GDAL_OF_READONLY | GDAL_OF_RASTER, NULL,
              (const char* const* )papszOpenOptions, NULL );
    if( poDataset == NULL )
    {
	    perror("Cloud not open the image");exit(1);
    }
    char **papszSubdatasets = GDALGetMetadata( poDataset, "SUBDATASETS" );
    std::vector<std::string> vSubDataSets;
    std::vector<std::string> vSubDataDesc;
    std::vector<GDALDatasetH> vRasterBands;
    int nSubdatasets = CSLCount( papszSubdatasets );
    printf("nSubdatasets:%d\n",nSubdatasets);
    if(nSubdatasets < 0)
    {
        printf("There are no dataset in this HDF\n");
        exit(1);
    }
    for(int i = 0; papszSubdatasets[i]!=NULL; i ++)
    {
       if(i%2!=0)
          continue;
       std::string tmpstr = std::string(papszSubdatasets[i]) ;
       tmpstr = tmpstr.substr(tmpstr.find_first_of("=")+1);
       std::string tmpdesc = std::string(papszSubdatasets[i+1]);
       tmpdesc = tmpdesc.substr(tmpdesc.find_first_of("=")+1);
       GDALDatasetH hTmpDt = GDALOpen(tmpstr.c_str(),GA_ReadOnly);
       if(hTmpDt!=NULL)
       {
            vSubDataSets.push_back(tmpstr);
            vSubDataDesc.push_back(tmpdesc);
            GDALClose(hTmpDt);
       }
    }
    // 读取波段数据 
    std::vector<std::string> scales;
    std::vector<std::string> offsets;
    std::vector<std::string> valid;
    float scale,offset;
    uint16_t range0, range1;
    GDALDataset* HTmpDt ;
    /*********读取4.subdataset数据********/
    HTmpDt= (GDALDataset*)GDALOpen(vSubDataSets[4].c_str(),GA_ReadOnly);// 第1，2 波段
    
    assert(HTmpDt!=NULL);
    char **props = HTmpDt->GetMetadata("");
    assert(props!=NULL);
    int ns = CSLCount(props);
    if(ns<=0)
    {
        printf("There is no metedata");exit(1);
    }

    for(int i=0; props[i]!=NULL; i++)
    {
       std::string tmpstr = std::string(props[i]);
 //      std::cout<<tmpstr<<std::endl;
       std::size_t idx = tmpstr.find("radiance_offsets");
       if(idx!=std::string::npos)
       {
     //      printf("%s\n",tmpstr.c_str());
           tmpstr = tmpstr.substr(tmpstr.find_first_of("=")+1);
           offsets = split(tmpstr,",");
         
        //   for(int i=0; i< offsets.size(); i++)
        //   {
        //        std::cout<<offsets[i]<<std::endl;
        //   }
           continue;
       }
       idx = tmpstr.find("radiance_scales");
       if(idx!=std::string::npos)
       {
   //        printf("%s\n",tmpstr.c_str());
           tmpstr = tmpstr.substr(tmpstr.find_first_of("=")+1);
           scales = split(tmpstr,",");
       //    for(int i=0; i<scales.size(); i++)
       //    {
       //         std::cout<<scales[i]<<std::endl;
       //    }
       }
       idx = tmpstr.find("valid_range");
       if(idx!=std::string::npos)
       {
     //      printf("%s\n",tmpstr.c_str());
           tmpstr = tmpstr.substr(tmpstr.find_first_of("=")+1);
           valid = split(tmpstr,",");
       //    for(int i=0; i<valid.size(); i++)
       //    {
       //         std::cout<<valid[i]<<std::endl;
       //    }
       }
       
    }

    printf("vSubDataSets:%s\n",vSubDataSets[4].c_str());
    GDALRasterBand * poband = HTmpDt->GetRasterBand(1);//从1开始。
    assert(poband!=NULL);
    poband->RasterIO(GF_Read,
                        0,0,
                        size->XSize,size->YSize,
                        pMemData,
                        size->XSize,size->YSize,
                        GDT_UInt16,
                        0,0
            );

    // 读取第一波段到data
    sscanf(scales[0].c_str(),"%f",&scale);
    sscanf(offsets[0].c_str(),"%f",&offset);
    sscanf(valid[0].c_str(),"%d",&range0);
    sscanf(valid[1].c_str(),"%d",&range1);
    for(int i = 0 ; i < size->XSize; i++)
    {
        for(int j =0 ; j < size->YSize ; j++)
        {
            data[i][j][0]=
            pMemData[i*size->YSize+j]*scale+offset;
        }
    }
    poband = HTmpDt->GetRasterBand(2);//读取第二波段
    assert(poband!=NULL);
    poband->RasterIO(GF_Read,
                        0,0,
                        size->XSize,size->YSize,
                        pMemData,
                        size->XSize,size->YSize,
                        GDT_UInt16,
                        0,0
            );
    scale = 0;
    offset = 0;
    sscanf(scales[1].c_str(),"%f",&scale);
    sscanf(offsets[1].c_str(),"%f",&offset);
    for(int i = 0 ; i < size->XSize; i++)
    {
        for(int j =0 ; j < size->YSize ; j++)
        {
            data[i][j][1]=
            pMemData[i*size->YSize+j]*scale+offset;
        }
    }

    GDALClose(HTmpDt);
/**********************读取第二波段结束，读取第二个subdataset************/

    scales.clear();
    offsets.clear();
    valid.clear();
    HTmpDt= (GDALDataset*)GDALOpen(vSubDataSets[7].c_str(),GA_ReadOnly);// 第3，4,5,6,7 波段
    
    assert(HTmpDt!=NULL);
    props = HTmpDt->GetMetadata("");
    assert(props!=NULL);
    ns = CSLCount(props);
    if(ns<=0)
    {
        printf("There is no metedata");exit(1);
    }
    for(int i=0; props[i]!=NULL; i++)
    {
       std::string tmpstr = std::string(props[i]);
  //     std::cout<<tmpstr<<std::endl;
       std::size_t idx = tmpstr.find("radiance_offsets");
       if(idx!=std::string::npos)
       {
        //   printf("%s\n",tmpstr.c_str());
           tmpstr = tmpstr.substr(tmpstr.find_first_of("=")+1);
           offsets = split(tmpstr,",");
       //    for(int i=0; i< offsets.size(); i++)
       //    {
       //         std::cout<<offsets[i]<<std::endl;
       //    }
           continue;
       }
       idx = tmpstr.find("radiance_scales");
       if(idx!=std::string::npos)
       {
        //   printf("%s\n",tmpstr.c_str());
           tmpstr = tmpstr.substr(tmpstr.find_first_of("=")+1);
           scales = split(tmpstr,",");
       //    for(int i=0; i<scales.size(); i++)
       //    {
       //         std::cout<<scales[i]<<std::endl;
       //    }
       }
       idx = tmpstr.find("valid_range");
       if(idx!=std::string::npos)
       {
        //   printf("%s\n",tmpstr.c_str());
           tmpstr = tmpstr.substr(tmpstr.find_first_of("=")+1);
           valid = split(tmpstr,",");
        //   for(int i=0; i<valid.size(); i++)
        //   {
        //        std::cout<<valid[i]<<std::endl;
        //   }
       }
       
    }
    assert(scales.size()==5);
    assert(offsets.size()==5);
    assert(valid.size()==2);
    poband = HTmpDt->GetRasterBand(1);//读取第三波段
    assert(poband!=NULL);
    poband->RasterIO(GF_Read,
                        0,0,
                        size->XSize,size->YSize,
                        pMemData,
                        size->XSize,size->YSize,
                        GDT_UInt16,
                        0,0
            );
    scale = 0;
    offset = 0;
    sscanf(scales[0].c_str(),"%f",&scale);
    sscanf(offsets[0].c_str(),"%f",&offset);
    
    for(int i = 0 ; i < size->XSize; i++)
    {
        for(int j =0 ; j <size->YSize ; j++)
        {
            data[i][j][2]=
            pMemData[i*size->YSize+j]*scale+offset;
        }
    }
    poband = HTmpDt->GetRasterBand(2);//读取第四波段
    assert(poband!=NULL);
    poband->RasterIO(GF_Read,
                        0,0,
                        size->XSize,size->YSize,
                        pMemData,
                        size->XSize,size->YSize,
                        GDT_UInt16,
                        0,0
            );
    scale = 0;
    offset = 0;
    sscanf(scales[1].c_str(),"%f",&scale);
    sscanf(offsets[1].c_str(),"%f",&offset);
    
    for(int i = 0 ; i < size->XSize; i++)
    {
        for(int j =0 ; j < size->YSize ; j++)
        {
            data[i][j][3]=
            pMemData[i*size->YSize+j]*scale+offset;
        }
    }
    poband = HTmpDt->GetRasterBand(3);//读取第5波段
    assert(poband!=NULL);
    poband->RasterIO(GF_Read,
                        0,0,
                        size->XSize,size->YSize,
                        pMemData,
                        size->XSize,size->YSize,
                        GDT_UInt16,
                        0,0
            );
    scale = 0;
    offset = 0;
    sscanf(scales[2].c_str(),"%f",&scale);
    sscanf(offsets[2].c_str(),"%f",&offset);
    
    for(int i = 0 ; i < size->XSize; i++)
    {
        for(int j =0 ; j < size->YSize ; j++)
        {
            data[i][j][4]=
            pMemData[i*size->YSize+j]*scale+offset;
        }
    }
    
    poband = HTmpDt->GetRasterBand(4);//读取第6波段
    assert(poband!=NULL);
    poband->RasterIO(GF_Read,
                        0,0,
                        size->XSize,size->YSize,
                        pMemData,
                        size->XSize,size->YSize,
                        GDT_UInt16,
                        0,0
            );
    scale = 0;
    offset = 0;
    sscanf(scales[3].c_str(),"%f",&scale);
    sscanf(offsets[3].c_str(),"%f",&offset);
    
    for(int i = 0 ; i < size->XSize; i++)
    {
        for(int j =0 ; j < size->YSize ; j++)
        {
            data[i][j][5]=
            pMemData[i*size->YSize+j]*scale+offset;
        }
    }
    poband = HTmpDt->GetRasterBand(5);//读取第7波段
    assert(poband!=NULL);
    poband->RasterIO(GF_Read,
                        0,0,
                        size->XSize,size->YSize,
                        pMemData,
                        size->XSize,size->YSize,
                        GDT_UInt16,
                        0,0
            );
    scale = 0;
    offset = 0;
    sscanf(scales[4].c_str(),"%f",&scale);
    sscanf(offsets[4].c_str(),"%f",&offset);
    
    for(int i = 0 ; i < size->XSize; i++)
    {
        for(int j =0 ; j < size->YSize ; j++)
        {
            data[i][j][6]=
            pMemData[i*size->YSize+j]*scale+offset;
        }
    }
    GDALClose(HTmpDt);
    /********************读取第8，9 波段， 第三个subdataset**********************************/
    scales.clear();
    offsets.clear();
    valid.clear();
    HTmpDt= (GDALDataset*)GDALOpen(vSubDataSets[0].c_str(),GA_ReadOnly);// 第8,9 波段

    assert(HTmpDt!=NULL);
    props = HTmpDt->GetMetadata("");
    assert(props!=NULL);
    ns = CSLCount(props);

    if(ns<=0)
    {
        printf("There is no metedata");exit(1);
    }
    for(int i=0; props[i]!=NULL; i++)
    {
       std::string tmpstr = std::string(props[i]);
//       std::cout<<tmpstr<<std::endl;
       std::size_t idx = tmpstr.find("radiance_offsets");
       if(idx!=std::string::npos)
       {
          // printf("%s\n",tmpstr.c_str());
           tmpstr = tmpstr.substr(tmpstr.find_first_of("=")+1);
           offsets = split(tmpstr,",");
       //    for(int i=0; i< offsets.size(); i++)
       //    {
       //         std::cout<<offsets[i]<<std::endl;
       //    }
           continue;
       }
       idx = tmpstr.find("radiance_scales");
       if(idx!=std::string::npos)
       {
          // printf("%s\n",tmpstr.c_str());
           tmpstr = tmpstr.substr(tmpstr.find_first_of("=")+1);
           scales = split(tmpstr,",");
        //   for(int i=0; i<scales.size(); i++)
        //   {
        //        std::cout<<scales[i]<<std::endl;
        //   }
       }
       idx = tmpstr.find("valid_range");
       if(idx!=std::string::npos)
       {
         //  printf("%s\n",tmpstr.c_str());
           tmpstr = tmpstr.substr(tmpstr.find_first_of("=")+1);
           valid = split(tmpstr,",");
        //   for(int i=0; i<valid.size(); i++)
        //   {
        //        std::cout<<valid[i]<<std::endl;
        //   }
       }
       
    }
    assert(scales.size()==15);
    assert(offsets.size()==15);
    assert(valid.size()==2);

    poband = HTmpDt->GetRasterBand(10);//读取第8波段
    assert(poband!=NULL);
    poband->RasterIO(GF_Read,
                        0,0,
                        size->XSize,size->YSize,
                        pMemData,
                        size->XSize,size->YSize,
                        GDT_UInt16,
                        0,0
            );
    scale = 0;
    offset = 0;
    sscanf(scales[0].c_str(),"%f",&scale);
    sscanf(offsets[0].c_str(),"%f",&offset);
    
    for(int i = 0 ; i < size->XSize; i++)
    {
        for(int j =0 ; j < size->YSize ; j++)
        {
            data[i][j][7]=
            pMemData[i*size->YSize+j]*scale+offset;
        }
    }


    poband = HTmpDt->GetRasterBand(11);//读取第9波段
    assert(poband!=NULL);
    poband->RasterIO(GF_Read,
                        0,0,
                        size->XSize,size->YSize,
                        pMemData,
                        size->XSize,size->YSize,
                        GDT_UInt16,
                        0,0
            );
    scale = 0;
    offset = 0;
    sscanf(scales[0].c_str(),"%f",&scale);
    sscanf(offsets[0].c_str(),"%f",&offset);
    
    for(int i = 0 ; i < size->XSize; i++)
    {
        for(int j =0 ; j < size->YSize ; j++)
        {
            data[i][j][8]=
            pMemData[i*size->YSize+j]*scale+offset;
        }
    }
    GDALClose(HTmpDt);
    printf("read MODimage data end\n");
    }// if(format==1) MOD1
}// i_read

void MODimage::i_free()
{
    printf("free img...\n");
    for(int i =0 ; i < size->XSize ; i++)
    {
        for (int j = 0 ; j < size->YSize ; j++)
        {
            free(data[i][j]);
        }
        free(data[i]);
    }
    free(data);
    data = NULL;
    printf("free img end.\n");
}
/*
void image::printdata(image * img)
{
    printf("print data.....\n");
    for(int i = 0; i < size->XSize ;  i ++)
    {
        for (int j = 0 ; j < size->YSize ; j++)
        {
            for ( int b = 0 ; b < size->NBand ; b++)
            {
              //  std::cout << data[b][i][j]<<" "<<std::flush;
  //              printf("%f,",data[i][j][b]);
            }
        }
    }
    for(int i = 0; i < size->XSize ;  i ++)
    {
        for (int j = 0 ; j < size->YSize ; j++)
        {
                std::cout << "7:"<<data[7][i][j]<<",8:"<<data[8][i][j]<<"; "<<std::flush;
  //              printf("%f,",data[i][j][b]);
        }
    }
    printf("print data end\n");
}*/
/*
int main(int argc, char * argv[])
{
    
    char *filename ="/home/yang/workspace/data/MOD021KM.A2012084.0210.005.2012084093853.hdf";
    image* img = new image(&MOD1);
    image::i_read(filename,1,img);
    printdata(img);
    image::i_free(img);
}
*/
