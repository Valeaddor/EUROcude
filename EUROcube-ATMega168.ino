#include <EEManager.h>
#include <EncButton.h>

#define LOW_LEVEL 2  // пин подключения нижено датчика (критически малого уровня) воды
#define ON_LEVEL 3   // пин подключения датчика воды малого уровня (требуется включение насоса)
#define OFF_LEVEL 4  // пин подключения датчика воды достаточного уровня (требуется выключение насоса)
#define HIGH_LEVEL 5  // пин подключения верхнего датчика (критически высогоко уровня) воды
#define RELAY_PIN 6 // пин подключения реле насоса
#define TONE_PIN 7 // пин подключения динамика
#define AUTO_PIN 8 // пин подключения светодиода атоматического режима работы
#define MODE_PIN 9 // пин подключения кнопки управления


// блок 1 - структура
struct DataBlock {
  bool Auto = false; // ремиж работы "ручной" = false, "автоматический" = true
  uint32_t run_count = 0; // количество включений насоса
};

DataBlock ee_data;

EEManager mem(ee_data);
EncButton<EB_TICK, MODE_PIN> btn(INPUT_PULLUP);

byte on_level,off_level,low_level,high_level = 0;
//byte mode_bt;
bool pump = false;
bool Too_High_Level = false;
bool Too_Low_Level = false;
bool Need_Pump = false;
bool Sensor_Error = false;
bool Normal_Work = true;
bool Alarm_Off = false;


void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(AUTO_PIN, OUTPUT);
  pinMode(TONE_PIN, OUTPUT);
  pinMode(LOW_LEVEL, INPUT);
  pinMode(HIGH_LEVEL, INPUT);
  pinMode(ON_LEVEL, INPUT);
  pinMode(OFF_LEVEL, INPUT);
//  pinMode(MODE_PIN, INPUT_PULLUP); // делается в инициализации конструктора кнопки

  
  Serial.begin(9600);  // можно подключить BT модуль для мониторинга
  
  byte stat = mem.begin(0, 'v');
  if(stat > 1) Mem_Error();

  Serial.print("run_count: ");
  Serial.println(ee_data.run_count);

  if(ee_data.Auto) digitalWrite(AUTO_PIN,HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:

  mem.tick();

  btn.tick();

  readSensors();

  checkSerial();

  if(Sensor_Error) {
    SensorError();
  }

  if(Too_High_Level) {
    if(!Alarm_Off) {
      if(btn.state()) Alarm_Off = true;
      else HighAlarm();
    }
  return;
  }  
  else if(Too_Low_Level)
    if(!Alarm_Off) {
      if(btn.state()) Alarm_Off = true;
      else LowAlarm();
    }

  if(Normal_Work && btn.held()) {
    ModeBeep();
    ee_data.Auto = !ee_data.Auto;
    digitalWrite(AUTO_PIN,!digitalRead(AUTO_PIN));
    mem.update();
  }

  if(ee_data.Auto) {
    if(pump && !Need_Pump) WaterPump(false);
    else if(Need_Pump && !pump) WaterPump(true);
  } else if(btn.click()) {
    if(pump && !Need_Pump) WaterPump(false);
    else if(Need_Pump && !pump) WaterPump(true);
    else WaterPump(!pump);
    
  }

}

void readSensors() {

  Too_High_Level = false;
  Too_Low_Level = false;
  Normal_Work = false;
  
  low_level = digitalRead(LOW_LEVEL);
  on_level = digitalRead(ON_LEVEL);
  off_level = digitalRead(OFF_LEVEL);
  high_level = digitalRead(HIGH_LEVEL);

  if(high_level&&off_level&&on_level&&low_level) {
    if(pump) { 
      WaterPump(false); 
      Alarm_Off = true; 
      }
    else Too_High_Level = true;
    return;
  }
  
  if(!low_level && !on_level && !off_level && !high_level) {
    Too_Low_Level = true;
    return;
  }
  
  if(low_level == true && on_level == true && off_level == false && high_level == false) {
    if(!pump) { 
      Normal_Work = true; 
      Alarm_Off = false; 
    }
  return;
  }
  
  if(low_level == true && on_level == false && off_level == false && high_level == false) {
    Need_Pump = true;
    return;
  }
  
  if(low_level && on_level && off_level) {
    Need_Pump = false;
    return;
  }
  
  Sensor_Error = true;
    
}

void HighAlarm() {

  Normal_Work = false;
  Serial.println("HighAlarm");
  tone(TONE_PIN, 800, 500);
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  delay(500);
  tone(TONE_PIN, 900, 500);
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  delay(500);
}

void LowAlarm() {

  Normal_Work = false;
  Serial.println("LowAlarm");
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  tone(TONE_PIN, 400, 500);
  delay(500);
  tone(TONE_PIN, 550, 500);
  delay(500);
 
}

void WaterPump(bool pump_mode) {

  Normal_Work = false;
  Alarm_Off = false;
  
  if(!pump_mode) {
    digitalWrite(RELAY_PIN,LOW);
    digitalWrite(LED_BUILTIN,LOW);
    pump = false;
    } 
    else {
    if(!pump) pump = true;
    if(!digitalRead(RELAY_PIN)) { 
      digitalWrite(RELAY_PIN, HIGH);
      ee_data.run_count++;
      mem.update();
      }
    digitalWrite(LED_BUILTIN,HIGH);
    }
}

void SensorError() {

  Normal_Work = false;

  Serial.println("SensorError");
  while(true) {
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
    delay(2000);
  }
}

void Mem_Error() {

  Normal_Work = false;
  Serial.println("Mem_Error");
  while(true) {
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
    delay(100);
  }
  
}

void ModeBeep() {

  tone(TONE_PIN,715,250);
}

void checkSerial() {

  if (Serial.available()) {
    while(Serial.available()) {
      Serial.read();
      }
    Serial.print("run_count: ");
    Serial.println(ee_data.run_count);
    Serial.print("Auto: ");
    Serial.println(ee_data.Auto);
    Serial.println();
    Serial.print("low_level = ");
    Serial.println(low_level);
    Serial.print("on_level = ");
    Serial.println(on_level);
    Serial.print("off_level = ");
    Serial.println(off_level);
    Serial.print("high_level = ");
    Serial.println(high_level);
    Serial.println();
    Serial.print("pump = ");
    Serial.println(pump);
    Serial.print("Need_Pump = ");
    Serial.println(Need_Pump);
    Serial.print("Normal_Work = ");
    Serial.println(Normal_Work);
    Serial.print("Alarm_Off = ");
    Serial.println(Alarm_Off);
  }

}
