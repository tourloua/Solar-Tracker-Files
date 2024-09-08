//By Alexandros Tourloukis
//August 19, 2024
// Define the pins used for the bottom stepper motor
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

// Define the pins used for the top two stepper motors
//BE MINDFUL that since the axles of the motors face eachother, one must be 
//wired the opposite way
#define IN5 4
#define IN6 5
#define IN7 6
#define IN8 7

int phi =0;//horizontal rotation
int theta=0;//vertical rotation
  //to prevent tangling of wires, if we rotate too much in one direction, the device will 
  //reset to it's initial position
// Full step sequence for 28BYJ-48 stepper motor clockwise
int clockwise[4][4] = {
  {1, 0, 0, 1},
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1}
};

// Full step sequence for 28BYJ-48 stepper motor counterclockwise
int counterclockwise[4][4] = {
  {1, 0, 0, 1},
  {0, 0, 1, 1},
  {0, 1, 1, 0},
  {1, 1, 0, 0}
};

// Delay between steps (in milliseconds)
int stepDelay = 2;

void setup() {
  // Set the motor control pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);

  //Serial.begin(9600);//for debugging, uncomment this line, line 162 and 163

}

void loop() {


  bool exitflag=false;

  // Read analog values from pins A0, A1, A2, and A3
  int valueA0 = analogRead(A0);
  int valueA1 = analogRead(A1);
  int valueA2 = analogRead(A2);
  int valueA3 = analogRead(A3);

  int left = valueA0+valueA2;
  int right = valueA1+valueA3;
  int top = valueA0+valueA1;
  int bottom = valueA2+valueA3;

  if (left>right*1.1 && phi<550)//rotates CCW
//NOTE THAT THE PHOTORESISTORS RESPOND LOGARITHMICALLY TO 
//LIGHT. CHANGE EVERY 1.1 TO 1.4 WHEN USING INDOORS
  {
    for (int step = 0; step < 4; step++) {
        digitalWrite(IN1, counterclockwise[step][0]);
        digitalWrite(IN2, counterclockwise[step][1]);
        digitalWrite(IN3, counterclockwise[step][2]);
        digitalWrite(IN4, counterclockwise[step][3]);
        delay(stepDelay); // Delay between steps
    }
    phi++;
  }
  if (top>bottom*1.1 && theta<250)//rotates up
  {
    for (int step = 0; step < 4; step++) {
        digitalWrite(IN5, clockwise[step][0]);
        digitalWrite(IN6, clockwise[step][1]);
        digitalWrite(IN7, clockwise[step][2]);
        digitalWrite(IN8, clockwise[step][3]);
        delay(stepDelay); // Delay between steps
    }
    theta++;
  }
  if (bottom>top*1.1 && theta>-250)//rotates down
  {
    for (int step = 0; step < 4; step++) {
        digitalWrite(IN5, counterclockwise[step][0]);
        digitalWrite(IN6, counterclockwise[step][1]);
        digitalWrite(IN7, counterclockwise[step][2]);
        digitalWrite(IN8, counterclockwise[step][3]);
        delay(stepDelay); // Delay between steps
    }
    theta--;
  }
  if (phi>=550)//untangles the wires once we rotate CCW approx 185 degrees
  {
      exitflag=false;
      while(!exitflag)
      {
        for (int step = 0; step < 4; step++) 
        {
          digitalWrite(IN1, clockwise[step][0]);
          digitalWrite(IN2, clockwise[step][1]);
          digitalWrite(IN3, clockwise[step][2]);
          digitalWrite(IN4, clockwise[step][3]);
          delay(stepDelay);
        }
        phi--;
        if (phi==0)
        {
          exitflag=true;
        }

      }    
      
  }

  if (right>left*1.1 && phi>-550)//rotates CW
  {
    for (int step = 0; step < 4; step++) {
        digitalWrite(IN1, clockwise[step][0]);
        digitalWrite(IN2, clockwise[step][1]);
        digitalWrite(IN3, clockwise[step][2]);
        digitalWrite(IN4, clockwise[step][3]);
        delay(stepDelay); 
    }
    phi--;
  }

  if (phi<=-550)//untangles the wires once we rotate CW approx 185 degrees
  {
    exitflag=false;
      while(!exitflag)
      {
        for (int step = 0; step < 4; step++) 
        {
          digitalWrite(IN1, counterclockwise[step][0]);
          digitalWrite(IN2, counterclockwise[step][1]);
          digitalWrite(IN3, counterclockwise[step][2]);
          digitalWrite(IN4, counterclockwise[step][3]);
          delay(stepDelay);
        }
        phi++;
        if (phi==0)
        {
          exitflag=true;
        }

      }    
      
  }
  //Serial.print("phi: ");
  //Serial.println(phi);

}
