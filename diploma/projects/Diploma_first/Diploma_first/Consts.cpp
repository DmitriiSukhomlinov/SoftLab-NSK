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

static std::array<const char*, 10> samplePaulWalkerMixed =
                                                { "samples/faces/paul_walker_mixed/1.jpg",
                                                  "samples/faces/paul_walker_mixed/2.jpg",
                                                  "samples/faces/paul_walker_mixed/3.png",
                                                  "samples/faces/paul_walker_mixed/4.jpg",
                                                  "samples/faces/paul_walker_mixed/5.jpg",
                                                  "samples/faces/paul_walker_mixed/6.jpg",
                                                  "samples/faces/paul_walker_mixed/7.jpg",
                                                  "samples/faces/paul_walker_mixed/8.jpg",
                                                  "samples/faces/paul_walker_mixed/9.jpg",
                                                  "samples/faces/paul_walker_mixed/10.jpg" };

static const char* resolutionTestFirstPic = "samples/faces/resolution_tests/1/1.jpg";

static std::array<const char*, 10> resolutionTestFirstGood = 
                                                { "samples/faces/resolution_tests/1/good/1.jpg",
                                                  "samples/faces/resolution_tests/1/good/2.jpg",
                                                  "samples/faces/resolution_tests/1/good/3.jpg",
                                                  "samples/faces/resolution_tests/1/good/4.jpg",
                                                  "samples/faces/resolution_tests/1/good/5.jpg",
                                                  "samples/faces/resolution_tests/1/good/6.jpg",
                                                  "samples/faces/resolution_tests/1/good/7.jpg",
                                                  "samples/faces/resolution_tests/1/good/8.jpg",
                                                  "samples/faces/resolution_tests/1/good/9.jpg",
                                                  "samples/faces/resolution_tests/1/good/10.jpg" };  

static std::array<const char*, 10> resolutionTestFirstMid = 
                                                { "samples/faces/resolution_tests/1/mid/1.jpg",
                                                  "samples/faces/resolution_tests/1/mid/2.jpg",
                                                  "samples/faces/resolution_tests/1/mid/3.jpg",
                                                  "samples/faces/resolution_tests/1/mid/4.jpg",
                                                  "samples/faces/resolution_tests/1/mid/5.jpg",
                                                  "samples/faces/resolution_tests/1/mid/6.jpg",
                                                  "samples/faces/resolution_tests/1/mid/7.jpg",
                                                  "samples/faces/resolution_tests/1/mid/8.jpg",
                                                  "samples/faces/resolution_tests/1/mid/9.jpg",
                                                  "samples/faces/resolution_tests/1/mid/10.jpg" };

static std::array<const char*, 10> resolutionTestFirstLow = 
                                                { "samples/faces/resolution_tests/1/low/1.jpg",
                                                  "samples/faces/resolution_tests/1/low/2.jpg",
                                                  "samples/faces/resolution_tests/1/low/3.jpg",
                                                  "samples/faces/resolution_tests/1/low/4.jpg",
                                                  "samples/faces/resolution_tests/1/low/5.jpg",
                                                  "samples/faces/resolution_tests/1/low/6.jpg",
                                                  "samples/faces/resolution_tests/1/low/7.jpg",
                                                  "samples/faces/resolution_tests/1/low/8.jpg",
                                                  "samples/faces/resolution_tests/1/low/9.jpg",
                                                  "samples/faces/resolution_tests/1/low/10.jpg" };  

static const char* resolutionTestSecondPic = "samples/faces/resolution_tests/2/1.jpg";

static std::array<const char*, 10> resolutionTestSecondGood =
                                                { "samples/faces/resolution_tests/2/good/1.jpg",
                                                  "samples/faces/resolution_tests/2/good/2.jpg",
                                                  "samples/faces/resolution_tests/2/good/3.jpg",
                                                  "samples/faces/resolution_tests/2/good/4.jpg",
                                                  "samples/faces/resolution_tests/2/good/5.jpg",
                                                  "samples/faces/resolution_tests/2/good/6.jpg",
                                                  "samples/faces/resolution_tests/2/good/7.jpg",
                                                  "samples/faces/resolution_tests/2/good/8.jpg",
                                                  "samples/faces/resolution_tests/2/good/9.jpg",
                                                  "samples/faces/resolution_tests/2/good/10.jpg" };  

static std::array<const char*, 10> resolutionTestSecondMid =
                                                { "samples/faces/resolution_tests/2/mid/1.jpg",
                                                  "samples/faces/resolution_tests/2/mid/2.jpg",
                                                  "samples/faces/resolution_tests/2/mid/3.jpg",
                                                  "samples/faces/resolution_tests/2/mid/4.jpg",
                                                  "samples/faces/resolution_tests/2/mid/5.jpg",
                                                  "samples/faces/resolution_tests/2/mid/6.jpg",
                                                  "samples/faces/resolution_tests/2/mid/7.jpg",
                                                  "samples/faces/resolution_tests/2/mid/8.jpg",
                                                  "samples/faces/resolution_tests/2/mid/9.jpg",
                                                  "samples/faces/resolution_tests/2/mid/10.jpg" };  

static std::array<const char*, 10> resolutionTestSecondLow =
                                                { "samples/faces/resolution_tests/2/low/1.jpg",
                                                  "samples/faces/resolution_tests/2/low/2.jpg",
                                                  "samples/faces/resolution_tests/2/low/3.jpg",
                                                  "samples/faces/resolution_tests/2/low/4.jpg",
                                                  "samples/faces/resolution_tests/2/low/5.jpg",
                                                  "samples/faces/resolution_tests/2/low/6.jpg",
                                                  "samples/faces/resolution_tests/2/low/7.jpg",
                                                  "samples/faces/resolution_tests/2/low/8.jpg",
                                                  "samples/faces/resolution_tests/2/low/9.jpg",
                                                  "samples/faces/resolution_tests/2/low/10.jpg" };  




