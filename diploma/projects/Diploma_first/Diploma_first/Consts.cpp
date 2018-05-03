#include <array>

static const char* key = "IlGjnMGtkEfv0Ds/kk1+P6p9D7a0LAOoXIHHdLpFV88wArBFV26/ExenoUXv8g2TvnkB0RIvERo3QquT4cy2BgRKHfBJNmi7xzlxc2oZbRnWK/9BHhcCfV13njdIOmIgCzg3xwORfv7ezjUmud5OiFCYEq+UjYT2kdZats0vqwI=";

//The path to the facesdk.dll
//Null pointer means current directory
static char* dllPath = nullptr;

static const char* sample1 = "samples/photo1.jpg";
static const char* sample2 = "samples/photo2.jpg";
static const char* sample3 = "samples/photo3.jpg";
static const char* sample4 = "samples/photo4.jpg";

static const char* sampleMe1 = "samples/Me/sampleMe1.jpg";
static const char* sampleMe2 = "samples/Me/sampleMe2.jpg";
static const char* sampleMe3 = "samples/Me/sampleMe3.jpg";
static const char* sampleMe4 = "samples/Me/sampleMe4.jpg";

static std::array<const char*, 10> sampleSame = { "samples/faces/same_faces/1.jpg" ,
                                                  "samples/faces/same_faces/2.jpg" ,
                                                  "samples/faces/same_faces/3.jpg" ,
                                                  "samples/faces/same_faces/4.jpg" ,
                                                  "samples/faces/same_faces/5.jpg" ,
                                                  "samples/faces/same_faces/6.jpg" ,
                                                  "samples/faces/same_faces/7.jpg" ,
                                                  "samples/faces/same_faces/8.jpg" ,
                                                  "samples/faces/same_faces/9.jpg" ,
                                                  "samples/faces/same_faces/10.jpg" };

static std::array<const char*, 10> sampleSameBlackAndWhite = 
                                                { "samples/faces/same_black_and_white/1.jpg" ,
                                                  "samples/faces/same_black_and_white/2.jpg" ,
                                                  "samples/faces/same_black_and_white/3.jpg" ,
                                                  "samples/faces/same_black_and_white/4.jpg" ,
                                                  "samples/faces/same_black_and_white/5.jpg" ,
                                                  "samples/faces/same_black_and_white/6.jpg" ,
                                                  "samples/faces/same_black_and_white/7.jpg" ,
                                                  "samples/faces/same_black_and_white/8.jpg" ,
                                                  "samples/faces/same_black_and_white/9.jpg" ,
                                                  "samples/faces/same_black_and_white/10.jpg" };


static std::array<const char*, 10> sampleDiff = { "samples/faces/different_faces/1.jpg" ,
                                                  "samples/faces/different_faces/2.jpg" ,
                                                  "samples/faces/different_faces/3.jpg" ,
                                                  "samples/faces/different_faces/4.jpg" ,
                                                  "samples/faces/different_faces/5.jpg" ,
                                                  "samples/faces/different_faces/6.jpg" ,
                                                  "samples/faces/different_faces/7.jpg" ,
                                                  "samples/faces/different_faces/8.jpg" ,
                                                  "samples/faces/different_faces/9.jpg" ,
                                                  "samples/faces/different_faces/10.jpg" };

static std::array<const char*, 10> sampleDiffBlackAndWhite = 
                                                { "samples/faces/different_black_and_white/1.jpg" ,
                                                  "samples/faces/different_black_and_white/2.jpg" ,
                                                  "samples/faces/different_black_and_white/3.jpg" ,
                                                  "samples/faces/different_black_and_white/4.jpg" ,
                                                  "samples/faces/different_black_and_white/5.jpg" ,
                                                  "samples/faces/different_black_and_white/6.jpg" ,
                                                  "samples/faces/different_black_and_white/7.jpg" ,
                                                  "samples/faces/different_black_and_white/8.jpg" ,
                                                  "samples/faces/different_black_and_white/9.jpg" ,
                                                  "samples/faces/different_black_and_white/10.jpg" };

static std::array<const char*, 10> samplePaulWalker =
                                                { "samples/faces/paul_walker/1.jpg",
                                                  "samples/faces/paul_walker/2.png",
                                                  "samples/faces/paul_walker/3.png",
                                                  "samples/faces/paul_walker/4.jpg",
                                                  "samples/faces/paul_walker/5.jpg",
                                                  "samples/faces/paul_walker/6.jpg",
                                                  "samples/faces/paul_walker/7.jpg",
                                                  "samples/faces/paul_walker/8.jpg",
                                                  "samples/faces/paul_walker/9.jpg",
                                                  "samples/faces/paul_walker/10.jpg" };

static std::array<const char*, 10> samplePaulWalkerWithAngle =
                                                { "samples/faces/paul_walker_with_angle/1.jpg",
                                                  "samples/faces/paul_walker_with_angle/2.jpg",
                                                  "samples/faces/paul_walker_with_angle/3.jpg",
                                                  "samples/faces/paul_walker_with_angle/4.jpg",
                                                  "samples/faces/paul_walker_with_angle/5.jpg",
                                                  "samples/faces/paul_walker_with_angle/6.jpg",
                                                  "samples/faces/paul_walker_with_angle/7.jpg",
                                                  "samples/faces/paul_walker_with_angle/8.jpg",
                                                  "samples/faces/paul_walker_with_angle/9.jpg",
                                                  "samples/faces/paul_walker_with_angle/10.jpg" };



