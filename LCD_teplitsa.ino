#include <LiquidCrystal_I2C.h>      // подключаем библиотеку lcd
LiquidCrystal_I2C lcd(0x27, 8, 2); // адрес, столбцов, строк
#include <microDS18B20.h>          //подключаем библиотеку датчика температуры
MicroDS18B20<2> sensor;
#define solPin A0 // порт для подключения датчика
int minsol = 0; // минимальное значение влажности почвы
int sol;
//int value;                                                                          //УБРАТЬ 
//int sensorValue;                                                                    //УБРАТЬ 
//int percentage;                                                                     //УБРАТЬ 
byte kaplya[]   = {B00100,B00100,B01110,B11011,B11101,B11101,B11111,B01110}; // Символ капли
byte RIP1[] = {B10100,B01000,B10100,B00000,B00000,B11111,B00000,B00000}; // Символ левой половины смайлика
byte RIP2[] = {B00101,B00010,B00101,B00000,B00000,B11111,B01111,B00110}; // Символ правой половины смайлика
byte termometr[] = {B00100,B01010,B01010,B01110,B11111,B11111,B11101,B01110};// Символ градусника

//int min = 200; //drowned in water                                                       //УБРАТЬ 
//int max = 500; //dry soil                                                               //УБРАТЬ 
 
void setup() {
  lcd.init();               // инициализация
  lcd.noBacklight();
  Serial.begin(9600);
  pinMode(solPin, INPUT);
  lcd.createChar(0, kaplya); // Создаем символ под номером 1
  lcd.createChar(1, kaplya); // Создаем символ под номером 2
  lcd.createChar(2, kaplya); // Создаем символ под номером 3
  lcd.createChar(3, kaplya); // Создаем символ под номером 4
  lcd.createChar(4, kaplya); // Создаем символ под номером 5
  lcd.createChar(5, RIP1); // Создаем символ под номером 6
  lcd.createChar(6, RIP2); // Создаем символ под номером 7
  lcd.createChar(7, termometr); // Создаем символ под номером 8
  //sensorValue = analogRead(A0);                                                      //УБРАТЬ 
  //sensorValue = map(sensorValue, 20, 100, min, max);  // соотношение значений и процентов    //УБРАТЬ 
  //percentage = (float)((sensorValue - min) * 100) / (max - min);                      //УБРАТЬ 
}
void loop() {
  sensor.requestTemp(); // запрос температуры
  delay(1000);          // ждём
  sol = analogRead(solPin);
  lcd.home();           // курсор в 0,0
  //lcd.setCursor(5, 0); // 6 столб, 1 строка                                          //УБРАТЬ 
  //lcd.write(sensorValue);                                                                  //УБРАТЬ 
  lcd.setCursor(7, 0); // 8 столб, 1 строка
  lcd.write('%');
  lcd.setCursor(0, 1); // 0 столб, 2 строка
  lcd.write(7);
  lcd.write(' ');
  lcd.print(sensor.getTemp(), 1); // текущая температура
  lcd.write(223);       // градус
  lcd.write('C');
 Serial.print(sol); //печать значения влажности
  Serial.print(' ');
 // Serial.print(percentage);                                                              //УБРАТЬ 
                 

  lcd.setCursor(0, 0);
  if (sol <= 310){
    lcd.write(0);
    lcd.write(1);
    lcd.write(2);
    lcd.write(3);
    lcd.write(4);}
  else if (sol >= 311 && sol<= 330){
    lcd.write(0);
    lcd.write(1);
    lcd.write(2);
    lcd.write(3);
    lcd.write(' ');}
  else if (sol >= 331 && sol<= 340){
    lcd.write(0);
    lcd.write(1);
    lcd.write(2);
    lcd.write(' ');
    lcd.write(' ');}
  else if (sol >= 341 && sol<= 390){
    lcd.write(0);
    lcd.write(1);
    lcd.write(' ');
    lcd.write(' ');
    lcd.write(' ');}
  else if (sol >= 391 && sol<= 400){
    lcd.write(0);
    lcd.write(' ');
    lcd.write(' ');
    lcd.write(' ');
    lcd.write(' ');}
    else if (sol >= 401){    //ok
    lcd.write(5);
    lcd.write(6);
    lcd.write(' ');
    lcd.write(' ');
    lcd.write(' ');}

}


//1. Не получается вывести влажность на дисплей// получилось, но она не меняется .. ГОТОВО
//2. Не получается убирать лишние капли, при изменении влажности .. ГОТОВО
//3. Не получается вывести букву 'Т' на дисплей).. ГОТОВО
//4. Температура сдвигается с 0.00, когда я дотрагиваюсь до датчика (мб. когда происходит скачок температуры).. ГОТОВО
//5. Осталось понять как сделать влажность в процентах
//6. Датчик показывает хуйню.Эксперимент не удался. МБ нужна калибровка
