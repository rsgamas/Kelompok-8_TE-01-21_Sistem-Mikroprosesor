#include <GP2YDustSensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define pinDHT 3 //Pin 3 digunakan untuk output sensor DHT
#define pinGP2Y A0 //Pin analog A0 digunakan untuk outputsensor GP2Y1010AU0F 
#define pinLEDGP 12 //pin 12 digunakan untuk LED pada sensor GP2Y1010AU0F
#define pinLED 2 //Pin 2 digunakan untuk LED sebagai pengganti aktuator

const int lt = 30.00; //Batas suhu yang ditentukan
const int lh = 80.00; //Batas kelembapan yang ditentukan
const int ld = 300.00; //Batas densitas debu yang ditentukan


DHT dht(pinDHT,DHT11);
GP2YDustSensor dustSensor(GP2YDustSensorType::GP2Y1010AU0F, pinLEDGP, pinGP2Y);

void setup() {
  dustSensor.setBaseline(0.4); 
  dustSensor.setCalibrationFactor(1.1);
  Serial.begin(9600);
  Serial.println("Program Filter Udara");
  pinMode(pinLED, OUTPUT);
  dht.begin();
  dustSensor.begin();
}

void loop() {
  float h = dht.readHumidity(); //Pembacaan kelembapan oleh DHT
  float t = dht.readTemperature(); //Pembacaan suhu oleh DHT
  float dd = dustSensor.getDustDensity(); //Pembacaan densitas debu oleh GP2Y1010AU0F
 
  //Menampilkan hasil pembacaan DHT pada serial monitor Arduino IDE
  if (isnan(t)||isnan(h)) {
    Serial.println("failed to read from DHT11");
  } else {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %RH ");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
  }

  //Menampilkan hasil pembacaan GP2Y1010AU0F pada serial monitor arduino IDE
  if (isnan(dd)) {
    Serial.println("failed to read from GP2Y1010AU0F");
  } else {
    Serial.print("Dust density: ");
    Serial.print(dd);
    Serial.println(" ug/m3");
  }
  
  //Pengambilan keputusan berdasarkan data yang telah didapat
  if ((t>lt)||(h>lh)||(dd>ld)) {
    digitalWrite(pinLED, HIGH);
    Serial.println("Actuator ON");
  } else {
    digitalWrite(pinLED, LOW);
    Serial.println("Actuator OFF");
  }
delay(1000); //Delay 1s setiap pembacaan
}
