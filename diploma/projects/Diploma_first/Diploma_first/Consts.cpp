#include <array>

static const char* key = "OGObpkvXCrfHElL9WEBXFpuQJKKAHYH7x3RhCCx5pPIlC3Dhs3uZ6IcSZOdbaGZ85xAyP2Y13Lvh+UYBdMnXdnPHD7Nox08lGz7CaKye8Kle+AK7evFqLUkSPOH83PG4FTYqAKnw5SdinVo0SK1yng0PiJKCpYOjPK2qNEqKPAE=";

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
