#include <InterfaceLibrary.h>

#define RED_PWM 11
#define GREEN_PWM 13
#define BLUE_PWM 12

#define LED_PIN_0 14
#define LED_PIN_1 15
#define LED_PIN_2 16
#define LED_PIN_3 17
#define LED_PIN_4 18
#define LED_PIN_5 19
#define LED_PIN_6 20
#define LED_PIN_7 21

#define BUZZER_PIN 10

ILCore core;

ILOscilloscope oscope;
ILOscilloscopeGraph analogIn0;
ILOscilloscopeGraph analogIn1;
ILOscilloscopeGraph analogIn2;
ILOscilloscopeGraph analogIn3;
ILOscilloscopeGraph analogIn4;
ILOscilloscopeGraph analogIn5;

ILInterface RGBLEDUI;
ILInterfaceGroupBox RGBLEDUIGroupBox;
ILInterfaceSlider redSlider;
ILInterfaceSlider greenSlider;
ILInterfaceSlider blueSlider;

ILInterface LEDBUI;
ILInterfaceGroupBox LEDBUIGroupBox;
ILInterfaceCheckBox led0;
ILInterfaceCheckBox led1;
ILInterfaceCheckBox led2;
ILInterfaceCheckBox led3;
ILInterfaceCheckBox led4;
ILInterfaceCheckBox led5;
ILInterfaceCheckBox led6;
ILInterfaceCheckBox led7;

ILInterfaceGroupBox buzzerGroupBox;
ILInterfaceSlider buzzerTone0;
ILInterfaceSlider buzzerTone1;
ILInterfaceSlider buzzerTone2;
ILInterfaceSlider buzzerTone3;
ILInterfaceRadioButton buzzerRB0;
ILInterfaceRadioButton buzzerRB1;

ILOscilloscope OCDemo;
ILOscilloscopeCurve XYPlot1;
ILOscilloscopeCurve XYPlot2;

void setup()
{
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);

    pinMode(9, INPUT);
    pinMode(8, INPUT);

    pinMode(LED_PIN_0, OUTPUT);
    pinMode(LED_PIN_1, OUTPUT);
    pinMode(LED_PIN_2, OUTPUT);
    pinMode(LED_PIN_3, OUTPUT);
    pinMode(LED_PIN_4, OUTPUT);
    pinMode(LED_PIN_5, OUTPUT);
    pinMode(LED_PIN_6, OUTPUT);
    pinMode(LED_PIN_7, OUTPUT);

    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);

    digitalWrite(LED_PIN_0, LOW);
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, LOW);
    digitalWrite(LED_PIN_3, LOW);
    digitalWrite(LED_PIN_4, LOW);
    digitalWrite(LED_PIN_5, LOW);
    digitalWrite(LED_PIN_6, LOW);
    digitalWrite(LED_PIN_7, LOW);

    ///////////////////////////////////////////////////////////////////////////

    core.init();
    // core.clearAll();

    ///////////////////////////////////////////////////////////////////////////

    oscope.initDocked(&core, "Analog In");

    oscope.setBackgroundColor(0xFF444444);
    oscope.setYAxisRangeAutoScale(false);
    oscope.setYAxisRangeLower(0);
    oscope.setYAxisRangeUpper(5);

    oscope.setXAxisLabel("Time");
    oscope.setYAxisLabel("Voltage");

    analogIn0.init(&oscope, "Potentiometer");
    analogIn1.init(&oscope, "Photo Resistor");
    analogIn2.init(&oscope, "Piezo Element");
    analogIn3.init(&oscope, "Flex Sensor");
    analogIn4.init(&oscope, "Soft Potentiometer");
    analogIn5.init(&oscope, "Force Sensitive Resistor");

    analogIn0.setDeltaMode(true);
    analogIn1.setDeltaMode(true);
    analogIn2.setDeltaMode(true);
    analogIn3.setDeltaMode(true);
    analogIn4.setDeltaMode(true);
    analogIn5.setDeltaMode(true);

    analogIn0.setSampleRate(66);
    analogIn1.setSampleRate(66);
    analogIn2.setSampleRate(66);
    analogIn3.setSampleRate(66);
    analogIn4.setSampleRate(66);
    analogIn5.setSampleRate(66);

    analogIn0.setScaler(1023/5);
    analogIn1.setScaler(1023/5);
    analogIn2.setScaler(1023/5);
    analogIn3.setScaler(1023/5);
    analogIn4.setScaler(1023/5);
    analogIn5.setScaler(1023/5);

    ///////////////////////////////////////////////////////////////////////////

    RGBLEDUI.initDocked(&core, "RGB LED Control");
    RGBLEDUIGroupBox.init(&RGBLEDUI, "Pin PWM Sliders");

    redSlider.init(&RGBLEDUIGroupBox, "Red PWM");
    greenSlider.init(&RGBLEDUIGroupBox, "Green PWM");
    blueSlider.init(&RGBLEDUIGroupBox, "Blue PWM");

    redSlider.setMaximum(255);
    greenSlider.setMaximum(255);
    blueSlider.setMaximum(255);

    LEDBUI.initDocked(&core, "LED & Buzzer Control");
    LEDBUIGroupBox.init(&LEDBUI, "LED Control");

    led0.init(&LEDBUIGroupBox, "LED 0");
    led1.init(&LEDBUIGroupBox, "LED 1");
    led2.init(&LEDBUIGroupBox, "LED 2");
    led3.init(&LEDBUIGroupBox, "LED 3");
    led4.init(&LEDBUIGroupBox, "LED 4");
    led5.init(&LEDBUIGroupBox, "LED 5");
    led6.init(&LEDBUIGroupBox, "LED 6");
    led7.init(&LEDBUIGroupBox, "LED 7");

    buzzerGroupBox.init(&LEDBUI, "Buzzer Control");

    buzzerTone0.init(&buzzerGroupBox, "1 Hz");
    buzzerTone1.init(&buzzerGroupBox, "10 Hz");
    buzzerTone2.init(&buzzerGroupBox, "100 Hz");
    buzzerTone3.init(&buzzerGroupBox, "1000 Hz");

    buzzerTone0.setSingleStep(1);
    buzzerTone1.setSingleStep(10);
    buzzerTone2.setSingleStep(100);
    buzzerTone3.setSingleStep(1000);

    buzzerTone0.setPageStep(2);
    buzzerTone1.setPageStep(20);
    buzzerTone2.setPageStep(200);
    buzzerTone3.setPageStep(2000);

    buzzerTone0.setMaximum(10);
    buzzerTone1.setMaximum(100);
    buzzerTone2.setMaximum(1000);
    buzzerTone3.setMaximum(10000);

    buzzerRB0.init(&buzzerGroupBox, "Buzzer Off");
    buzzerRB1.init(&buzzerGroupBox, "Buzzer On");

    buzzerRB0.setChecked(true);
    buzzerRB1.setChecked(false);

    ///////////////////////////////////////////////////////////////////////////

    OCDemo.initDocked(&core, "OC Demo");

    XYPlot1.init(&OCDemo, "");
    XYPlot2.init(&OCDemo, "");

    XYPlot1.setSize(4096);
    XYPlot2.setSize(4096);
}

void loop()
{
    analogReadLoop();
    RGBLEDLoop();
    pinControlLoop();
    demoLoop();
}

void analogReadLoop()
{
    analogIn0.addValue(analogRead(0));
    analogIn1.addValue(analogRead(1));
    analogIn2.addValue(analogRead(2));
    analogIn3.addValue(analogRead(3));
    analogIn4.addValue(analogRead(4));
    analogIn5.addValue(analogRead(5));
}

void RGBLEDLoop()
{
    analogWrite(RED_PWM, redSlider.getValue());
    analogWrite(GREEN_PWM, greenSlider.getValue());
    analogWrite(BLUE_PWM, blueSlider.getValue());
}

void pinControlLoop()
{
    digitalWrite(LED_PIN_0, led0.getChecked());
    digitalWrite(LED_PIN_1, led1.getChecked());
    digitalWrite(LED_PIN_2, led2.getChecked());
    digitalWrite(LED_PIN_3, led3.getChecked());
    digitalWrite(LED_PIN_4, led4.getChecked());
    digitalWrite(LED_PIN_5, led5.getChecked());
    digitalWrite(LED_PIN_6, led6.getChecked());
    digitalWrite(LED_PIN_7, led7.getChecked());

    if(buzzerRB1.getChecked())
    {
        tone(BUZZER_PIN, buzzerTone0.getValue() +
                         buzzerTone1.getValue() +
                         buzzerTone2.getValue() +
                         buzzerTone3.getValue());
    }
    else
    {
        noTone(BUZZER_PIN);
    }
}

void demoLoop()
{
    static enum
    {
        BUTTERFLY,
        EPICYCLOID,
        FERMATS
    }
    e = BUTTERFLY;

    switch(e)
    {
        case BUTTERFLY:
        {
            if(runButterflyLoop())
            {
                e = EPICYCLOID;
            }

            break;
        }

        case EPICYCLOID:
        {
            if(runEpicycloidLoop())
            {
                e = FERMATS;
            }

            break;
        }

        case FERMATS:
        {
            if(runFermatsSprialLoop())
            {
                e = BUTTERFLY;
            }

            break;
        }
    }
}

bool runButterflyLoop()
{
    static unsigned int i = 0;

    static enum
    {
        INIT,
        LOOP,
        PAUSE
    }
    e = INIT;

    switch(e)
    {
        case INIT:
        {
            XYPlot1.removeData();
            XYPlot2.removeData();

            XYPlot1.setName("Butterfly");
            XYPlot2.setName("");

            XYPlot1.setLineColor(0xFFFF00FF);
            XYPlot1.setLineStyle(LS_SOLID_LINE);
            XYPlot1.setFillColor(0x7FFFC8FF);
            XYPlot1.setFillStyle(FS_SOLID_PATTERN);

            i = 0;

            e = LOOP;

            return false;
        }

        case LOOP:
        {
            XYPlot1.addKeyValueF(
            sin(radians(i))*(exp(cos(radians(i)))-
            (2*cos(radians(4*i)))-pow(sin(radians(i/12.0)),5)),
            cos(radians(i))*(exp(cos(radians(i)))-
            (2*cos(radians(4*i)))-pow(sin(radians(i/12.0)),5)));

            i += 1; if(i == 4096) { i = 0; e = PAUSE; }

            return false;
        }

        case PAUSE:
        {
            i += 1; if(i == 64) { i = 0; e = INIT; return true; } return false;
        }
    }
}

const float epicycloid_k = 2.1;
const float epicycloid_r = 3.0;

bool runEpicycloidLoop()
{
    static unsigned int i = 0;

    static enum
    {
        INIT,
        LOOP,
        PAUSE
    }
    e = INIT;

    switch(e)
    {
        case INIT:
        {
            XYPlot1.removeData();
            XYPlot2.removeData();

            XYPlot1.setName("Epicycloid");
            XYPlot2.setName("");

            XYPlot1.setLineColor(0xFF00FFFF);
            XYPlot1.setLineStyle(LS_SOLID_LINE);
            XYPlot1.setFillColor(0x7FC8FFFF);
            XYPlot1.setFillStyle(FS_SOLID_PATTERN);

            i = 0; e = LOOP; return false;
        }

        case LOOP:
        {
            XYPlot1.addKeyValueF(
            (epicycloid_r*(epicycloid_k+1)*cos(radians(i)))-
            (epicycloid_r*cos(radians((epicycloid_k+1)*i))),
            (epicycloid_r*(epicycloid_k+1)*sin(radians(i)))-
            (epicycloid_r*sin(radians((epicycloid_k+1)*i))));

            i += 1; if(i == 4096) { i = 0; e = PAUSE; } return false;
        }

        case PAUSE:
        {
            i += 1; if(i == 64) { i = 0; e = INIT; return true; } return false;
        }
    }
}

bool runFermatsSprialLoop()
{
    static unsigned int i = 0;

    static enum
    {
        INIT,
        LOOP,
        PAUSE
    }
    e = INIT;

    switch(e)
    {
        case INIT:
        {
            XYPlot1.removeData();
            XYPlot2.removeData();

            XYPlot1.setName("Fermat's Spiral 1");
            XYPlot2.setName("Fermat's Spiral 2");

            XYPlot1.setLineColor(0xFF0000FF);
            XYPlot1.setLineStyle(LS_SOLID_LINE);
            XYPlot1.setFillColor(0x7FC8C8FF);
            XYPlot1.setFillStyle(FS_SOLID_PATTERN);

            XYPlot2.setLineColor(0xFFFF0000);
            XYPlot2.setLineStyle(LS_SOLID_LINE);
            XYPlot2.setFillColor(0x7FFFC8C8);
            XYPlot2.setFillStyle(FS_SOLID_PATTERN);

            i = 0; e = LOOP; return false;
        }

        case LOOP:
        {
            XYPlot1.addKeyValueF(
            sqrt(i)*cos(radians(i))*abs(5),
            sqrt(i)*sin(radians(i))*abs(5));

            XYPlot2.addKeyValueF(
            -sqrt(i)*cos(radians(i))*abs(5),
            -sqrt(i)*sin(radians(i))*abs(5));

            i += 1; if(i == 4096) { i = 0; e = PAUSE; } return false;
        }

        case PAUSE:
        {
            i += 1; if(i == 64) { i = 0; e = INIT; return true; } return false;
        }
    }
}
