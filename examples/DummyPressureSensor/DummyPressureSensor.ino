/**
 * @brief  This example demonstrates the basic usage of this library by creating a fake (dummy) pressure sensor.
 * @author Alexander Entinger, MSc / LXRobotics GmbH
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <ArduinoSensor.hpp>

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class DummyPressureSensor : public drone::PressureSensorBase
{

public:

  DummyPressureSensor()
  : drone::PressureSensorBase("BMP388",
                              0.0    * drone::unit::pascal,
                              1000.0 * drone::unit::pascal,
                              1.0    * drone::unit::pascal,
                              25.0   * drone::unit::hertz,
                              [](drone::unit::Pressure const pressure)
                              {
                                Serial.print("[ASYNC] p = ");
                                Serial.print(pressure.value());
                                Serial.println(" Pascal");
                              })
  { }
  virtual ~DummyPressureSensor() { }


  virtual drone::unit::Pressure get() const override { return drone::unit::Pressure(1023.0 * drone::unit::pascal); }

  void onExternalEvent()
  {
    /* Retrieve value from sensor. */
    drone::unit::Pressure const latest_sensor_val = drone::unit::Pressure(65.8 * drone::unit::pascal);
    /* Invoke callback function. */
    onSensorValueUpdate(latest_sensor_val);
  }
};

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

DummyPressureSensor pressure_sensor;

/**************************************************************************************
 * SETUP/LOOP
 **************************************************************************************/

void setup()
{
  Serial.begin(9600);
  while (!Serial) { }

  Serial.println(pressure_sensor);

  Serial.print("[SYNC] p = ");
  Serial.print(pressure_sensor.get().value());
  Serial.println(" Pascal");
  Serial.println();

  pressure_sensor.onExternalEvent();
}

void loop()
{

}
