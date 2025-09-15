/*
  DVM1 Initial Test1

  Read ADC and convert to voltage at R divider input.
  Display Vinput at PC screen
  Manually set voltage range using variable Vrange in Setup()
*/

int Vrange = 0;               // 0 - 4V Range, 1 - 20V Range
int ADCword = 0;              // ADC value (counts)
float Vinput = 0;             // input voltage (V)

const int SW1 = 12;           // digital bits - control sw1,2
const int SW2 = 13;

float R1 = 806000;            // R divider
float R2 = 200000;     
float Kdiv = 1;           

// the setup routine runs once *****************************
void setup() { 
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // configure digital pins
  pinMode(SW1, OUTPUT);    // set as output
  pinMode(SW2, OUTPUT);    // set as output

  // set voltage range manually with variable
  Vrange = 0;    // 0 - 4V Range, 1 - 20V Range

  // set Vrange switches at R Divider
  if (Vrange == 0) {  // 4V Range
    // sw to straight in
    digitalWrite(SW1, LOW); // sw1 ON
    digitalWrite(SW2, HIGH); // sw2 OFF
  }
  else {              // 20V Range
    // sw to divider tap
    digitalWrite(SW1, HIGH); // sw1 OFF
    digitalWrite(SW2, LOW); // sw2 ON
  }
}

// the loop routine runs continuously **********************
void loop() {

  // read analog input from ADC at pin A0
  ADCword = analogRead(A0);
  
  // calc input divider scaling
  if (Vrange == 0) {  // 4V Range
    Kdiv = 1;
  }
  else {              // 20V Range
    Kdiv = R2/(R1+R2);
  }

  // convert ADC counts to input voltage
  // Vinput = ADCvalue * Vref/2^N * 1/Kdiv
  Vinput = ADCword * (5.0 / 1024.0) * 1/Kdiv ;

  // print out value to computer as ASCII
  Serial.print("Vinput,ADCword,Vrange\t");
  Serial.print(Vinput,4);
  Serial.print("\t");
  Serial.print(ADCword);
  Serial.print("\t");
  Serial.println(Vrange);

  // read Vrange Pushbutton (skip for initial test)

  // if Pushbutton pressed, then change Vrange (skip for initial test)

  // time delay (ms) for approx 4 readings per second
  delay(250);   
}
