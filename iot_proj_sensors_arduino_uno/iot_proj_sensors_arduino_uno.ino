// turbidity sensor
#define TURBIDITY_PIN A0

// pH sensor
#define PH_PIN A1
#define TEMPARATURE_PIN A2

float calibration_value = 0;
float avg_ph, avg_temp; 
int ph_arr[10],temp_arr[10];

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}

void setup() {
  Serial.begin(115200);
}

void loop() {
   //turbidity sensor
  float volt = 0;
  float ntu = 0;
    for(int i=0; i<800; i++)
    {
        volt += ((float)analogRead(TURBIDITY_PIN)/1023)*5;
    }
    volt = volt/800;
    volt = round_to_dp(volt,2);
    volt += 1;
    Serial.println(volt);
    if(volt < 2.5){
      ntu = 3000;
    }else{
      ntu = -1120.4*square(volt)+5742.3*volt-4353.8; 
    }

  float turb = ntu;
  int turbInt = turb;
  float turbFrac= turb - turbInt;
  int turbDec = trunc(turbFrac * 10000);

  float temp = analogRead(TEMPERATURE_PIN;

  int tempInt = temp;
  float tempFrac = temp - tempInt;
  int tempDec = trunc(tempFrac * 10000);

  float ph = analogRead(PH_PIN);
  int phInt = ph;
  float phFrac = ph - phInt;
  int phDec = trunc(phFrac * 10000);

  char data[1024];
  sprintf(data, "{\"turbidity\": \"%d.%04d\", \"temperature\": \"%d.%04d\", \"ph\": \"%d.%04d\"}", turbInt, abs(turbDec), tempInt, abs(tempDec), phInt, abs(phDec));
  Serial.println(data);

  delay(1000);
}
