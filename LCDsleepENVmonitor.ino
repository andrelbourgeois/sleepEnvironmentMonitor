#include <LiquidCrystal.h>

#define lightPin A2 //set analog pin to recieve light level value
#define tempPin A0 // set analog pin to recieve temperature value#define Vcc 5.0 // board voltage
#define switchPin 9 // set analog pin to recieve button press info

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // declare pins LCD will use

int tempInput; // declare temperature input integer variable
int lightInput; // declare light input integer variable
float temp; // declare temperature as a float variable
float light; // declare light level as a float variable
float tempAvg; // declare a float variable for the average temeperature
float lightAvg; // declare a float variable for average light
float tempSum = 0; // declare variable to capture a summed total of temp readings
float lightSum = 0; // declare variable to capture a summed total of light readings
float tempImpact; // declare a variable to hold the impact of temperature on sleep quality
float lightImpact; // declare a variable to hold the impact of temperature on sleep quality
float voltage; // declare a float variable to store voltage
float Vcc = 5; // board voltage
int switchState = LOW; // declare int value for the switch state (0=LOW, 1=HIGH)
float sleepQuality; // declare a variable for sleep quality
int readingCount = 0; // declare a counter variable to remember how many readings
// have been completed

void setup()
{
  Serial.begin(9600); // start serial connection

  pinMode(switchPin, INPUT);

  lcd.begin(16, 2); // start LCD screen
  lcd.print("How did");
  lcd.setCursor(0,1); // write an opening message to the LCD
  lcd.print("you sleep?");
  delay(5000);
}

void loop()
{

  switchState = digitalRead(switchPin); // check switchPin

  while (switchState == LOW)
  {
    tempInput = analogRead(tempPin);
    voltage = tempInput * Vcc; // multiply by board voltage
    voltage /= 1024; // divide by 1024 to get volts
    Serial.print(voltage);
    Serial.println(" volts");
    // print voltage in serial monitor for debugging
    temp = (voltage - 0.5) * 100; // subtract offset and multiply by
    // 100 to convert voltage to degrees celsius
    Serial.print(temp);
    Serial.println(" degrees celsius");
    // print temp in serial monitor for debugging
    tempSum += temp; // add current temp reading to the temp sum

    lightInput = analogRead(lightPin);
    // lower light level = less resistance & higher value
    light = map(round(lightInput), 0, 1023, 1000, 0);
    // map the analog value to lux - provides a rough estimate of light levels
    Serial.print(lightInput);
    Serial.println(" lightInput");
    // print to serial monitor for debugging
    Serial.print(light);
    Serial.println(" lux");
    // print to serial monitor for debugging
    lightSum += light; // add current light reading to the light sum

    lcd.clear(); // clears the LCD screen
    lcd.print("Current Temp");
    lcd.setCursor(0,1);
    lcd.print(temp);
    lcd.print("C");
    delay(2000);

    lcd.clear();
    lcd.print("Current Light");
    lcd.setCursor(0,1);
    lcd.print(light);
    lcd.print("Lx");
    delay(2000);

    readingCount += 1; // add 1 to readingCount after each complete reading
    switchState = digitalRead(switchPin); // check switchPin
  }

// average value loop
  while (switchState == HIGH)
  {
    tempInput = analogRead(tempPin);
    voltage = tempInput * Vcc; // multiply by board voltage
    voltage /= 1024; // divide by 1024 to get volts
    Serial.print(voltage);
    Serial.println(" volts");
    // print voltage in serial monitor for debugging
    temp = (voltage - 0.5) * 100; // subtract offset and multiply by
    tempAvg = tempSum/readingCount;
    // 100 to convert voltage to degrees celsius
    Serial.print(tempAvg);
    Serial.println(" tempAvg");
    // print temp in serial monitor for debugging
    tempSum += temp; // add current temp reading to the temp sum

    lightInput = analogRead(lightPin);
    // lower light level = less resistance & higher value
    light = map(round(lightInput), 0, 1023, 1000, 0);
    // map the analog value to lux - provides a rough estimate of light levels
    lightAvg = lightSum/readingCount;
    // print to serial monitor for debugging
    Serial.print(lightAvg);
    Serial.println(" lightAvg");
    // print to serial monitor for debugging
    lightSum += light; // add current light reading to the light sum

    /*
    the chunk of code used to get temperature and light would be more efficient
    as a function call, instead of rewriting it in both instances
    */
    tempImpact = map(round(tempAvg), 18, 40, 5, 0);
    lightImpact = map(round(lightAvg), 0, 1000, 5, 0);

    sleepQuality = tempImpact + lightImpact; // declare a variable for sleep quality

    /*
    Serial.print(tempImpact);
    Serial.println(" tempImpact");
    Serial.print(lightImpact);
    Serial.println(" lightImpact");
    Serial.print(sleepQuality);
    Serial.println(" sleepQuality");
    */

    lcd.clear(); // clears the LCD screen

    lcd.print("Average Temp");
    lcd.setCursor(0,1);
    lcd.print(tempAvg);
    lcd.print("C");
    delay(2000);

    lcd.clear();
    lcd.print("Average Light");
    lcd.setCursor(0,1);
    lcd.print(lightAvg);
    lcd.print("Lx");
    delay(2000);

    lcd.clear();

    /*
    SLEEP QUALITY SCALE
    0 - 1.99 = Very Bad
    2 - 3.99 = Bad
    4 - 5.99 = Satisfactory
    6 - 7.99 = Good
    8 - 10 = Great!


    lcd.print("SLEEP NUM ");
    lcd.setCursor(0,1);
    lcd.print(sleepQuality);
    delay(2000);

    lcd.clear();
    */

    if (sleepQuality < 2) // sleep quality is VERY BAD!
    {
      lcd.print("Sleep Quality");
      lcd.setCursor(0,1);
      lcd.print("VERY BAD");
      delay(2000);
    }

    else if (sleepQuality >= 2 && sleepQuality < 4) // sleep quality is BAD!
    {
      lcd.print("Sleep Quality");
      lcd.setCursor(0,1);
      lcd.print("BAD");
      delay(2000);
    }

    else if (sleepQuality >= 4 && sleepQuality < 5.99) // sleep quality was OKAY!
    {
      lcd.print("Sleep Quality");
      lcd.setCursor(0,1);
      lcd.print("OKAY");
      delay(2000);
    }

    else if (sleepQuality >= 6 && sleepQuality < 7.99) // sleep quality was GOOD!
    {
      lcd.print("Sleep Quality");
      lcd.setCursor(0,1);
      lcd.print("GOOD");
      delay(2000);
    }

    else if (sleepQuality >= 8) // sleep quality was GREAT!
    {
      lcd.print("Sleep Quality");
      lcd.setCursor(0,1);
      lcd.print("GREAT");
      delay(2000);
    }

    readingCount += 1; // add 1 to readingCount after each complete reading
    switchState = digitalRead(switchPin); // check switchPin
  }

}
