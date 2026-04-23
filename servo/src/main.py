import sys
import serial
import time
from PyQt5 import QtWidgets, QtCore
# Lưu ý: Thay 'servo_control_ui' bằng tên file .py mà bạn đã tạo từ file .ui
from servo_control import Ui_MainWindow 

class RobotArmApp(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        # --- CẤU HÌNH SERIAL ---
        # Thay 'COM3' bằng cổng thực tế của ESP32 (xem trong Device Manager)
        self.port = "COM5" 
        self.baudrate = 115200
        try:
            self.ser = serial.Serial(self.port, self.baudrate, timeout=0.1)
            time.sleep(2)  # Đợi ESP32 khởi động lại sau khi kết nối
            print(f"Đã kết nối thành công với {self.port}")
        except Exception as e:
            print(f"Lỗi: Không thể kết nối cổng {self.port}. {e}")
            self.ser = None

        # --- KẾT NỐI SLIDERS VỚI LOGIC ---
        # Sử dụng sliderMoved để gửi dữ liệu liên tục khi kéo
        self.ui.horizontalSlider.sliderMoved.connect(lambda val: self.send_servo_cmd(1, val))
        self.ui.horizontalSlider_2.sliderMoved.connect(lambda val: self.send_servo_cmd(2, val))
        self.ui.horizontalSlider_3.sliderMoved.connect(lambda val: self.send_servo_cmd(3, val))

        # Hoặc dùng valueChanged nếu muốn gửi cả khi nhấn phím mũi tên
        # self.ui.horizontalSlider.valueChanged.connect(lambda val: self.send_servo_cmd(1, val))

    def send_servo_cmd(self, servo_id, angle):
        """
        Gửi lệnh theo định dạng: s1=90\n
        Định dạng này khớp hoàn toàn với hàm sscanf trong code ESP32 của bạn.
        """
        if self.ser and self.ser.is_open:
            command = f"s{servo_id}={angle}\n"
            try:
                self.ser.write(command.encode('utf-8'))
                # In ra console để bạn theo dõi
                print(f"Gửi lệnh: {command.strip()}")
            except Exception as e:
                print(f"Lỗi khi gửi dữ liệu: {e}")

    def closeEvent(self, event):
        """Đóng cổng Serial khi tắt ứng dụng"""
        if self.ser and self.ser.is_open:
            self.ser.close()
            print("Đã đóng kết nối Serial.")
        event.accept()

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    # Tùy chỉnh style cho đẹp hơn (optional)
    app.setStyle("Fusion") 
    
    window = RobotArmApp()
    window.show()
    sys.exit(app.exec_())