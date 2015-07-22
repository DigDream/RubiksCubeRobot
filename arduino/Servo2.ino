#include <Servo.h>

Servo servo1f;
Servo servo1b;
Servo servo2f;
Servo servo2b;
Servo servo3f;
Servo servo3b;
Servo servo4f;
Servo servo4b;

char buffer[80];

void setup() {
  // put your setup code here, to run once:
  initServo();
  // The WiFi module and the bps rate of the same
  Serial.begin(115200);
  Serial.flush();
  initServoAngle();
  Serial.println("=======================================");
  Serial.println("=Hello,I'm a RubikSolverRobot,I'm from SXAU.");
  Serial.println("=By Dubuqingfeng...");
  Serial.println("=======================================");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    int index = 0;
    delay(50);
    int numChar = Serial.available();
    if (numChar > 80) {
      numChar = 80;
    }
    while (numChar--) {
      buffer[index++] = Serial.read();
    }
    splitString(buffer);
  }
}

void initServo() {
  servo1f.attach(4);
  servo1b.attach(3);

  servo2f.attach(6);
  servo2b.attach(5);

  servo3f.attach(8);
  servo3b.attach(7);

  servo4f.attach(10);
  servo4b.attach(9);
}

void initServoAngle() {
  servo1f.writeMicroseconds(1500);
  servo1b.writeMicroseconds(1500);

  servo2f.writeMicroseconds(1500);
  servo2b.writeMicroseconds(1500);
  
  servo3f.writeMicroseconds(1500);
  servo3b.writeMicroseconds(1500);
  
  servo4f.writeMicroseconds(1500);
  servo4b.writeMicroseconds(1500);
}

void splitString(char* data) {
  Serial.println(data);
  
  //split two number;

  char* parameter;
  //parameter = data.substring(0,2);
  parameter = strtok(data, " ");

  if ((parameter[0] == 'A') || (parameter[0] == 'a')) {
    while (parameter != NULL) {
      setServoCommand(parameter);
      parameter = strtok(NULL, " ");
      delay(100);
    }
  } else {
      while (parameter != NULL) {
      setServo(parameter);
      parameter = strtok(NULL, " ");
      delay(100);
    }
  }

  for (int x = 0; x < 79; x++) {
    buffer[x] = '\0'; 
  }
  Serial.flush();
}

void setServoCommand(char* data) {
  if ((data[0] == 'B') || (data[0] == 'b' )) {
    //Back servos back
    servo1b.writeMicroseconds(500);
    servo2b.writeMicroseconds(500);
    servo3b.writeMicroseconds(500);
    servo4b.writeMicroseconds(500);
  } else if ((data[0] == 'F') || (data[0] == 'f' )) {
    //Back servos forward
    servo1b.write(100);
    servo2b.write(100);
    servo3b.write(100);
    servo4b.write(100);
  } else if ((data[0] == 'U') || (data[0] == 'u' )) {
    servo2b.write(0);
  } else if ((data[0] == 'L') || (data[0] == 'l' )) {
    servo2f.write(170);
    delay(500);
    servo2b.write(0);
    delay(500);
    servo2f.writeMicroseconds(1500);
    delay(500);
    servo2b.write(100);
  } else if ((data[0] == 'Z') || (data[0] == 'z' )) {
    //all servos 
    servo1f.writeMicroseconds(1500);
    servo1b.writeMicroseconds(1500);

    servo2f.writeMicroseconds(1500);
    servo2b.writeMicroseconds(1500);
    
    servo3f.writeMicroseconds(1500);
    servo3b.writeMicroseconds(1500);
    
    servo4f.writeMicroseconds(1500);
    servo4b.writeMicroseconds(1500);
  }
}

void setServo(char* data) {
  if ((data[0] == 'L') || (data[0] == 'l')) {
    if (data[1] == '+') {
      servo2f.write(170);
      delay(1000);
      servo2b.write(0);
      delay(1000);
      servo2f.writeMicroseconds(1500);
      delay(1000);
      servo2b.write(100);
    } else if (data[1] == '-') {
      servo2f.write(5);
      delay(1000);
      servo2b.write(0);
      delay(1000);
      servo2f.writeMicroseconds(1500);
      delay(1000);
      servo2b.write(100);
    } else if (data[1] == '2') {
      servo2f.write(10);
      delay(1000);
      servo2b.write(0);
      delay(1000);
      servo2f.writeMicroseconds(1500);
      delay(1000);
      servo2b.write(100);
      delay(1000);
      servo2f.write(10);
      delay(1000);
      servo2b.write(0);
      delay(1000);
      servo2f.write(84);
      delay(1000);
      servo2b.write(100);
    }
  } else if ((data[0] == 'R') || (data[0] == 'r')) {
    if (data[1] == '+') {
      servo4f.write(173);
      delay(1000);
      servo4b.write(0);
      delay(1000);
      servo4f.write(90);
      delay(1000);
      servo4b.write(100);
    } else if (data[1] == '-') {
      servo4f.write(10);
      delay(1000);
      servo4b.write(0);
      delay(1000);
      servo4f.write(90);
      delay(1000);
      servo4b.write(100);
    } else if (data[1] == '2') {
      servo4f.write(10);
      delay(1000);
      servo4b.write(0);
      delay(1000);
      servo4f.write(90);
      delay(1000);
      servo4b.write(100);
      delay(1000);
      servo4f.write(10);
      delay(1000);
      servo4b.write(0);
      delay(1000);
      servo4f.write(90);
      delay(1000);
      servo4b.write(100);
    }
  } else if ((data[0] == 'U') || (data[0] == 'u')) {
    //r- l+
    if (data[1] == '+') {
      rotateWholexMinus();
      servo1f.write(180);
      delay(1000);
      servo1b.write(0);
      delay(1000);
      servo1f.write(90);
      delay(1000);
      servo1b.write(100);
      rotateWholex();
    } else if (data[1] == '-') {
      rotateWholexMinus();
      servo1f.write(10);
      delay(1000);
      servo1b.write(0);
      delay(1000);
      servo1f.write(90);
      delay(1000);
      servo1b.write(100);
      rotateWholex();
    } else if (data[1] == '2') {
      rotateWholexMinus();
      servo1f.write(180);
      delay(1000);
      servo1b.write(0);
      delay(1000);
      servo1f.write(90);
      delay(1000);
      servo1b.write(100);
      delay(1000);
      servo1f.write(180);
      delay(1000);
      servo1b.write(0);
      delay(1000);
      servo1f.write(90);
      delay(1000);
      servo1b.write(100);
      rotateWholex();
    }
  } else if ((data[0] == 'F') || (data[0] == 'f')) {
    if (data[1] == '+') {
      servo1f.write(180);
      delay(1000);
      servo1b.write(0);
      delay(1000);
      servo1f.write(90);
      delay(1000);
      servo1b.write(100);
    } else if (data[1] == '-') {
      servo1f.write(10);
      delay(1000);
      servo1b.write(0);
      delay(1000);
      servo1f.write(90);
      delay(1000);
      servo1b.write(100);
    } else if (data[1] == '2') {
      servo1f.write(10);
      delay(1000);
      servo1b.write(0);
      delay(1000);
      servo1f.write(90);
      delay(1000);
      servo1b.write(100);
      delay(1000);
      servo1f.write(10);
      delay(1000);
      servo1b.write(0);
      delay(1000);
      servo1f.write(90);
      delay(1000);
      servo1b.write(100);
    }
  } else if ((data[0] == 'B') || (data[0] == 'b')) {
   if (data[1] == '+') {
      servo3f.write(175);
      delay(1000);
      servo3b.write(0);
      delay(1000);
      servo3f.write(90);
      delay(1000);
      servo3b.write(100);
    } else if (data[1] == '-') {
      servo3f.write(10);
      delay(1000);
      servo3b.write(0);
      delay(1000);
      servo3f.write(90);
      delay(1000);
      servo3b.write(100);
    } else if (data[1] == '2') {
      servo3f.write(10);
      delay(1000);
      servo3b.write(0);
      delay(1000);
      servo3f.write(90);
      delay(1000);
      servo3b.write(100);
      delay(1000);
      servo3f.write(10);
      delay(1000);
      servo3b.write(0);
      delay(1000);
      servo3f.write(90);
      delay(1000);
      servo3b.write(100);
    }
  } else if ((data[0] == 'D') || (data[0] == 'd')) {
    //r- l+
    if (data[1] == '+') {
      rotateWholex();
      servo1f.write(170);
      delay(1000);
      servo1b.write(0);
      delay(1000);
      servo1f.write(90);
      delay(1000);
      servo1b.write(100);
      rotateWholexMinus();
    } else if (data[1] == '-') {
      rotateWholex();
      servo1f.write(10);
      delay(1000);
      servo1b.write(0);
      delay(1000);
      servo1f.write(90);
      delay(1000);
      servo1b.write(100);
      rotateWholexMinus();
    } else if (data[1] == '2') {
      rotateWholex();
      servo1f.write(170);
      delay(1000);
      servo1b.write(0);
      delay(1000);
      servo1f.write(90);
      delay(1000);
      servo1b.write(100);
      delay(1000);
      servo1f.write(170);
      delay(1000);
      servo1b.write(0);
      delay(1000);
      servo1f.write(90);
      delay(1000);
      servo1b.write(100);
      rotateWholexMinus();
    }
  }
}

void rotateWholexMinus(){
  servo1b.write(0);
  servo3b.write(0);
  delay(500);
  servo4f.write(10);
  servo2f.write(170);
  delay(500);
  servo1b.write(100);
  servo3b.write(100);
  delay(500);
  servo4b.write(0);
  servo2b.write(0);
  delay(500);
  servo4f.write(90);
  servo2f.write(84);
  delay(500);
  servo4b.write(100);
  servo2b.write(100);
  delay(500);
}
void rotateWholex(){
  servo1b.write(0);
  servo3b.write(0);
  delay(500);
  servo4f.write(170);
  servo2f.write(10);
  delay(500);
  servo1b.write(100);
  servo3b.write(100);
  delay(500);
  servo4b.write(0);
  servo2b.write(0);
  delay(500);
  servo4f.write(90);
  servo2f.write(84);
  delay(500);
  servo4b.write(100);
  servo2b.write(100);
  delay(500);
}