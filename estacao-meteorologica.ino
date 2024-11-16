#include <Adafruit_BMP280.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <math.h> 

// Declarações dos sensores
DHT dht(2, DHT22); // Sensor DHT22 no pino digital 2
Adafruit_BMP280 bmp; // Objeto BMP280 para o sensor de pressão
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 16x2 no endereço I2C 0x27

// Declaração de variáveis
int bin;
float tensao, tempLM35, umidDHT22, res, lum, press, tempBMP, altitude;

// Define caracteres personalizados
byte cedilha[] = {
  0b00000,
  0b00000,
  0b00000,
  0b01110, // Parte superior do "ç"
  0b10000,
  0b10000,
  0b01110,
  0b00100  // Parte inferior do "ç"
};

byte acento_agudo[] = {
  0b00100, // Parte superior do acento agudo para "ó"
  0b00000,
  0b01110,
  0b10001,
  0b10001,
  0b01110,
  0b00000,
  0b00000
};

byte til[] = {
  0b00000, 
  0b00101, 
  0b01010,
  0b00000,
  0b01110, // Corpo da letra "ã"
  0b10001,
  0b11111,
  0b10001
};

byte maisMenos[] = { 
  0b00100, //   +
  0b11111, //  -----
  0b00100, //   +
  0b00000, 
  0b00000, 
  0b11111, //  -----
  0b00000, 
  0b00000 
};

void setup() {
  Serial.begin(9600); // Inicializa a comunicação Serial
  dht.begin(); // Inicializa o sensor DHT22
  bmp.begin(0x76); // Inicializa o sensor BMP280
  lcd.init(); // Inicializa o LCD
  lcd.backlight(); // Liga a luz de fundo do LCD

  // Carrega os caracteres personalizados no LCD
  lcd.createChar(0, cedilha);         // Carrega "ç"
  lcd.createChar(1, acento_agudo);    // Carrega "ó"
  lcd.createChar(2, til);             // Carrega "ã"
  lcd.createChar(3, maisMenos);       // Carrega "±"
  
  // Exibe "Estação Meteorológica", nomes e turma uma vez
  lcd.clear();
  lcd.print("Esta");
  lcd.write(byte(0));  // Exibe "ç"
  lcd.write(byte(2));  // Exibe "ã"
  lcd.print("o");
  lcd.setCursor(0, 1);
  lcd.print("Meteorol");
  lcd.write(byte(1));  // Exibe "ó"
  lcd.print("gica");
  delay(2000);

  lcd.clear();
  lcd.print("Micaele Gomes");
  delay(2000);

  lcd.clear();
  lcd.print("1B - InstruMed");
  delay(2000);
}

void loop() {
  // Leitura do sensor LM35
  bin = analogRead(A0); // Leitura analógica do LM35
  tensao = (bin / 1024.0) * 5.0; // Converte para tensão
  tempLM35 = 98.29368086 * tensao + 0.029367031; // Calcula a temperatura com dados da calibração
  
  // Exibe a temperatura do LM35 com incerteza no Serial Monitor
  Serial.print("\n\nDado LM35: ");
  Serial.print(bin);
  Serial.print("\nTensão LM35 [V]: ");
  Serial.print(tensao, 6);
  Serial.print("\nTemperatura LM35 [ºC]: ");
  Serial.print(tempLM35, 1); // Exibe com uma casa decimal
  Serial.print(" ± 1,1");

  // Exibe a temperatura no LCD com a incerteza para o sensor LM35
  lcd.clear();
  lcd.print("Temperatura:");
  lcd.setCursor(0, 1);
  lcd.print(tempLM35, 1);    // Exibe o valor lido com uma casa decimal
  lcd.print(" ");            // Espaço antes do símbolo
  lcd.write(byte(3));        // Exibe o caractere "±" apenas para a incerteza
  lcd.print(" 1,1 ");
  lcd.print((char)223);      // Exibe o símbolo de grau
  lcd.print("C");
  delay(2000); // Exibe por 2 segundos

  // Leitura do sensor DHT22
  umidDHT22 = dht.readHumidity(); // Leitura da umidade
  umidDHT22 = 1.231685541 * umidDHT22 -13.16915295; // Ajuste de calibração
  
  // Exibe a umidade do DHT22 com incerteza no Serial Monitor
  Serial.print("\n\nUmidade [%]: ");
  Serial.print(umidDHT22, 1); // Exibe com uma casa decimal
  Serial.print(" ± 2,0");

  // Exibe a umidade do DHT22 com incerteza no LCD
  lcd.clear();
  lcd.print("Umidade:");
  lcd.setCursor(0, 1);
  lcd.print(umidDHT22, 1);    // Exibe a umidade com uma casa decimal
  lcd.print(" ");             // Espaço antes do símbolo
  lcd.write(byte(3));         // Exibe o caractere "±" apenas para a incerteza
  lcd.print(" 2,0 ");
  lcd.print("%");
  delay(2000); // Exibe por 2 segundos

  // Leitura do sensor LDR para luminosidade
  bin = analogRead(A1); // Leitura analógica do LDR
  tensao = (bin / 1024.0) * 5.0; // Converte para tensão
  res = tensao * 100.0 / (5.0 - tensao); // Calcula a resistência
  lum = pow(10, 7.02094664 - 1.415562415 * log10(res)); // Calcula a luminosidade em Lux
  
  // Exibe a luminosidade no LCD
  lcd.clear();
  lcd.print("Luminosidade:");
  lcd.setCursor(0, 1);
  lcd.print(lum);
  lcd.print(" lx");
  delay(2000); // Exibe por 2 segundos

  // Leitura do sensor de pressão BMP280
  press = bmp.readPressure() / 100; // Lê pressão e converte para hPa
  tempBMP = bmp.readTemperature();  // Lê temperatura do BMP280
  altitude = bmp.readAltitude(1013.25); // Calcula a altitude com base na pressão do nível do mar (1013.25 hPa)
  
  // Exibe a pressão no LCD
  lcd.clear();
  lcd.print("Press");
  lcd.write(byte(2));       // Exibe "ã"
  lcd.print("o:");
  lcd.setCursor(0, 1);
  lcd.print(press);          // Exibe o valor lido
  lcd.print(" ");            // Espaço antes do símbolo
  lcd.write(byte(3));        // Exibe o caractere "±" apenas para a incerteza
  lcd.print(" 0,12 ");
  lcd.print("hPa");          // Corrigido para exibir "hPa" com "A" correto
  delay(2000); // Exibe por 2 segundos

  // Exibe a altitude no LCD com incerteza de ± 1 m
  lcd.clear();
  lcd.print("Altitude:");
  lcd.setCursor(0, 1);
  lcd.print(altitude, 1); // Exibe o valor lido com uma casa decimal
  lcd.print(" ");
  lcd.write(byte(3));        // Exibe o caractere "±"
  lcd.print(" 1,0 m");
  delay(2000); // Exibe por 2 segundos
}
