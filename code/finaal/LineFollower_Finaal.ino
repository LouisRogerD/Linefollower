#include "SerialCommand.h"
#include "EEPROMAnything.h"

#define SerialPort Serial1
#define Baudrate 9600

SerialCommand sCmd(SerialPort);
bool debug;
bool run;
unsigned long previous, calculationTime;
float iTerm;
float lastErr;
float filteredDeriv = 0; 


const int sensor[] = {A0, A1, A2, A3, A4, A5};

const int AIN1 = 9;
const int AIN2 = 10;
const int PWMA = 11;

const int BIN1 = 7;
const int BIN2 = 6;
const int PWMB = 5;

const int STBY = 8;

struct param_t
{
  unsigned long cycleTime;

  int black[6];
  int white[6];
  int power;
  float diff;
  float kp;
  float ki;
  float kd;
  float dAlpha;
  /* andere parameters die in het eeprom geheugen moeten opgeslagen worden voeg je hier toe ... */
} params;

int normalised[6];
float debugPosition;

void setup()
{
  SerialPort.begin(Baudrate);

  sCmd.addCommand("set", onSet);
  sCmd.addCommand("debug", onDebug);
  sCmd.addCommand("calibrate", onCalibrate);
  sCmd.addCommand("run", onRun);
  sCmd.setDefaultHandler(onUnknownCommand);

  EEPROM_readAnything(0, params);

  pinMode(13, OUTPUT);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);   // H-brug aan

  SerialPort.println("ready");
}

void loop()
{
  sCmd.readSerial();
 
  unsigned long current = micros();
  if (current - previous >= params.cycleTime)
  {
    previous = current;
    
    /* code die cyclisch moet uitgevoerd worden programmeer je hier ... */

    for (int i = 0; i < 6; i++)
    {
      normalised[i] = map(analogRead(sensor[i]), params.black[i], params.white[i], 0, 1000);
    }

    float position;
    int index = 0;
    for (int i = 1; i < 6; i++)if (normalised[i] < normalised[index]) index = i;

    if(normalised[index] > 800) run = false;
    
    if (index == 0) position = -30;
    else if (index == 5) position = 30;
    else
    { 
      int sNul = normalised[index];
      int sMinEen = normalised[index-1];
      int sPlusEen = normalised[index+1];

      float b = sPlusEen - sMinEen;
      b = b / 2;

      float a = sPlusEen - b - sNul;

      position = -b / (2 * a);
      position += index;
      position -= 2.5;

      position *= 15;
    }

    debugPosition = position;
    
    /*p regeling */
    float error = -position;
    float output = error * params.kp;

    /*i regeling */
    if (run) {
    iTerm += params.ki * error;
    iTerm = constrain(iTerm, -510, 510);
    output += iTerm;
    }   
    else {
    iTerm = 0;  // iterm resetten bij stoppen
    }

    /* d regeling*/

    float rawDeriv = error - lastErr;
    filteredDeriv = filteredDeriv * params.dAlpha + rawDeriv * (1.0 - params.dAlpha);
    output += params.kd * filteredDeriv;
    lastErr = error;

    output += iTerm;

  
    /* aansturen motoren */
    output = constrain(output, -510, 510);

    int powerLeft = 0;
    int powerRight = 0;

    if (run) if (output >= 0)
    {
      powerLeft = constrain(params.power + params.diff * output, -255, 255);
      powerRight = constrain(powerLeft - output, -255, 255);
      powerLeft = powerRight + output;
    }
    else //negatieve waardes van pos
    {
      powerRight = constrain(params.power - params.diff * output, -255, 255);
      powerLeft = constrain(powerRight + output, -255, 255);
      powerRight = powerLeft - output;
    }


    // Rechts
    digitalWrite(BIN1, powerRight > 0 ? HIGH : LOW);
    digitalWrite(BIN2, powerRight < 0 ? HIGH : LOW);
    analogWrite(PWMB, abs(powerRight));

    // Links
    digitalWrite(AIN2, powerLeft > 0 ? HIGH : LOW);
    digitalWrite(AIN1, powerLeft < 0 ? HIGH : LOW);
    analogWrite(PWMA, abs(powerLeft));

    

  }

  unsigned long difference = micros() - current;
  if (difference > calculationTime) calculationTime = difference;
}

void onUnknownCommand(char *command)
{
  SerialPort.print("unknown command: \"");
  SerialPort.print(command);
  SerialPort.println("\"");
}

void onSet()
{
  char* param = sCmd.next();
  char* value = sCmd.next();  
  
  if (strcmp(param, "cycle") == 0)
  {
    long newCycleTime = atol(value);
    float ratio = ((float) newCycleTime) / ((float) params.cycleTime);

    params.ki *= ratio;
    params.kd /= ratio;

    params.cycleTime = newCycleTime;
  }

  else if (strcmp(param, "ki") == 0)
  {
    float cycleTimeInSec = ((float) params.cycleTime) / 1000000;
    params.ki = atof(value) * cycleTimeInSec;
  }

  else if (strcmp(param, "kd") == 0)
  {
    float cycleTimeInSec = ((float) params.cycleTime) / 1000000;
    params.kd = atof(value) / cycleTimeInSec;
  }

  else if (strcmp(param, "dAlpha") == 0)
  {
    params.dAlpha = atof(value);
  }

  else if (strcmp(param, "power") == 0) params.power = atol(value);
  else if (strcmp(param, "diff") == 0) params.diff = atof(value);
  else if (strcmp(param, "kp") == 0) params.kp = atof(value);

  /* parameters een nieuwe waarde geven via het set commando doe je hier ... */
  
  EEPROM_writeAnything(0, params);
}

void onDebug()
{
  SerialPort.print("cycle time: ");
  SerialPort.println(params.cycleTime);
  
  /*parameters weergeven met behulp van het debug commando doe je hier ... */
  SerialPort.print("black: ");
  for (int i = 0; i < 6; i++)
  {
    SerialPort.print(params.black[i]);
    SerialPort.print(" ");
  }
  SerialPort.println(" ");

  SerialPort.print("white: ");
  for (int i = 0; i < 6; i++)
  {
    SerialPort.print(params.white[i]);
    SerialPort.print(" ");
  }
  SerialPort.println(" ");

  SerialPort.print("normalised values: ");
  for (int i = 0; i < 6; i++)
    {
      SerialPort.print(normalised[i]);
      SerialPort.print(" ");
    }
  SerialPort.println(" ");

  SerialPort.print("positie:");
  SerialPort.println(debugPosition);

  SerialPort.print("power: ");
  SerialPort.println(params.power);
  SerialPort.print("diff: ");
  SerialPort.println(params.diff);
  SerialPort.print("kp: ");
  SerialPort.println(params.kp);

  float cycleTimeInSec = ((float) params.cycleTime) / 1000000;

  float ki = params.ki / cycleTimeInSec;
  SerialPort.print("ki: ");
  SerialPort.println(ki);

  float kd = params.kd * cycleTimeInSec;
  SerialPort.print("kd: ");
  SerialPort.println(kd);

  SerialPort.print("dAlpha: ");
  SerialPort.println(params.dAlpha);

  SerialPort.print("calculation time: ");
  SerialPort.println(calculationTime);
  calculationTime = 0;
}

/*Sensor kalibreren op welke waarde wit/zwart zijn*/
void onCalibrate()
{
  char* param = sCmd.next();

  if (strcmp(param, "black") == 0)
  {
    SerialPort.print("start calibrating black... ");
    for (int i = 0; i < 6; i++) params.black[i]=analogRead(sensor[i]);
    SerialPort.println("done");
  }
  else if (strcmp(param, "white") == 0)
  {
    SerialPort.print("start calibrating white... ");    
    for (int i = 0; i < 6; i++) params.white[i]=analogRead(sensor[i]);  
    SerialPort.println("done");      
  }

  EEPROM_writeAnything(0, params);
}

void onRun() 
{
  char* parameter = sCmd.next();
  char* value = sCmd.next();
  if(strcmp(parameter, "on") == 0) 
  {
    run = true;
    iTerm = 0;
    lastErr = 0;
  }
  else run = false;
}