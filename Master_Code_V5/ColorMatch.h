// Header file for the ColorMatch application
// This file is generated by the ColorMatch Application in Learn Mode

// Calibration data
sensorData sdBlack = { 6820, 5630, 7310 };
sensorData sdWhite = { 44360, 38650, 51400 };

// Color Table for matching
typedef struct
{
  char    name[9];  // color name 8+nul
  colorData rgb;    // RGB value
} colorTable;

colorTable ct[] = 
{
  {"WHITE", {192, 195, 188} },
  {"BLACK", {0, 0, 0} },
  {"YELLOW", {169, 137, 53} },
  {"ORANGE", {125, 40, 27} },
  {"RED", {86, 14, 16} },
  {"GREEN", {12, 31, 14} },
  {"BLUE", {12, 13, 21} },
  {"BROWN", {8, 2, 0} },
};

