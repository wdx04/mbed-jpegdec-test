#include "mbed.h"
#include "EventQueue.h"
#include "JPEGDEC.h"
#include "tulips.h"
JPEGDEC jpegDec;

EventQueue *event_queue = mbed_event_queue();

DigitalOut led(LED1);

int jpegDrawToMat(JPEGDRAW *pDraw)
{
    return 1;
}

void reverse_led()
{
    led = !led;
}

void decode_image()
{
    Timer timer;
    timer.start();
    jpegDec.openRAM((uint8_t*)tulips, sizeof(tulips), &jpegDrawToMat);
    bool decoded = jpegDec.decode(0, 0, 0) == 1;
    jpegDec.close();
    timer.stop();
    if(decoded)
    {
        printf("Jpeg image decoded in %lld us!\n", chrono::duration_cast<chrono::microseconds>(timer.elapsed_time()).count());
    }
    else
    {
        printf("Jpeg image NOT decoded!\n");
    }
}

int main()
{
    sleep_manager_lock_deep_sleep();
    printf("Application Started!\n");
    printf("System Core Clock: %d MHz\n", int(SystemCoreClock / 1000000));
    decode_image();
    event_queue->call_every(1s, &reverse_led);
    event_queue->dispatch_forever();
}
