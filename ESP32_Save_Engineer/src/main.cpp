#include <Arduino.h>

#define ACS_PIN 36
#define MOCK 1

const float ACS712_SENSITIVITY = 0.185;  // Độ nhạy của ACS712 (V/A)
const float V_REF = 3.3;                 // Điện áp tham chiếu (V)
const int SAMPLES = 100;                 // Số lượng mẫu để lấy trung bình
float zeroCurrentOffset = 0;             // Giá trị trung bình khi không có dòng điện

// Hàm mock tạo giá trị điện áp giả lập (từ 1V đến 5V)
float mockData() {
  return 1 + ((float)(random(0, 1000)) / 200);  // Trả về giá trị từ 1.0 đến 5.0V
}

// Hiệu chỉnh để lấy giá trị zero khi không có dòng điện đi qua
float calibrateZeroCurrent(int pin) {
  float total = 0;
  for (int i = 0; i < SAMPLES; i++) {
    #if MOCK
      total += mockData();  // Sử dụng giá trị mock
    #else 
      total += analogRead(pin);  // Đọc giá trị thực từ cảm biến
    #endif
    delay(10);
  }

  // Tính giá trị trung bình
  float analogValue = total / SAMPLES;

  // Tính toán điện áp zeroCurrentOffset
  #if MOCK
    float voltage = analogValue;  // Trong chế độ mock, giá trị mockData() đã là điện áp
  #else
    float voltage = (analogValue / 4095) * V_REF;  // Với cảm biến thực, chuyển đổi từ ADC sang điện áp
  #endif  

  return voltage;  // Trả về điện áp zero (zeroCurrentOffset)
}

// Hàm tính toán dòng điện từ giá trị analog
float readCurrent(int pin) {
  float total = 0;
  for (int i = 0; i < SAMPLES; i++) {
    #if MOCK
      total += mockData();  // Sử dụng mock data
    #else 
      total += analogRead(pin);  // Đọc từ chân analog
    #endif
    delay(10);
  }

  float analogValue = total / SAMPLES;
  
  // Chuyển đổi giá trị ADC sang điện áp hoặc sử dụng giá trị mock
  float voltage;
  #if MOCK
    voltage = analogValue;  // Trong chế độ mock, giá trị đã là điện áp
  #else
    voltage = (analogValue / 4095) * V_REF;  // Chuyển đổi giá trị ADC sang điện áp
  #endif

  // Tính toán dòng điện dựa trên điện áp và zeroCurrentOffset
  float current = (voltage - zeroCurrentOffset) / ACS712_SENSITIVITY;
  
  return current;  // Trả về dòng điện đo được
}

void setup() {
  Serial.begin(9600);
  Serial.println("Project starting....");

  // Hiệu chuẩn zeroCurrentOffset khi không có dòng điện
  zeroCurrentOffset = calibrateZeroCurrent(ACS_PIN);
  Serial.print("Zero Current Offset: ");
  Serial.println(zeroCurrentOffset);
}

void loop() {
  // Đọc dòng điện từ cảm biến (hoặc giá trị mock)
  float current = readCurrent(ACS_PIN);

  // In ra dòng điện đo được
  Serial.print("Measured Current: ");
  Serial.println(current);

  delay(1000);  // Chờ một giây trước khi lấy mẫu tiếp theo
}
