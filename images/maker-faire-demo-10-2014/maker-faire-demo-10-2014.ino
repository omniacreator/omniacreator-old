/**
* @file maker-faire-demo-10-2014.ino
* Atlanta Maker Faire Demo
*
* @version @n 1.0
* @date @n Mon Oct 2014
*
* @author @n Kwabena W. Agyeman
*/

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

#define BUTTON_0 9
#define BUTTON_1 8

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
ILInterfaceSeperator seperator0;
ILInterfaceRadioButton buzzerRB0;
ILInterfaceRadioButton buzzerRB1;
ILInterfaceSeperator seperator1;

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

    oscope.setFFTYAxisRangeAutoScale(false);
    oscope.setFFTYAxisRangeLower(0);
    oscope.setFFTYAxisRangeUpper(1);

    oscope.setXAxisLabel("\u0394 Time (s)");
    oscope.setYAxisLabel("Voltage (v)");

    oscope.setFFTXAxisLabel("Frequency (hz)");
    oscope.setFFTYAxisLabel("Voltage (v)");

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

    analogIn0.setSampleRate(50);
    analogIn1.setSampleRate(50);
    analogIn2.setSampleRate(50);
    analogIn3.setSampleRate(50);
    analogIn4.setSampleRate(50);
    analogIn5.setSampleRate(50);

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

    LEDBUI.initDocked(&core, "LED and Buzzer Control");
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

    seperator0.init(&buzzerGroupBox);
    buzzerRB0.init(&buzzerGroupBox, "Buzzer Off");
    buzzerRB1.init(&buzzerGroupBox, "Buzzer On");
    seperator1.init(&buzzerGroupBox);

    buzzerRB0.setChecked(true);
    buzzerRB1.setChecked(false);

    ///////////////////////////////////////////////////////////////////////////

    OCDemo.initDocked(&core, "OC Demo");

    XYPlot1.init(&OCDemo, "");
    XYPlot2.init(&OCDemo, "");

    XYPlot1.setSize(4096);
    XYPlot2.setSize(4096);
}

bool button0State = false;
bool button0State2 = false;
bool button1State = false;
bool button1State2 = false;

void loop()
{
    if(digitalRead(BUTTON_0) != button0State)
    {
        button0State = !button0State;

        if(button0State)
        {
            button0State2 = !button0State2;
        }

        analogIn0.setFFT(button0State2 ? GFFT_MAGNITUDE : GFFT_NONE);
        analogIn1.setFFT(button0State2 ? GFFT_MAGNITUDE : GFFT_NONE);
        analogIn2.setFFT(button0State2 ? GFFT_MAGNITUDE : GFFT_NONE);
        analogIn3.setFFT(button0State2 ? GFFT_MAGNITUDE : GFFT_NONE);
        analogIn4.setFFT(button0State2 ? GFFT_MAGNITUDE : GFFT_NONE);
        analogIn5.setFFT(button0State2 ? GFFT_MAGNITUDE : GFFT_NONE);
    }

    if(digitalRead(BUTTON_1) != button1State)
    {
        button1State = !button1State;

        if(button1State)
        {
            button1State2 = !button1State2;
        }
    }

    analogReadLoop();
    RGBLEDLoop();
    pinControlLoop();
    demoLoop();
}

void analogReadLoop()
{
    static unsigned int x0 = 0;
    static unsigned int x1 = 0;
    static unsigned int x2 = 0;

    if(!button1State2)
    {
        analogIn0.addValue(analogRead(0));
        analogIn1.addValue(analogRead(1));
        analogIn2.addValue(analogRead(2));
        analogIn3.addValue(analogRead(3));
        analogIn4.addValue(analogRead(4));
        analogIn5.addValue(analogRead(5));
    }
    else
    {
        float y0 = cos(radians(x0)); x0 += redSlider.getValue();
        float y1 = cos(radians(x1)); x1 += greenSlider.getValue();
        float y2 = cos(radians(x2)); x2 += blueSlider.getValue();

        analogIn0.addValue(analogRead(0) * y0 * y1 * y2);
        analogIn1.addValue(analogRead(1) * y0 * y1 * y2);
        analogIn2.addValue(analogRead(2) * y0 * y1 * y2);
        analogIn3.addValue(analogRead(3) * y0 * y1 * y2);
        analogIn4.addValue(analogRead(4) * y0 * y1 * y2);
        analogIn5.addValue(analogRead(5) * y0 * y1 * y2);
    }
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
        LISSAJOUS,
        EPICYCLOID,
        FERMATS,
        NCURVE,
        CIRCLE
    }
    e = BUTTERFLY;

    switch(e)
    {
        case BUTTERFLY:
        {
            if(runButterflyLoop())
            {
                e = LISSAJOUS;
            }

            break;
        }

        case LISSAJOUS:
        {
            if(runLissajousLoop())
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
                e = NCURVE;
            }

            break;
        }

        case NCURVE:
        {
            if(runNCurveLoop())
            {
                e = CIRCLE;
            }

            break;
        }

        case CIRCLE:
        {
            if(runParametricCircleLoop())
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

            XYPlot1.setLineColor(0xFF7F007F);
            XYPlot1.setLineStyle(LS_SOLID_LINE);
            XYPlot1.setFillColor(0x7F7F007F);
            XYPlot1.setFillStyle(FS_SOLID_PATTERN);

            i = 0; e = LOOP; return false;
        }

        case LOOP:
        {
            XYPlot1.addKeyValueF(
            sin(radians(i))*(exp(cos(radians(i)))-
            (2*cos(radians(4*i)))-pow(sin(radians(i/12.0)),5)),
            cos(radians(i))*(exp(cos(radians(i)))-
            (2*cos(radians(4*i)))-pow(sin(radians(i/12.0)),5)));

            i += 1; if(i == 4096) { i = 0; e = PAUSE; } return false;
        }

        case PAUSE:
        {
            i += 1; if(i == 64) { i = 0; e = INIT; return true; } return false;
        }
    }
}

bool runLissajousLoop()
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

            XYPlot1.setName("Lissajous Curve 1");
            XYPlot2.setName("Lissajous Curve 2");

            XYPlot1.setLineColor(0xFFFF7F00);
            XYPlot1.setLineStyle(LS_SOLID_LINE);
            XYPlot1.setFillColor(0x7FFF7FC8);
            XYPlot1.setFillStyle(FS_SOLID_PATTERN);

            XYPlot2.setLineColor(0xFFFFFF00);
            XYPlot2.setLineStyle(LS_SOLID_LINE);
            XYPlot2.setFillColor(0x7FFFFFC8);
            XYPlot2.setFillStyle(FS_SOLID_PATTERN);

            i = 0; e = LOOP; return false;
        }

        case LOOP:
        {
            XYPlot1.addKeyValueF(
            sin(radians(5*i)),
            sin(radians(6*i)));

            XYPlot2.addKeyValueF(
            sin(radians(6*i)),
            sin(radians(5*i)));

            i += 1; if(i == 512) { i = 0; e = PAUSE; } return false;
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

            XYPlot1.setLineColor(0xFF007F7F);
            XYPlot1.setLineStyle(LS_SOLID_LINE);
            XYPlot1.setFillColor(0x7F007F7F);
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
            sqrt(i)*cos(radians(i))*abs(1),
            sqrt(i)*sin(radians(i))*abs(1));

            XYPlot2.addKeyValueF(
            -sqrt(i)*cos(radians(i))*abs(1),
            -sqrt(i)*sin(radians(i))*abs(1));

            i += 1; if(i == 4096) { i = 0; e = PAUSE; } return false;
        }

        case PAUSE:
        {
            i += 1; if(i == 64) { i = 0; e = INIT; return true; } return false;
        }
    }
}

bool runNCurveLoop()
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

            XYPlot1.setName("N-Curve");
            XYPlot2.setName("");

            XYPlot1.setLineColor(0xFF007F00);
            XYPlot1.setLineStyle(LS_SOLID_LINE);
            XYPlot1.setFillColor(0x7F007F00);
            XYPlot1.setFillStyle(FS_SOLID_PATTERN);

            i = 0; e = LOOP; return false;
        }

        case LOOP:
        {
            XYPlot1.addKeyValueF(
            (2*PI)*((i/4096.0) - 1 + (cos(76*PI*(i/4096.0))*
                                      cos(38*PI*(i/4096.0)))),
            cos(2*PI*(i/4096.0)) + ((2*PI)*cos(76*PI*(i/4096.0))*
                                           sin(38*PI*(i/4096.0))));

            i += 1; if(i == 4096) { i = 0; e = PAUSE; } return false;
        }

        case PAUSE:
        {
            i += 1; if(i == 64) { i = 0; e = INIT; return true; } return false;
        }
    }
}

bool runParametricCircleLoop()
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

            XYPlot1.setName("Left Circle");
            XYPlot2.setName("Right Circle");

            XYPlot1.setLineColor(0xFFFFA500);
            XYPlot1.setLineStyle(LS_SOLID_LINE);
            XYPlot1.setFillColor(0x00000000);
            XYPlot1.setFillStyle(FS_NO_BRUSH);

            XYPlot2.setLineColor(0xFFFFA500);
            XYPlot2.setLineStyle(LS_SOLID_LINE);
            XYPlot2.setFillColor(0x00000000);
            XYPlot2.setFillStyle(FS_NO_BRUSH);

            i = 0; e = LOOP; return false;
        }

        case LOOP:
        {
            XYPlot1.addKeyValueF(
            (3 * sin(i) * cos(i)) - 1.5,
            (3 * cos(i) * cos(i)));

            XYPlot2.addKeyValueF(
            (3 * sin(i) * cos(i)) + 1.5,
            (3 * cos(i) * cos(i)));

            i += 1; if(i == 512) { i = 0; e = PAUSE; } return false;
        }

        case PAUSE:
        {
            i += 1; if(i == 64) { i = 0; e = INIT; return true; } return false;
        }
    }
}
