#include <stdio.h>

#include <sysapp/launch.h>
#include <vpad/input.h>
#include <whb/proc.h>


int
main(void)
{
    printf("Hello world!\n");
    printf("Press any button to quit.\n");

    WHBProcInit();
    while (WHBProcIsRunning()) {
        VPADStatus vpad;
        int r = VPADRead(VPAD_CHAN_0, &vpad, 1, nullptr);
        if (r == 1)
            if (vpad.trigger) {
                printf("Button press detected!\n");
                SYSLaunchMenu();
            }
    }
    WHBProcShutdown();
}
