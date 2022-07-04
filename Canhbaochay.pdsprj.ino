#include <LiquidCrystal.h>
LiquidCrystal lcd(9,8,7,6,5,4); //khai báo lcd số chân kết nối vào arduino
int sensorPin = A0; //khai báo senserPin
int ledred = 12; //khai báo chân đèn ledred 12
int ledgreen = 13; //khai báo chân đèn ledgreen 13
int buzzer = 11;//khai báo chân còi  11
String notification; 
void setup() {
pinMode(ledred, OUTPUT); //đặt chế độ ledred OUPUT
pinMode(ledgreen, OUTPUT);//đặt chế độ ledgreen OUPUT
pinMode(buzzer, OUTPUT);//đặt chế độ còi OUPUT
Serial.begin(9600);//giao tiếp kết nối ở tốc độ 9600
lcd.begin(16,2);//kích thước lcd 16x2 
}
void loop() {
  //đọc dữ liệu từ cảm biến
int reading = analogRead(sensorPin);
//tính ra giá trị hiệu điện thế (đơn vị Volt) từ giá trị cảm biến
float voltage = reading*5.0/1023.0;
//thì ta chỉ việc nhân voltage cho 100 là ra được nhiệt độ
float temp = voltage*100;
Serial.println(temp);

if (temp < 70) //điều kiện nhiệt độ <70 độ
{
digitalWrite(ledred,HIGH); // đèn đỏ sáng
digitalWrite(ledgreen,LOW);// đèn xanh tắt
notification = "Binh thuong";  // in ra thông báo "Bình thường"
}
else // nhiệt độ lớn hơn hoặc bằng 70
{
digitalWrite(ledgreen,HIGH);// đèn xanh sáng
digitalWrite(ledred,LOW);// đèn đỏ tắt
notification = "Canh bao chay";// in ra thông báo "Cảnh báo cháy"
tone(11,2093,250); // còi hú
}
lcd.setCursor(0,0); // đưa con trỏ đến hàng 0 cột 0
lcd.print(notification);// in ra thông báo trên màn LCD
lcd.setCursor(0,1);// đưa con trỏ đến hàng 1 cột 0
lcd.print("Nhiet do: "); // in ra nhiệt độ
lcd.print(temp);// xuất nhiệt độ
lcd.print("");
delay(500); // thời gian trễ 0.5s
lcd.clear();// giải phóng màn lcd
}
