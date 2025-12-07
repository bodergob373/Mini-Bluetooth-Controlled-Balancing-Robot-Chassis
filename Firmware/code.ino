#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <BluetoothSerial.h>

// ------------------------ Pin definitions ------------------------
#define LEFT_DIR_PIN 35
#define RIGHT_DIR_PIN 32
#define LEFT_PWM_PIN 34
#define RIGHT_PWM_PIN 33
#define I2C_SCL 22
#define I2C_SDA 21

// ------------------------ Motor configuration ------------------------
bool LEFT_REVERSED = false;
bool RIGHT_REVERSED = false;
const int PWM_FREQ = 5000; // Hz
const int PWM_RESOLUTION = 8; // bits (0-255)
const int PWM_LEFT_CHANNEL = 0;
const int PWM_RIGHT_CHANNEL = 1;
// PWM scaling from 20% to 100% (0 RPM -> max)
float pwmMin = 0.2;
float pwmMax = 1.0;

// ------------------------ IMU setup ------------------------
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

// ------------------------ Control variables ------------------------
float forwardSpeed = 0.0; // Forward/backward command
float rotationSpeed = 0.0; // Rotation/turn command

// ------------------------ PID / tuning variables ------------------------
float Kp = 15.0; // Proportional gain
float Ki = 0.0; // Integral gain
float Kd = 0.8; // Derivative gain
float targetAngle = 0.0; // Upright position

// ------------------------ Internal variables ------------------------
float angle = 0.0;
float angleRate = 0.0;
float lastError = 0.0;
float integral = 0.0;

// ------------------------ Bluetooth setup ------------------------
BluetoothSerial SerialBT;
unsigned long lastCommandTime = 0;
unsigned long sleepthreshold = 1000; // milliseconds, adjust as needed

void setup() {
  Serial.begin(115200);
  
  // Setup Bluetooth
  SerialBT.begin("BalancingRobot"); // Bluetooth device name
  Serial.println("Bluetooth started, waiting for connections...");

  // Setup pins
  pinMode(LEFT_DIR_PIN, OUTPUT);
  pinMode(RIGHT_DIR_PIN, OUTPUT);

  ledcSetup(PWM_LEFT_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(PWM_RIGHT_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(LEFT_PWM_PIN, PWM_LEFT_CHANNEL);
  ledcAttachPin(RIGHT_PWM_PIN, PWM_RIGHT_CHANNEL);

  // Setup I2C
  Wire.begin(I2C_SDA, I2C_SCL);

  // Initialize IMU
  if (!bno.begin()) {
    Serial.println("BNO055 not detected");
    while (1);
  }
  bno.setExtCrystalUse(true);
  delay(1000);
}

void loop() {
  // Check for Bluetooth commands
  if (SerialBT.available()) {
    String cmd = SerialBT.readStringUntil(';');
    if (cmd.startsWith("(") && cmd.endsWith(")")) {
      // Remove parentheses
      cmd = cmd.substring(1, cmd.length() - 1);
      // Find comma position
      int commaIndex = cmd.indexOf(',');
      if (commaIndex != -1) {
        String forwardStr = cmd.substring(0, commaIndex);
        String rotationStr = cmd.substring(commaIndex + 1);
        // Parse floats
        float newForward = forwardStr.toFloat();
        float newRotation = rotationStr.toFloat();
        // Update variables
        forwardSpeed = newForward;
        rotationSpeed = newRotation;
        lastCommandTime = millis();
        Serial.printf("Updated: forwardSpeed=%.2f, rotationSpeed=%.2f\n", forwardSpeed, rotationSpeed);
      }
    }
  }

  // Check for timeout
  if (millis() - lastCommandTime > sleepthreshold) {
    forwardSpeed = 0.0;
    rotationSpeed = 0.0;
  }

  sensors_event_t event;
  bno.getEvent(&event);

  // IMU orientation: x = back, y = right, z = up
  // Pitch angle (forward/backward tilt)
  angle = event.orientation.x;

  // Simple PID calculation
  float error = targetAngle - angle;
  integral += error * 0.01; // assuming loop ~10ms
  float derivative = (error - lastError) / 0.01;
  lastError = error;

  float pidOutput = Kp * error + Ki * integral + Kd * derivative;

  // Add user command influence (forward/backward)
  float controlSignal = pidOutput + forwardSpeed;

  // Motor speeds
  float leftMotor = constrain(controlSignal - rotationSpeed, -1.0, 1.0);
  float rightMotor = constrain(controlSignal + rotationSpeed, -1.0, 1.0);

  // Apply direction reversal
  if (LEFT_REVERSED) leftMotor = -leftMotor;
  if (RIGHT_REVERSED) rightMotor = -rightMotor;

  // Convert to PWM (0-255) using 20%-100% scaling
  int leftPWM = mapMotorPWM(leftMotor);
  int rightPWM = mapMotorPWM(rightMotor);

  // Set motor direction pins
  digitalWrite(LEFT_DIR_PIN, leftMotor >= 0 ? HIGH : LOW);
  digitalWrite(RIGHT_DIR_PIN, rightMotor >= 0 ? HIGH : LOW);

  // Set PWM output
  ledcWrite(PWM_LEFT_CHANNEL, leftPWM);
  ledcWrite(PWM_RIGHT_CHANNEL, rightPWM);

  delay(10); // ~100 Hz loop
}

int mapMotorPWM(float value) {
  // value expected -1.0 to 1.0
  float pwm = pwmMin + (pwmMax - pwmMin) * abs(value);
  return (int)(pwm * 255.0);
}