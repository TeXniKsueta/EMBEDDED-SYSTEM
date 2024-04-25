
#define LED_25 2 // Уровень в баке соответсвутющий 25 процентам
#define LED_50 4 // Уровень в баке соответсвутющий 50 процентам
#define LED_75 7 // Уровень в баке соответсвутющий 75 процентам
#define LED_100 8 // Уровень в баке соответсвутющий 100 процентам
#define LED_KA4 11 // Индикатор, обозначащиюй, что вода НАЛИВАЕТСЯ в БАК
#define LED_VIKA4 12 // Индикатор, обозначащиюй, что вода ВЫЛИВАЕТСЯ из БАКА
#define LED_WARNING 13 // Индикатор основной ОШИБКИ (по уровню воды)
#define LED_WARNING_DAT4IK 9 // Индикатор ошибки основного датчика
#define LED_POPLAVOK A4 // Индикатор обозначающий включение аварийного датчика
#define PIN_POT_1     A0 // Пользовательский потенциометр для выбора желаемого количества воды
#define PIN_POT_2     A1 // Аварийный датчк, cлив, налив воды
volatile bool flag1; // Флаг1 проверки датчика
volatile unsigned long lastUpdateTime = 0; // Переменная для проверки времени
volatile int pot1del,pot2del; // Значения с датчика и потенциометра
volatile bool flag = false;  // Флаг проверки датчика
volatile int count = 0;  // Переменная, запоминающая количества воды в баке
volatile int count1 = 0; // Переменная, запоминающая количества воды в баке
volatile int count2 = 0; // Переменная, запоминающая количества воды в баке
volatile int count3 = 0; // Переменная, запоминающая количества воды в баке
volatile int count4 = 0; // Переменная, запоминающая количества воды в баке
volatile int potValue; // Переменная, для обнаружения резкого скачка значений
volatile int prevPotValue; // Прошлое значение переменной potValue
int rotat, brightn; // Значение с потенциометра
volatile int rotat1, brightn1;  // Значения с датчика
volatile int prevbrightn = 0; // Прошлое значение с основного датчика
volatile int prevbrightn1 = 0; // Прошлое значение с основного датчика
int button1 = 10; //  Пользовательская кнопка, для включения выбора уставки
int button2 = 5;  // Поплавковый датчик
int button3 = 6;  // Сброс ошибки
volatile int potValue1 = 0; 
void setup() {
  
  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);

  pinMode(LED_25, OUTPUT);
  pinMode(LED_50, OUTPUT);
  pinMode(LED_75, OUTPUT);
  pinMode(LED_100, OUTPUT);
  pinMode(LED_KA4, OUTPUT);
  pinMode(LED_VIKA4, OUTPUT);
  pinMode(LED_WARNING, OUTPUT);
  pinMode(LED_WARNING_DAT4IK, OUTPUT);
  pinMode(LED_POPLAVOK, OUTPUT);

}

void loop() 
{
  proverka(); // Функция первичной проверки системы
  sbros_owibki(); // Функция сброса ошибки
  vibor_ustavki(); // Пользовательская функция для выбора уставки
  vklu4enie_nasosov(); // Запоминание и включение насосов 
  poplavok(); // Реализация поплавкового датчика
 if (flag == true)
 {

  perekrut();

 }
 perekrut();
  Serial.print("Do ");
  Serial.println(brightn1);
  Serial.print("Posle ");
  Serial.println(prevbrightn1);
}
int proverka() {
  if (flag==false) {
    
    pot1del = analogRead(PIN_POT_2) / 4; // Считываем значение первого потенциометра
    delay(2000);
    pot2del = analogRead(PIN_POT_2) / 4; // Считываем значение первого потенциометра после задержки
    if (abs(pot2del > pot1del + 30))  { // Если разница между значениями потенциометра меньше на 30
      digitalWrite(LED_WARNING_DAT4IK, 1); // Включаем светодиод
     flag1 = false; // Устанавливаем flag1 в 0
    }
     else if (pot1del == pot2del)
      {
        digitalWrite(LED_WARNING_DAT4IK, LOW); // Выключаем светодиод
      }
      else {
        digitalWrite(LED_WARNING_DAT4IK, LOW); // Выключаем светодиод
    
    }
  }
      flag = true;    // Устанавливаем значение флага в 1
  
}
int sbros_owibki()
{

  int buttonStateDT = digitalRead(button3); // Считываем значение
  
  if (buttonStateDT == 1 && flag1 == false) // если флаг 0 и кнопна нажата
  {
  
 // vibor_ustavki();
 // vklu4enie_nasosov();
    digitalWrite(LED_WARNING_DAT4IK,0); // Выключаем светодиод
  }
}

int vibor_ustavki() {
  // Считываем состояние кнопки
  int buttonState = digitalRead(button1); // Считываем кнопку
  
  if (buttonState == 1) { 
    ustavka(); // Запоминаем текущее количество светодиодов
  } 
  else {
    // Выключаем все светодиоды при отпускании кнопки
    digitalWrite(LED_25, LOW);
    digitalWrite(LED_50, LOW);
    digitalWrite(LED_75, LOW);
    digitalWrite(LED_100, LOW);
  }
}

int ustavka() {
  // Считываем значение первого потенциометра
  rotat = analogRead(PIN_POT_1);
  brightn = rotat / 4;
  
  if (brightn > 64) {
    digitalWrite(LED_25, 1);
    digitalWrite(LED_50, 0);
    digitalWrite(LED_75, 0);
    digitalWrite(LED_100, 0);
    count = 1;

  }
  if (brightn > 128) {
    digitalWrite(LED_25, 1);
    digitalWrite(LED_50, 1);
    digitalWrite(LED_75, 0);
    digitalWrite(LED_100, 0);
  count1 = 1;
  }
  if (brightn > 192) {
    digitalWrite(LED_25, 1);
    digitalWrite(LED_50, 1);
    digitalWrite(LED_75, 1);
    digitalWrite(LED_100, 0);
    count2 = 1;

  }
  if (brightn > 250) { 
    digitalWrite(LED_25, 1);
    digitalWrite(LED_50, 1);
    digitalWrite(LED_75, 1);
    digitalWrite(LED_100, 1);
    count3 =1;

  }
  else {
    digitalWrite(LED_25, 0);
    digitalWrite(LED_50, 0);
    digitalWrite(LED_75, 0);
    digitalWrite(LED_100, 0);
    count4 = 1;
  }
}



int vklu4enie_nasosov() {
  rotat1 = analogRead(PIN_POT_2);
  brightn1 = rotat1 / 4;
  if (brightn1 > 64 && count >= 1) {
    digitalWrite(LED_25, 1);
    digitalWrite(LED_50, 0);
    digitalWrite(LED_75, 0);
    digitalWrite(LED_100, 0);
  }
  if (brightn1 > 128 && count1 >= 1) {
    digitalWrite(LED_25, 1);
    digitalWrite(LED_50, 1);
    digitalWrite(LED_75, 0);
    digitalWrite(LED_100, 0);
  }
  if (brightn1 > 192 && count2 >=1 ) {
    digitalWrite(LED_25, 1);
    digitalWrite(LED_50, 1);
    digitalWrite(LED_75, 1);
    digitalWrite(LED_100, 0);
  }  
  if (brightn1 > 250 && count3 >= 1) {
    digitalWrite(LED_25, 1);
    digitalWrite(LED_50, 1);
    digitalWrite(LED_75, 1);
    digitalWrite(LED_100, 1);
  }
  if (count4 == 0) {
    digitalWrite(LED_25, 0);
    digitalWrite(LED_50, 0);
    digitalWrite(LED_75, 0);
    digitalWrite(LED_100, 0);
  }
  if (brightn1 > brightn + 20) {
    digitalWrite(LED_WARNING, 1);
  }
  else {
    digitalWrite(LED_WARNING, 0);  
  }
  if (brightn1 > prevbrightn1) { // Вращение вправо
    digitalWrite(LED_KA4, HIGH);
    digitalWrite(LED_VIKA4, LOW);
    digitalWrite(LED_WARNING, LOW);
  }
  else if (brightn1 < prevbrightn1) { // Вращение влево
    digitalWrite(LED_KA4, LOW);
    digitalWrite(LED_VIKA4, HIGH);
    digitalWrite(LED_WARNING, LOW);
  }
  else { // Нет изменений на потенциометре
    digitalWrite(LED_KA4, LOW);
    digitalWrite(LED_VIKA4, LOW);
    digitalWrite(LED_WARNING, LOW);
  }
  prevbrightn1 = brightn1; // Сохраняем текущее значение яркости для следующей итерации
}
void poplavok() {

    int buttonStateP = digitalRead(button2); // Читаем значение кнопки
  
  if (buttonStateP == 1) // Если кнопка нажата
  {
  digitalWrite(LED_POPLAVOK, HIGH);
  
  }
  else {
    digitalWrite(LED_POPLAVOK, LOW);
  
  }
}
  
   void perekrut()
  {
    unsigned long currentTime = millis();
    
    int potValue1 = analogRead(PIN_POT_2)/4;

    if (currentTime - lastUpdateTime > 300)
    {
      currentTime = millis();
      if (potValue1 - prevPotValue > 50 && prevPotValue !=0)
      {
        digitalWrite(LED_WARNING_DAT4IK,1);
      }
     
      prevPotValue = potValue1;
    }

  }

  

    
  
  
