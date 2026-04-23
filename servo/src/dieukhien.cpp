//Khai báo thư viện và biến toàn cục
#include <Arduino.h>
#include <ESP32Servo.h>

Servo myservo1, myservo2, myservo3;  // create servo object to control servos
int pos1 = 0;
int pos2 = 0;
int pos3 = 0;

//Hàm chỉ chạy đúng 1 lần khi reset hoặc khởi động lại thiết bị
void setup(){
   //Khai báo chân GPIO cho các servo
   myservo1.attach(13); // attaches on GPIO 13
   myservo2.attach(12); // attaches on GPIO 12
   myservo3.attach(14); // attaches on GPIO 14

   /*Khởi động Serial để giao tiếp với máy tính qua cổng USB
   với tốc độ 115200 baud */
   Serial.begin(115200); // monitor speed
   Serial.setTimeout(10000); // 10 giây

   // Thiết lập tần số PWM cho servo (thường là 50 Hz)
   myservo1.setPeriodHertz(50); // standard 50 hz servo
   myservo2.setPeriodHertz(50); // standard 50 hz servo
   myservo3.setPeriodHertz(50); // standard 50 hz servo

   // In ra hướng dẫn sử dụng trên Serial Monitor
   Serial.println("Servo is ready");
   Serial.println("Use format: s1=90 or s2=45 or s3=120"); // instruction
}

//Hàm chạy liên tục sau khi hàm setup() hoàn thành
void loop(){

  //Kiểm tra xem nếu có dữ liệu được gửi từ máy tính qua Serial Monitor thì đọc và xử lý
  if (Serial.available()){
      //Đọc dữ liệu từ Serial Monitor cho đến khi gặp ký tự xuống dòng '\n'
     String s = Serial.readStringUntil('\n');
     s.trim(); // loại bỏ khoảng trắng đầu cuối nếu có
     
      // Biến tạm để lưu số servo và góc điều khiển
     int servoNum = 0; // servo index (1,2,3)
     int angle = 0;    // input angle

     /* Sử dụng sscanf để phân tích chuỗi đầu vào theo định
      dạng "sX=Y" trong đó X là số servo (1-3) và Y là góc (0-180) */
     if (sscanf(s.c_str(), "s%d=%d", &servoNum, &angle) == 2){

        // check valid angle
        if (angle >= 0 && angle <= 180){

           // control each servo separately
           if (servoNum == 1){
              pos1 = angle;
              myservo1.write(pos1); // move servo 1
              Serial.println("Servo 1 moved to position:");
              Serial.println(pos1);
           }

           else if (servoNum == 2){
              pos2 = angle;
              myservo2.write(pos2); // move servo 2
              Serial.println("Servo 2 moved to position:");
              Serial.println(pos2);
           }

           else if (servoNum == 3){
              pos3 = angle;
              myservo3.write(pos3); // move servo 3
              Serial.println("Servo 3 moved to position:");
              Serial.println(pos3);
           }

           else{
              Serial.println("Invalid servo number (1-3)");
           }
        }

        else{
           Serial.println("Invalid position (0-180 only)");
        }
     }

     else{
        Serial.println("Wrong format! Example: s1=90");
     }
  }
}
