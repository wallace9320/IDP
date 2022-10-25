// Constants
#define BLACK 0
#define WHITE 1
const int normalSpeed = 255;
const int ot = 250;
const int it = 1;
const int innerTurnSpeed = 120;
const int turnTime = 2200;
const int straightTime = 1000;
const int slowSpeed = 50;       // Speed when very close to block
const int blockDistance = 5;
const double tunnelLeftClearance = 5.0;

// pins
const int leftLSPin = 0;
const int rightLSPin = 1;
const int farRightLSPin = 2;
const int frontUSechoPin = 3;
const int frontUStrigPin = 4;
const int leftUSechoPin = 5;
const int leftUStrigPin = 6;
const int buttonPin = 7;
const int redLED = 8;
const int greenLED = 11;
const int lservoPin = 10;
const int rservoPin = 9;
const int runningLED = 13;

const int hallEffectPin = A0;

// booleans for logic
bool start = false;
bool turn = false;
bool holding = false;
bool magnet = false;
bool drop = false;
bool button = true;

// time
unsigned long timeStart;
unsigned long timeButton;
unsigned long pickupTime;

int noOfWhiteLines = 0;
int mlSpeed = normalSpeed;
int mrSpeed = normalSpeed;

int leftLSReading = 0;
int rightLSReading = 0;
int farRightLSReading = 0;

double frontUS;