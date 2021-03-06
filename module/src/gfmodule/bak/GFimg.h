
#ifndef GFIMG_H
#define GFIMG_H
#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif 

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "geoshape.h"
#define ST_WFV1 0 // SensorType WFV1
#define ST_WFV2 1 // SensorType WFV2
#define ST_WFV3 2 // SensorType WFV3
#define ST_WFV4 3 // SensorType WFV4
#define RESOLUTION 8
#define NEAR_POINTS_NUM 300
#define FILLVALUE 1000
#define WATERFILLVALUE 0
#define NDVI_WATERINDEX (-0.1)
#define NDVI_CENTER (0.5)
#define NDWI_MIN (-5)
#define NDWI_MAX (5)
#define NDWI_WATERINDEX (0.15)
#define RATIO43_WATERINDEX (3.5)
#define RATIO43_MIN (-5)
#define RATIO43_MAX (5)
    enum Method 
    {
        withoutDist = 0,
        withDist_1
    };
    enum write_var
    {
        var_ndvi = 0,
        var_ndwi,
        var_svi,
        var_dist,
        var_wet,
        var_isShade,
        var_reflectance,
        var_density
    };
    enum DistAlgo
    {
        Pixel2Water = 0,
        Water2Pixel  
    };
struct NearBody {
    bool up;
    bool down;
    bool left;
    bool right;
};

class GFimg
{
    private:
        std::string filename;
        int SensorType;
        std::string xmlfile;
        std::string rpbfile;
        float tllat,tllong,trlat,trlong,bllat,bllong,brlat,brlong;
        float * band1;
        float * band2;
        float * band3;
        float * band4;
        float * latitude;
        float * longitude;
        float * ndvi;
        bool * wi;
        float * svi;
        float * ndwi;
        float * bright;
        float * green;
        float * wet;
        float * dis;
        float * distance;
        float * density;
        float * isShade;
        int insituPoints;
        float * geoinfo; // latitude and longitude  of in situ points
     //   float * latitude;
     //   float * longitude;
        int width;
        int height;
//        std::vector<vector<int>> colrow;
        std::vector<int> i_colrow;
       // std::vector<int> i_row;
     //   std::vector<float> i_lat;
     //   std::vector<float> i_long;


    public:
        GFimg(const std::string & _filename, const int & _SensorType,
               const  std::string _xmlfile, const std::string _rpbfile
                );
        ~GFimg();
        void init();        
        void getNDVI();
        void getNDWI();
        void getSVI();
        void getWI();
        void getIsShade();
        void KTtransform();
        void getDistance2water(DistAlgo da);
        void getDistance2water();
        void caldensity();
        void caldensity(Method me);
        void generate_Lat_Long();
        void getAllValueNearLine(float * li, float * res);
        void getValueByPoints(float * li, std::vector<int> * colrowtemp);
        void extractValueByFile(std::string geofile,std::string savefile);
        void write(write_var var, std::string sfile);
        void print();
        int geo2num(float num1, float num2, int hw, float num3);
        void num2geo(int col, int row, float * res);
        void writeDen(std::string sfile);
        void print_lat_long();
        void doextract(std::string savefile);
        void extractAll(std::string savefile);
        void readGeoinfo(std::string geofile);
        void getCorner(); // extract the latitude and longitude corner
        void checkNearWater(NearBody * nb , int row, int col);
};



#endif /* GFIMG_H*/
