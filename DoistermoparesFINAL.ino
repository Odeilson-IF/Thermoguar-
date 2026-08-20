#include <SPI.h>
#include <Adafruit_MAX31856.h>

// Pinos de chip select (CS)
#define MAX31856_CS1 10
#define MAX31856_CS2 7

// Criação dos objetos dos sensores
Adafruit_MAX31856 max31856_1 = Adafruit_MAX31856(MAX31856_CS1);
Adafruit_MAX31856 max31856_2 = Adafruit_MAX31856(MAX31856_CS2);

// Parâmetros de calibração (ajuste conforme necessário)

const double m1 = 1.01073;
const double b1 = -0.52651;

// Use valores diferentes se quiser calibrar os dois separadamente

const double m2 = 1.01504;
const double b2 = -0.66818;

unsigned long contador = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10);

  SPI.begin();

  // Inicializa os sensores
  if (!max31856_1.begin()) {
    Serial.println("Erro ao iniciar MAX31856 #1!");
    while (1);
  }

  if (!max31856_2.begin()) {
    Serial.println("Erro ao iniciar MAX31856 #2!");
    while (1);
  }

  // Define o tipo de termopar
  max31856_1.setThermocoupleType(MAX31856_TCTYPE_K);
  max31856_2.setThermocoupleType(MAX31856_TCTYPE_K);
}

void loop() {
  double T1 = max31856_1.readThermocoupleTemperature();
  double T2 = max31856_2.readThermocoupleTemperature();

  // Aplica calibração individual
  double T1_c = m1 * T1 + b1;
  double T2_c = m2 * T2 + b2;


  Serial.print("Tempo: ");
  Serial.print(contador);
  Serial.print(" s | T1: ");
  Serial.print(T1_c, 2);
  Serial.print(" °C | T2: ");
  Serial.print(T2_c, 2);
  Serial.println(" °C");

  contador++;
  delay(1000);
}